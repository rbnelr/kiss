#include "../test_util/test_util.hpp"
#include "win32_window.hpp"
#include "timer.hpp"

int main () {
	auto kiss_wnd = kiss::Window("Kiss Test Window", 500);
	auto ogl = kiss::Opengl_Context(kiss_wnd, {3,1}, true);

	Ngon_Spinner ngon;

	kiss::DT_Measure dtm;
	float dt = dtm.start();

	for (;;) {
		auto inp = kiss_wnd.get_input();

		if (inp.close)
			break;

		ngon.draw(inp.window_size);

		ogl.swap_buffers();

		float dt = dtm.frame_end();
	}
	return 0;
}
