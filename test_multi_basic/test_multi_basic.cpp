#include "../test_util/test_util.hpp"
#include "thread_name.hpp"

void window (int ngon_n) {
	kiss::set_current_thread_name(kiss::prints("Window Renderer %d", ngon_n));

	auto kiss_wnd = kiss::Window(kiss::prints("Kiss Test Window %d", ngon_n), 500);

	for (;;) {
		auto inp = kiss_wnd.get_input();

		if (inp.close)
			break;

		draw(inp.window_size, ngon_n);

		kiss_wnd.swap_buffers();
	}
}

#include "stdio.h"
#include <thread>
#include <vector>

int main () {
	
	std::vector<std::thread> threads;
	for (int n=3; n<8; ++n) {
		threads.emplace_back(window, n);
	}

	int i=0;
	for (auto& thr : threads) {
		thr.join();
		//printf("joined thread %d\n", i++);
	}

	return 0;
}
