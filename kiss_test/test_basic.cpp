#include "../test_util/test_util.hpp"
#include "win32_window.hpp"

int main () {
	auto kiss_wnd = kiss::Window("Kiss Test Window", 500);
	auto ogl = kiss::Opengl_Context(kiss_wnd);

	for (;;) {
		auto inp = kiss_wnd.get_input();

		if (inp.close)
			break;

		draw(inp.window_size);

		kiss_wnd.swap_buffers();
	}
	return 0;
}
