#include "timer.hpp"
#include "clean_windows_h.hpp"

namespace kiss {
	timestamp_t _get_timestamp_freq () {
		LARGE_INTEGER li;
		QueryPerformanceFrequency(&li);
		return li.QuadPart;
	}

	timestamp_t get_timestamp () {
		LARGE_INTEGER li;
		QueryPerformanceCounter(&li);
		return li.QuadPart;
	}

	auto _freq = _get_timestamp_freq();

	timeperiod_t timestamp_diff (timestamp_t a, timestamp_t b) {
		return timeperiod_t(b - a) / timeperiod_t(_freq);
	}
}
