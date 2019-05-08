#include "thread_name.hpp"
#include "string.hpp"

#if defined(_WIN32)
#include "clean_windows_h.hpp"
#endif

namespace kiss {
	void set_current_thread_name (string_view name) {
	#if defined(_WIN32)
		SetThreadDescription(GetCurrentThread(), utf8_to_wchar(name).c_str());
	#endif
	}
}
