#pragma once

#ifdef AI_EXPORTS
	#define AI_API __declspec(dllexport)
#else
	#define AI_API __declspec(dllimport)
#endif

namespace AI {
	extern "C" AI_API void HelloWorld();
} // namespace AI
