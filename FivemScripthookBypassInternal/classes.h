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

class Offsets
{
private:
	uintptr_t gtaCoreFiveDllEnc = 0xE8F7A;
	uintptr_t adhesiveDllEnc    = 0x1D6F27E;
private:
	uintptr_t decryptGtaCoreFiveDll() const
	{
		return ((((((gtaCoreFiveDllEnc - 0x6666) - 0x299) + 0x2297) - 0x3570) + 0x4398) - 0x5912);
	}

	uintptr_t decryptAdhesiveDll() const
	{
		return ((((((adhesiveDllEnc - 0x6666) - 0x299) + 0x2297) - 0x3570) + 0x4398) - 0x5912);
	}
public:
	uintptr_t getGtaCoreFiveDll() const
	{
		return decryptGtaCoreFiveDll();
	}

	uintptr_t getAdhesiveDll() const
	{
		return decryptAdhesiveDll();
	}
};