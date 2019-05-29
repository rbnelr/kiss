#pragma once
#include "move_only.hpp"
#include "opengl_api.hpp"
#include "assert.h"
#include "vector/vector.hpp"
#include "string.hpp"

namespace kiss {
	class Texture { // GPU Texture
		MOVE_ONLY_CLASS(Texture)
	public:

		Texture ();

		GLuint	handle = 0;
		~Texture ();

		void generate (GLenum target);

		void set_minmag_filtering (GLenum target);
		void set_border (GLenum target);
		void set_active_mips (GLenum target, int first, int last);

		void reupload_mipmap_2d (void const* pixels, iv2 size_px, int mip);

		// pixels for cubemap faces in contiguous memory
		void reupload_mipmap (GLenum target, void const* pixels, iv2 size_px, int mip);
		// pixels for cubemap faces in contiguous memory
		void reupload (GLenum target, void const* pixels, iv2 size_px);

	};
	void swap (Texture& l, Texture& r);
}
