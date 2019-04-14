import srcgen

floats = ['f32', 'f64']
ints = ['s8', 's32', 's64']
uints = ['u8', 'u32', 'u64']

scalars = floats + ints + uints


global_vars = { k:v for k,v in globals().items() if k in ['floats', 'ints', 'uints', 'scalars'] }

hello = 5

def kissmath():
	


	format = '''
		#include "types.hpp"
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
		#define INFd		F64_INF
		#define INF			F32_INF
		#define QNANd		F64_QNAN
		#define QNAN		F32_QNAN
		#define PId			3.1415926535897932384626433832795
		#define PI			3.1415926535897932384626433832795f
		#define TAUd		6.283185307179586476925286766559
		#define TAU			6.283185307179586476925286766559f
		#define SQRT_2d		1.4142135623730950488016887242097
		#define SQRT_2		1.4142135623730950488016887242097f
		#define EULERd		2.7182818284590452353602874713527
		#define EULER		2.7182818284590452353602874713527f
		#define DEG_TO_RADd	0.01745329251994329576923690768489	// 180/PI
		#define DEG_TO_RAD	0.01745329251994329576923690768489f
		#define RAD_TO_DEGd	57.295779513082320876798154814105	// PI/180
		#define RAD_TO_DEG	57.295779513082320876798154814105f

		// Scalar math
		${'for T in scalars:
			${generic_math_funcs}
		'}
	'''
	
	def function(c, ret, name, args, body):
		body = body.strip()
		
		if c.header:
			return f'{ret} {name} ({args});\n'
		else:
			return f'''{ret} {name} ({args}) {{
				{body}
			}}\n'''

	generic_math_funcs = """
	${function(c, T, 'mymod', f'{T} x, {T} y', f'''
		// BLah 1
		T modded = '''+ ('std::fmod(x, y)' if T in floats else 'x % y') +''';
		if (range > 0) {
			if (modded < 0) modded += range;
		} else {
			if (modded > 0) modded -= range;
		}
		return modded;
	''')}

	// BLah 2
	${function(c, T, 'mymod', f'{T} x, {T} y', f'''
		T modded = '''+ ('std::fmod(x, y)' if T in floats else 'x % y') +''';
		if (range > 0) {
			if (modded < 0) modded += range;
		} else {
			if (modded > 0) modded -= range;
		}
		return modded;
	''')}
	"""

	srcgen.write_metacode('kissmath', generic_math_funcs, **global_vars, T='blah', function=function, generic_math_funcs=generic_math_funcs)
	
kissmath()