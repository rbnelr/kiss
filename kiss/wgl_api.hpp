#pragma once

#include "glad/glad_wgl.h"
#include "stdio.h"

struct WGL_Api {
	static void init_singleton (HDC hdc) {
		static WGL_Api singleton = WGL_Api(hdc); // threadsafe, only the first thread calls WGL_Api()
	}
private:
	WGL_Api (HDC hdc) {
		printf("gladLoadWGL()\n");

		// NOTE: We only init glad wgl once, but we actually have multiple hdc if we support multiple windows, and one for the dummy window needed to create a modern opengl context
		// since glad just sets global variables, we cannot even init it for different hdcs, so i hope that the hdc of the dummy window is fine
		gladLoadWGL(hdc);
	}
};
