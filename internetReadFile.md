[InternetOpenA](https://learn.microsoft.com/en-us/windows/win32/api/wininet/nf-wininet-internetopena) -> [InternetOpenUrlA](https://learn.microsoft.com/en-us/windows/win32/api/wininet/nf-wininet-internetopenurla) -> [InternetReadFile](https://learn.microsoft.com/en-us/windows/win32/api/wininet/nf-wininet-internetreadfile) -> [InternetCloseHandle](https://learn.microsoft.com/en-us/windows/win32/api/wininet/nf-wininet-internetclosehandle)

Command to compile: x86_64-w64-mingw32-g++ file.cpp -o file.exe -lwininet

```cpp
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <wininet.h>

#pragma comment(lib, "wininet")

int main()
{
    char buffer[4096];
    DWORD bytesRead;
    HINTERNET hInternet = InternetOpenA("Internet sample", 0, 0, 0, 0);
    HINTERNET hConnect = InternetOpenUrlA(hInternet, "https://0xk4n3ki.github.io/robots.txt", 0, 0, 0x80000000, 0);
    if(!hConnect)
    {
        std::cout << "[+] Connection failed :)" << std::endl;
        return 1;
    }
    BOOL result = InternetReadFile(hConnect, buffer, sizeof(buffer), &bytesRead);
    if(result)
    {
        std::cout << buffer << std::endl;
    }else
    {
        std::cout << "[+] couldn't read :)" << std::endl;
        return 1;
    }
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);
    return 0;
}
```
