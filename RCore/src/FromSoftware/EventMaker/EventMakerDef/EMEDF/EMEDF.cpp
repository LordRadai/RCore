#include "EMEDF.h"
#include "RMemory/RMemory.h"

#define INVALID_OFFSET -1

namespace EventMaker
{
	namespace EMEDF
	{
		void EnumValue::locate(bool bigEndian, char* stringsBase)
		{
			if (bigEndian)
			{
				this->name = RMemory::endianSwap(this->name);
				this->value = RMemory::endianSwap(this->value);
			}

			RMemory::fixPtr(this->name, stringsBase);
		}

		void Enum::locate(bool bigEndian, char* stringsBase, char* enumValueBase)
		{
			if (bigEndian)
			{
				this->name = RMemory::endianSwap(this->name);
				this->numValues = RMemory::endianSwap(this->numValues);
				this->pEnumValues = RMemory::endianSwap(this->pEnumValues);
			}

			RMemory::fixPtr(this->name, stringsBase);
			RMemory::fixPtr(this->pEnumValues, enumValueBase);
		}

		void Argument::locate(bool bigEndian, char* stringsBase, char* enumsBase)
		{
			if (bigEndian)
			{
				this->name = RMemory::endianSwap(this->name);
				this->type = RMemory::endianSwap(this->type);
				this->pEnum = RMemory::endianSwap(this->pEnum);
				this->defaultValue = RMemory::endianSwap(this->defaultValue);
				this->minValue = RMemory::endianSwap(this->minValue);
				this->maxValue = RMemory::endianSwap(this->maxValue);
				this->incValue = RMemory::endianSwap(this->incValue);
				this->formatOffset = RMemory::endianSwap(this->formatOffset);
				this->pad = RMemory::endianSwap(this->pad);
			}

			RMemory::fixPtr(this->name, stringsBase);

			if ((size_t)this->pEnum != INVALID_OFFSET)
				RMemory::fixPtr(this->pEnum, enumsBase);
			else
				this->pEnum = nullptr;

			if ((size_t)this->formatOffset != INVALID_OFFSET)
				RMemory::fixPtr(this->formatOffset, stringsBase);
			else
				this->formatOffset = nullptr;
		}

		void Instruction::locate(bool bigEndian, char* stringBase, char* argBase)
		{
			if (bigEndian)
			{
				this->id = RMemory::endianSwap(this->id);
				this->argCount = RMemory::endianSwap(this->argCount);
				this->pArgs = RMemory::endianSwap(this->pArgs);
				this->name = RMemory::endianSwap(this->name);
			}

			RMemory::fixPtr(this->pArgs, argBase);
			RMemory::fixPtr(this->name, stringBase);
		}

		void Class::locate(bool bigEndian, char* stringBase, char* instrBase)
		{
			if (bigEndian)
			{
				this->id = RMemory::endianSwap(this->id);
				this->numInstructions = RMemory::endianSwap(this->numInstructions);
				this->pInstructions = RMemory::endianSwap(this->pInstructions);
				this->name = RMemory::endianSwap(this->name);
			}

			RMemory::fixPtr(this->pInstructions, instrBase);
			RMemory::fixPtr(this->name, stringBase);
		}

		void EMEDF::locate()
		{
			bool bigEndian = this->bigEndian;

			if (bigEndian)
			{
				this->unk06 = RMemory::endianSwap(this->unk06);
				this->unk07 = RMemory::endianSwap(this->unk07);
				this->unk08 = RMemory::endianSwap(this->unk08);
				this->unk0A = RMemory::endianSwap(this->unk0A);
				this->fileSize = RMemory::endianSwap(this->fileSize);
				this->mainClassCount = RMemory::endianSwap(this->mainClassCount);
				this->mainClassesOffset = RMemory::endianSwap(this->mainClassesOffset);
				this->mainInstrCount = RMemory::endianSwap(this->mainInstrCount);
				this->mainInstrsOffset = RMemory::endianSwap(this->mainInstrsOffset);
				this->mainArgCount = RMemory::endianSwap(this->mainArgCount);
				this->mainArgsOffset = RMemory::endianSwap(this->mainArgsOffset);
				this->extraClassCount = RMemory::endianSwap(this->extraClassCount);
				this->extraClassesOffset = RMemory::endianSwap(this->extraClassesOffset);
				this->extraInstrCount = RMemory::endianSwap(this->extraInstrCount);
				this->extraInstrsOffset = RMemory::endianSwap(this->extraInstrsOffset);
				this->extraArgCount = RMemory::endianSwap(this->extraArgCount);
				this->extraArgsOffset = RMemory::endianSwap(this->extraArgsOffset);
				this->enumCount = RMemory::endianSwap(this->enumCount);
				this->enumsOffset = RMemory::endianSwap(this->enumsOffset);
				this->enumValueCount = RMemory::endianSwap(this->enumValueCount);
				this->enumValuesOffset = RMemory::endianSwap(this->enumValuesOffset);
				this->stringsLength = RMemory::endianSwap(this->stringsLength);
				this->stringsOffset = RMemory::endianSwap(this->stringsOffset);
				this->unk = RMemory::endianSwap(this->unk);
			}

			char* basePtr = reinterpret_cast<char*>(this);
			RMemory::fixPtr(this->mainClassesOffset, basePtr);
			RMemory::fixPtr(this->mainInstrsOffset, basePtr);
			RMemory::fixPtr(this->mainArgsOffset, basePtr);
			RMemory::fixPtr(this->extraClassesOffset, basePtr);
			RMemory::fixPtr(this->extraInstrsOffset, basePtr);
			RMemory::fixPtr(this->extraArgsOffset, basePtr);
			RMemory::fixPtr(this->enumsOffset, basePtr);
			RMemory::fixPtr(this->enumValuesOffset, basePtr);
			RMemory::fixPtr(this->stringsOffset, basePtr);

			for (int i = 0; i < this->mainClassCount; i++)
				this->mainClassesOffset[i].locate(bigEndian, this->stringsOffset, (char*)this->mainInstrsOffset);

			for (int i = 0; i < this->mainInstrCount; i++)
				this->mainInstrsOffset[i].locate(bigEndian, this->stringsOffset, (char*)this->mainArgsOffset);

			for (int i = 0; i < this->mainArgCount; i++)
				this->mainArgsOffset[i].locate(bigEndian, this->stringsOffset, (char*)this->enumsOffset);

			for (int i = 0; i < this->extraClassCount; i++)
				this->extraClassesOffset[i].locate(bigEndian, this->stringsOffset, (char*)this->extraInstrsOffset);

			for (int i = 0; i < this->extraInstrCount; i++)
				this->extraInstrsOffset[i].locate(bigEndian, this->stringsOffset, (char*)this->extraArgsOffset);

			for (int i = 0; i < this->extraArgCount; i++)
				this->extraArgsOffset[i].locate(bigEndian, this->stringsOffset, (char*)this->enumsOffset);

			for (int i = 0; i < this->enumCount; i++)
				this->enumsOffset[i].locate(bigEndian, this->stringsOffset, (char*)this->enumValuesOffset);

			for (int i = 0; i < this->enumValueCount; i++)
				this->enumValuesOffset[i].locate(bigEndian, this->stringsOffset);
		}
	}
}