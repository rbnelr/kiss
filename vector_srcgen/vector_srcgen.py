import srcgen
from collections import namedtuple

def util(header):
	if header:
		return \
	''' #define STRINGIFY(x) #x
		#define TO_STRING(x) STRINGIFY(x)

		#define CONCAT(a,b) a##b

		#define STATIC_ASSERT(cond) static_assert((cond), STRINGIFY(cond))

		#define ARRLEN(arr) (sizeof(arr) / sizeof(arr[0]))

		#define EVEN(i)			(((i) % 2) == 0)
		#define ODD(i)			(((i) % 2) == 1)

		#define BOOL_XOR(a, b)	(((a) != 0) != ((b) != 0))
		'''
	else:
		return ''

srcgen.generate('util', util)

def types(header):
	if header:
		return \
	''' typedef signed char			schar;
		typedef unsigned char		uchar;
		typedef short				sshort;
		typedef unsigned short		ushort;
		typedef int					sint;
		typedef unsigned int		uint;
		typedef long				slong;
		typedef unsigned long		ulong;
		typedef long long			sllong;
		typedef unsigned long long	ullong;

		#include "stdint.h"

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
		'''
	else:
		return ''

srcgen.generate('types', types)

floats = ['f32', 'f64']
ints = ['s32', 's64', 's8']
uints = ['u32', 'u64', 'u8']

scalars = floats + ints + uints

float_const = {'f32':'', 'f64':'d'} # postfix of Math constants

#
vec = namedtuple('vec', 'name type size conversions')

vec_sizes = [2,3,4]

vectors = [
	[vec(f'bv{s}',	 type='bool',	size=s, conversions=[]) for s in vec_sizes],

	[vec(f'fv{s}',	 type='f32',	size=s, conversions=[f'iv{s}', f's64v{s}', f'u8v{s}']) for s in vec_sizes],
	[vec(f'dv{s}',	 type='f64',	size=s, conversions=[f'iv{s}', f's64v{s}', f'u8v{s}']) for s in vec_sizes],
	[vec(f'iv{s}',	 type='int',	size=s, conversions=[f'fv{s}', f'dv{s}']) for s in vec_sizes],
	[vec(f's64v{s}', type='s64',	size=s, conversions=[f'fv{s}', f'dv{s}']) for s in vec_sizes],
	[vec(f'u8v{s}',	 type='u8',		size=s, conversions=[f'fv{s}', f'dv{s}']) for s in vec_sizes],
]

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

def _function(ret, name, args, body, header, clsname=None, init_list=None, comment=None, const=False):
	body = body.strip()
	comment = ''.join('// '+ comment.strip() + '\n' for l in comment.splitlines()) if comment else ''

	clsname = f'{clsname}::' if clsname else ''
	init_list = f': {init_list}' if init_list else ''

	const = ' const' if const else ''

	if header:
		return comment + f'{ret} {name} ({args}){const};\n'
	else:
		if '=' in args:
			import re
			args = re.sub(r'=.*?(?=(?:,|$))', '', args)

		return f'''\n{ret} {clsname}{name} ({args}){const}{init_list} {{
			{body}
		}}\n'''
def _method(clsname, *args, **kwargs):
	return _function(*args, clsname=clsname, **kwargs)
def _constructor(clsname, args, body='', init_list=None, ret='', **kwargs):
	return _function(ret, clsname, args, body, clsname=clsname, init_list=init_list, **kwargs)

def kissmath(header):
	src = ''

	if header:
		src += \
		''' #include "types.hpp"
			#include "util.hpp"
			#include <cmath>
		
			// windows.h defines min and max by default
			#undef min
			#undef max
		
			// Use std math functions for these
			using std::sin;
			using std::cos;
			using std::floor;
			using std::ceil;
			using std::pow;
			using std::round;
			
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
		
		src += scalar_math(T, header)
		src += generic_math(T, header)

	return src

def scalar_math(T, header):
	src = ''
	
	def function(*args, **kwargs):	return _function(*args, header=header, **kwargs)

	BT = bool_type(T)
	
	IT = f2i_scalar(T) or T # int scalar for roundi funcs

	src += function(T, 'wrap', f'{T} x, {T} range', f'''
		{T} modded = '''+ ('std::fmod(x, range)' if T in floats else 'x % range') +''';
		if (range > 0) {
			if (modded < 0) modded += range;
		} else {
			if (modded > 0) modded -= range;
		}
		return modded;
	''', comment='wrap x into range [0,range), negative x wrap back to +range unlike c++ % operator, negative range supported')

	src += function(T, 'wrap', f'{T} x, {T} a, {T} b', f'''
		x -= a;
		{T} range = b -a;
			
		{T} modulo = wrap(x, range);
			
		return modulo + a;
	''', comment='wrap x into [a,b) range')
		
	if T in floats:
		src += function(T, 'wrap', f'{T} x, {T} a, {T} b, {T}* quotient', f'''
			x -= a;
			{T} range = b -a;
			
			{T} modulo = wrap(x, range);
			*quotient = floor(x / range);
			
			return modulo + a;
		''')
		src += '\n'
			
		src += function(IT, 'floori',	f'{T} x', f'return ({IT})floor(x);')
		src += function(IT, 'ceili',	f'{T} x', f'return ({IT})ceil(x);')
		src += function(IT, 'roundi',	f'{T} x', f'return '+ {'f32':'std::lround(x)', 'f64':'std::llround(x)'}[T] +';')
			
		src += '\n'

	min_func = 'std::fmin(l,r)' if T in floats else f'l <= r ? l : r'
	max_func = 'std::fmax(l,r)' if T in floats else f'l >= r ? l : r'
		
	src += function(T, 'min',		f'{T} l, {T} r',			f'return {min_func};')
	src += function(T, 'max',		f'{T} l, {T} r',			f'return {max_func};')
	src += function(T, 'clamp',		f'{T} x, {T} a=0, {T} b=1',	f'return min(max(x,a), b);')
	src += function(T, 'select',	f'{BT} c, {T} l, {T} r',	f'return c ? l : r;', comment='equivalent to ternary c ? l : r, for conformity with vectors')

	src += '\n'

	abs_func = f'std::fabs(x)' if T in floats else f'std::abs(x)'
		
	if T not in uints: # no abs for unsigned types
		src += function(T, 'length',		f'{T} x',	f'return {abs_func};', comment="length(scalar) = abs(scalar), for conformity with vectors")
		src += function(T, 'length_sqr',	f'{T} x',	f'x = {abs_func};\nreturn x*x;', comment="length_sqr(scalar) = abs(scalar)^2, for conformity with vectors (for vectors this func would save the sqrt)")
			
		src += function(T, 'normalize',		f'{T} x',	f'return x / length(x);', comment="normalize(-6.2f) = -1f, normalize(7) = 1, normalize(0) = <div 0>, can be useful")
		
		src += function(T, 'normalize_or_zero', f'{T} x', f'''
			{T} len = length(x);
			if (len == {T}(0)) {{
				return {T}(0);
			}}
			return x /= len;
		''', comment='normalize(x) for length(x) != 0 else 0')

		src += '\n'

	return src

def generic_math(T, header):
	src = ''
	
	def function(*args, **kwargs):	return _function(*args, header=header, **kwargs)

	ST = scalar_type.get(T, None)
	
	if ST in floats:

		src += function(T, 'lerp',	f'{T} a, {T} b, {T} t',				f'return a * ({T}(1) - t) + b * t;', comment='linear interpolation t=0 -> a ; t=1 -> b ; t=0.5 -> (a+b)/2')
		src += function(T, 'map',	f'{T} x, {T} in_a, {T} in_b',		f'return (x - in_a) / (in_b - in_a);', comment='linear mapping (reverse linear interpolation), map(70, 0,100) -> 0.7 ; map(0.5, -1,+1) -> 0.75')
		src += function(T, 'map',	f'{T} x, {T} in_a, {T} in_b, {T} out_a, {T} out_b',		f'return lerp(out_a, out_b, map(x, in_a, in_b));', comment='linear mapping, lerp(out_a, out_b, map(x, in_a, in_b))')

		src += function(T, 'smoothstep',	f'{T} x', f'''
			{T} t = clamp(x);
			return t * t * ({T}(3) - {T}(2) * t);
		''')
			
		src += function(T, 'bezier',		f'{T} a, {T} b, {T} c, {ST} t', f'''
			{T} d = lerp(a, b, t);
			{T} e = lerp(b, c, t);
			{T} f = lerp(d, e, t);
			return f;
		''')
		src += function(T, 'bezier',		f'{T} a, {T} b, {T} c, {T} d, {ST} t', f'''
			return bezier(
							lerp(a, b, t),
							lerp(b, c, t),
							lerp(c, d, t),
							t
						);
		''')
		src += function(T, 'bezier',		f'{T} a, {T} b, {T} c, {T} d, {T} e, {ST} t', f'''
			return bezier(
							lerp(a, b, t),
							lerp(b, c, t),
							lerp(c, d, t),
							lerp(d, e, t),
							t
						);
		''')
		
		src += '\n//// angle stuff\n'
		src += function(f'constexpr {T}', 'to_rad',	f'{T} deg', f'return deg * DEG_TO_RAD{float_const[ST]};')
		src += function(f'constexpr {T}', 'deg',	f'{T} deg', f'return deg * DEG_TO_RAD{float_const[ST]};', comment='degress "literal", converts degrees to radiants')
		src += function(f'constexpr {T}', 'to_deg',	f'{T} rad', f'return rad * RAD_TO_DEG{float_const[ST]};')
		
	return src

srcgen.generate('kissmath', kissmath)

def gen_vector(vec, header):
	V, T, size, conversions = vec

	all_dims = ('x', 'y', 'z', 'w')
	dims = all_dims[:size]
	
	FT = i2f_scalar(vec) or T # Float scalar for length ops
	
	FV = i2f_type(vec) # Float vec for normalize ops
	FV = FV.name if FV else V

	IV = f2i_type(vec) # Int vec for roundi funcs
	IV = IV.name if IV else V

	BV = bool_type(vec).name


	src = ''
	
	def function(*args, **kwargs):	return _function(*args, header=header, **kwargs)
	def method(*a, **kwargs):		return _method(*a, header=header, **kwargs)
	def constructor(*a, **kwargs):	return _constructor(*a, header=header, **kwargs)
	
	def unary_op(op):
		tmp = ', '.join(f'{op}v.{d}' for d in dims)
		return function(f'constexpr {V}', f'operator{op}', f'{V} v', f'return {V}({tmp});')
	def binary_op(op):
		tmp = ', '.join(f'l.{d} {op} r.{d}' for d in dims)
		return function(f'constexpr {V}', f'operator{op}', f'{V} l, {V} r', f'return {V}({tmp});')
	def comparison_op(op):
		tmp = ', '.join(f'l.{d} {op} r.{d}' for d in dims)
		return function(f'constexpr {BV}', f'operator{op}', f'{V} l, {V} r', f'return {BV}({tmp});')
	
	def unary_func(func, arg='v', ret=None):
		ret = ret or V
		return function(f'{ret}', func, f'{V} {arg}', f'return {ret}(%s);' % ', '.join(f'{func}({arg}.{d})' for d in dims))
	def nary_func(func, args):
		return function(f'{V}', func, ', '.join(f'{V} {a}' for a in args),
			f'return {V}(%s);' % ', '.join(f'{func}(%s)' % ','.join(f'{a}.{d}' for a in args) for d in dims))

	def compound_binary_op(op):
		if False: # compact
			tmp = ', '.join(f'{d} {op} r.{d}' for d in dims)
			body = f'return *this = {V}({tmp});'
		else:
			body = ''.join(f'{d} {op}= r.{d};\n' for d in dims) + 'return *this;'

		return method(V, V, f'operator{op}=', f'{V} r', body)

	def conversion_op(to_type):
		tt = scalar_type[to_type]

		tmp = ', '.join(f'({tt}){d}' for d in dims)
		body = f'return {to_type}({tmp});'
		
		return method(V, '', f'operator {to_type}', '', body, const=True)

	forward_decl_vecs = [get_vector(T, sz).name for sz in vec_sizes if sz != size] + [BV] + conversions
	if header:
		src += '#include "kissmath.hpp"\n\n'
		
		src += '//// forward declarations\n'
		src += ''.join(f'union {n};\n' for n in forward_decl_vecs)

	else:
		src += ''.join(f'#include "{n}.hpp"\n' for n in forward_decl_vecs)

	if header:
		src += f'''
		union {V} {{
			struct {{
				{T}	{', '.join(dims)};
			}};
			{T}		arr[{size}];

		'''
		
	src += method(V, f'{T}&', 'operator[]', 'int i', 'return arr[i];')
	src += method(V, f'{T}', 'operator[]', 'int i', 'return arr[i];', const=True)

	src += '\n'
	
	src += constructor(V, args='')
	src += constructor(V, ret='constexpr', args=f'{T} all',							 init_list=', '.join(f'{d}{{all}}' for d in dims),
		comment='sets all components to one value')
	src += constructor(V, ret='constexpr', args=', '.join(f'{T} {d}' for d in dims), init_list=', '.join(f'{d}{{{d}}}' for d in dims),
		comment='supply all components')
	
	for vsz in range(2,size):
		U = get_vector(T, vsz).name
		u = ''.join(dims[:vsz])

		src += constructor(V, ret='constexpr', comment='extend vector',
					 args=', '.join([f'{U} {u}'] + [f'{T} {d}' for d in dims[vsz:]]),
					 init_list=', '.join([f'{d}{{{u}.{d}}}' for d in dims[:vsz]] + [f'{d}{{{d}}}' for d in dims[vsz:]]))

	for vsz in range(size+1,vec_sizes[-1]+1):
		U = get_vector(T, vsz).name

		src += constructor(V, ret='constexpr', comment='truncate vector',
					 args=f'{U} v',
					 init_list=', '.join(f'{d}{{v.{d}}}' for d in dims[:size]))

	src += '\n'

	if T != 'bool':
		for op in ('+', '-', '*', '/'):
			src += compound_binary_op(op)
			
		src += '\n'
		
		src += '//// Conversion operators\n'
		for to_vec in conversions:
			src += conversion_op(to_vec)

	if header:
		src += '};\n'
	
	if T == 'bool':
		src += '\n//// reducing ops\n'
		
		src += function(f'constexpr {T}', 'all', f'{V} v', 'return %s;' % ' && '.join(f'v.{d}' for d in dims), comment='all components are true')
		src += function(f'constexpr {T}', 'any', f'{V} v', 'return %s;' % ' || '.join(f'v.{d}' for d in dims), comment='any components is true')
		
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
	src += function(f'constexpr bool', 'equal', f'{V} l, {V} r', 'return all(l == r);', comment='vectors are equal, equivalent to all(l == r)')
	
	src += function(f'constexpr {V}', 'select', f'{V} c, {V} l, {V} r', 'return %s;' % ', '.join(f'c.{d} ? l.{d} : r.{d}' for d in dims),
		comment='componentwise ternary c ? l : r')
	
	if T != 'bool':
		src += '\n//// misc ops\n'
		
		src += unary_func('abs')
		
		src += nary_func('min', ('l', 'r'))
		src += nary_func('max', ('l', 'r'))

		src += function(V, 'clamp', f'{V} x, {V} a={V}(0), {V} b={V}(1)', f'return min(max(x,a), b);')
		
		def minmax_component(mode):
			op = {'min':'<=', 'max':'>='}[mode]
			return function(T, f'{mode}_component', f'{V} v, int* {mode}_index=nullptr', f'''
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

		src += '\n//// linear algebra ops\n'
		
		src += function(FT, 'length', f'{V} v',				f'return sqrt(({FT})(%s));' % ' + '.join(f'v.{d} * v.{d}' for d in dims), comment='magnitude of vector')
		src += function(T, 'length_sqr', f'{V} v',			f'return %s;' % ' + '.join(f'v.{d} * v.{d}' for d in dims), comment='squared magnitude of vector, cheaper than length() because it avoids the sqrt(), some algorithms only need the squared magnitude')
		src += function(FT, 'distance', f'{V} a, {V} b',	f'return length(a - b);', comment='distance between points, equivalent to length(a - b)')
		src += function(FV, 'normalize', f'{V} v',			f'return {FV}(v) / length(v);', comment='normalize vector so that it has length() = 1, undefined for zero vector')
		src += function(FV, 'normalize_or_zero', f'{V} v', f'''
			{FT} len = length(v);
			if (len == {FT}(0)) {{
				return {FT}(0);
			}}
			return {FV}(v) / {FV}(len);
		''', comment='normalize vector so that it has length() = 1, returns zero vector if vector was zero vector')
		
		src += '\n'

		src += generic_math(V, header)

	return src

for tvec in vectors:
	for v in tvec:
		srcgen.generate(v.name, lambda header: gen_vector(v, header))

def main(header):
	# main file to include
	
	src = ''

	if header:
		src += '#include "kissmath.hpp"\n\n'
		
		src += '// Vectors\n'
		for tvec in vectors:
			for v in tvec:
				src += f'#include "{v.name}.hpp"\n'

			src += '\n'

		#s.include('m2')
		#s.include('m3')
		#s.include('m4', nl=1)
		#
		#s.include('fquat', nl=1)
		#
		#s.include('lrgb')
		#s.include('lrgba', nl=2)

		3
		src += "// Typedefs that define 'standart' floats to use across program\n"
		src += 'typedef float flt;\n\n'

		src += 'typedef fv2 v2;\n'
		src += 'typedef fv3 v3;\n'
		src += 'typedef fv4 v4;\n'

	return src
	
srcgen.generate('vector', main)