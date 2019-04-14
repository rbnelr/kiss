#pragma once

struct iv2 {
	int x, y;

	inline iv2 () {}
	inline constexpr iv2 (int all): x{all}, y{all} {}
	inline explicit constexpr iv2 (int x, int y): x{x}, y{y} {}

	inline constexpr iv2& operator+= (iv2 r) { return x += r.x, y += r.y, *this; }
	inline constexpr iv2& operator-= (iv2 r) { return x -= r.x, y -= r.y, *this; }
	inline constexpr iv2& operator*= (iv2 r) { return x *= r.x, y *= r.y, *this; }
	inline constexpr iv2& operator/= (iv2 r) { return x /= r.x, y /= r.y, *this; }
};

inline constexpr iv2 operator+ (iv2 l, iv2 r) { return iv2(l.x + r.x, l.y + r.y); }
inline constexpr iv2 operator- (iv2 l, iv2 r) { return iv2(l.x - r.x, l.y - r.y); }
inline constexpr iv2 operator* (iv2 l, iv2 r) { return iv2(l.x * r.x, l.y * r.y); }
inline constexpr iv2 operator/ (iv2 l, iv2 r) { return iv2(l.x / r.x, l.y / r.y); }

struct v2 {
	float x, y;

	inline v2 () {}
	inline constexpr v2 (float all): x{all}, y{all} {}
	inline explicit constexpr v2 (float x, float y): x{x}, y{y} {}

	inline constexpr v2& operator+= (v2 r) { return x += r.x, y += r.y, *this; }
	inline constexpr v2& operator-= (v2 r) { return x -= r.x, y -= r.y, *this; }
	inline constexpr v2& operator*= (v2 r) { return x *= r.x, y *= r.y, *this; }
	inline constexpr v2& operator/= (v2 r) { return x /= r.x, y /= r.y, *this; }
};

inline constexpr v2 operator+ (v2 l, v2 r) { return v2(l.x + r.x, l.y + r.y); }
inline constexpr v2 operator- (v2 l, v2 r) { return v2(l.x - r.x, l.y - r.y); }
inline constexpr v2 operator* (v2 l, v2 r) { return v2(l.x * r.x, l.y * r.y); }
inline constexpr v2 operator/ (v2 l, v2 r) { return v2(l.x / r.x, l.y / r.y); }