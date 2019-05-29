#include "texture.hpp"

namespace kiss {
	Texture::Texture () {
		generate(GL_TEXTURE_2D);
	}
	Texture::~Texture () {
		if (handle) // maybe this helps to optimize out destructing of unalloced textures
			glDeleteTextures(1, &handle); // would be ok to delete unalloced texture (handle = 0)
	}

	void Texture::generate (GLenum target) {
		assert(handle == 0);

		glGenTextures(1, &handle);

		glBindTexture(target, handle);

		set_minmag_filtering(target);
		set_border(target);

		set_active_mips(target, 0,0);

		glBindTexture(target, 0);
	}

	void Texture::set_minmag_filtering (GLenum target) {
		GLenum min, mag;

		min = mag = GL_NEAREST;

		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, min);
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, mag);
	}

	void Texture::set_border (GLenum target) {
		if (		target == GL_TEXTURE_2D ) {

			GLenum mode;

			mode = GL_CLAMP_TO_EDGE;

			glTexParameteri(target, GL_TEXTURE_WRAP_S, mode);
			glTexParameteri(target, GL_TEXTURE_WRAP_T, mode);


		}
	}

	void Texture::set_active_mips (GLenum target, int first, int last) { // i am not sure that just setting abitrary values for these actually works correctly
		glTexParameteri(target, GL_TEXTURE_BASE_LEVEL, first);
		glTexParameteri(target, GL_TEXTURE_MAX_LEVEL, last);
	}

	void Texture::reupload_mipmap_2d (void const* pixels, iv2 size_px, int mip) {
		glTexImage2D(GL_TEXTURE_2D, mip, GL_RGB32F, size_px.x,size_px.y, 0, GL_RGB, GL_FLOAT, pixels);
	}

	void Texture::reupload_mipmap (GLenum target, void const* pixels, iv2 size_px, int mip) {
		glBindTexture(target, handle);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		reupload_mipmap_2d(pixels, size_px, mip);

		glBindTexture(target, 0);
	}

	void Texture::reupload (GLenum target, void const* pixels, iv2 size_px) {
		reupload_mipmap(target, pixels, size_px, 0);
	}

	void swap (Texture& l, Texture& r) {
		std::swap(l.handle, r.handle);
	}
}
