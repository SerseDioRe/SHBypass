#include "memory.h"

namespace memory
{
	void nop(BYTE* dst, unsigned int size)
	{
		DWORD oldProtect;
		VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldProtect);
		memset(dst, 0x90, size);
		VirtualProtect(dst, size, oldProtect, &oldProtect);
	}
}