[GetUserNameA](https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-getusernamea) -> Retrieves the name of the user associated with the current thread.

```cpp
#include <windows.h>
#include <iostream>
#include <lmcons.h>

int main()
{
    char name[UNLEN + 1];
    DWORD nameSize = UNLEN + 1;
    if(!GetUserNameA(name, &nameSize))
    {
        std::cout << "[+] Function failed :)" << std::endl;
        std::cout << GetLastError() << std::endl;
        return 0;
    }
    std::cout << "[+] Name of the user associated with the current thread : " << name << std::endl;

    return 0;
}
```
