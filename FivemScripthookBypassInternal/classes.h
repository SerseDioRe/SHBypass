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
	uintptr_t gtaCoreFiveDllEnc = 0xEAF8A;
	uintptr_t adhesiveDllEnc    = 0x22B2AAA;
	uintptr_t offsetsHookRd     = 0xB4617E;
	BYTE checkUpdate[6] = { 0x88, 0x81, 0x4B, 0xCF, 0xF9, 0xFF };
private:
	uintptr_t decryptGtaCoreFiveDll() const
	{
		return ((((((gtaCoreFiveDllEnc - 0x6666) - 0x299) + 0x2297) - 0x3570) + 0x4398) - 0x5912);
	}
	uintptr_t decryptAdhesiveDll() const
	{
		return ((((((adhesiveDllEnc - 0x6666) - 0x299) + 0x2297) - 0x3570) + 0x4398) - 0x5912);
	}
	uintptr_t decryptAdhesiveHookDll() const
	{
		return ((((((offsetsHookRd - 0x6666) - 0x299) + 0x2297) - 0x3570) + 0x4398) - 0x5912);
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

	uintptr_t getAdhesiveHookDll() const
	{
		return decryptAdhesiveHookDll();
	}

	bool needUpdate(uintptr_t moduleBaseAdhesive)
	{
		for (int count{ 0 }; count < 6; ++count)
		{
			if (((BYTE*)(moduleBaseAdhesive + getAdhesiveHookDll()))[count] != checkUpdate[count])
				return true;
		}

		return false;
	}

	void warningUpdate()
	{
		MessageBox(0, L"Scripthook bypass need to be updated!", L"ERROR", MB_ICONERROR);
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
	uintptr_t gtaCoreFiveDllEnc = 0xEAF9A;
	uintptr_t offsetsHook[3]    = { 0xB46152, 0x1F13BA, 0xB4617E };
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
