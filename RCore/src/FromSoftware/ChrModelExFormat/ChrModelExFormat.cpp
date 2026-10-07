#include <filesystem>

#include "ChrModelExFormat.h"
#include "RFile/RFile.h"

namespace ChrModelExFormat
{
	Bone* Bone::createFromResource(FLVPWV::Bone* flvpwvBone)
	{
		Bone* bone = new Bone;

		bone->m_name = flvpwvBone->Name;
		bone->m_baseBone = flvpwvBone->BaseBone;
		bone->m_rotationAdditionBone = flvpwvBone->RotationAdditionBone;
		bone->m_rotationScale = flvpwvBone->fRotationScale;
		bone->m_type = flvpwvBone->Type;

		return bone;
	}

	ChrModelExFormat* ChrModelExFormat::createFromFile(std::wstring filepath)
	{
		int64_t size;
		void* buffer;

		int64_t bytesRead = RFile::allocAndLoad(filepath, &buffer, &size);

		if (bytesRead > 0)
		{
			FLVPWV::Header* flvpw = static_cast<FLVPWV::Header*>(buffer);
			flvpw->locate();

			ChrModelExFormat* chrModelExFormat = new ChrModelExFormat;

			chrModelExFormat->m_filePath = filepath;
			chrModelExFormat->m_name = std::filesystem::path(filepath).filename();

			FLVPWV::Bone* flvpwvBones = reinterpret_cast<FLVPWV::Bone*>(reinterpret_cast<char*>(buffer) + flvpw->BoneListOffset);

			for (size_t i = 0; i < flvpw->NumBones; i++)
				chrModelExFormat->m_bones.push_back(Bone::createFromResource(&flvpwvBones[i]));

			return chrModelExFormat;
		}
	}

	ChrModelExFormat* ChrModelExFormat::createFromResource(FLVPWV::Header* flvpwvHeader)
	{
		ChrModelExFormat* chrModelExFormat = new ChrModelExFormat;

		FLVPWV::Bone* flvpwvBones = reinterpret_cast<FLVPWV::Bone*>(reinterpret_cast<char*>(flvpwvHeader) + flvpwvHeader->BoneListOffset);
		
		for (size_t i = 0; i < flvpwvHeader->NumBones; i++)
			chrModelExFormat->m_bones.push_back(Bone::createFromResource(&flvpwvBones[i]));

		return chrModelExFormat;
	}

	void ChrModelExFormat::destroy()
	{
		for (size_t i = 0; i < this->m_bones.size(); i++)
		{
			if (this->m_bones[i])
				this->m_bones[i]->destroy();
		}

		this->m_bones.clear();
	}

	Bone* ChrModelExFormat::getBone(int idx) const
	{
		if (idx < 0 || idx >= m_bones.size())
			return nullptr;

		return m_bones[idx];
	}
}