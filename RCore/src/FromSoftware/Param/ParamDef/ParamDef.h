#pragma once
#include <string>
#include "PARAMDEF/PARAMDEF.h"

namespace Param
{
	class ParamDef
	{
		PARAMDEF::PARAMDEF* m_pParamDef;

	public:
		ParamDef() : m_pParamDef(nullptr) {}
		~ParamDef() {}

		static ParamDef* createFromFile(std::wstring filepath);

		PARAMDEF::PARAMDEF* getParamDef() const { return this->m_pParamDef; }
	};
}
