#pragma once

#include "glad/glad.h"

struct GL_Api {
	static void init_singleton () {
		static GL_Api singleton = GL_Api(); // threadsafe, only the first thread calls WGL_Api()
	}
private:
	GL_Api () {
		gladLoadGL();
	}
};
