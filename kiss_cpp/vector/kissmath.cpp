// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#include "kissmath.hpp"


namespace vector {
	
	
	////// Scalar math ///////
	
	//// f32
	
	
	// wrap x into range [0,range), negative x wrap back to +range unlike c++ % operator, negative range supported
	f32 wrap (f32 x, f32 range) {
		f32 modded = std::fmod(x, range);
		if (range > 0) {
			if (modded < 0) modded += range;
		} else {
			if (modded > 0) modded += range;
		}
		return modded;
	}
	
	// wrap x into [a,b) range
	f32 wrap (f32 x, f32 a, f32 b) {
		x -= a;
		f32 range = b -a;
		
		f32 modulo = wrap(x, range);
		
		return modulo + a;
	}
	
	f32 wrap (f32 x, f32 a, f32 b, s32* quotient) {
		x -= a;
		f32 range = b -a;
		
		f32 modulo = wrap(x, range);
		*quotient = floori(x / range);
		
		return modulo + a;
	}
	
	
	s32 floori (f32 x) {
		return (s32)floor(x);
	}
	
	s32 ceili (f32 x) {
		return (s32)ceil(x);
	}
	
	s32 roundi (f32 x) {
		return std::lround(x);
	}
	
	
	f32 min (f32 l, f32 r) {
		return std::fmin(l,r);
	}
	
	f32 max (f32 l, f32 r) {
		return std::fmax(l,r);
	}
	
	f32 clamp (f32 x, f32 a, f32 b) {
		return min(max(x,a), b);
	}
	
	// equivalent to ternary c ? l : r, for conformity with vectors
	f32 select (bool c, f32 l, f32 r) {
		return c ? l : r;
	}
	
	
	// length(scalar) = abs(scalar), for conformity with vectors
	f32 length (f32 x) {
		return std::fabs(x);
	}
	
	// length_sqr(scalar) = abs(scalar)^2, for conformity with vectors (for vectors this func would save the sqrt)
	f32 length_sqr (f32 x) {
		x = std::fabs(x);
		return x*x;
	}
	
	// normalize(-6.2f) = -1f, normalize(7) = 1, normalize(0) = <div 0>, can be useful
	f32 normalize (f32 x) {
		return x / length(x);
	}
	
	// normalize(x) for length(x) != 0 else 0
	f32 normalize_or_zero (f32 x) {
		f32 len = length(x);
		if (len == f32(0)) {
			return f32(0);
		}
		return x /= len;
	}
	
	
	// linear interpolation t=0 -> a ; t=1 -> b ; t=0.5 -> (a+b)/2
	f32 lerp (f32 a, f32 b, f32 t) {
		return a * (f32(1) - t) + b * t;
	}
	
	// linear mapping (reverse linear interpolation), map(70, 0,100) -> 0.7 ; map(0.5, -1,+1) -> 0.75
	f32 map (f32 x, f32 in_a, f32 in_b) {
		return (x - in_a) / (in_b - in_a);
	}
	
	// linear mapping, lerp(out_a, out_b, map(x, in_a, in_b))
	f32 map (f32 x, f32 in_a, f32 in_b, f32 out_a, f32 out_b) {
		return lerp(out_a, out_b, map(x, in_a, in_b));
	}
	
	//// angle stuff
	
	f32 to_rad (f32 deg) {
		return (f32)deg * DEG_TO_RAD;
	}
	
	// degress "literal", converts degrees to radiants
	f32 deg (f32 deg) {
		return (f32)deg * DEG_TO_RAD;
	}
	
	f32 to_deg (f32 rad) {
		return (f32)rad * RAD_TO_DEG;
	}
	
	//// f64
	
	
	// wrap x into range [0,range), negative x wrap back to +range unlike c++ % operator, negative range supported
	f64 wrap (f64 x, f64 range) {
		f64 modded = std::fmod(x, range);
		if (range > 0) {
			if (modded < 0) modded += range;
		} else {
			if (modded > 0) modded += range;
		}
		return modded;
	}
	
	// wrap x into [a,b) range
	f64 wrap (f64 x, f64 a, f64 b) {
		x -= a;
		f64 range = b -a;
		
		f64 modulo = wrap(x, range);
		
		return modulo + a;
	}
	
	f64 wrap (f64 x, f64 a, f64 b, s64* quotient) {
		x -= a;
		f64 range = b -a;
		
		f64 modulo = wrap(x, range);
		*quotient = floori(x / range);
		
		return modulo + a;
	}
	
	
	s64 floori (f64 x) {
		return (s64)floor(x);
	}
	
	s64 ceili (f64 x) {
		return (s64)ceil(x);
	}
	
	s64 roundi (f64 x) {
		return std::llround(x);
	}
	
	
	f64 min (f64 l, f64 r) {
		return std::fmin(l,r);
	}
	
	f64 max (f64 l, f64 r) {
		return std::fmax(l,r);
	}
	
	f64 clamp (f64 x, f64 a, f64 b) {
		return min(max(x,a), b);
	}
	
	// equivalent to ternary c ? l : r, for conformity with vectors
	f64 select (bool c, f64 l, f64 r) {
		return c ? l : r;
	}
	
	
	// length(scalar) = abs(scalar), for conformity with vectors
	f64 length (f64 x) {
		return std::fabs(x);
	}
	
	// length_sqr(scalar) = abs(scalar)^2, for conformity with vectors (for vectors this func would save the sqrt)
	f64 length_sqr (f64 x) {
		x = std::fabs(x);
		return x*x;
	}
	
	// normalize(-6.2f) = -1f, normalize(7) = 1, normalize(0) = <div 0>, can be useful
	f64 normalize (f64 x) {
		return x / length(x);
	}
	
	// normalize(x) for length(x) != 0 else 0
	f64 normalize_or_zero (f64 x) {
		f64 len = length(x);
		if (len == f64(0)) {
			return f64(0);
		}
		return x /= len;
	}
	
	
	// linear interpolation t=0 -> a ; t=1 -> b ; t=0.5 -> (a+b)/2
	f64 lerp (f64 a, f64 b, f64 t) {
		return a * (f64(1) - t) + b * t;
	}
	
	// linear mapping (reverse linear interpolation), map(70, 0,100) -> 0.7 ; map(0.5, -1,+1) -> 0.75
	f64 map (f64 x, f64 in_a, f64 in_b) {
		return (x - in_a) / (in_b - in_a);
	}
	
	// linear mapping, lerp(out_a, out_b, map(x, in_a, in_b))
	f64 map (f64 x, f64 in_a, f64 in_b, f64 out_a, f64 out_b) {
		return lerp(out_a, out_b, map(x, in_a, in_b));
	}
	
	//// angle stuff
	
	f64 to_rad (f64 deg) {
		return (f64)deg * DEG_TO_RADd;
	}
	
	// degress "literal", converts degrees to radiants
	f64 deg (f64 deg) {
		return (f64)deg * DEG_TO_RADd;
	}
	
	f64 to_deg (f64 rad) {
		return (f64)rad * RAD_TO_DEGd;
	}
	
	//// s32
	
	
	// wrap x into range [0,range), negative x wrap back to +range unlike c++ % operator, negative range supported
	s32 wrap (s32 x, s32 range) {
		s32 modded = x % range;
		if (range > 0) {
			if (modded < 0) modded += range;
		} else {
			if (modded > 0) modded += range;
		}
		return modded;
	}
	
	// wrap x into [a,b) range
	s32 wrap (s32 x, s32 a, s32 b) {
		x -= a;
		s32 range = b -a;
		
		s32 modulo = wrap(x, range);
		
		return modulo + a;
	}
	
	s32 min (s32 l, s32 r) {
		return l <= r ? l : r;
	}
	
	s32 max (s32 l, s32 r) {
		return l >= r ? l : r;
	}
	
	s32 clamp (s32 x, s32 a, s32 b) {
		return min(max(x,a), b);
	}
	
	// equivalent to ternary c ? l : r, for conformity with vectors
	s32 select (bool c, s32 l, s32 r) {
		return c ? l : r;
	}
	
	
	// length(scalar) = abs(scalar), for conformity with vectors
	s32 length (s32 x) {
		return std::abs(x);
	}
	
	// length_sqr(scalar) = abs(scalar)^2, for conformity with vectors (for vectors this func would save the sqrt)
	s32 length_sqr (s32 x) {
		x = std::abs(x);
		return x*x;
	}
	
	// normalize(-6.2f) = -1f, normalize(7) = 1, normalize(0) = <div 0>, can be useful
	s32 normalize (s32 x) {
		return x / length(x);
	}
	
	// normalize(x) for length(x) != 0 else 0
	s32 normalize_or_zero (s32 x) {
		s32 len = length(x);
		if (len == s32(0)) {
			return s32(0);
		}
		return x /= len;
	}
	
	
	f32 to_rad (s32 deg) {
		return (f32)deg * DEG_TO_RAD;
	}
	
	// degress "literal", converts degrees to radiants
	f32 deg (s32 deg) {
		return (f32)deg * DEG_TO_RAD;
	}
	
	f32 to_deg (s32 rad) {
		return (f32)rad * RAD_TO_DEG;
	}
	
	//// s64
	
	
	// wrap x into range [0,range), negative x wrap back to +range unlike c++ % operator, negative range supported
	s64 wrap (s64 x, s64 range) {
		s64 modded = x % range;
		if (range > 0) {
			if (modded < 0) modded += range;
		} else {
			if (modded > 0) modded += range;
		}
		return modded;
	}
	
	// wrap x into [a,b) range
	s64 wrap (s64 x, s64 a, s64 b) {
		x -= a;
		s64 range = b -a;
		
		s64 modulo = wrap(x, range);
		
		return modulo + a;
	}
	
	s64 min (s64 l, s64 r) {
		return l <= r ? l : r;
	}
	
	s64 max (s64 l, s64 r) {
		return l >= r ? l : r;
	}
	
	s64 clamp (s64 x, s64 a, s64 b) {
		return min(max(x,a), b);
	}
	
	// equivalent to ternary c ? l : r, for conformity with vectors
	s64 select (bool c, s64 l, s64 r) {
		return c ? l : r;
	}
	
	
	// length(scalar) = abs(scalar), for conformity with vectors
	s64 length (s64 x) {
		return std::abs(x);
	}
	
	// length_sqr(scalar) = abs(scalar)^2, for conformity with vectors (for vectors this func would save the sqrt)
	s64 length_sqr (s64 x) {
		x = std::abs(x);
		return x*x;
	}
	
	// normalize(-6.2f) = -1f, normalize(7) = 1, normalize(0) = <div 0>, can be useful
	s64 normalize (s64 x) {
		return x / length(x);
	}
	
	// normalize(x) for length(x) != 0 else 0
	s64 normalize_or_zero (s64 x) {
		s64 len = length(x);
		if (len == s64(0)) {
			return s64(0);
		}
		return x /= len;
	}
	
	
	f64 to_rad (s64 deg) {
		return (f64)deg * DEG_TO_RADd;
	}
	
	// degress "literal", converts degrees to radiants
	f64 deg (s64 deg) {
		return (f64)deg * DEG_TO_RADd;
	}
	
	f64 to_deg (s64 rad) {
		return (f64)rad * RAD_TO_DEGd;
	}
	
	//// s8
	
	
	// wrap x into range [0,range), negative x wrap back to +range unlike c++ % operator, negative range supported
	s8 wrap (s8 x, s8 range) {
		s8 modded = x % range;
		if (range > 0) {
			if (modded < 0) modded += range;
		} else {
			if (modded > 0) modded += range;
		}
		return modded;
	}
	
	// wrap x into [a,b) range
	s8 wrap (s8 x, s8 a, s8 b) {
		x -= a;
		s8 range = b -a;
		
		s8 modulo = wrap(x, range);
		
		return modulo + a;
	}
	
	s8 min (s8 l, s8 r) {
		return l <= r ? l : r;
	}
	
	s8 max (s8 l, s8 r) {
		return l >= r ? l : r;
	}
	
	s8 clamp (s8 x, s8 a, s8 b) {
		return min(max(x,a), b);
	}
	
	// equivalent to ternary c ? l : r, for conformity with vectors
	s8 select (bool c, s8 l, s8 r) {
		return c ? l : r;
	}
	
	
	// length(scalar) = abs(scalar), for conformity with vectors
	s8 length (s8 x) {
		return std::abs(x);
	}
	
	// length_sqr(scalar) = abs(scalar)^2, for conformity with vectors (for vectors this func would save the sqrt)
	s8 length_sqr (s8 x) {
		x = std::abs(x);
		return x*x;
	}
	
	// normalize(-6.2f) = -1f, normalize(7) = 1, normalize(0) = <div 0>, can be useful
	s8 normalize (s8 x) {
		return x / length(x);
	}
	
	// normalize(x) for length(x) != 0 else 0
	s8 normalize_or_zero (s8 x) {
		s8 len = length(x);
		if (len == s8(0)) {
			return s8(0);
		}
		return x /= len;
	}
	
	
	f32 to_rad (s8 deg) {
		return (f32)deg * DEG_TO_RAD;
	}
	
	// degress "literal", converts degrees to radiants
	f32 deg (s8 deg) {
		return (f32)deg * DEG_TO_RAD;
	}
	
	f32 to_deg (s8 rad) {
		return (f32)rad * RAD_TO_DEG;
	}
	
	//// u32
	
	
	// wrap x into range [0,range), negative x wrap back to +range unlike c++ % operator, negative range supported
	u32 wrap (u32 x, u32 range) {
		u32 modded = x % range;
		if (range > 0) {
			if (modded < 0) modded += range;
		} else {
			if (modded > 0) modded += range;
		}
		return modded;
	}
	
	// wrap x into [a,b) range
	u32 wrap (u32 x, u32 a, u32 b) {
		x -= a;
		u32 range = b -a;
		
		u32 modulo = wrap(x, range);
		
		return modulo + a;
	}
	
	u32 min (u32 l, u32 r) {
		return l <= r ? l : r;
	}
	
	u32 max (u32 l, u32 r) {
		return l >= r ? l : r;
	}
	
	u32 clamp (u32 x, u32 a, u32 b) {
		return min(max(x,a), b);
	}
	
	// equivalent to ternary c ? l : r, for conformity with vectors
	u32 select (bool c, u32 l, u32 r) {
		return c ? l : r;
	}
	
	
	f32 to_rad (u32 deg) {
		return (f32)deg * DEG_TO_RAD;
	}
	
	// degress "literal", converts degrees to radiants
	f32 deg (u32 deg) {
		return (f32)deg * DEG_TO_RAD;
	}
	
	f32 to_deg (u32 rad) {
		return (f32)rad * RAD_TO_DEG;
	}
	
	//// u64
	
	
	// wrap x into range [0,range), negative x wrap back to +range unlike c++ % operator, negative range supported
	u64 wrap (u64 x, u64 range) {
		u64 modded = x % range;
		if (range > 0) {
			if (modded < 0) modded += range;
		} else {
			if (modded > 0) modded += range;
		}
		return modded;
	}
	
	// wrap x into [a,b) range
	u64 wrap (u64 x, u64 a, u64 b) {
		x -= a;
		u64 range = b -a;
		
		u64 modulo = wrap(x, range);
		
		return modulo + a;
	}
	
	u64 min (u64 l, u64 r) {
		return l <= r ? l : r;
	}
	
	u64 max (u64 l, u64 r) {
		return l >= r ? l : r;
	}
	
	u64 clamp (u64 x, u64 a, u64 b) {
		return min(max(x,a), b);
	}
	
	// equivalent to ternary c ? l : r, for conformity with vectors
	u64 select (bool c, u64 l, u64 r) {
		return c ? l : r;
	}
	
	
	f64 to_rad (u64 deg) {
		return (f64)deg * DEG_TO_RADd;
	}
	
	// degress "literal", converts degrees to radiants
	f64 deg (u64 deg) {
		return (f64)deg * DEG_TO_RADd;
	}
	
	f64 to_deg (u64 rad) {
		return (f64)rad * RAD_TO_DEGd;
	}
	
	//// u8
	
	
	// wrap x into range [0,range), negative x wrap back to +range unlike c++ % operator, negative range supported
	u8 wrap (u8 x, u8 range) {
		u8 modded = x % range;
		if (range > 0) {
			if (modded < 0) modded += range;
		} else {
			if (modded > 0) modded += range;
		}
		return modded;
	}
	
	// wrap x into [a,b) range
	u8 wrap (u8 x, u8 a, u8 b) {
		x -= a;
		u8 range = b -a;
		
		u8 modulo = wrap(x, range);
		
		return modulo + a;
	}
	
	u8 min (u8 l, u8 r) {
		return l <= r ? l : r;
	}
	
	u8 max (u8 l, u8 r) {
		return l >= r ? l : r;
	}
	
	u8 clamp (u8 x, u8 a, u8 b) {
		return min(max(x,a), b);
	}
	
	// equivalent to ternary c ? l : r, for conformity with vectors
	u8 select (bool c, u8 l, u8 r) {
		return c ? l : r;
	}
	
	
	f32 to_rad (u8 deg) {
		return (f32)deg * DEG_TO_RAD;
	}
	
	// degress "literal", converts degrees to radiants
	f32 deg (u8 deg) {
		return (f32)deg * DEG_TO_RAD;
	}
	
	f32 to_deg (u8 rad) {
		return (f32)rad * RAD_TO_DEG;
	}
	
	//// templated math
	
	
} // namespace vector

