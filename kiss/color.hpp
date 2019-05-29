#pragma once

#include "vector/vector.hpp"

namespace kiss {
	template <typename T> inline T to_linear (T srgb) {
		return select(srgb <= T(0.0404482362771082f),
			srgb * (T(1)/T(12.92f)),
			pow( (srgb +T(0.055f)) * T(1/1.055f), T(2.4f) )
		);
	}
	template <typename T> inline T to_srgb (T linear) {
		return select(linear <= T(0.00313066844250063f),
			linear * T(12.92f),
			( T(1.055f) * pow(linear, T(1/2.4f)) ) -T(0.055f)
		);
	}

	enum color_space_e {
		CS_LINEAR,
		CS_SRGB,
	};

	struct lrgb;
	struct lrgba;

	struct srgb8 : u8v3 {
		static constexpr color_space_e COLOR_SPACE = CS_SRGB;
		static constexpr int CHANNELS = 3;

		srgb8 (): u8v3{} {}
		srgb8 (u8v3 v): u8v3{v} {}
		srgb8 (u8 all): u8v3{all,all,all} {}
		srgb8 (u8 r, u8 g, u8 b): u8v3{r,g,b} {}

		inline operator lrgb () const;
	};
	struct srgba8 : u8v4 {
		static constexpr color_space_e COLOR_SPACE = CS_SRGB;
		static constexpr int CHANNELS = 4;

		srgba8 (): u8v4{} {}
		srgba8 (u8v4 v): u8v4{v} {}
		srgba8 (u8 all): u8v4{all,all,all, 255} {}
		srgba8 (u8 r, u8 g, u8 b): u8v4{r,g,b, 255} {}
		srgba8 (u8 r, u8 g, u8 b, u8 a): u8v4{r,g,b,a} {}

		inline operator lrgba () const;
	};

	struct lrgb : v3 {
		static constexpr color_space_e COLOR_SPACE = CS_LINEAR;
		static constexpr int CHANNELS = 3;

		lrgb (): v3{} {}
		lrgb (v3 v): v3{v} {}
		lrgb (flt all): v3{all,all,all} {}
		lrgb (flt r, flt g, flt b): v3{r,g,b} {}

		inline operator srgb8 () const;
	};
	struct lrgba : v4 {
		static constexpr color_space_e COLOR_SPACE = CS_LINEAR;
		static constexpr int CHANNELS = 4;

		lrgba (): v4{} {}
		lrgba (v4 v): v4{v} {}
		lrgba (flt all): v4{all,all,all, (flt)1} {}
		lrgba (flt r, flt g, flt b): v4{r,g,b, (flt)1} {}
		lrgba (flt r, flt g, flt b, flt a): v4{r,g,b,a} {}

		inline operator srgba8 () const;
	};

	inline srgb8::operator lrgb () const {
		v3 cv = to_linear((v3)u8v3(x,y,z) / 255);
		return lrgb(cv.x, cv.y, cv.z);
	}
	inline srgba8::operator lrgba () const {
		v4 v = (v4)u8v4(x,y,z,w) / 255;
		v3 cv = to_linear((v3)v);
		return lrgba(cv.x, cv.y, cv.z, v.w);
	}

	inline lrgb::operator srgb8 () const {
		u8v3 cv = (u8v3)(to_srgb(v3(x,y,z)) * 255);
		return srgb8(cv);
	}
	inline lrgba::operator srgba8 () const {
		v3 cv = to_srgb(v3(x,y,z));
		u8v4 v = (u8v4)(v4(cv,w) * 255);
		return srgba8(v);
	}

	inline lrgb srgb (u8 r, u8 g, u8 b) {
		return (lrgb)srgb8(r,g,b);
	}
	inline lrgba srgb (u8 r, u8 g, u8 b, u8 a) {
		return (lrgba)srgba8(r,g,b,a);
	}

	struct Float {
		static constexpr color_space_e COLOR_SPACE = CS_LINEAR;
		static constexpr int CHANNELS = 1;

		flt val;

		Float () {}
		Float (flt val): val{val} {}

		inline operator flt () const { return val; };
	};
	
}
