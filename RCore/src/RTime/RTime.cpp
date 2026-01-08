#include "RTime.h"

namespace RTime
{
	std::time_t getCurrentTime()
	{
		return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	}

	std::string getTimeStamp()
	{
		std::time_t time = getCurrentTime();

		char buffer[20];
		std::strftime(buffer, sizeof(buffer), "%Y%m%d_%H%M%S", std::localtime(&time));
		return std::string(buffer);
	}
}