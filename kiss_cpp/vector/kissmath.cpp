// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#include "kissmath.hpp"


////// Scalar math ///////

//// f32

f32 wrap (f32 x, f32 range) {
	f32 modded = std::fmod(x, range);
	if (range > 0) {
		if (modded < 0) modded += range;
	} else {
		if (modded > 0) modded -= range;
	}
	return modded;
}

f32 wrap (f32 x, f32 a, f32 b) {
	x -= a;
	f32 range = b -a;
	
	f32 modulo = wrap(x, range);
	
	return modulo + a;
}

f32 wrap (f32 x, f32 a, f32 b, f32* quotient) {
	x -= a;
	f32 range = b -a;
	
	f32 modulo = wrap(x, range);
	*quotient = floor(x / range);
	
	return modulo + a;
}


int floori (f32 x) {
	return (int)floor(x);
}

int ceili (f32 x) {
	return (int)ceil(x);
}

int roundi (f32 x) {
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

f32 select (bool c, f32 l, f32 r) {
	return c ? l : r;
}


f32 length (f32 x) {
	return std::fabs(x);
}

f32 length_sqr (f32 x) {
	x = std::fabs(x);
	return x*x;
}

f32 normalize (f32 x) {
	return x / length(x);
}

f32 normalize_or_zero (f32 x) {
	f32 len = length(x);
	if (len == f32(0)) {
		return f32(0);
	}
	return x /= len;
}


f32 lerp (f32 a, f32 b, f32 t) {
	return a * (f32(1) - t) + b * t;
}

f32 map (f32 x, f32 in_a, f32 in_b) {
	return (x - in_a) / (in_b - in_a);
}

f32 map (f32 x, f32 in_a, f32 in_b, f32 out_a, f32 out_b) {
	return lerp(out_a, out_b, map(x, in_a, in_b));
}

f32 smoothstep (f32 x) {
	f32 t = clamp(x);
	return t * t * (f32(3) - f32(2) * t);
}

f32 bezier (f32 a, f32 b, f32 c, f32 t) {
	f32 d = lerp(a, b, t);
	f32 e = lerp(b, c, t);
	f32 f = lerp(d, e, t);
	return f;
}

f32 bezier (f32 a, f32 b, f32 c, f32 d, f32 t) {
	return bezier(
		lerp(a, b, t),
		lerp(b, c, t),
		lerp(c, d, t),
		t
	);
}

f32 bezier (f32 a, f32 b, f32 c, f32 d, f32 e, f32 t) {
	return bezier(
		lerp(a, b, t),
		lerp(b, c, t),
		lerp(c, d, t),
		lerp(d, e, t),
		t
	);
}

//// angle stuff

constexpr f32 to_rad (f32 deg) {
	return deg * DEG_TO_RAD;
}

constexpr f32 deg (f32 deg) {
	return deg * DEG_TO_RAD;
}

constexpr f32 to_deg (f32 rad) {
	return rad * RAD_TO_DEG;
}

//// f64

f64 wrap (f64 x, f64 range) {
	f64 modded = std::fmod(x, range);
	if (range > 0) {
		if (modded < 0) modded += range;
	} else {
		if (modded > 0) modded -= range;
	}
	return modded;
}

f64 wrap (f64 x, f64 a, f64 b) {
	x -= a;
	f64 range = b -a;
	
	f64 modulo = wrap(x, range);
	
	return modulo + a;
}

f64 wrap (f64 x, f64 a, f64 b, f64* quotient) {
	x -= a;
	f64 range = b -a;
	
	f64 modulo = wrap(x, range);
	*quotient = floor(x / range);
	
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

f64 select (bool c, f64 l, f64 r) {
	return c ? l : r;
}


f64 length (f64 x) {
	return std::fabs(x);
}

f64 length_sqr (f64 x) {
	x = std::fabs(x);
	return x*x;
}

f64 normalize (f64 x) {
	return x / length(x);
}

f64 normalize_or_zero (f64 x) {
	f64 len = length(x);
	if (len == f64(0)) {
		return f64(0);
	}
	return x /= len;
}


f64 lerp (f64 a, f64 b, f64 t) {
	return a * (f64(1) - t) + b * t;
}

f64 map (f64 x, f64 in_a, f64 in_b) {
	return (x - in_a) / (in_b - in_a);
}

f64 map (f64 x, f64 in_a, f64 in_b, f64 out_a, f64 out_b) {
	return lerp(out_a, out_b, map(x, in_a, in_b));
}

f64 smoothstep (f64 x) {
	f64 t = clamp(x);
	return t * t * (f64(3) - f64(2) * t);
}

f64 bezier (f64 a, f64 b, f64 c, f64 t) {
	f64 d = lerp(a, b, t);
	f64 e = lerp(b, c, t);
	f64 f = lerp(d, e, t);
	return f;
}

f64 bezier (f64 a, f64 b, f64 c, f64 d, f64 t) {
	return bezier(
		lerp(a, b, t),
		lerp(b, c, t),
		lerp(c, d, t),
		t
	);
}

f64 bezier (f64 a, f64 b, f64 c, f64 d, f64 e, f64 t) {
	return bezier(
		lerp(a, b, t),
		lerp(b, c, t),
		lerp(c, d, t),
		lerp(d, e, t),
		t
	);
}

//// angle stuff

constexpr f64 to_rad (f64 deg) {
	return deg * DEG_TO_RADd;
}

constexpr f64 deg (f64 deg) {
	return deg * DEG_TO_RADd;
}

constexpr f64 to_deg (f64 rad) {
	return rad * RAD_TO_DEGd;
}

//// s32

s32 wrap (s32 x, s32 range) {
	s32 modded = x % range;
	if (range > 0) {
		if (modded < 0) modded += range;
	} else {
		if (modded > 0) modded -= range;
	}
	return modded;
}

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

s32 select (bool c, s32 l, s32 r) {
	return c ? l : r;
}


s32 length (s32 x) {
	return std::abs(x);
}

s32 length_sqr (s32 x) {
	x = std::abs(x);
	return x*x;
}

s32 normalize (s32 x) {
	return x / length(x);
}

s32 normalize_or_zero (s32 x) {
	s32 len = length(x);
	if (len == s32(0)) {
		return s32(0);
	}
	return x /= len;
}


//// s64

s64 wrap (s64 x, s64 range) {
	s64 modded = x % range;
	if (range > 0) {
		if (modded < 0) modded += range;
	} else {
		if (modded > 0) modded -= range;
	}
	return modded;
}

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

s64 select (bool c, s64 l, s64 r) {
	return c ? l : r;
}


s64 length (s64 x) {
	return std::abs(x);
}

s64 length_sqr (s64 x) {
	x = std::abs(x);
	return x*x;
}

s64 normalize (s64 x) {
	return x / length(x);
}

s64 normalize_or_zero (s64 x) {
	s64 len = length(x);
	if (len == s64(0)) {
		return s64(0);
	}
	return x /= len;
}


//// s8

s8 wrap (s8 x, s8 range) {
	s8 modded = x % range;
	if (range > 0) {
		if (modded < 0) modded += range;
	} else {
		if (modded > 0) modded -= range;
	}
	return modded;
}

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

s8 select (bool c, s8 l, s8 r) {
	return c ? l : r;
}


s8 length (s8 x) {
	return std::abs(x);
}

s8 length_sqr (s8 x) {
	x = std::abs(x);
	return x*x;
}

s8 normalize (s8 x) {
	return x / length(x);
}

s8 normalize_or_zero (s8 x) {
	s8 len = length(x);
	if (len == s8(0)) {
		return s8(0);
	}
	return x /= len;
}


//// u32

u32 wrap (u32 x, u32 range) {
	u32 modded = x % range;
	if (range > 0) {
		if (modded < 0) modded += range;
	} else {
		if (modded > 0) modded -= range;
	}
	return modded;
}

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

u32 select (bool c, u32 l, u32 r) {
	return c ? l : r;
}


//// u64

u64 wrap (u64 x, u64 range) {
	u64 modded = x % range;
	if (range > 0) {
		if (modded < 0) modded += range;
	} else {
		if (modded > 0) modded -= range;
	}
	return modded;
}

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

u64 select (bool c, u64 l, u64 r) {
	return c ? l : r;
}


//// u8

u8 wrap (u8 x, u8 range) {
	u8 modded = x % range;
	if (range > 0) {
		if (modded < 0) modded += range;
	} else {
		if (modded > 0) modded -= range;
	}
	return modded;
}

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

u8 select (bool c, u8 l, u8 r) {
	return c ? l : r;
}


