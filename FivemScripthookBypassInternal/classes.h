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
	uintptr_t m_gtaCoreFiveDllEnc = 0xE1E38;
	uintptr_t m_adhesiveDllEnc    = 0x244E978;
	uintptr_t m_offsetsHookRd     = 0x1A9096;
	BYTE m_checkUpdate[6] = { 0x88, 0x9A, 0x95, 0x12, 0xF1, 0xFF };
public:
	uintptr_t getGtaCoreFiveDll() const
	{
		return m_gtaCoreFiveDllEnc;
	}

	uintptr_t getAdhesiveDll() const
	{
		return m_adhesiveDllEnc;
	}

	uintptr_t getAdhesiveHookRdDll() const
	{
		return m_offsetsHookRd;
	}

	bool needUpdate(uintptr_t moduleBaseAdhesive)
	{
		for (int count{ 0 }; count < 6; ++count)
		{
			if (((BYTE*)(moduleBaseAdhesive + getAdhesiveHookRdDll()))[count] != m_checkUpdate[count])
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
	uintptr_t m_gtaCoreFiveDllEnc = 0xE1E38;
	uintptr_t m_offsetsHook[3]    = { 0x1A9069, 0x226D084, 0x1A9096 };
public:
	uintptr_t getGtaCoreFiveDll() const
	{
		return m_gtaCoreFiveDllEnc;
	}

	uintptr_t getAdhesiveDll(OffsetsEnum offset) const
	{
		switch (offset)
		{
		case Offsets::firstHook:
			return m_offsetsHook[OffsetsEnum::firstHook];
			break;
		case Offsets::secondHook:
			return m_offsetsHook[OffsetsEnum::secondHook];
			break;
		case Offsets::thirdHook:
			return m_offsetsHook[OffsetsEnum::thirdHook];
			break;
		case Offsets::maxHookNumber:
			break;
		default:
			break;
		}
	}
};
#endif // INTEGRITY_CHECK
