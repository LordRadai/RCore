#pragma once
#include <vector>
#include <string>

#include "FLVPWV/FLVPWV.h"

namespace ChrModelExFormat
{
	class Bone
	{
		std::wstring m_name;
		int16_t m_baseBone;
		int16_t m_rotationAdditionBone;
		float m_rotationScale;
		FLVPWV::Bone::TwistBoneType m_type;

	public:
		static Bone* createFromResource(FLVPWV::Bone* flvpwvBone);

		void destroy() { delete this; }

		const wchar_t* getName() const { return this->m_name.c_str(); }
		int16_t getBaseBone() const { return this->m_baseBone; }
		int16_t getRotationAdditionBone() const { return this->m_rotationAdditionBone; }
		float getRotationScale() const { return this->m_rotationScale; }
		FLVPWV::Bone::TwistBoneType getType() const { return this->m_type; }

		bool isTwistBone() const { return this->m_type != FLVPWV::Bone::TWIST_BONE_NONE; }
	private:
		Bone() {}
		~Bone() {}
	};

	class ChrModelExFormat
	{
		std::wstring m_filePath;
		std::wstring m_name;
		std::vector<Bone*> m_bones;
	public:
		static ChrModelExFormat* createFromFile(std::wstring filepath);
		static ChrModelExFormat* createFromResource(FLVPWV::Header* flvpwvHeader);

		void destroy();

		size_t getNumBones() const { return this->m_bones.size(); }
		Bone* getBone(int idx) const;

	private:
		ChrModelExFormat() {}
		~ChrModelExFormat() {}
	};
}