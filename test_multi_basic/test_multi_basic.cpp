#include "../test_util/test_util.hpp"

void window (int ngon_n) {
	auto kiss_wnd = kiss::Window("Kiss Test Window");

	for (;;) {
		auto inp = kiss_wnd.get_input();

		if (inp.close)
			break;

		draw(inp.window_size, ngon_n);

		swap_buffers(kiss_wnd);
	}
}

#include "stdio.h"
#include <thread>
#include <vector>

int main () {
	
	std::vector<std::thread> threads;
	for (int n=3; n<5; ++n) {
		threads.emplace_back(window, n);
	}

	int i=0;
	for (auto& thr : threads) {
		thr.join();
		printf("joined thread %d\n", i);
	}

	return 0;
}
