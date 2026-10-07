#pragma once
#include <Windows.h>
#include <cstdint>

namespace ChrModelExFormat
{
	namespace FLVPWV
	{
		struct Bone
		{
			enum TwistBoneType : uint8_t
			{
				TWIST_BONE_NONE,
				TWIST_BONE_ONE_AXIS,
				TWIST_BONE_THREE_AXIS
			};

			wchar_t Name[64];
			uint16_t BaseBone;
			uint16_t RotationAdditionBone;
			float fRotationScale;
			TwistBoneType Type;
			uint8_t bVar89;
			uint8_t bVar8A;
			uint8_t bVar8B;
			uint32_t iVar8C;
			uint32_t iVar90;

			void locate() {}
		};

		struct Header
		{
			int Version;
			int8_t bVar4;
			int8_t bVar5;
			uint16_t NumBones;
			uint16_t BoneListOffset;
			uint16_t BoneListSize;
			uint32_t iVarC;
			uint32_t iVar10;

			void locate() {}
		};
	}
}