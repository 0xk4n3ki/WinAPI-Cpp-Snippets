[GetCurrentHwProfileA](https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-getcurrenthwprofilea) -> Retrieves information about the current hardware profile for the local computer.

```cpp
#include <windows.h>
#include <stdio.h>
#include <iostream>

int main()
{
    HW_PROFILE_INFOA lpHwProfileInfo;
    if(!GetCurrentHwProfileA(&lpHwProfileInfo))
    {
        std::cout << "[+] Function failed :)" << std::endl;
        return 1;
    }

    std::cout << "[+] Hardware Profile Information:" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    switch (lpHwProfileInfo.dwDockInfo)
    {
    case 1:
        std::cout << "[+] dwDockInfo : DOCKINFO_UNDOCKED(0x1)" << std::endl;
        break;
    case 2:
        std::cout << "[+] dwDockInfo : DOCKINFO_DOCKED(0x2)" << std::endl;
        break;
    case 4:
        std::cout << "[+] dwDockInfo : DOCKINFO_USER_SUPPLIED(0x4)" << std::endl;
        break;
    case 5:
        std::cout << "[+] dwDockInfo : DOCKINFO_USER_DOCKED(0x5)" << std::endl;
        break;
    case 6:
        std::cout << "[+] dwDockInfo : DOCKINFO_USER_UNDOCKED(0x6)" << std::endl;
        break;
    default:
        break;
    }
    std::cout << "[+] Globally unique identifier (GUID), szHwProfileGuild : " << lpHwProfileInfo.szHwProfileGuid << std::endl;
    std::cout << "[+] display name for the current hardware profile, szHwProfileName : " << lpHwProfileInfo.szHwProfileName << std::endl; 
    return 0;
}
```
