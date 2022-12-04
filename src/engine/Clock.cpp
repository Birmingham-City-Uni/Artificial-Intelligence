#include "Clock.h"
#include <chrono>
#include <iostream>
#define CLOCK 0

namespace timer{
	namespace {
		std::chrono::steady_clock::time_point g_StartTime;
		std::chrono::steady_clock::time_point g_EndTime;
	}

	void StartTimer() {
		g_StartTime = std::chrono::high_resolution_clock::now();
	}

	void StopTimer(const char* function_name) {
		g_EndTime = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(g_EndTime - g_StartTime);
#ifdef LOGGING
	#if CLOCK == 1
		std::cout << "Time taken by function (" << function_name << "): " << duration.count() << " microseconds\n";
	#endif // CLOCK
#endif // LOGGING
	}
}