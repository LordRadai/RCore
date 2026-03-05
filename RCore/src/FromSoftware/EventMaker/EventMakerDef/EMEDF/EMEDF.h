#pragma once
#include <Windows.h>

namespace EventMaker
{
	namespace EMEDF
	{
        struct EnumValue
        {
			char* name;
			int value;
#ifndef _WIN64
            int pad;
#endif

            void locate(bool bigEndian, char* stringBase);
        };

        struct Enum
        {
            char* name;
            int numValues;
			EnumValue* pEnumValues;
#ifndef _WIN64
            int pad;
#endif

            void locate(bool bigEndian, char* stringsBase, char* enumValueBase);
        };

        struct Argument
        {
            char* name;
            int type;
            Enum* pEnum;
            int defaultValue;
            int minValue;
			int maxValue;
            int incValue;
            char* formatOffset;
            int pad;

            void locate(bool bigEndian, char* stringsBase, char* enumsBase);
		};

        struct Instruction
        {
            int id;
            int argCount;
            Argument* pArgs;
            char* name;
#ifndef _WIN64
			int pad;
#endif

            void locate(bool bigEndian, char* stringBase, char* argBase);
		};

        struct Class
        {
            int id;
            int numInstructions;
            Instruction* pInstructions;
            char* name;
#ifndef _WIN64
            int pad;
#endif

            void locate(bool bigEndian, char* stringBase, char* instrBase);
        };

		struct EMEDF
		{
            char magic[4];
            byte bigEndian;
            byte is64Bit;
            byte unk06;
            byte unk07;
            short unk08;
            short unk0A;
            int fileSize;
            int mainClassCount;
            Class* mainClassesOffset;
            int mainInstrCount;
            Instruction* mainInstrsOffset;
            int mainArgCount;
            Argument* mainArgsOffset;
            int extraClassCount;
            Class* extraClassesOffset;
            int extraInstrCount;
            Instruction* extraInstrsOffset;
            int extraArgCount;
            Argument* extraArgsOffset;
            int enumCount;
            Enum* enumsOffset;
            int enumValueCount;
            EnumValue* enumValuesOffset;
            size_t stringsLength;
            char* stringsOffset;
            size_t unk;

#ifndef _WIN64
            int pad;
#endif
            void locate();
		};
	}
}