[EnumProcesses](https://learn.microsoft.com/en-us/windows/win32/api/psapi/nf-psapi-enumprocesses), [EnumProcessMoudles](https://learn.microsoft.com/en-us/windows/win32/api/psapi/nf-psapi-enumprocessmodules), [GetModuleBaseNameA](https://learn.microsoft.com/en-us/windows/win32/api/psapi/nf-psapi-getmodulebasenamea) are used to retreive the PiD list and iterate over them to obtain the Module Base name.

LoadLibraryA is being used to load psapi.dll and GetProcAddress to dynamically import the above functions.

```cpp
#include <iostream>
#include <Windows.h>

int main(){
    HMODULE libraryA = LoadLibraryA("psapi.dll");

    typedef BOOL(WINAPI* EnumProcessModulesFn)(HANDLE, HMODULE*, DWORD, DWORD);
    EnumProcessModulesFn enumProcessModulesFn = reinterpret_cast<EnumProcessModulesFn>(
        GetProcAddress(libraryA, "EnumProcessModules")
    );
    if(!enumProcessModulesFn){
        std::cout << "failed to import EnumProcessModules." << std::endl;
    }

    typedef BOOL(WINAPI* EnumProcessesFn)(DWORD*, DWORD, DWORD*);
    EnumProcessesFn enumProcessesFn = reinterpret_cast<EnumProcessesFn>(
        GetProcAddress(libraryA, "EnumProcesses")
    );
    if(!enumProcessesFn){
        std::cout << "failed to import EnumProcesses." << std::endl;
    }

    typedef BOOL(WINAPI* GetModuleBaseNameAFn)(HANDLE, HMODULE, LPSTR, DWORD);
    GetModuleBaseNameAFn getModuleBaseNameAFn = reinterpret_cast<GetModuleBaseNameAFn>(
        GetProcAddress(libraryA, "GetModuleBaseNameA")
    );
    if(!getModuleBaseNameAFn){
        std::cout << "failed to import GetModuleBaseNameA" << std::endl;
    }

    DWORD dwProcessId[1024];
    DWORD bytes_returned;
    if(!enumProcessesFn(dwProcessId, 4096, &bytes_returned)){
        std::cout << "error in EnumProcesses." << std::endl;
        return 1;
    }
    DWORD processCount = bytes_returned/sizeof(DWORD);
    for(int i = 0; i < processCount; i++){
        int ith_pid = dwProcessId[i];
        HANDLE hObject = OpenProcess(0x401u, 0, ith_pid);
        if(hObject != NULL){
            HMODULE moduleHandles[1024];
            DWORD numModules;
            if(enumProcessModulesFn(hObject, moduleHandles, sizeof(moduleHandles), numModules)){
                char pName[MAX_PATH];
                if(numModules > 0){
                    DWORD moduleNameLength = getModuleBaseNameAFn(hObject, moduleHandles[0], pName, sizeof(pName));
                    if(moduleNameLength > 0){
                        std::cout << i << " : " << ith_pid << " : " << pName << std::endl;
                    }
                }
            }
        }
        CloseHandle(hObject);
    }

    FreeLibrary(libraryA);

    return 0;
}
```
