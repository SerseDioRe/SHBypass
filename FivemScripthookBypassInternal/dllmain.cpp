#include "pch.h"
#include "classes.h"
#include "memory.h"

#define INTEGRITY_CHECK

#ifdef INTEGRITY_CHECK
DWORD WINAPI HackThread(HMODULE hModule)
{
    uintptr_t moduleBaseCore = (uintptr_t)GetModuleHandle(L"gta-core-five.dll");
    uintptr_t moduleBaseAdhesive = (uintptr_t)GetModuleHandle(L"adhesive.dll");

    Offsets offsets{};
    GtaCoreFiveDll* gtaCoreFiveDll = (GtaCoreFiveDll*)(moduleBaseCore + offsets.getGtaCoreFiveDll());
    AdhesiveDll* adhesiveDll        =  (AdhesiveDll*)(moduleBaseAdhesive + offsets.getAdhesiveDll());

    int temp{ adhesiveDll->value };
    bool patchAdhesive{ false };

    while (true)
    {
        gtaCoreFiveDll->value = true;

        if (GetAsyncKeyState(VK_DELETE) & 1)
            patchAdhesive = !patchAdhesive;

        if(patchAdhesive)
           adhesiveDll->value = temp;

        Sleep(5);
    }

    return 0;
}
#else
DWORD WINAPI HackThread(HMODULE hModule)
{
    uintptr_t moduleBaseCore = (uintptr_t)GetModuleHandle(L"gta-core-five.dll");
    uintptr_t moduleBaseAdhesive = (uintptr_t)GetModuleHandle(L"adhesive.dll");

    Offsets offsets{};
    GtaCoreFiveDll* gtaCoreFiveDll = (GtaCoreFiveDll*)(moduleBaseCore + offsets.getGtaCoreFiveDll());

    memory::Nop((BYTE*)moduleBaseAdhesive + offsets.getAdhesiveDll(offsets.firstHook), 4);
    memory::Nop((BYTE*)moduleBaseAdhesive + offsets.getAdhesiveDll(offsets.secondHook), 4);
    memory::Nop((BYTE*)moduleBaseAdhesive + offsets.getAdhesiveDll(offsets.thirdHook), 6);

    while (true)
    {
        gtaCoreFiveDll->value = true;

        Sleep(5);
    }

    return 0;
}
#endif // INTEGRITY_CHECK

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

