#include "pch.h"
#include "patternscanning.h"
#include "memory.h"
#include "classes.h"
#include "config.h"

DWORD WINAPI SerseDioRe(HMODULE hModule)
{
    void* hookSt = patternscanning::FindPattern(config::modules[Modules::adhesiveDll], config::patterns[Patterns::patternStHook], config::masks[Masks::maskStHook]);
    void* hookNd = patternscanning::FindPattern(config::modules[Modules::adhesiveDll], config::patterns[Patterns::patternNdHook], config::masks[Masks::maskNdHook]);
    void* hookRd = patternscanning::FindPattern(config::modules[Modules::adhesiveDll], config::patterns[Patterns::patternRdHook], config::masks[Masks::maskRdHook]);
    uintptr_t shallow = patternscanning::ScanPattern(config::process, config::modules[Modules::gtaCoreFiveDll], config::combo) + config::jmp;

    memory::nop((BYTE*)hookSt, 4);
    memory::nop((BYTE*)hookNd, 4);
    memory::nop((BYTE*)hookRd, 6);

    while (true)
    {
        GtaCoreFiveDll* gtaCoreFiveDll = (GtaCoreFiveDll*)(shallow);
        gtaCoreFiveDll->value = true;
    }

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)SerseDioRe, hModule, 0, nullptr));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

