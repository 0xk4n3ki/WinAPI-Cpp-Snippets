Test for the debugger

command : x86_64-w64-mingw32-g++ peb_teb.cpp -o peb.exe -Wint-to-pointer-cast -fpermissive


```cpp
#include <windows.h>
#include <winternl.h>
#include <winnt.h>
#include <stdio.h>
#include <stdlib.h>


int main()
{
#ifdef _WIN64
    PPEB pebPtr = (PPEB)__readgsdword(0x60);
    DWORD debuggedTest = pebPtr->BeingDebugged;
    printf("[+] Debug test status: 0x%x\n", debuggedTest);
#else
    PPEB pebPtr = (PPEB)___readfsdword(0x30);
    DWORD debuggedTest = pebPtr->BeingDebugged;
    printf("[+] Debug test status: 0x%x\n", debuggedTest);
#endif
    return 0;
}
```

structure resource: [Vergilius](https://www.vergiliusproject.com/kernels/x86/Windows%2010/2110%2021H2%20(November%202021%20Update)/_PEB), [msdn](https://learn.microsoft.com/en-us/windows/win32/api/winternl/ns-winternl-peb)
