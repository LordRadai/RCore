#include "RTime.h"

namespace RTime
{
	std::time_t getCurrentTime()
	{
		return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	}

	std::string getTimeStamp(std::string format)
	{
		std::time_t time = getCurrentTime();

		struct tm tstruct = *localtime(&time);
		char  buf[80];

		if (format.compare("now") == 0)
			strftime(buf, sizeof(buf), "%d-%m-%Y %X", &tstruct);
		else if (format.compare("date") == 0)
			strftime(buf, sizeof(buf), "%d-%m-%Y", &tstruct);
		else if (format.compare("time") == 0)
			strftime(buf, sizeof(buf), "%X", &tstruct);
		else
			throw std::invalid_argument("Invalid format type " + format);

		return std::string(buf);
	}
}