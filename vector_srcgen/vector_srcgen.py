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

def type_exist(scalar_type, size):
	return (str(scalar_type), size) in _types

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

##########
import os

dir = os.path.join('..', 'kiss_cpp', 'vector')
gen = srcgen.Generator(dir, default_constexpr=False, default_inline=False)

def util(f):
	f.header += \
	'''	#define STRINGIFY(x) #x
		#define TO_STRING(x) STRINGIFY(x)

		#define CONCAT(a,b) a##b

		#define STATIC_ASSERT(cond) static_assert((cond), STRINGIFY(cond))

		#define ARRLEN(arr) (sizeof(arr) / sizeof(arr[0]))

		#define EVEN(i)			(((i) % 2) == 0)
		#define ODD(i)			(((i) % 2) == 1)

		#define BOOL_XOR(a, b)	(((a) != 0) != ((b) != 0))
		'''

util(gen.add_file('util'))

def types(f):
	f.header += '''
		#include "stdint.h"
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

types(gen.add_file('types'))

def kissmath(f):
	f.header += \
		'''	#include "types.hpp"
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

				#define NOINLINE						__declspec(noinline) // for testing/debugging purposes
				#define FORCEINLINE						__forceinline

			#elif __GNUC__ || __clan_
				#define F32_INF							(__builtin_inff())
				#define F64_INF							(__builtin_inf())
				#define F32_QNAN						((float)__builtin_nan("0"))
				#define F64_QNAN						(__builtin_nan("0"))
			#endif
		'''

	f += '\nnamespace vector {\n\n'
			
	f.header += \
		'''	// Use std math functions for these
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
	
	f += '\n////// Scalar math ///////\n'

	for T in scalars:
		f += f'\n//// {T}\n\n'
		
		scalar_math(T, f)
		generic_math(T, f)
		
	f += f'\n//// templated math\n\n'

	f.function(template='tn T', ret='T', name='smoothstep',	args='T x', body='''
		T t = clamp(x);
		return t * t * (T(3) - T(2) * t);
	''')

	for ST in floats:
		f.function(template='tn T', ret='T', name='bezier', args=f'T a, T b, T c, {ST} t', body='''
			T d = lerp(a, b, t);
			T e = lerp(b, c, t);
			T f = lerp(d, e, t);
			return f;
		''')
		f.function(template='tn T', ret=f'{T}', name='bezier', args=f'T a, T b, T c, T d, {ST} t', body='''
			return bezier(
							lerp(a, b, t),
							lerp(b, c, t),
							lerp(c, d, t),
							t
						);
		''')
		f.function(template='tn T', ret=f'{T}', name='bezier', args=f'T a, T b, T c, T d, T e, {ST} t', body='''
			return bezier(
							lerp(a, b, t),
							lerp(b, c, t),
							lerp(c, d, t),
							lerp(d, e, t),
							t
						);
		''')


	f += '\n} // namespace vector\n'

def scalar_math(T, f):
	BT = T.bool_type
	IT = T.int_cast_type # int scalar for roundi funcs
	
	f.function(f'{T}', 'wrap', f'{T} x, {T} range', f'''
		{T} modded = '''+ ('std::fmod(x, range)' if T in floats else 'x % range') +''';
		if (range > 0) {
			if (modded < 0) modded += range;
		} else {
			if (modded > 0) modded += range;
		}
		return modded;
	''', comment='wrap x into range [0,range), negative x wrap back to +range unlike c++ % operator, negative range supported')

	f.function(f'{T}', 'wrap', f'{T} x, {T} a, {T} b', f'''
		x -= a;
		{T} range = b -a;
			
		{T} modulo = wrap(x, range);
			
		return modulo + a;
	''', comment='wrap x into [a,b) range')
		
	if T in floats:
		f.function(f'{T}', 'wrap', f'{T} x, {T} a, {T} b, {IT}* quotient', f'''
			x -= a;
			{T} range = b -a;
			
			{T} modulo = wrap(x, range);
			*quotient = floori(x / range);
			
			return modulo + a;
		''')
		f += '\n'
			
		f.function(f'{IT}', 'floori',	f'{T} x', f'return ({IT})floor(x);')
		f.function(f'{IT}', 'ceili',	f'{T} x', f'return ({IT})ceil(x);')
		f.function(f'{IT}', 'roundi',	f'{T} x', f'return '+ {'f32':'std::lround(x)', 'f64':'std::llround(x)'}[str(T)] +';')
			
		f += '\n'

	#min_func = 'std::fmin(l,r)' if T in floats else f'l <= r ? l : r'
	#max_func = 'std::fmax(l,r)' if T in floats else f'l >= r ? l : r'
	min_func = f'l <= r ? l : r'
	max_func = f'l >= r ? l : r'
		
	f.function(f'{T}', 'min',		f'{T} l, {T} r',			f'return {min_func};')
	f.function(f'{T}', 'max',		f'{T} l, {T} r',			f'return {max_func};')
	f.function(f'{T}', 'clamp',		f'{T} x, {T} a=0, {T} b=1',	f'return min(max(x,a), b);')
	f.function(f'{T}', 'select',	f'{BT} c, {T} l, {T} r',	f'return c ? l : r;', comment='equivalent to ternary c ? l : r, for conformity with vectors')

	f += '\n'

	abs_func = f'std::fabs(x)' if T in floats else f'std::abs(x)'
		
	if T not in uints: # no abs for unsigned types
		f.function(f'{T}', 'length',		f'{T} x',	f'return {abs_func};', comment="length(scalar) = abs(scalar), for conformity with vectors")
		f.function(f'{T}', 'length_sqr',	f'{T} x',	f'x = {abs_func};\nreturn x*x;', comment="length_sqr(scalar) = abs(scalar)^2, for conformity with vectors (for vectors this func would save the sqrt)")
			
		f.function(f'{T}', 'normalize',		f'{T} x',	f'return x / length(x);', comment="normalize(-6.2f) = -1f, normalize(7) = 1, normalize(0) = <div 0>, can be useful")
		
		f.function(f'{T}', 'normalize_or_zero', f'{T} x', f'''
			{T} len = length(x);
			if (len == {T}(0)) {{
				return {T}(0);
			}}
			return x /= len;
		''', comment='normalize(x) for length(x) != 0 else 0')

		f += '\n'

def generic_math(T, f):
	ST = T.scalar_type
	FT = T.float_cast_type
	FST = T.scalar_type.float_cast_type
	
	if ST in floats:
		f.function(f'{T}', 'lerp',	f'{T} a, {T} b, {T} t',
				  f'return a * ({T}(1) - t) + b * t;', comment='linear interpolation t=0 -> a ; t=1 -> b ; t=0.5 -> (a+b)/2')
		f.function(f'{T}', 'map',	f'{T} x, {T} in_a, {T} in_b',
				  f'return (x - in_a) / (in_b - in_a);', comment='linear mapping (reverse linear interpolation), map(70, 0,100) -> 0.7 ; map(0.5, -1,+1) -> 0.75')
		f.function(f'{T}', 'map',	f'{T} x, {T} in_a, {T} in_b, {T} out_a, {T} out_b',
				  f'return lerp(out_a, out_b, map(x, in_a, in_b));', comment='linear mapping, lerp(out_a, out_b, map(x, in_a, in_b))')

		f += '\n//// angle stuff\n'
	
	if ST.name != 'bool':
		f.function(f'{FT}', 'to_rad',	f'{T} deg', f'return ({FT})deg * DEG_TO_RAD{float_const[str(FST)]};')
		f.function(f'{FT}', 'deg',		f'{T} deg', f'return ({FT})deg * DEG_TO_RAD{float_const[str(FST)]};', comment='degress "literal", converts degrees to radiants')
		f.function(f'{FT}', 'to_deg',	f'{T} rad', f'return ({FT})rad * RAD_TO_DEG{float_const[str(FST)]};')
	
kissmath(gen.add_file('kissmath'))

def gen_vector(V, f):
	size = V.size

	all_dims = ('x', 'y', 'z', 'w')
	dims = all_dims[:size]
	
	T = V.scalar_type
	FT = T.float_cast_type
	FV = V.float_cast_type
	IV = V.int_cast_type
	BV = V.bool_type

	def unary_op(op):
		tmp = ', '.join(f'{op}v.{d}' for d in dims)
		f.function(f'{V}', f'operator{op}', f'{V} v', f'return {V}({tmp});', forceinline=True)
	def binary_op(op):
		tmp = ', '.join(f'l.{d} {op} r.{d}' for d in dims)
		f.function(f'{V}', f'operator{op}', f'{V} l, {V} r', f'return {V}({tmp});', forceinline=True)
	def comparison_op(op):
		tmp = ', '.join(f'l.{d} {op} r.{d}' for d in dims)
		f.function(f'{BV}', f'operator{op}', f'{V} l, {V} r', f'return {BV}({tmp});')
	
	def unary_func(func, arg='v', ret=None):
		forceinline = ret == None
		ret = ret or V
		f.function(f'{ret}', func, f'{V} {arg}', f'return {ret}(%s);' % ', '.join(f'{func}({arg}.{d})' for d in dims), forceinline=forceinline)
	def nary_func(func, args):
		f.function(f'{V}', func, ', '.join(f'{V} {a}' for a in args),
			f'return {V}(%s);' % ', '.join(f'{func}(%s)' % ','.join(f'{a}.{d}' for a in args) for d in dims), forceinline=True)

	def compound_binary_op(op):
		if False: # compact
			tmp = ', '.join(f'{d} {op} r.{d}' for d in dims)
			body = f'return *this = {V}({tmp});'
		else:
			body = ''.join(f'{d} {op}= r.{d};\n' for d in dims) + 'return *this;'

		f.method(f'{V}', f'{V}', f'operator{op}=', f'{V} r', body, forceinline=True)

	def casting_op(to_type):
		tt = to_type.scalar_type

		tmp = ', '.join(f'({tt}){d}' for d in dims)
		body = f'return {to_type}({tmp});'
		
		f.method(f'{V}', '', f'operator {to_type}', '', body, const=True, explicit=True)

	other_size_vecs = [v for v in all_vectors if v.size != size and v.scalar_type == T]
	other_type_vecs = [v for v in all_vectors if v.size == size and v.scalar_type != T]

	forward_decl_vecs = other_size_vecs +[BV]+ other_type_vecs
	
	f.header += '#include "kissmath.hpp"\n\n'
	f.header += '\nnamespace vector {\n'
		
	f.header += '//// forward declarations\n'
	f.header += ''.join(f'union {n};\n' for n in forward_decl_vecs)
	
	#
	f.source += ''.join(f'#include "{n}.hpp"\n' for n in forward_decl_vecs)

	f.source += '\nnamespace vector {\n'

	f.header += f'''
		union {V} {{
			struct {{
				{T}	{', '.join(dims)};
			}};
			{T}		arr[{size}];

		'''
		
	f.method(V, f'{T}&', 'operator[]', 'int i', 'return arr[i];', forceinline=True)
	f.method(V, f'{T} const&', 'operator[]', 'int i', 'return arr[i];', const=True, forceinline=True)

	f += '\n'
	
	f.constructor(f'{V}', args='', forceinline=True)
	f.constructor(f'{V}', args=f'{T} all',						init_list=', '.join(f'{d}{{all}}' for d in dims), forceinline=True,
		comment='sets all components to one value\nimplicit constructor -> v3(x,y,z) * 5 will be turned into v3(x,y,z) * v3(5) by to compiler to be able to execute operator*(v3, v3), which is desirable, also v3 a = 0; works')
	f.constructor(f'{V}', args=', '.join(f'{T} {d}' for d in dims), init_list=', '.join(f'{d}{{{d}}}' for d in dims), forceinline=True,
		comment='supply all components')
	
	for vsz in range(2,size):
		U = get_type(T, vsz)
		u = ''.join(dims[:vsz])

		f.constructor(f'{V}', comment='extend vector',
					 args=', '.join([f'{U} {u}'] + [f'{T} {d}' for d in dims[vsz:]]),
					 init_list=', '.join([f'{d}{{{u}.{d}}}' for d in dims[:vsz]] + [f'{d}{{{d}}}' for d in dims[vsz:]]))

	for vsz in range(size+1,vec_sizes[-1]+1):
		U = get_type(T, vsz)

		f.constructor(f'{V}', comment='truncate vector',
					 args=f'{U} v',
					 init_list=', '.join(f'{d}{{v.{d}}}' for d in dims[:size]))
		
	f += '\n//// Truncating cast operators\n\n'
	
	for vsz in range(2,size):
		U = get_type(T, vsz)
		vdims = dims[:vsz]
		
		f.method(f'{V}', '', f'operator {U}', '', f'return {U}(%s);' % ', '.join(vdims), const=True, explicit=True)
		
	f += '\n//// Type cast operators\n\n'
	if str(T) != 'bool':
		for to_vec in other_type_vecs:
			casting_op(to_vec)
			
		f += '\n'

		for op in ('+', '-', '*', '/'):
			compound_binary_op(op)
		

	f.header += '};\n'
	
	if str(T) == 'bool':
		f += '\n//// reducing ops\n'
		
		f.function(f'{T}', 'all', f'{V} v', 'return %s;' % ' && '.join(f'v.{d}' for d in dims), comment='all components are true')
		f.function(f'{T}', 'any', f'{V} v', 'return %s;' % ' || '.join(f'v.{d}' for d in dims), comment='any components is true')
		
		f += '\n//// arthmethic ops\n'
		
		unary_op('!')
		binary_op('&&')
		binary_op('||')
		
		f += '\n//// comparison ops\n'
	else:
		f += '\n//// arthmethic ops\n'
		for op in ['+', '-']:
			unary_op(op)
		for op in ['+', '-', '*', '/']:
			binary_op(op)
		
		f += '\n//// comparison ops\n'
		comparison_op('<')
		comparison_op('<=')
		comparison_op('>')
		comparison_op('>=')

	comparison_op('==')
	comparison_op('!=')
	f.function(f'bool', 'equal', f'{V} l, {V} r', 'return all(l == r);', comment='vectors are equal, equivalent to all(l == r)')
	
	f.function(f'{V}', 'select', f'{BV} c, {V} l, {V} r', 'return %s;' % ', '.join(f'c.{d} ? l.{d} : r.{d}' for d in dims),
		comment='componentwise ternary c ? l : r')
	
	if str(T) != 'bool':
		f += '\n//// misc ops\n'
		
		unary_func('abs')
		
		nary_func('min', ('l', 'r'))
		nary_func('max', ('l', 'r'))

		f.function(f'{V}', 'clamp', f'{V} x, {V} a={V}(0), {V} b={V}(1)', f'return min(max(x,a), b);')
		
		def minmax_component(mode):
			op = {'min':'<=', 'max':'>='}[mode]
			f.function(f'{T}', f'{mode}_component', f'{V} v, int* {mode}_index=nullptr', f'''
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

		minmax_component('min')
		minmax_component('max')
		
		f += '\n'
		
		if T in floats:
			unary_func('floor')
			unary_func('ceil')
			unary_func('round')

			unary_func('floori', ret=IV)
			unary_func('ceili', ret=IV)
			unary_func('roundi', ret=IV)

			nary_func('pow', ('v','e'))

		nary_func('wrap', ('v','range'))
		nary_func('wrap', ('v','a','b'))

		f += '\n'

		generic_math(V, f)

		f += '\n//// linear algebra ops\n'
		
		f.function(f'{FT}', 'length', f'{V} v',				f'return sqrt(({FT})(%s));' % ' + '.join(f'v.{d} * v.{d}' for d in dims), comment='magnitude of vector')
		f.function(f'{T}', 'length_sqr', f'{V} v',			f'return %s;' % ' + '.join(f'v.{d} * v.{d}' for d in dims), comment='squared magnitude of vector, cheaper than length() because it avoids the sqrt(), some algorithms only need the squared magnitude')
		f.function(f'{FT}', 'distance', f'{V} a, {V} b',	f'return length(a - b);', comment='distance between points, equivalent to length(a - b)')
		f.function(f'{FV}', 'normalize', f'{V} v',			f'return {FV}(v) / length(v);', comment='normalize vector so that it has length() = 1, undefined for zero vector')
		f.function(f'{FV}', 'normalize_or_zero', f'{V} v', f'''
			{FT} len = length(v);
			if (len == {FT}(0)) {{
				return {FT}(0);
			}}
			return {FV}(v) / {FV}(len);
		''', comment='normalize vector so that it has length() = 1, returns zero vector if vector was zero vector')
		
		f.function(f'{T}', 'dot', f'{V} l, {V} r', f'return %s;' % ' + '.join(f'l.{d} * r.{d}' for d in dims), comment='dot product')
		
		if size == 3:
			f.function(f'{V}', 'cross', f'{V} l, {V} r', comment='3d cross product', body=f'''
				return {V}(
					l.y * r.z - l.z * r.y,
					l.z * r.x - l.x * r.z,
					l.x * r.y - l.y * r.x);
			''')
				
		elif size == 2:
			f.function(f'{T}', 'cross', f'{V} l, {V} r', 'return l.x * r.y - l.y * r.x;',
				comment='''
				2d cross product hack for convinient 2d stuff
				same as cross(v3(l, 0), v3(r, 0)).z,
				ie. the cross product of the 2d vectors on the z=0 plane in 3d space and then return the z coord of that (signed mag of cross product)
				''')
			
			f.function(f'{V}', 'rotate90', f'{V} v', f'return {V}(-v.y, v.x);',
				comment=f'rotate 2d vector counterclockwise 90 deg, ie. {V}(-y, x) which is fast')

	f += '}// namespace vector\n'

for tvec in vectors:
	for v in tvec:
		gen_vector(v, gen.add_file(v.name))

def gen_matrix(M, f):
	
	T = M.scalar_type
	size = M.size

	mpass = 'const&'

	# standart math way of writing matrix size:
	# size[0] = rows	ie. height
	# size[1] = columns	ie. width

	V = get_type(T, size[0]).name # column vectors
	RV = get_type(T, size[1]).name # row vectors

	other_size_mats = [m for m in all_matricies if m.size[0] != size[0] or m.size[1] != size[1] if m.scalar_type == T]
	other_type_mats = [m for m in all_matricies if m.size[0] == size[0] and m.size[1] == size[1] if m.scalar_type != T]

	forward_decl_vecs = [m.name for m in other_size_mats] + [m.name for m in other_type_mats]
	
	f.header += '#include "kissmath.hpp"\n\n'

	for v in set((V, RV)):
		f.header += f'#include "{v}.hpp"\n'
		
	f.header += '\nnamespace vector {\n\n'

	f.header += '//// matrix forward declarations\n'
	f.header += ''.join(f'struct {n};\n' for n in forward_decl_vecs)

	#
	f.source += ''.join(f'#include "{n}.hpp"\n' for n in forward_decl_vecs)

	f.source += '\nnamespace vector {\n\n'

	def row_major(cell_format):	return ',\n'.join(', '.join(cell_format.format(c=c,r=r) for c in range(size[1])) for r in range(size[0]))
	def col_major(cell_format):	return ',\n'.join(', '.join(cell_format.format(c=c,r=r) for r in range(size[0])) for c in range(size[1]))
	
	def row_vec_cells(cell_format):	return ',\n'.join(f'{RV}(%s)' % ', '.join(cell_format.format(c=c,r=r) for c in range(size[1])) for r in range(size[0]))
	def col_vec_cells(cell_format):	return ',\n'.join(f'{V}(%s)' % ', '.join(cell_format.format(c=c,r=r) for r in range(size[0])) for c in range(size[1]))

	def row_vecs(vec_format):	return ', '.join(vec_format.format(r=r) for r in range(size[0]))
	def col_vecs(vec_format):	return ', '.join(vec_format.format(c=c) for c in range(size[1]))

	def elementwise(op_format):
		return f'return {M}(%s);' % row_major(op_format)
	
	################
	f.header += f'''
		struct {M} {{
			{V} arr[{size[1]}]; // column major for compatibility with OpenGL
		\n'''
		
	f += '//// Accessors\n\n'
	#src += method(f, f'{M}', f'{T}&', 'get', F'int r, int c', 'return arr[c][r];', comment='get cell with r,c indecies (r=row, c=column)')
	f.method(f'{M}', f'{T} const&', 'get', F'int r, int c', 'return arr[c][r];', const=True, comment='get cell with r,c indecies (r=row, c=column)', forceinline=True)

	#f.method(f'{M}', f'{V}&', 'get_column', F'int indx', 'return arr[indx];', comment='get matrix column')
	f.method(f'{M}', f'{V} const&', 'get_column', F'int indx', 'return arr[indx];', const=True, comment='get matrix column', forceinline=True)
	
	f.method(f'{M}', f'{RV}', 'get_row', F'int indx', f'return {RV}(%s);' % ', '.join(f'arr[{c}][indx]' for c in range(size[1])),
		const=True, comment='get matrix row')
	
	f += '\n//// Constructors\n\n'
	f.constructor(f'{M}', '', forceinline=True)

	f.constructor(f'{M}', args=f'{T} all',						explicit=True, init_list='\narr{%s}' % col_vec_cells('all'),		forceinline=True, comment='supply one value for all cells')
	f.constructor(f'{M}', args=row_major(str(T) +' c{r}{c}'),	explicit=True, init_list='\narr{%s}' % col_vec_cells('c{r}{c}'),	forceinline=True, comment='supply all cells, in row major order for readability -> c<r><c> (r=row, c=column)')
	
	f += '\n// static rows() and columns() methods are preferred over constructors, to avoid confusion if column or row vectors are supplied to the constructor\n'
	
	f.static_method(f'{M}', f'{M}', 'rows',	args=row_vecs(str(RV) +' row{r}'), body=f'return {M}(%s);' % row_major('row{r}[{c}]'),
		comment='supply all row vectors')
	f.static_method(f'{M}', f'{M}', 'rows',	args=row_major(str(T) +' c{r}{c}'), body=f'return {M}(%s);' % row_major('c{r}{c}'),
		comment='supply all cells in row major order')

	f.static_method(f'{M}', f'{M}', 'columns',	args=col_vecs(str(V) +' col{c}'), body=f'return {M}(%s);' % row_major('col{c}[{r}]'),
		comment='supply all column vectors')
	f.static_method(f'{M}', f'{M}', 'columns',	args=col_major(str(T) +' c{r}{c}'), body=f'return {M}(%s);' % row_major('c{r}{c}'),
		comment='supply all cells in column major order')

	f += '\n'
	f.static_method(f'{M}', f'{M}', 'identity', args='', forceinline=True,
		comment='identity matrix',
		body=f'return {M}(%s);' % ',\n'.join(','.join('1' if x==y else '0' for x in range(size[1])) for y in range(size[0])))
	
	f += '\n// Casting operators\n\n'
	for m in other_size_mats:
		def cell(r,c):
			if r<size[1] and c<size[0]:
				return f'arr[{r}][{c}]'
			else:
				return '        1' if r == c else '        0'

		f.method(f'{M}', '', f'operator {m.name}', '', explicit=True, const=True,
			comment='extend/truncate matrix of other size',
			body=f'return {m.name}(%s);' % ',\n'.join(', '.join(cell(c,r) for c in range(m.size[1])) for r in range(m.size[0])))

	for m in other_type_mats:
		f.method(f'{M}', '', f'operator {m.name}', '', explicit=True, const=True,
			comment='typecast',
			body=f'return {m.name}(%s);' % ',\n'.join(', '.join(f'({m.scalar_type})arr[{r}][{c}]' for c in range(m.size[1])) for r in range(m.size[0])))
	
	f += '\n// Elementwise operators\n\n'

	for op in ['+', '-', '*', '/']:
		f.method(f'{M}', f'{M}&', f'operator{op}=', f'{T} r', f'*this = *this {op} r;\nreturn *this;')
		
	f += '\n// Matrix multiplication\n\n'

	f.method(f'{M}', f'{M}&', 'operator*=', f'{M} {mpass} r', '*this = *this * r;\nreturn *this;')
		
	f.header += '};\n'

	f += '\n// Elementwise operators\n\n'
	
	for op in ['+', '-']:
		f.function(f'{M}', 'operator'+ op, f'{M} {mpass} m', elementwise(op +'m.arr[{c}][{r}]'))
		
	for op in ['+', '-', '*', '/']:
		f += '\n'

		name = f'operator{op}'

		if op == '*':	name = 'mul_elementwise'
		elif op == '/':	name = 'div_elementwise'

		f.function(f'{M}', name, f'{M} {mpass} l, {M} {mpass} r', elementwise(f'l.arr[{{c}}][{{r}}] {op} r.arr[{{c}}][{{r}}]'))
		f.function(f'{M}', f'operator{op}', f'{M} {mpass} l, {T} r', elementwise(f'l.arr[{{c}}][{{r}}] {op} r'))
		f.function(f'{M}', f'operator{op}', f'{T} l, {M} {mpass} r', elementwise(f'l {op} r.arr[{{c}}][{{r}}]'))
	
	f += '\n// Matrix ops\n\n'

	dims = ['x', 'y', 'z', 'w']
	def matmul(op, m=None):
		nonlocal f
		if op == 'mm':
			if M.scalar_type != m.scalar_type or size[1] != m.size[0]:
				return
			if not type_exist(T, (size[0], m.size[1])):
				f += f'// {M} * {m} -> {size[0]}x{m.size[1]} ; matrix not implemented\n'
				return

			ret = get_type(T, (size[0], m.size[1])).name
			args = f'{M} {mpass} l, {m} {mpass} r'
			body = f'{ret} ret;\n%s\nreturn ret;' % '\n'.join(f'ret.arr[{c}] = l * r.arr[{c}];' for c in range(m.size[1]))
		elif op == 'mv':
			ret = f'{V}'
			args = f'{M} {mpass} l, {RV} r'
			body = f'{V} ret;\n%s\nreturn ret;' % '\n'.join(f'ret.{dims[r]} = %s;' % ' + '.join(f'l.arr[{c}].{dims[r]} * r.{dims[c]}' for c in range(size[1])) for r in range(size[0]))
		elif op == 'vm':
			ret = f'{RV}'
			args = f'{V} l, {M} {mpass} r'
			body = f'{RV} ret;\n%s\nreturn ret;' % '\n'.join(f'ret.{dims[c]} = %s;' % ' + '.join(f'l.{dims[r]} * r.arr[{c}].{dims[r]}' for r in range(size[0])) for c in range(size[1]))
		f.function(ret, 'operator*', args, body)
	def matmul_shortform(op, r):
		nonlocal f
		if r == None:
			return
		if op == 'mm':
			sqr = get_type(T, (size[1],size[1]))
		
			f.function(f'{M}', 'operator*', f'{M} {mpass} l, {r} {mpass} r', f'''
				return l * ({sqr})r;
			''', comment=f'{M} * {r} = {M}, shortform for {M} * ({sqr}){r} = {M}')
		elif op == 'mv':
			v = get_type(T, size[1])
		
			f.function(f'{r}', 'operator*', f'{M} {mpass} l, {r} r', f'''
				return l * {v}(r, 1);
			''', comment=f'{M} * {r} = {r}, shortform for {M} * {v}({r}, 1) = {r}')
			

	for m in all_matricies:
		matmul('mm', m)
	matmul('mv')
	matmul('vm')
	
	if size[0] == size[1]-1:
		f += f'\n// Matrix op shortforms for working with {size[0]}x{size[0]+1} matricies as {size[0]}x{size[0]} matricies plus translation\n\n'

		matmul_shortform('mm', get_type(T, (size[0],size[0])))
		matmul_shortform('mm', get_type(T, size))

		matmul_shortform('mv', get_type(T, size[0]))

	if type_exist(T, (size[1], size[0])):
		m = get_type(T, (size[1], size[0]))
		f.function(m, 'transpose', f'{M} {mpass} m', f'return {m}::rows(%s);' % ', '.join( f'm.arr[{c}]' for c in range(size[1]) ))

	if size[0] == size[1]:
		f += '\n'

		import matrix_stuff as ms

		f.source += ms.define_letterify(T, size[0]) + '\n'

		f.function(f'{T}', 'det', f'{M} {mpass} mat', ms.gen_determinate_code(T, size[0]))
		f.function(f'{M}', 'inverse', f'{M} {mpass} mat', ms.gen_inverse_code(M, T, size[0]))
		
		f.source += '\n#undef LETTERIFY\n\n'

	f += '} // namespace vector\n'

for tmat in matricies:
	for m in tmat:
		gen_matrix(m, gen.add_file(m.name))

def transformations(f):
	src = ''

	f.header += '#include "vector.hpp"\n\n'
		
	f += 'namespace vector {\n\n'

	f.function('fm2', 'scale', 'fv2 v', '''
		return fm2(
			v.x,   0,
			  0, v.y
		);
	''')
	f.function('fm2x3', 'translate', 'fv2 v', '''
		return fm2x3(
			1, 0, v.x,
			0, 1, v.y
		);
	''')
	
	f += '\n'

	f.function('fm3', 'scale', 'fv3 v', '''
		return fm3(
			v.x,   0,   0,
			  0, v.y,   0,
			  0,   0, v.z
		);
	''')
	f.function('fm3x4', 'translate', 'fv3 v', '''
		return fm3x4(
			1, 0, 0, v.x,
			0, 1, 0, v.y,
			0, 0, 1, v.z
		);
	''')
	
	f += '} // namespace vector\n'

transformations(gen.add_file('transformations'))

def main(f):
	# main file to include
	
	f.header += '#include "kissmath.hpp"\n\n'
	
	f.header += '// Vectors\n'
	for tvec in vectors:
		for v in tvec:
			f.header += f'#include "{v.name}.hpp"\n'

		f.header += '\n'
			
	f.header += '// Matricies\n'
	for tmat in matricies:
		for m in tmat:
			f.header += f'#include "{m.name}.hpp"\n'

		f.header += '\n'
		
	#s.include('fquat', nl=1)
	#
	#s.include('lrgb')
	#s.include('lrgba', nl=2)

	f.header += 'using namespace vector;\n\n'

	f.header += "// Typedefs that define 'standard' floats to use across program\n"
	f.header += 'typedef float flt;\n\n'

	for v in all_vectors:
		if v.scalar_type.name == 'f32':
			f.header += f'typedef {v} v{v.size};\n'

	for m in all_matricies:
		if m.scalar_type.name == 'f32':
			f.header += f'typedef {m} {m.name[1:]};\n'
				
	f.header += '\n#include "transformations.hpp"\n\n'
	
main(gen.add_file('vector'))

gen.write_files()
