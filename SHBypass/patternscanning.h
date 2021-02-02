#pragma once
#include "pch.h"

namespace patternscanning
{
	MODULEINFO GetModuleInfo(char szModule);
	void* FindPattern(char* module, char* pattern, char* mask);
	void Parse(const char* combo, char* pattern, char* mask);
	uintptr_t ScanPattern(char* process, char* module, char* combopattern);
}