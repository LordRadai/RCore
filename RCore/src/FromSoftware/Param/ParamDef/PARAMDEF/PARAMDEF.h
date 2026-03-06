#pragma once
#include <Windows.h>

namespace Param
{
    namespace PARAMDEF
    {
        struct Field
        {
            enum EditorFlags
            {
				EDITOR_FLAGS_NONE = 0,
                EDITOR_FLAGS_WRAP = 1,
                EDITOR_FLAGS_LOCK = 4
            };

			wchar_t editorName[32];
			char editorType[8];
            char editorFormat[8];
			float defaultValue;
			float minimum;
			float maximum;
			float increment;
			int editorFlags;
			int byteCount;
            wchar_t* description;
			char engineType[32];
			char engineName[32];
            int sortID;
            wchar_t* bonusStringA;
			wchar_t* bonusStringB;
			wchar_t* bonusStringC;

			void locate(bool bigEndian, char* stringBase);
        };

        struct Header
        {
            int fileSize;
            short headerSize;
            short dataVersion;
            short fieldCount;
            short fieldSize;
            char paramID[32];
            byte bigEndian;
            bool unicode;
            short formatVersion;

			void locate(char* stringBase);
        };

        struct PARAMDEF
        {
            Header header;
			Field fields[1];

			void locate();
        };
    }
}