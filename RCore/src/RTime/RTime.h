#pragma once
#include <chrono>

namespace RTime
{
	using Clock = std::chrono::high_resolution_clock;
	using TimePoint = Clock::time_point;
	using Duration = Clock::duration;

	std::time_t getCurrentTime();
	std::string getTimeStamp(std::string format);
}
