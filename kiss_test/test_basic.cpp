#include "../test_util/test_util.hpp"

int main () {
	auto kiss_wnd = kiss::Window("Kiss Test Window");

	for (;;) {
		auto inp = kiss_wnd.get_input();

		if (inp.close)
			break;

		draw(inp.window_size);

		kiss_wnd.swap_buffers();
	}
	return 0;
}
