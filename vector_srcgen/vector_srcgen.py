import srcgen
from collections import namedtuple
from itertools import chain

def util(f):
	if f == 'header':
		return \
	''' #define STRINGIFY(x) #x
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

floats = ['f32', 'f64']
ints = ['s32', 's64', 's8']
uints = ['u32', 'u64', 'u8']

scalars = floats + ints + uints

float_const = {'f32':'', 'f64':'d'} # postfix of Math constants

#
vec = namedtuple('vec', 'name type size')

vec_sizes = [2,3,4]

vectors = [
	[vec(f'bv{s}',	 type='bool',	size=s) for s in vec_sizes],

	[vec(f'fv{s}',	 type='f32',	size=s) for s in vec_sizes],
	[vec(f'dv{s}',	 type='f64',	size=s) for s in vec_sizes],
	[vec(f'iv{s}',	 type='int',	size=s) for s in vec_sizes],
	[vec(f's64v{s}', type='s64',	size=s) for s in vec_sizes],
	[vec(f'u8v{s}',	 type='u8',		size=s) for s in vec_sizes],
]
all_vectors = list(chain.from_iterable(vectors))

vectors_of_t = { vs[0].type: vs for vs in vectors }
def get_vector(T, size):
	return vectors_of_t[T][size -2]

scalar_type = { f:f for f in floats } # scalar type of vector or type itself for scalars
for tvec in vectors:
	for v in tvec:
		scalar_type[v.name] = v.type

#
def bool_type(T): return'bool' if not isinstance(T, vec) else get_vector('bool', T.size) # bool for scalars or bv* for vectors

def f2i_type(T): # int cast for float types
	_f2i_type = {'f32':'int', 'f64':'s64'}
	if not isinstance(T, vec):
		return _f2i_type.get(T)
	t = _f2i_type.get(T.type, None)
	return get_vector(t, T.size) if t else None

def f2i_scalar(T): # float cast for int types (scalar for length() funcs)
	_f2i_type = {'f32':'int', 'f64':'s64'}
	return _f2i_type.get(T) if not isinstance(T, vec) else _f2i_type.get(T.type, None)

def i2f_type(T): # float cast for int types for normalize() funcs
	_i2f_type = {'int':'f32', 's64':'f64', 'u8':'f32'}
	if not isinstance(T, vec):
		return _i2f_type.get(T)
	t = _i2f_type.get(T.type, None)
	return get_vector(t, T.size) if t else None

def i2f_scalar(T): # float cast for int types (scalar for length() funcs)
	_i2f_scalar = {'int':'f32', 's64':'f64', 'u8':'f32'}
	return _i2f_scalar.get(T) if not isinstance(T, vec) else _i2f_scalar.get(T.type, None)

use_contexpr_where_possible = False
all_inline = False

def _function(file, ret, name, args, body, clsname=None, init_list=None, comment=None, const=False, static=False, constexpr='auto', inline='auto'):
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
		if inline:
			decl = spaced_join(static, inline, constexpr, ret, name)
			return body_(decl, comment)
		else:
			decl = spaced_join(static, inline, constexpr, ret, name)
			return f'{comment}{decl} ({args}){const};\n'
	elif file == 'source':
		if inline:
			return ''
		else:
			decl = spaced_join(constexpr, ret, clsname + name)
			return body_(decl)
		
	else:
		raise ValueError(f"Wrong file type '{file}'")

def function(file, ret, name, args, body, comment=None):
	return _function(file, ret, name, args, body, comment=comment)
def method(file, clsname, ret, name, args, body, comment=None, const=False):
	return _function(file, ret, name, args, body, clsname=clsname, comment=comment, const=const)
def static_method(file, clsname, ret, name, args, body, comment=None, const=False):
	return _function(file, ret, name, args, body, clsname=clsname, comment=comment, const=const, static=True)
def constructor(file, clsname, args, body='', init_list=None, ret='', comment=None):
	return _function(file, ret, clsname, args, body, clsname=clsname, comment=comment, init_list=init_list)

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
		src += f'\n//// {T}\n'
		
		src += scalar_math(T, f)
		src += generic_math(T, f)
		
	src += '} // namespace vector\n'
	return src

def scalar_math(T, f):
	src = ''

	BT = bool_type(T)
	
	IT = f2i_scalar(T) or T # int scalar for roundi funcs
	
	src += function(f, T, 'wrap', f'{T} x, {T} range', f'''
		{T} modded = '''+ ('std::fmod(x, range)' if T in floats else 'x % range') +''';
		if (range > 0) {
			if (modded < 0) modded += range;
		} else {
			if (modded > 0) modded -= range;
		}
		return modded;
	''', comment='wrap x into range [0,range), negative x wrap back to +range unlike c++ % operator, negative range supported')

	src += function(f, T, 'wrap', f'{T} x, {T} a, {T} b', f'''
		x -= a;
		{T} range = b -a;
			
		{T} modulo = wrap(x, range);
			
		return modulo + a;
	''', comment='wrap x into [a,b) range')
		
	if T in floats:
		src += function(f, T, 'wrap', f'{T} x, {T} a, {T} b, {T}* quotient', f'''
			x -= a;
			{T} range = b -a;
			
			{T} modulo = wrap(x, range);
			*quotient = floor(x / range);
			
			return modulo + a;
		''')
		src += '\n'
			
		src += function(f, IT, 'floori',	f'{T} x', f'return ({IT})floor(x);')
		src += function(f, IT, 'ceili',	f'{T} x', f'return ({IT})ceil(x);')
		src += function(f, IT, 'roundi',	f'{T} x', f'return '+ {'f32':'std::lround(x)', 'f64':'std::llround(x)'}[T] +';')
			
		src += '\n'

	min_func = 'std::fmin(l,r)' if T in floats else f'l <= r ? l : r'
	max_func = 'std::fmax(l,r)' if T in floats else f'l >= r ? l : r'
		
	src += function(f, T, 'min',	f'{T} l, {T} r',			f'return {min_func};')
	src += function(f, T, 'max',	f'{T} l, {T} r',			f'return {max_func};')
	src += function(f, T, 'clamp',	f'{T} x, {T} a=0, {T} b=1',	f'return min(max(x,a), b);')
	src += function(f, T, 'select',	f'{BT} c, {T} l, {T} r',	f'return c ? l : r;', comment='equivalent to ternary c ? l : r, for conformity with vectors')

	src += '\n'

	abs_func = f'std::fabs(x)' if T in floats else f'std::abs(x)'
		
	if T not in uints: # no abs for unsigned types
		src += function(f, T, 'length',		f'{T} x',	f'return {abs_func};', comment="length(scalar) = abs(scalar), for conformity with vectors")
		src += function(f, T, 'length_sqr',	f'{T} x',	f'x = {abs_func};\nreturn x*x;', comment="length_sqr(scalar) = abs(scalar)^2, for conformity with vectors (for vectors this func would save the sqrt)")
			
		src += function(f, T, 'normalize',		f'{T} x',	f'return x / length(x);', comment="normalize(-6.2f) = -1f, normalize(7) = 1, normalize(0) = <div 0>, can be useful")
		
		src += function(f, T, 'normalize_or_zero', f'{T} x', f'''
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

	ST = scalar_type.get(T, None)

	if ST in floats:

		src += function(f, T, 'lerp',	f'{T} a, {T} b, {T} t',				f'return a * ({T}(1) - t) + b * t;', comment='linear interpolation t=0 -> a ; t=1 -> b ; t=0.5 -> (a+b)/2')
		src += function(f, T, 'map',	f'{T} x, {T} in_a, {T} in_b',		f'return (x - in_a) / (in_b - in_a);', comment='linear mapping (reverse linear interpolation), map(70, 0,100) -> 0.7 ; map(0.5, -1,+1) -> 0.75')
		src += function(f, T, 'map',	f'{T} x, {T} in_a, {T} in_b, {T} out_a, {T} out_b',		f'return lerp(out_a, out_b, map(x, in_a, in_b));', comment='linear mapping, lerp(out_a, out_b, map(x, in_a, in_b))')

		src += function(f, T, 'smoothstep',	f'{T} x', f'''
			{T} t = clamp(x);
			return t * t * ({T}(3) - {T}(2) * t);
		''')
			
		src += function(f, T, 'bezier',		f'{T} a, {T} b, {T} c, {ST} t', f'''
			{T} d = lerp(a, b, t);
			{T} e = lerp(b, c, t);
			{T} f = lerp(d, e, t);
			return f;
		''')
		src += function(f, T, 'bezier',		f'{T} a, {T} b, {T} c, {T} d, {ST} t', f'''
			return bezier(
							lerp(a, b, t),
							lerp(b, c, t),
							lerp(c, d, t),
							t
						);
		''')
		src += function(f, T, 'bezier',		f'{T} a, {T} b, {T} c, {T} d, {T} e, {ST} t', f'''
			return bezier(
							lerp(a, b, t),
							lerp(b, c, t),
							lerp(c, d, t),
							lerp(d, e, t),
							t
						);
		''')
		
		src += '\n//// angle stuff\n'
		src += function(f, f'{T}', 'to_rad',	f'{T} deg', f'return deg * DEG_TO_RAD{float_const[ST]};')
		src += function(f, f'{T}', 'deg',	f'{T} deg', f'return deg * DEG_TO_RAD{float_const[ST]};', comment='degress "literal", converts degrees to radiants')
		src += function(f, f'{T}', 'to_deg',	f'{T} rad', f'return rad * RAD_TO_DEG{float_const[ST]};')
		
	return src

srcgen.generate('kissmath', kissmath)

def gen_vector(vec, f):
	V, T, size = vec

	all_dims = ('x', 'y', 'z', 'w')
	dims = all_dims[:size]
	
	FT = i2f_scalar(vec) or T # Float scalar for length ops
	
	FV = i2f_type(vec) # Float vec for normalize ops
	FV = FV.name if FV else V

	IV = f2i_type(vec) # Int vec for roundi funcs
	IV = IV.name if IV else V

	BV = bool_type(vec).name


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

		return method(f, V, V, f'operator{op}=', f'{V} r', body)

	def casting_op(to_type):
		tt = scalar_type[to_type]

		tmp = ', '.join(f'({tt}){d}' for d in dims)
		body = f'return {to_type}({tmp});'
		
		return method(f, V, '', f'operator {to_type}', '', body, const=True)

	other_size_vecs = [v.name for v in all_vectors if v.size != size and v.type == T]
	other_type_vecs = [v.name for v in all_vectors if v.size == size and v.type != T]

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
	src += method(f, V, f'{T}', 'operator[]', 'int i', 'return arr[i];', const=True)

	src += '\n'
	
	src += constructor(f, V, args='')
	src += constructor(f, V, args=f'{T} all',						init_list=', '.join(f'{d}{{all}}' for d in dims),
		comment='sets all components to one value\nimplicit constructor -> v3(x,y,z) * 5 will be turned into v3(x,y,z) * v3(5) by to compiler to be able to execute operator*(v3, v3), which is desirable, also v3 a = 0; works')
	src += constructor(f, V, args=', '.join(f'{T} {d}' for d in dims), init_list=', '.join(f'{d}{{{d}}}' for d in dims),
		comment='supply all components')
	
	for vsz in range(2,size):
		U = get_vector(T, vsz).name
		u = ''.join(dims[:vsz])

		src += constructor(f, V, comment='extend vector',
					 args=', '.join([f'{U} {u}'] + [f'{T} {d}' for d in dims[vsz:]]),
					 init_list=', '.join([f'{d}{{{u}.{d}}}' for d in dims[:vsz]] + [f'{d}{{{d}}}' for d in dims[vsz:]]))

	for vsz in range(size+1,vec_sizes[-1]+1):
		U = get_vector(T, vsz).name

		src += constructor(f, V, comment='truncate vector',
					 args=f'{U} v',
					 init_list=', '.join(f'{d}{{v.{d}}}' for d in dims[:size]))
		
	src += '\n//// Truncating cast operators\n\n'
	
	for vsz in range(2,size):
		U = get_vector(T, vsz).name
		vdims = dims[:vsz]
		
		src += method(f, V, '', f'operator {U}', '', f'return {U}(%s);' % ', '.join(vdims), const=True)
		
	src += '\n//// Type cast operators\n\n'
	if T != 'bool':
		for to_vec in other_type_vecs:
			src += casting_op(to_vec)
			
		src += '\n'

		for op in ('+', '-', '*', '/'):
			src += compound_binary_op(op)
		

	if f == 'header':
		src += '};\n'
	
	if T == 'bool':
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
	
	src += function(f, f'{V}', 'select', f'{V} c, {V} l, {V} r', 'return %s;' % ', '.join(f'c.{d} ? l.{d} : r.{d}' for d in dims),
		comment='componentwise ternary c ? l : r')
	
	if T != 'bool':
		src += '\n//// misc ops\n'
		
		src += unary_func('abs')
		
		src += nary_func('min', ('l', 'r'))
		src += nary_func('max', ('l', 'r'))

		src += function(f, V, 'clamp', f'{V} x, {V} a={V}(0), {V} b={V}(1)', f'return min(max(x,a), b);')
		
		def minmax_component(mode):
			op = {'min':'<=', 'max':'>='}[mode]
			return function(f, T, f'{mode}_component', f'{V} v, int* {mode}_index=nullptr', f'''
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
		
		src += function(f, FT, 'length', f'{V} v',				f'return sqrt(({FT})(%s));' % ' + '.join(f'v.{d} * v.{d}' for d in dims), comment='magnitude of vector')
		src += function(f, T, 'length_sqr', f'{V} v',			f'return %s;' % ' + '.join(f'v.{d} * v.{d}' for d in dims), comment='squared magnitude of vector, cheaper than length() because it avoids the sqrt(), some algorithms only need the squared magnitude')
		src += function(f, FT, 'distance', f'{V} a, {V} b',	f'return length(a - b);', comment='distance between points, equivalent to length(a - b)')
		src += function(f, FV, 'normalize', f'{V} v',			f'return {FV}(v) / length(v);', comment='normalize vector so that it has length() = 1, undefined for zero vector')
		src += function(f, FV, 'normalize_or_zero', f'{V} v', f'''
			{FT} len = length(v);
			if (len == {FT}(0)) {{
				return {FT}(0);
			}}
			return {FV}(v) / {FV}(len);
		''', comment='normalize vector so that it has length() = 1, returns zero vector if vector was zero vector')
		
		src += function(f, T, 'dot', f'{V} l, {V} r', f'return %s;' % ' + '.join(f'l.{d} * r.{d}' for d in dims), comment='dot product')
		
		if size == 3:
			body = f'''
				return {V}(
					l.y * r.z - l.z * r.y,
					l.z * r.x - l.x * r.z,
					l.x * r.y - l.y * r.x);
			'''
			comment='3d cross product'
			src += function(f, V, 'cross', f'{V} l, {V} r', comment=comment, body=body)
				
		elif size == 2:
			body = 'return l.x * r.y - l.y * r.x;'
			comment='2d cross product hack for convinient 2d stuff\nsame as cross(v3(l, 0), v3(r, 0)).z, ie. the cross product of the 2d vectors on the z=0 plane in 3d space and then return the z coord of that (signed mag of cross product)'
			src += function(f, T, 'cross', f'{V} l, {V} r', comment=comment, body=body)

	src += '}// namespace vector\n'
	return src

for tvec in vectors:
	for v in tvec:
		srcgen.generate(v.name, lambda f: gen_vector(v, f))

mat = namedtuple('mat', 'type size name')

mat_sizes = [(2,2), (3,3), (4,4), (2,3), (3,4)]

matricies = [
	[ mat(type='f32', size=s, name='m%s' % (s[0] if s[0]==s[1] else f'{s[0]}x{s[1]}')) for s in mat_sizes ],
	[ mat(type='f64', size=s, name='f64m%s' % (s[0] if s[0]==s[1] else f'{s[0]}x{s[1]}')) for s in mat_sizes ],
]
all_matricies = list(chain.from_iterable(matricies))

def gen_matrix(type, size, name, f):
	
	T = type
	M = name

	# standart math way of writing matrix size:
	# size[0] = rows	ie. height
	# size[1] = columns	ie. width

	V = get_vector(T, size[0]).name # column vectors
	RV = get_vector(T, size[1]).name # row vectors

	src = ''
	
	other_size_mats = [m for m in all_matricies if m.size[0] != size[0] or m.size[1] != size[1] if m.type == type]
	other_type_mats = [m for m in all_matricies if m.size[0] == size[0] and m.size[1] == size[1] if m.type != type]

	forward_decl_vecs = [m.name for m in other_size_mats] + [m.name for m in other_type_mats]
	if f == 'header':
		src += '#include "kissmath.hpp"\n\n'
		src += '\n#include <string>\n\n'

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
	#src += method(f, M, f'{T}&', 'get', F'int r, int c', 'return arr[c][r];', comment='get cell with r,c indecies (r=row, c=column)')
	src += method(f, M, f'{T}', 'get', F'int r, int c', 'return arr[c][r];', const=True, comment='get cell with r,c indecies (r=row, c=column)')

	#src += method(f, M, f'{V}&', 'get_column', F'int indx', 'return arr[indx];', comment='get matrix column')
	src += method(f, M, f'{V}', 'get_column', F'int indx', 'return arr[indx];', const=True, comment='get matrix column')
	
	src += method(f, M, f'{RV}', 'get_row', F'int indx', f'return {RV}(%s);' % ', '.join(f'arr[{c}][indx]' for c in range(size[1])),
		const=True, comment='get matrix row')
	
	src += '\n//// Constructors\n\n'
	src += constructor(f, M, '')

	src += constructor(f, M, args=f'{T} all',				init_list='\narr{%s}' % col_vec_cells('all'),		comment='supply one value for all cells')
	src += constructor(f, M, args=row_major(T +' c{r}{c}'), init_list='\narr{%s}' % col_vec_cells('c{r}{c}'),	comment='supply all cells, in row major order for readability -> c<r><c> (r=row, c=column)')
	
	src += '\n// static rows() and columns() methods are preferred over constructors, to avoid confusion if column or row vectors are supplied to the constructor\n'
	
	src += static_method(f, M, f'{M}', 'rows',	args=row_vecs(RV +' row{r}'), body=f'return {M}(%s);' % row_major('row{r}[{c}]'),
		comment='supply all row vectors')
	src += static_method(f, M, f'{M}', 'rows',	args=row_major(T +' c{r}{c}'), body=f'return {M}(%s);' % row_major('c{r}{c}'),
		comment='supply all cells in row major order')

	src += static_method(f, M, f'{M}', 'columns',	args=col_vecs(V +' col{c}'), body=f'return {M}(%s);' % row_major('col{c}[{r}]'),
		comment='supply all column vectors')
	src += static_method(f, M, f'{M}', 'columns',	args=col_major(T +' c{r}{c}'), body=f'return {M}(%s);' % row_major('c{r}{c}'),
		comment='supply all cells in column major order')

	src += '\n'
	src += static_method(f, M, f'{M}', 'identity', args='',
		comment='identity matrix',
		body=f'return {M}(\n%s);' % ',\n'.join(','.join('1' if x==y else '0' for x in range(size[1])) for y in range(size[0])))
	
	src += '\n// Casting operators\n\n'
	for m in other_size_mats:
		def cell(r,c):
			if r<size[1] and c<size[0]:
				return f'arr[{r}][{c}]'
			else:
				return '        1' if r == c else '        0'

		src += method(f, M, '', f'operator {m.name}', '',
			comment='extend/truncate matrix of other size',
			body=f'return {m.name}(\n%s);' % ',\n'.join(', '.join(cell(c,r) for c in range(m.size[1])) for r in range(m.size[0])))

	for m in other_type_mats:
		src += method(f, M, '', f'operator {m.name}', '',
			comment='typecast',
			body=f'return {m.name}(\n%s);' % ',\n'.join(', '.join(f'({m.type})arr[{r}][{c}]' for c in range(m.size[1])) for r in range(m.size[0])))
		
	src += '\n// Elementwise operators\n\n'

	src += method(f, M, f'{M}', 'operator+', f'{M} m', elementwise('+m.arr[{c}][{r}]'))
	src += method(f, M, f'{M}', 'operator-', f'{M} m', elementwise('-m.arr[{c}][{r}]'))

	if f == 'header':
		src += '};\n\n'

	src += function(f, f'{M}', f'operator+', f'{M} l, {M} r', elementwise('l.arr[{c}][{r}] + r.arr[{c}][{r}]'))
	src += function(f, f'{M}', f'operator-', f'{M} l, {M} r', elementwise('l.arr[{c}][{r}] - r.arr[{c}][{r}]'))
	src += function(f, f'{M}', f'operator*', f'{M} l, {M} r', elementwise('l.arr[{c}][{r}] * r.arr[{c}][{r}]'))
	src += function(f, f'{M}', f'operator/', f'{M} l, {M} r', elementwise('l.arr[{c}][{r}] / r.arr[{c}][{r}]'))
	
	#	src += '\n#include <iostream>\n'
	#src += function(f, 'std::ostream&', 'operator<<', f'std::ostream& os, const {M}& m', body=f'''
	#	os << "{M}";
	#	return os;
	#''')
	
	src += '} // namespace vector\n'
	return src

for tmat in matricies:
	for m in tmat:
		srcgen.generate(m.name, lambda f: gen_matrix(m.type, m.size, m.name, f))

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

		src += 'typedef fv2 v2;\n'
		src += 'typedef fv3 v3;\n'
		src += 'typedef fv4 v4;\n'

	return src
	
srcgen.generate('vector', main)