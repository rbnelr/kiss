import srcgen
from collections import namedtuple
from itertools import chain

class type_:
	def __init__(self):
		self.name = None
		self.scalar_type = None
		self.size = None
		self.bool_type = None
		self.int_cast_type = None
		self.float_cast_type = None
	def __repr__(self): return f'type_<{self.name}>'
	def __str__(self): return self.name

_types = {}
def get_type(scalar_type, size=1):
	if not scalar_type: return None

	if not isinstance(scalar_type, type_) and size != 1:
		scalar_type = _types[(str(scalar_type), 1)]

	id = str(scalar_type), size
	if id in _types:
		return _types[id]

	f2i = {
			'f32':	's32',	'f64':	's64',
			's8':	's8',	's32':	's32',	's64':	's64',
			'u8':	'u8',	'u32':	'u32',	'u64':	'u64',
			'bool': None,
		}
	i2f = {
			'f32':	'f32',	'f64':	'f64',
			's8':	'f32',	's32':	'f32',	's64':	'f64',
			'u8':	'f32',	'u32':	'f32',	'u64':	'f64',
			'bool': None,
		}

	if size == 1:
		name = str(scalar_type)
	elif not isinstance(size, tuple):
		prefix = {
				'f32':	'f',	'f64':	'd',
				'bool':	'b',
				's32':	'i',	's64':	's64',	'u8':	'u8',
			}
		name = f'{prefix[str(scalar_type)]}v{size}'
	else:
		if not scalar_type in floats:
			return None # only float matricies matricies

		prefix = {
				'f32':	'f',	'f64':	'd',
			}
		name = f'{prefix[str(scalar_type)]}m' + (f'{size[0]}' if size[0] == size[1] else f'{size[0]}x{size[1]}')
		
	t = type_()
	_types[id] = t

	t.name = name
	t.size = size
	t.scalar_type		= get_type(scalar_type, 1)
	t.bool_type			= get_type('bool', size)
	t.int_cast_type		= get_type(f2i[str(scalar_type)], size)
	t.float_cast_type	= get_type(i2f[str(scalar_type)], size)

	return t

floats =	[get_type(t) for t in ['f32', 'f64']]
ints =		[get_type(t) for t in ['s32', 's64', 's8']]
uints =		[get_type(t) for t in ['u32', 'u64', 'u8']]

scalars = floats + ints + uints

float_const = {'f32':'', 'f64':'d'} # postfix of Math constants


vec_sizes = [2,3,4]

vectors = [
	[get_type('bool',	s) for s in vec_sizes],

	[get_type('f32',	s) for s in vec_sizes],
	[get_type('f64',	s) for s in vec_sizes],
	[get_type('s32',	s) for s in vec_sizes],
	[get_type('s64',	s) for s in vec_sizes],
	[get_type('u8',		s) for s in vec_sizes],
]
all_vectors = list(chain.from_iterable(vectors))

mat_sizes = [(2,2), (3,3), (4,4), (2,3), (3,4)]


matricies = [
	[ get_type('f32', s) for s in mat_sizes ],
	[ get_type('f64', s) for s in mat_sizes ],
]
all_matricies = list(chain.from_iterable(matricies))


use_contexpr_where_possible = False
all_inline = False

def _function(file, ret, name, args, body, clsname=None, init_list=None, template=None, comment=None, const=False, static=False, explicit=False, constexpr='auto', inline='auto'):
	body = body.strip()
	comment = ''.join(f'// '+ l.strip() +'\n' for l in comment.splitlines()) if comment else ''

	# automaticly try to detect constexpr-ness by looking at the numer of lines in code body and function name blacklist (blacklisted functions call non-constexpr funcs like std lib sqrt())
	# this is what the c++ standard should have make the compiler do, instead of introducing another keyword that makes everyones live harder 
	non_constexpr_funcs = ['abs', 'sqrt', 'length', 'distance', 'normalize', 'normalize_or_zero', 'floor', 'floori', 'ceil', 'ceili', 'round', 'roundi', 'pow', 'wrap', 'min', 'max', 'clamp', 'bezier']
	if constexpr == 'auto':
		constexpr = use_contexpr_where_possible and (init_list or body.count(';') == 1) and name not in non_constexpr_funcs
	if inline == 'auto':
		inline = all_inline

	clsname = f'{clsname}::' if clsname else ''
	init_list = f': {init_list}' if init_list else ''

	const = ' const' if const else ''

	static = 'static' if static else None
	constexpr = 'constexpr' if constexpr else None
	inline = 'inline' if inline else None
	explicit = 'explicit' if explicit else ''

	template = 'template<%s>\n' % template.replace('tn', 'typename') if template else ''

	def spaced_join(*args):
		s = ''
		for a in args:
			if a:
				if s: s += ' '
				s += a
		return s

	def body_(decl, comment=''):
		nonlocal args

		if file == 'source' and '=' in args:
			import re
			args = re.sub(r'=.*?(?=(?:,|$))', '', args)

		return f'''\n{comment}{decl} ({args}){const}{init_list} {{
			{body}
		}}\n'''

	if file == 'header':
		if inline or template:
			decl = template + spaced_join(static, inline, constexpr, explicit, ret, name)
			return body_(decl, comment)
		else:
			decl = spaced_join(static, constexpr, explicit, ret, name)
			return f'{comment}{decl} ({args}){const};\n'
	elif file == 'source':
		if inline or template:
			return ''
		else:
			decl = spaced_join(constexpr, ret, clsname + name)
			return body_(decl)
		
	else:
		raise ValueError(f"Wrong file type '{file}'")

def function(file, ret, name, args, body,										constexpr='auto', template=None, comment=None):
	return _function(file, ret, name, args, body,											constexpr=constexpr, template=template, comment=comment)
def method(file, clsname, ret, name, args, body,								constexpr='auto', template=None, comment=None, const=False):
	return _function(file, ret, name, args, body, clsname=clsname,							constexpr=constexpr, template=template, comment=comment, const=const)
def static_method(file, clsname, ret, name, args, body,							constexpr='auto', template=None, comment=None, const=False):
	return _function(file, ret, name, args, body, clsname=clsname,							constexpr=constexpr, template=template, comment=comment, const=const, static=True)
def constructor(file, clsname, args, body='', init_list=None, explicit=False,	constexpr='auto', template=None, comment=None):
	return _function(file, '', clsname, args, body, clsname=clsname, init_list=init_list,	explicit=explicit,	constexpr=constexpr, template=template, comment=comment)

def util(f):
	if f == 'header':
		return '''
		#define STRINGIFY(x) #x
		#define TO_STRING(x) STRINGIFY(x)

		#define CONCAT(a,b) a##b

		#define STATIC_ASSERT(cond) static_assert((cond), STRINGIFY(cond))

		#define ARRLEN(arr) (sizeof(arr) / sizeof(arr[0]))

		#define EVEN(i)			(((i) % 2) == 0)
		#define ODD(i)			(((i) % 2) == 1)

		#define BOOL_XOR(a, b)	(((a) != 0) != ((b) != 0))
		'''.strip()
	else:
		return ''

srcgen.generate('util', util)

def types(f):
	if f == 'header':
		return \
	''' #include "stdint.h"
		namespace vector {
			typedef signed char			schar;
			typedef unsigned char		uchar;
			typedef short				sshort;
			typedef unsigned short		ushort;
			typedef int					sint;
			typedef unsigned int		uint;
			typedef long				slong;
			typedef unsigned long		ulong;
			typedef long long			sllong;
			typedef unsigned long long	ullong;

			typedef int8_t				s8;
			typedef uint8_t				u8;
			typedef int16_t				s16;
			typedef uint16_t			u16;
			typedef int32_t				s32;
			typedef uint32_t			u32;
			typedef int64_t				s64;
			typedef uint64_t			u64;

			typedef u8					byte;

			typedef s64					sptr;
			typedef u64					uptr;

			static_assert(sizeof(sptr) == sizeof(byte*), "sizeof(sptr) != sizeof(byte*)");
			static_assert(sizeof(uptr) == sizeof(byte*), "sizeof(uptr) != sizeof(byte*)");

			typedef float				f32;
			typedef double				f64;

			typedef char const*			cstr;
			typedef char				utf8;
			typedef char32_t			utf32;
		}
		'''.strip()
	else:
		return ''

srcgen.generate('types', types)

def kissmath(f):
	src = ''

	if f == 'header':
		src += \
		''' #include "types.hpp"
			#include "util.hpp"
			#include <cmath>
			
			// windows.h defines min and max by default
			#undef min
			#undef max
			
			// Math constants
			#if _MSC_VER && !__INTELRZ_COMPILER && !__clan_
				#include <limits>
				#define F32_INF							((float)(1e+300 * 1e+300))
				#define F64_INF							(1e+300 * 1e+300)
				#define F32_QNAN						std::numeric_limits<float>::quiet_NaN()
				#define F64_QNAN						std::numeric_limits<double>::quiet_NaN()
			#elif __GNUC__ || __clan_
				#define F32_INF							(__builtin_inff())
				#define F64_INF							(__builtin_inf())
				#define F32_QNAN						((float)__builtin_nan("0"))
				#define F64_QNAN						(__builtin_nan("0"))
			#endif
		'''

	src += 'namespace vector {\n'
			
	if f == 'header':
		src += \
		''' // Use std math functions for these
			using std::abs;
			using std::sin;
			using std::cos;
			using std::floor;
			using std::ceil;
			using std::pow;
			using std::round;

			constexpr f64 INFd			= F64_INF;
			constexpr f32 INF			= F32_INF;
			constexpr f64 QNANd			= F64_QNAN;
			constexpr f32 QNAN			= F32_QNAN;
			constexpr f64 PId			= 3.1415926535897932384626433832795;
			constexpr f32 PI			= 3.1415926535897932384626433832795f;
			constexpr f64 TAUd			= 6.283185307179586476925286766559;
			constexpr f32 TAU			= 6.283185307179586476925286766559f;
			constexpr f64 SQRT_2d		= 1.4142135623730950488016887242097;
			constexpr f32 SQRT_2		= 1.4142135623730950488016887242097f;
			constexpr f64 EULERd		= 2.7182818284590452353602874713527;
			constexpr f32 EULER			= 2.7182818284590452353602874713527f;
			constexpr f64 DEG_TO_RADd	= 0.01745329251994329576923690768489;	// 180/PI
			constexpr f32 DEG_TO_RAD	= 0.01745329251994329576923690768489f;
			constexpr f64 RAD_TO_DEGd	= 57.295779513082320876798154814105;	// PI/180
			constexpr f32 RAD_TO_DEG	= 57.295779513082320876798154814105f;
		'''
	
	src += '\n////// Scalar math ///////\n'

	for T in scalars:
		src += f'\n//// {T}\n\n'
		
		src += scalar_math(T, f)
		src += generic_math(T, f)
		
	src += f'\n//// templated math\n\n'

	src += function(f, template='tn T', ret='T', name='smoothstep',	args='T x', body='''
		T t = clamp(x);
		return t * t * (T(3) - T(2) * t);
	''')

	for ST in floats:
		src += function(f, template='tn T', ret='T', name='bezier', args=f'T a, T b, T c, {ST} t', body='''
			T d = lerp(a, b, t);
			T e = lerp(b, c, t);
			T f = lerp(d, e, t);
			return f;
		''')
		src += function(f, template='tn T', ret=f'{T}', name='bezier', args=f'T a, T b, T c, T d, {ST} t', body='''
			return bezier(
							lerp(a, b, t),
							lerp(b, c, t),
							lerp(c, d, t),
							t
						);
		''')
		src += function(f, template='tn T', ret=f'{T}', name='bezier', args=f'T a, T b, T c, T d, T e, {ST} t', body='''
			return bezier(
							lerp(a, b, t),
							lerp(b, c, t),
							lerp(c, d, t),
							lerp(d, e, t),
							t
						);
		''')


	src += '} // namespace vector\n'
	return src

def scalar_math(T, f):
	src = ''

	BT = T.bool_type
	IT = T.int_cast_type # int scalar for roundi funcs
	
	src += function(f, f'{T}', 'wrap', f'{T} x, {T} range', f'''
		{T} modded = '''+ ('std::fmod(x, range)' if T in floats else 'x % range') +''';
		if (range > 0) {
			if (modded < 0) modded += range;
		} else {
			if (modded > 0) modded += range;
		}
		return modded;
	''', comment='wrap x into range [0,range), negative x wrap back to +range unlike c++ % operator, negative range supported')

	src += function(f, f'{T}', 'wrap', f'{T} x, {T} a, {T} b', f'''
		x -= a;
		{T} range = b -a;
			
		{T} modulo = wrap(x, range);
			
		return modulo + a;
	''', comment='wrap x into [a,b) range')
		
	if T in floats:
		src += function(f, f'{T}', 'wrap', f'{T} x, {T} a, {T} b, {IT}* quotient', f'''
			x -= a;
			{T} range = b -a;
			
			{T} modulo = wrap(x, range);
			*quotient = floori(x / range);
			
			return modulo + a;
		''')
		src += '\n'
			
		src += function(f, f'{IT}', 'floori',	f'{T} x', f'return ({IT})floor(x);')
		src += function(f, f'{IT}', 'ceili',	f'{T} x', f'return ({IT})ceil(x);')
		src += function(f, f'{IT}', 'roundi',	f'{T} x', f'return '+ {'f32':'std::lround(x)', 'f64':'std::llround(x)'}[str(T)] +';')
			
		src += '\n'

	min_func = 'std::fmin(l,r)' if T in floats else f'l <= r ? l : r'
	max_func = 'std::fmax(l,r)' if T in floats else f'l >= r ? l : r'
		
	src += function(f, f'{T}', 'min',		f'{T} l, {T} r',			f'return {min_func};')
	src += function(f, f'{T}', 'max',		f'{T} l, {T} r',			f'return {max_func};')
	src += function(f, f'{T}', 'clamp',		f'{T} x, {T} a=0, {T} b=1',	f'return min(max(x,a), b);')
	src += function(f, f'{T}', 'select',	f'{BT} c, {T} l, {T} r',	f'return c ? l : r;', comment='equivalent to ternary c ? l : r, for conformity with vectors')

	src += '\n'

	abs_func = f'std::fabs(x)' if T in floats else f'std::abs(x)'
		
	if T not in uints: # no abs for unsigned types
		src += function(f, f'{T}', 'length',		f'{T} x',	f'return {abs_func};', comment="length(scalar) = abs(scalar), for conformity with vectors")
		src += function(f, f'{T}', 'length_sqr',	f'{T} x',	f'x = {abs_func};\nreturn x*x;', comment="length_sqr(scalar) = abs(scalar)^2, for conformity with vectors (for vectors this func would save the sqrt)")
			
		src += function(f, f'{T}', 'normalize',		f'{T} x',	f'return x / length(x);', comment="normalize(-6.2f) = -1f, normalize(7) = 1, normalize(0) = <div 0>, can be useful")
		
		src += function(f, f'{T}', 'normalize_or_zero', f'{T} x', f'''
			{T} len = length(x);
			if (len == {T}(0)) {{
				return {T}(0);
			}}
			return x /= len;
		''', comment='normalize(x) for length(x) != 0 else 0')

		src += '\n'
	
	return src

def generic_math(T, f):
	src = ''

	ST = T.scalar_type
	FT = T.float_cast_type
	FST = T.scalar_type.float_cast_type
	
	if ST in floats:
		src += function(f, f'{T}', 'lerp',	f'{T} a, {T} b, {T} t',
				  f'return a * ({T}(1) - t) + b * t;', comment='linear interpolation t=0 -> a ; t=1 -> b ; t=0.5 -> (a+b)/2')
		src += function(f, f'{T}', 'map',	f'{T} x, {T} in_a, {T} in_b',
				  f'return (x - in_a) / (in_b - in_a);', comment='linear mapping (reverse linear interpolation), map(70, 0,100) -> 0.7 ; map(0.5, -1,+1) -> 0.75')
		src += function(f, f'{T}', 'map',	f'{T} x, {T} in_a, {T} in_b, {T} out_a, {T} out_b',
				  f'return lerp(out_a, out_b, map(x, in_a, in_b));', comment='linear mapping, lerp(out_a, out_b, map(x, in_a, in_b))')

		src += '\n//// angle stuff\n'
	
	if ST.name != 'bool':
		src += function(f, f'{FT}', 'to_rad',	f'{T} deg', f'return ({FT})deg * DEG_TO_RAD{float_const[str(FST)]};')
		src += function(f, f'{FT}', 'deg',		f'{T} deg', f'return ({FT})deg * DEG_TO_RAD{float_const[str(FST)]};', comment='degress "literal", converts degrees to radiants')
		src += function(f, f'{FT}', 'to_deg',	f'{T} rad', f'return ({FT})rad * RAD_TO_DEG{float_const[str(FST)]};')
		
	return src

srcgen.generate('kissmath', kissmath)

def gen_vector(V, f):
	size = V.size

	all_dims = ('x', 'y', 'z', 'w')
	dims = all_dims[:size]
	
	T = V.scalar_type
	FT = T.float_cast_type
	FV = V.float_cast_type
	IV = V.int_cast_type
	BV = V.bool_type

	src = ''
	
	def unary_op(op):
		tmp = ', '.join(f'{op}v.{d}' for d in dims)
		return function(f, f'{V}', f'operator{op}', f'{V} v', f'return {V}({tmp});')
	def binary_op(op):
		tmp = ', '.join(f'l.{d} {op} r.{d}' for d in dims)
		return function(f, f'{V}', f'operator{op}', f'{V} l, {V} r', f'return {V}({tmp});')
	def comparison_op(op):
		tmp = ', '.join(f'l.{d} {op} r.{d}' for d in dims)
		return function(f, f'{BV}', f'operator{op}', f'{V} l, {V} r', f'return {BV}({tmp});')
	
	def unary_func(func, arg='v', ret=None):
		ret = ret or V
		return function(f, f'{ret}', func, f'{V} {arg}', f'return {ret}(%s);' % ', '.join(f'{func}({arg}.{d})' for d in dims))
	def nary_func(func, args):
		return function(f, f'{V}', func, ', '.join(f'{V} {a}' for a in args),
			f'return {V}(%s);' % ', '.join(f'{func}(%s)' % ','.join(f'{a}.{d}' for a in args) for d in dims))

	def compound_binary_op(op):
		if False: # compact
			tmp = ', '.join(f'{d} {op} r.{d}' for d in dims)
			body = f'return *this = {V}({tmp});'
		else:
			body = ''.join(f'{d} {op}= r.{d};\n' for d in dims) + 'return *this;'

		return method(f, f'{V}', f'{V}', f'operator{op}=', f'{V} r', body)

	def casting_op(to_type):
		tt = to_type.scalar_type

		tmp = ', '.join(f'({tt}){d}' for d in dims)
		body = f'return {to_type}({tmp});'
		
		return method(f, f'{V}', '', f'operator {to_type}', '', body, const=True)

	other_size_vecs = [v for v in all_vectors if v.size != size and v.scalar_type == T]
	other_type_vecs = [v for v in all_vectors if v.size == size and v.scalar_type != T]

	forward_decl_vecs = other_size_vecs +[BV]+ other_type_vecs
	if f == 'header':
		src += '#include "kissmath.hpp"\n\n'
		
		src += '\nnamespace vector {\n'
		
		src += '//// forward declarations\n'
		src += ''.join(f'union {n};\n' for n in forward_decl_vecs)

	else:
		src += ''.join(f'#include "{n}.hpp"\n' for n in forward_decl_vecs)

		src += '\nnamespace vector {\n'

	if f == 'header':
		src += f'''
		union {V} {{
			struct {{
				{T}	{', '.join(dims)};
			}};
			{T}		arr[{size}];

		'''
		
	src += method(f, V, f'{T}&', 'operator[]', 'int i', 'return arr[i];')
	src += method(f, V, f'{T} const&', 'operator[]', 'int i', 'return arr[i];', const=True)

	src += '\n'
	
	src += constructor(f, f'{V}', args='')
	src += constructor(f, f'{V}', args=f'{T} all',						init_list=', '.join(f'{d}{{all}}' for d in dims),
		comment='sets all components to one value\nimplicit constructor -> v3(x,y,z) * 5 will be turned into v3(x,y,z) * v3(5) by to compiler to be able to execute operator*(v3, v3), which is desirable, also v3 a = 0; works')
	src += constructor(f, f'{V}', args=', '.join(f'{T} {d}' for d in dims), init_list=', '.join(f'{d}{{{d}}}' for d in dims),
		comment='supply all components')
	
	for vsz in range(2,size):
		U = get_type(T, vsz)
		u = ''.join(dims[:vsz])

		src += constructor(f, f'{V}', comment='extend vector',
					 args=', '.join([f'{U} {u}'] + [f'{T} {d}' for d in dims[vsz:]]),
					 init_list=', '.join([f'{d}{{{u}.{d}}}' for d in dims[:vsz]] + [f'{d}{{{d}}}' for d in dims[vsz:]]))

	for vsz in range(size+1,vec_sizes[-1]+1):
		U = get_type(T, vsz)

		src += constructor(f, f'{V}', comment='truncate vector',
					 args=f'{U} v',
					 init_list=', '.join(f'{d}{{v.{d}}}' for d in dims[:size]))
		
	src += '\n//// Truncating cast operators\n\n'
	
	for vsz in range(2,size):
		U = get_type(T, vsz)
		vdims = dims[:vsz]
		
		src += method(f, f'{V}', '', f'operator {U}', '', f'return {U}(%s);' % ', '.join(vdims), const=True)
		
	src += '\n//// Type cast operators\n\n'
	if str(T) != 'bool':
		for to_vec in other_type_vecs:
			src += casting_op(to_vec)
			
		src += '\n'

		for op in ('+', '-', '*', '/'):
			src += compound_binary_op(op)
		

	if f == 'header':
		src += '};\n'
	
	if str(T) == 'bool':
		src += '\n//// reducing ops\n'
		
		src += function(f, f'{T}', 'all', f'{V} v', 'return %s;' % ' && '.join(f'v.{d}' for d in dims), comment='all components are true')
		src += function(f, f'{T}', 'any', f'{V} v', 'return %s;' % ' || '.join(f'v.{d}' for d in dims), comment='any components is true')
		
		src += '\n//// arthmethic ops\n'
		
		src += unary_op('!')
		src += binary_op('&&')
		src += binary_op('||')
		
		src += '\n//// comparison ops\n'
	else:
		src += '\n//// arthmethic ops\n'
		for op in ['+', '-']:
			src += unary_op(op)
		for op in ['+', '-', '*', '/']:
			src += binary_op(op)
		
		src += '\n//// comparison ops\n'
		src += comparison_op('<')
		src += comparison_op('<=')
		src += comparison_op('>')
		src += comparison_op('>=')

	src += comparison_op('==')
	src += comparison_op('!=')
	src += function(f, f'bool', 'equal', f'{V} l, {V} r', 'return all(l == r);', comment='vectors are equal, equivalent to all(l == r)')
	
	src += function(f, f'{V}', 'select', f'{BV} c, {V} l, {V} r', 'return %s;' % ', '.join(f'c.{d} ? l.{d} : r.{d}' for d in dims),
		comment='componentwise ternary c ? l : r')
	
	if str(T) != 'bool':
		src += '\n//// misc ops\n'
		
		src += unary_func('abs')
		
		src += nary_func('min', ('l', 'r'))
		src += nary_func('max', ('l', 'r'))

		src += function(f, f'{V}', 'clamp', f'{V} x, {V} a={V}(0), {V} b={V}(1)', f'return min(max(x,a), b);')
		
		def minmax_component(mode):
			op = {'min':'<=', 'max':'>='}[mode]
			return function(f, f'{T}', f'{mode}_component', f'{V} v, int* {mode}_index=nullptr', f'''
				int index = 0;
				{T} {mode}_val = v.x;	
				for (int i=1; i<{size}; ++i) {{
					if (v.arr[i] {op} {mode}_val) {{
						index = i;
						{mode}_val = v.arr[i];
					}}
				}}
				if ({mode}_index) *{mode}_index = index;
				return {mode}_val;
			''', comment=f'get {mode} component of vector, optionally get component index via {mode}_index')

		src += minmax_component('min')
		src += minmax_component('max')
		
		src += '\n'
		
		if T in floats:
			src += unary_func('floor')
			src += unary_func('ceil')
			src += unary_func('round')

			src += unary_func('floori', ret=IV)
			src += unary_func('ceili', ret=IV)
			src += unary_func('roundi', ret=IV)

			src += nary_func('pow', ('v','e'))

		src += nary_func('wrap', ('v','range'))
		src += nary_func('wrap', ('v','a','b'))

		src += '\n'

		src += generic_math(V, f)

		src += '\n//// linear algebra ops\n'
		
		src += function(f, f'{FT}', 'length', f'{V} v',				f'return sqrt(({FT})(%s));' % ' + '.join(f'v.{d} * v.{d}' for d in dims), comment='magnitude of vector')
		src += function(f, f'{T}', 'length_sqr', f'{V} v',			f'return %s;' % ' + '.join(f'v.{d} * v.{d}' for d in dims), comment='squared magnitude of vector, cheaper than length() because it avoids the sqrt(), some algorithms only need the squared magnitude')
		src += function(f, f'{FT}', 'distance', f'{V} a, {V} b',	f'return length(a - b);', comment='distance between points, equivalent to length(a - b)')
		src += function(f, f'{FV}', 'normalize', f'{V} v',			f'return {FV}(v) / length(v);', comment='normalize vector so that it has length() = 1, undefined for zero vector')
		src += function(f, f'{FV}', 'normalize_or_zero', f'{V} v', f'''
			{FT} len = length(v);
			if (len == {FT}(0)) {{
				return {FT}(0);
			}}
			return {FV}(v) / {FV}(len);
		''', comment='normalize vector so that it has length() = 1, returns zero vector if vector was zero vector')
		
		src += function(f, f'{T}', 'dot', f'{V} l, {V} r', f'return %s;' % ' + '.join(f'l.{d} * r.{d}' for d in dims), comment='dot product')
		
		if size == 3:
			body = f'''
				return {V}(
					l.y * r.z - l.z * r.y,
					l.z * r.x - l.x * r.z,
					l.x * r.y - l.y * r.x);
			'''
			comment='3d cross product'
			src += function(f, f'{V}', 'cross', f'{V} l, {V} r', comment=comment, body=body)
				
		elif size == 2:
			body = 'return l.x * r.y - l.y * r.x;'
			comment='2d cross product hack for convinient 2d stuff\nsame as cross(v3(l, 0), v3(r, 0)).z, ie. the cross product of the 2d vectors on the z=0 plane in 3d space and then return the z coord of that (signed mag of cross product)'
			src += function(f, f'{T}', 'cross', f'{V} l, {V} r', comment=comment, body=body)

	src += '}// namespace vector\n'
	return src

for tvec in vectors:
	for v in tvec:
		srcgen.generate(v.name, lambda f: gen_vector(v, f))

def gen_matrix(M, f):
	
	T = M.scalar_type
	size = M.size

	mpass = 'const&'

	# standart math way of writing matrix size:
	# size[0] = rows	ie. height
	# size[1] = columns	ie. width

	V = get_type(T, size[0]).name # column vectors
	RV = get_type(T, size[1]).name # row vectors

	src = ''
	
	other_size_mats = [m for m in all_matricies if m.size[0] != size[0] or m.size[1] != size[1] if m.scalar_type == T]
	other_type_mats = [m for m in all_matricies if m.size[0] == size[0] and m.size[1] == size[1] if m.scalar_type != T]

	forward_decl_vecs = [m.name for m in other_size_mats] + [m.name for m in other_type_mats]
	if f == 'header':
		src += '#include "kissmath.hpp"\n\n'

		for v in set((V, RV)):
			src += f'#include "{v}.hpp"\n'
		
		src += '\nnamespace vector {\n\n'

		src += '//// matrix forward declarations\n'
		src += ''.join(f'struct {n};\n' for n in forward_decl_vecs)

	else:
		src += ''.join(f'#include "{n}.hpp"\n' for n in forward_decl_vecs)

		src += '\nnamespace vector {\n\n'

	def row_major(cell_format):	return '\n'+ ',\n'.join(', '.join(cell_format.format(c=c,r=r) for c in range(size[1])) for r in range(size[0]))
	def col_major(cell_format):	return '\n'+ ',\n'.join(', '.join(cell_format.format(c=c,r=r) for r in range(size[0])) for c in range(size[1]))
	
	def row_vec_cells(cell_format):	return '\n'+ ',\n'.join(f'{RV}(%s)' % ', '.join(cell_format.format(c=c,r=r) for c in range(size[1])) for r in range(size[0]))
	def col_vec_cells(cell_format):	return '\n'+ ',\n'.join(f'{V}(%s)' % ', '.join(cell_format.format(c=c,r=r) for r in range(size[0])) for c in range(size[1]))

	def row_vecs(vec_format):	return ', '.join(vec_format.format(r=r) for r in range(size[0]))
	def col_vecs(vec_format):	return ', '.join(vec_format.format(c=c) for c in range(size[1]))

	def elementwise(op_format):
		return f'return {M}(%s);' % row_major(op_format)
	
	################
	if f == 'header':
		src += f'''
		struct {M} {{
			{V} arr[{size[1]}]; // column major for compatibility with OpenGL
		\n'''
		
	src += '//// Accessors\n\n'
	#src += method(f, f'{M}', f'{T}&', 'get', F'int r, int c', 'return arr[c][r];', comment='get cell with r,c indecies (r=row, c=column)')
	src += method(f, f'{M}', f'{T} const&', 'get', F'int r, int c', 'return arr[c][r];', const=True, comment='get cell with r,c indecies (r=row, c=column)')

	#src += method(f, f'{M}', f'{V}&', 'get_column', F'int indx', 'return arr[indx];', comment='get matrix column')
	src += method(f, f'{M}', f'{V} const&', 'get_column', F'int indx', 'return arr[indx];', const=True, comment='get matrix column')
	
	src += method(f, f'{M}', f'{RV}', 'get_row', F'int indx', f'return {RV}(%s);' % ', '.join(f'arr[{c}][indx]' for c in range(size[1])),
		const=True, comment='get matrix row')
	
	src += '\n//// Constructors\n\n'
	src += constructor(f, f'{M}', '')

	src += constructor(f, f'{M}', args=f'{T} all',						explicit=True, init_list='\narr{%s}' % col_vec_cells('all'),		comment='supply one value for all cells')
	src += constructor(f, f'{M}', args=row_major(str(T) +' c{r}{c}'),	explicit=True, init_list='\narr{%s}' % col_vec_cells('c{r}{c}'),	comment='supply all cells, in row major order for readability -> c<r><c> (r=row, c=column)')
	
	src += '\n// static rows() and columns() methods are preferred over constructors, to avoid confusion if column or row vectors are supplied to the constructor\n'
	
	src += static_method(f, f'{M}', f'{M}', 'rows',	args=row_vecs(str(RV) +' row{r}'), body=f'return {M}(%s);' % row_major('row{r}[{c}]'),
		comment='supply all row vectors')
	src += static_method(f, f'{M}', f'{M}', 'rows',	args=row_major(str(T) +' c{r}{c}'), body=f'return {M}(%s);' % row_major('c{r}{c}'),
		comment='supply all cells in row major order')

	src += static_method(f, f'{M}', f'{M}', 'columns',	args=col_vecs(str(V) +' col{c}'), body=f'return {M}(%s);' % row_major('col{c}[{r}]'),
		comment='supply all column vectors')
	src += static_method(f, f'{M}', f'{M}', 'columns',	args=col_major(str(T) +' c{r}{c}'), body=f'return {M}(%s);' % row_major('c{r}{c}'),
		comment='supply all cells in column major order')

	src += '\n'
	src += static_method(f, f'{M}', f'{M}', 'identity', args='',
		comment='identity matrix',
		body=f'return {M}(\n%s);' % ',\n'.join(','.join('1' if x==y else '0' for x in range(size[1])) for y in range(size[0])))
	
	src += '\n// Casting operators\n\n'
	for m in other_size_mats:
		def cell(r,c):
			if r<size[1] and c<size[0]:
				return f'arr[{r}][{c}]'
			else:
				return '        1' if r == c else '        0'

		src += method(f, f'{M}', '', f'operator {m.name}', '',
			comment='extend/truncate matrix of other size',
			body=f'return {m.name}(\n%s);' % ',\n'.join(', '.join(cell(c,r) for c in range(m.size[1])) for r in range(m.size[0])))

	for m in other_type_mats:
		src += method(f, f'{M}', '', f'operator {m.name}', '',
			comment='typecast',
			body=f'return {m.name}(\n%s);' % ',\n'.join(', '.join(f'({m.scalar_type})arr[{r}][{c}]' for c in range(m.size[1])) for r in range(m.size[0])))
	
	src += '\n// Elementwise operators\n\n'

	for op in ['+', '-', '*', '/']:
		src += method(f, f'{M}', f'{M}&', f'operator{op}=', f'{T} r', f'*this = *this {op} r;\nreturn *this;')
		
	src += '\n// Matrix multiplication\n\n'

	src += method(f, f'{M}', f'{M}&', 'operator*=', f'{M} {mpass} r', '*this = *this * r;\nreturn *this;')
		
	if f == 'header':
		src += '};\n'

	src += '\n// Elementwise operators\n\n'
	
	for op in ['+', '-']:
		src += function(f, f'{M}', 'operator'+ op, f'{M} {mpass} m', elementwise(op +'m.arr[{c}][{r}]'))
		
	for op in ['+', '-', '*', '/']:
		src += '\n'

		name = f'operator{op}'

		if op == '*':	name = 'mul_elementwise'
		elif op == '/':	name = 'div_elementwise'

		src += function(f, f'{M}', name, f'{M} {mpass} l, {M} {mpass} r', elementwise(f'l.arr[{{c}}][{{r}}] {op} r.arr[{{c}}][{{r}}]'))
		src += function(f, f'{M}', f'operator{op}', f'{M} {mpass} l, {T} r', elementwise(f'l.arr[{{c}}][{{r}}] {op} r'))
		src += function(f, f'{M}', f'operator{op}', f'{T} l, {M} {mpass} r', elementwise(f'l {op} r.arr[{{c}}][{{r}}]'))
	
	src += '\n// Matrix multiplication\n\n'

	def matmul(op, m=None):
		dims = ['x', 'y', 'z', 'w']

		if op == 'mm':
			if size[1] != m.size[0] or M.scalar_type != m.scalar_type:
				return ''
			if (str(T), (size[0], m.size[1])) not in _types:
				return f'// {M} * {m} -> {size[0]}x{m.size[1]} ; matrix not implemented\n'
			ret = get_type(T, (size[0], m.size[1])).name
			args = f'{M} const& l, {m} const& r'
			body = f'{ret} ret;\n%s\nreturn ret;' % '\n'.join(f'ret.arr[{c}] = l * r.arr[{c}];' for c in range(m.size[1]))
		elif op == 'mv':
			ret = f'{V}'
			args = f'{M} const& l, {RV} r'
			body = f'{V} ret;\n%s\nreturn ret;' % '\n'.join(f'ret.{dims[r]} = %s;' % ' + '.join(f'l.arr[{c}].{dims[r]} * r.{dims[c]}' for c in range(size[1])) for r in range(size[0]))
		elif op == 'vm':
			ret = f'{RV}'
			args = f'{V} l, {M} const& r'
			body = f'{RV} ret;\n%s\nreturn ret;' % '\n'.join(f'ret.{dims[c]} = %s;' % ' + '.join(f'l.{dims[r]} * r.arr[{c}].{dims[r]}' for r in range(size[0])) for c in range(size[1]))
		return function(f, ret, 'operator*', args, body)

	for m in all_matricies:
		src += matmul('mm', m)

	src += matmul('mv')
	src += matmul('vm')

	src += '} // namespace vector\n'
	return src

for tmat in matricies:
	for m in tmat:
		srcgen.generate(m.name, lambda f: gen_matrix(m, f))

def transformations(f):
	src = ''

	if f == 'header':
		src += '#include "vector.hpp"\n\n'
		
	src += 'namespace vector {\n'

	src += function(f, 'fm2', 'scale2', 'fv2 v', '''
		return fm2(
			v.x,   0,
			  0, v.y
		);
	''')
	src += function(f, 'fm2x3', 'translate2', 'fv2 v', '''
		return fm2x3(
			1, 0, v.x,
			0, 1, v.y
		);
	''')
	
	src += '} // namespace vector\n'
	return src

srcgen.generate('transformations', transformations)

def main(f):
	# main file to include
	
	src = ''

	if f == 'header':
		src += '#include "kissmath.hpp"\n\n'
		
		src += '// Vectors\n'
		for tvec in vectors:
			for v in tvec:
				src += f'#include "{v.name}.hpp"\n'

			src += '\n'
			
		src += '// Matricies\n'
		for tmat in matricies:
			for m in tmat:
				src += f'#include "{m.name}.hpp"\n'

			src += '\n'
		
		#s.include('fquat', nl=1)
		#
		#s.include('lrgb')
		#s.include('lrgba', nl=2)

		src += 'using namespace vector;\n\n'

		src += "// Typedefs that define 'standart' floats to use across program\n"
		src += 'typedef float flt;\n\n'

		for v in all_vectors:
			if v.scalar_type.name == 'f32':
				src += f'typedef {v} v{v.size};\n'

		for m in all_matricies:
			if m.scalar_type.name == 'f32':
				src += f'typedef {m} {m.name[1:]};\n'
				
		src += '#include "transformations.hpp"\n\n'

	return src
	
srcgen.generate('vector', main)