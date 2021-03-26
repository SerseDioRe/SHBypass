#pragma once
#include <stdint.h>

#define INTEGRITY_CHECK

#ifdef INTEGRITY_CHECK
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
	uintptr_t gtaCoreFiveDllEnc = 0xE8F9A;
	uintptr_t adhesiveDllEnc = 0x1DB6F0A;
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

#else
class GtaCoreFiveDll
{
public:
	bool value;
	char pad_0001[127];
};
static_assert(sizeof(GtaCoreFiveDll) == 0x80);

class Offsets
{
public:
	enum OffsetsEnum
	{
		firstHook,
		secondHook,
		thirdHook,
		maxHookNumber,
	};
private:
	uintptr_t gtaCoreFiveDllEnc = 0xE8F9A;
	uintptr_t offsetsHook[3]    = { 0x12352E5, 0xC0BC98, 0x1235303 };
private:
	uintptr_t decryptGtaCoreFiveDll() const
	{
		return ((((((gtaCoreFiveDllEnc - 0x6666) - 0x299) + 0x2297) - 0x3570) + 0x4398) - 0x5912);
	}

	uintptr_t decryptAdhesiveDll(OffsetsEnum offset) const
	{
		switch (offset)
		{
		case Offsets::firstHook:
			return ((((((offsetsHook[Offsets::firstHook] - 0x6666) - 0x299) + 0x2297) - 0x3570) + 0x4398) - 0x5912);
			break;
		case Offsets::secondHook:
			return ((((((offsetsHook[Offsets::secondHook] - 0x6666) - 0x299) + 0x2297) - 0x3570) + 0x4398) - 0x5912);
			break;
		case Offsets::thirdHook:
			return ((((((offsetsHook[Offsets::thirdHook] - 0x6666) - 0x299) + 0x2297) - 0x3570) + 0x4398) - 0x5912);
			break;
		case Offsets::maxHookNumber:
			break;
		default:
			break;
		}
	}

public:
	uintptr_t getGtaCoreFiveDll() const
	{
		return decryptGtaCoreFiveDll();
	}

	uintptr_t getAdhesiveDll(OffsetsEnum offset) const
	{
		switch (offset)
		{
		case Offsets::firstHook:
			return decryptAdhesiveDll(OffsetsEnum::firstHook);
			break;
		case Offsets::secondHook:
			return decryptAdhesiveDll(OffsetsEnum::secondHook);
			break;
		case Offsets::thirdHook:
			return decryptAdhesiveDll(OffsetsEnum::thirdHook);
			break;
		case Offsets::maxHookNumber:
			break;
		default:
			break;
		}
	}
};
#endif // INTEGRITY_CHECK
