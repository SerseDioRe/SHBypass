#pragma once
#include <stdint.h>

class GtaCoreFiveDll
{
public:
	bool value;
	char pad_0001[127];
};
static_assert(sizeof(GtaCoreFiveDll) == 0x80);

class AdhesiveDll
{
public:
	int32_t value;
	char pad_0004[124];
};
static_assert(sizeof(AdhesiveDll) == 0x80);