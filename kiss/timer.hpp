#pragma once
#include "stdint.h"

namespace kiss {
	typedef uint64_t	timestamp_t;
	typedef float		timeperiod_t;

	timestamp_t get_timestamp ();
	timeperiod_t timestamp_diff (timestamp_t a, timestamp_t b);

	struct Timer {
		timestamp_t		begin;
		timeperiod_t	seconds;

		void start () {
			begin = get_timestamp();
		}
		timeperiod_t end () {
			auto now = get_timestamp();
			return seconds = timestamp_diff(begin, now);
		}
	};

	struct DT_Measure {
		timestamp_t		prev_frame_end;

		timeperiod_t start () { // call one before frame loop
			prev_frame_end = get_timestamp();
			return 0; // zero dt on first frame, timestep calc should be able to handle this
		}
		timeperiod_t frame_end () { // call after frame is done (after swapbuffers usually)
			auto now = get_timestamp();

			auto dt = timestamp_diff(prev_frame_end, now);

			prev_frame_end = now;

			return dt;
		}
	};
}
