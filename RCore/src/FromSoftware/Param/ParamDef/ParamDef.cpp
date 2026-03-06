#include "ParamDef.h"
#include "RCore.h"

namespace Param
{
	ParamDef* ParamDef::createFromFile(std::wstring filepath)
	{
		int64_t size;
		void* buffer;
		int64_t bytesRead = RFile::allocAndLoad(filepath, &buffer, &size);

		if (bytesRead > 0)
		{
			ParamDef* def = new ParamDef;
			def->m_pParamDef = static_cast<PARAMDEF::PARAMDEF*>(buffer);
			def->m_pParamDef->locate();
			return def;
		}

		return nullptr;
	}
}