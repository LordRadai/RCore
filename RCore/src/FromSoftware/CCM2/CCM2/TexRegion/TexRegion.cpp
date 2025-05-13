#include "TexRegion.h"

namespace CCM2
{
	TexRegion::TexRegion(RFile* resource)
	{
		resource->read(&this->m_x1);
		resource->read(&this->m_x2);
		resource->read(&this->m_y1);
		resource->read(&this->m_y2);
	}

	TexRegion::TexRegion(short x1, short y1, short x2, short y2)
	{
		this->m_x1 = x1;
		this->m_y1 = y1;
		this->m_x2 = x2;
		this->m_y2 = y2;
	}

	bool TexRegion::writeToFile(RFile* pOut)
	{
		pOut->write(this->m_x1);
		pOut->write(this->m_y1);
		pOut->write(this->m_x2);
		pOut->write(this->m_y2);

		return true;
	}
}