#pragma once
#include "vector/vector.hpp"

namespace kiss {
	struct Input {
		bool	close;
		iv2		window_size;

		// clear input that is frame-by-frame like mouse deltas or the close flag
		inline void clear () {
			close = false;
		}
	};
}
