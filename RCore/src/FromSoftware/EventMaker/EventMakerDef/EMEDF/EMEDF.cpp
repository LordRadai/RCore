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
				this->format = RMemory::endianSwap(this->format);
				this->pad = RMemory::endianSwap(this->pad);
			}

			RMemory::fixPtr(this->name, stringsBase);

			if ((size_t)this->pEnum != INVALID_OFFSET)
				RMemory::fixPtr(this->pEnum, enumsBase);
			else
				this->pEnum = nullptr;

			if ((size_t)this->format != INVALID_OFFSET)
				RMemory::fixPtr(this->format, stringsBase);
			else
				this->format = nullptr;
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
				this->pMainClasses = RMemory::endianSwap(this->pMainClasses);
				this->mainInstrCount = RMemory::endianSwap(this->mainInstrCount);
				this->pMainInstructions = RMemory::endianSwap(this->pMainInstructions);
				this->mainArgCount = RMemory::endianSwap(this->mainArgCount);
				this->pMainArguments = RMemory::endianSwap(this->pMainArguments);
				this->extraClassCount = RMemory::endianSwap(this->extraClassCount);
				this->pExtraClasses = RMemory::endianSwap(this->pExtraClasses);
				this->extraInstrCount = RMemory::endianSwap(this->extraInstrCount);
				this->pExtraInstructions = RMemory::endianSwap(this->pExtraInstructions);
				this->extraArgCount = RMemory::endianSwap(this->extraArgCount);
				this->pExtraArguments = RMemory::endianSwap(this->pExtraArguments);
				this->enumCount = RMemory::endianSwap(this->enumCount);
				this->pEnums = RMemory::endianSwap(this->pEnums);
				this->enumValueCount = RMemory::endianSwap(this->enumValueCount);
				this->pEnumValues = RMemory::endianSwap(this->pEnumValues);
				this->stringsLength = RMemory::endianSwap(this->stringsLength);
				this->strings = RMemory::endianSwap(this->strings);
				this->unk = RMemory::endianSwap(this->unk);
			}

			char* basePtr = reinterpret_cast<char*>(this);
			RMemory::fixPtr(this->pMainClasses, basePtr);
			RMemory::fixPtr(this->pMainInstructions, basePtr);
			RMemory::fixPtr(this->pMainArguments, basePtr);
			RMemory::fixPtr(this->pExtraClasses, basePtr);
			RMemory::fixPtr(this->pExtraInstructions, basePtr);
			RMemory::fixPtr(this->pExtraArguments, basePtr);
			RMemory::fixPtr(this->pEnums, basePtr);
			RMemory::fixPtr(this->pEnumValues, basePtr);
			RMemory::fixPtr(this->strings, basePtr);

			for (int i = 0; i < this->mainClassCount; i++)
				this->pMainClasses[i].locate(bigEndian, this->strings, (char*)this->pMainInstructions);

			for (int i = 0; i < this->mainInstrCount; i++)
				this->pMainInstructions[i].locate(bigEndian, this->strings, (char*)this->pMainArguments);

			for (int i = 0; i < this->mainArgCount; i++)
				this->pMainArguments[i].locate(bigEndian, this->strings, (char*)this->pEnums);

			for (int i = 0; i < this->extraClassCount; i++)
				this->pExtraClasses[i].locate(bigEndian, this->strings, (char*)this->pExtraInstructions);

			for (int i = 0; i < this->extraInstrCount; i++)
				this->pExtraInstructions[i].locate(bigEndian, this->strings, (char*)this->pExtraClasses);

			for (int i = 0; i < this->extraArgCount; i++)
				this->pExtraArguments[i].locate(bigEndian, this->strings, (char*)this->pEnums);

			for (int i = 0; i < this->enumCount; i++)
				this->pEnums[i].locate(bigEndian, this->strings, (char*)this->pEnumValues);

			for (int i = 0; i < this->enumValueCount; i++)
				this->pEnumValues[i].locate(bigEndian, this->strings);
		}
	}
}