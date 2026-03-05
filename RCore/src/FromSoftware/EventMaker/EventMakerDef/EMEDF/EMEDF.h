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
            enum Type
            {
                kTypeU8,
                kTypeU16,
                kTypeU32,
                kTypeS8,
                kTypeS16,
                kTypeS32,
                kTypeFloat32,
                kTypeFloat64,
				kTypeString,

                kNumTypes
			};

            char* name;
            int type;
            Enum* pEnum;
			size_t defaultValue;
			size_t minValue;
			size_t maxValue;
			size_t incValue;
            char* format;
            int pad;

            void locate(bool bigEndian, char* stringsBase, char* enumsBase);

            template<typename T>
            T getDefault() const { return *(T*)&defaultValue; }

            template<typename T>
            void setDefault(T v) { *(T*)&defaultValue = v; }

            template<typename T>
            T getMin() const { return *(T*)&minValue; }

            template<typename T>
            void setMin(T v) { *(T*)&minValue = v; }

            template<typename T>
            T getMax() const { return *(T*)&maxValue; }

            template<typename T>
            void setMax(T v) { *(T*)&maxValue = v; }

            template<typename T>
            T getIncrement() const { return *(T*)&incValue; }

            template<typename T>
            void setIncrement(T v) { *(T*)&incValue = v; }
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
            Class* pMainClasses;
            int mainInstrCount;
            Instruction* pMainInstructions;
            int mainArgCount;
            Argument* pMainArguments;
            int extraClassCount;
            Class* pExtraClasses;
            int extraInstrCount;
            Instruction* pExtraInstructions;
            int extraArgCount;
            Argument* pExtraArguments;
            int enumCount;
            Enum* pEnums;
            int enumValueCount;
            EnumValue* pEnumValues;
            size_t stringsLength;
            char* strings;
            size_t unk;

#ifndef _WIN64
            int pad;
#endif
            void locate();
		};
	}
}