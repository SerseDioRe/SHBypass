#include "patternscanning.h"

namespace patternscanning
{
	MODULEINFO GetModuleInfo(char* szModule)
	{
		MODULEINFO modInfo = { 0 };
		HMODULE hModule = GetModuleHandle(szModule);
		if (hModule == 0)
			return modInfo;

		GetModuleInformation(GetCurrentProcess(), hModule, &modInfo, sizeof(MODULEINFO));
		return modInfo;
	}

	void* FindPattern(char* module, char* pattern, char* mask)
	{
		MODULEINFO mInfo = GetModuleInfo(module);

		char* base = (char*)mInfo.lpBaseOfDll;
		size_t size = (uintptr_t)mInfo.SizeOfImage;

		size_t patternLength = (uintptr_t)strlen(mask);

		for (unsigned int i = 0; i < size - patternLength; i++)
		{
			bool found = true;
			for (unsigned int j = 0; j < patternLength; j++)
			{
				if (mask[j] != '?' && pattern[j] != *(base + i + j))
				{
					found = false;
					break;
				}
			}

			if (found)
			{
				return (void*)(base + i);
			}
		}

		return nullptr;
	}

	void Parse(const char* combo, char* pattern, char* mask)
	{
		char lastChar = ' ';
		unsigned int j = 0;

		for (unsigned int i = 0; i < strlen(combo); i++)
		{
			if ((combo[i] == '?' || combo[i] == '*') && (lastChar != '?' && lastChar != '*'))
			{
				pattern[j] = mask[j] = '?';
				j++;
			}

			else if (isspace(lastChar))
			{
				pattern[j] = lastChar = (char)strtol(&combo[i], 0, 16);
				mask[j] = 'x';
				j++;
			}
			lastChar = combo[i];
		}
		pattern[j] = mask[j] = '\0';
	}

	uintptr_t ScanPattern(char* process, char* module, char* comboPattern)
	{
		char pattern[100]{};
		char mask[100]{};

		Parse(comboPattern, pattern, mask);

		return (uintptr_t)FindPattern(module, pattern, mask);
	}
}