#pragma once
#include "vector/vector.hpp"
#include "smart_ptr.hpp"
#include "assert.h"
#include "string.hpp"
#include "stb/stb_image.h"

namespace kiss {
	template <typename T> // T is kiss::lrgb, kiss::lrgba, kiss::srgb8, kiss::srgba8, float
	struct Image { // CPU Image/Texture
		iv2				size = 0;
		unique_ptr<T[]>	pixels = nullptr;

		Image () {}
		Image (iv2 size): size{size}, pixels{make_unique<T[]>(size.x * size.y)} {}
		Image (cstr filepath): Image{load<T>(filepath)} {}

		T* get_pixels () {
			return pixels.get();
		}
		T const* get_pixels () const {
			return pixels.get();
		}

		T& get_pixel (int x, int y) {
			if (!(x >= 0 && x < size.x && y >= 0 && y < size.y)) {
				//DBGLOG("x: %d y: %d  size.x: %d size.y: %d\n", x,y, size.x, size.y);
				assert(false);
			}
			return pixels.get()[ y * size.x + x ];
		}
		T const& get_pixel (int x, int y) const {
			if (!(x >= 0 && x < size.x && y >= 0 && y < size.y)) {
				//DBGLOG("x: %d y: %d  size.x: %d size.y: %d\n", x,y, size.x, size.y);
				assert(false);
			}
			return pixels.get()[ y * size.x + x ];
		}

		T& get_pixel (iv2 pos) { return get_pixel(pos.x, pos.y); }
		T const& get_pixel (iv2 pos) const { return get_pixel(pos.x, pos.y); }

		T const& sample_nearest (v2 uv) const {
			iv2 pos = clamp(floori(wrap(uv, 1) * (v2)size), 0, size -1);
			//printf("uv: %g %g  wrap(uv, 1): %g %g\n", uv.x, uv.y, wrap(uv, 1).x, wrap(uv, 1).y);
			return get_pixel(pos);
		}
		T const& sample_equirectangular (v3 dir) const {
			auto x = atan2f(dir.x, dir.y);
			auto y = atan2f(length((v2)dir), dir.z);

			x += deg(180);
			x /= deg(360);
			y /= deg(180);
			
			return sample_nearest(v2(x,y));
		}

		// load image from image file
		template <typename T> // T is kiss::lrgb, kiss::lrgba, kiss::srgb8, kiss::srgba8, float
		static Image<T> load (cstr filepath) {
			Image<T> img;
			iv2 size;
			int c;

			switch (T::COLOR_SPACE) {
				case CS_SRGB: {
					auto* pixels = stbi_load(filepath, &size.x, &size.y, &c, T::CHANNELS);
					if (!pixels)
						return img;
					img.size = size;
					img.pixels = unique_ptr<T[]>((T*)pixels); // ~unique_ptr<T> should just call free() so this is fine
				} break;
				case CS_LINEAR: {
					auto* pixels = stbi_loadf(filepath, &size.x, &size.y, &c, T::CHANNELS);
					if (!pixels)
						return img;
					img.size = size;
					img.pixels = unique_ptr<T[]>((T*)pixels); // ~unique_ptr<T> should just call free() so this is fine
				} break;
			}

			return img;
		}
	};

	// TODO: Image class with dynamic pixel type

}

