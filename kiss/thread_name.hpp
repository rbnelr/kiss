#pragma once

#include "string.hpp"

namespace kiss {
	// give the thread this function is called on a name that might get shown in the debugger
	void set_current_thread_name (string_view name);
}
