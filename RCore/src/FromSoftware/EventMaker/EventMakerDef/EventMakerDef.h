#pragma once
#include "EMEDF/EMEDF.h"
#include <string>

namespace EventMaker
{
	class EventMakerDef
	{
		EMEDF::EMEDF* m_pEmedf = nullptr;

	public:
		EventMakerDef() {}
		~EventMakerDef() {}

		static EventMakerDef* createFromFile(std::wstring filepath);

		EMEDF::EMEDF* getEmedf() const { return this->m_pEmedf; }
	};
}