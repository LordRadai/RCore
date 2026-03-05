#include "RFile/RFile.h"
#include "EventMakerDef.h"

namespace EventMaker
{
	EventMakerDef* EventMakerDef::createFromFile(std::wstring filepath)
	{
		int64_t size;
		void* buffer;

		int64_t bytesRead = RFile::allocAndLoad(filepath, &buffer, &size);

		if (bytesRead > 0)
		{
			EventMakerDef* def = new EventMakerDef;
			def->m_pEmedf = static_cast<EMEDF::EMEDF*>(buffer);
			def->m_pEmedf->locate();

			return def;
		}

		return nullptr;
	}
}