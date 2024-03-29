[ShellExecuteA](https://learn.microsoft.com/en-us/windows/win32/api/shellapi/nf-shellapi-shellexecutea) -> Sets the specified window's show state.

```cpp
HINSTANCE ShellExecuteA(
  [in, optional] HWND   hwnd,
  [in, optional] LPCSTR lpOperation,
  [in]           LPCSTR lpFile,
  [in, optional] LPCSTR lpParameters,
  [in, optional] LPCSTR lpDirectory,
  [in]           INT    nShowCmd
);
```

This code is developed to execute an executable by using the verb "runas".

```cpp
#include <windows.h>
#include <iostream>
#include <stdio.h>

int main()
{
    const char* lpOperation = "runas";
    const char* lpFile = "E:\\test.exe";
    const char* lpDirectory = NULL;
    INT nShowCmd = SW_SHOW;
    HINSTANCE result = ShellExecuteA(NULL, lpOperation, lpFile, NULL, lpDirectory, nShowCmd);
    
    if ((INT_PTR)result <= 32)
    {
        // An error occurred
        switch ((INT_PTR)result)
        {
            case SE_ERR_FNF:
                printf("File not found!\n");
                break;
            case SE_ERR_PNF:
                printf("Path not found!\n");
                break;
            case SE_ERR_ACCESSDENIED:
                printf("Access denied!\n");
                break;
            // Handle other error cases as needed
            default:
                printf("Failed to launch the executable! Error code: %d\n", (INT_PTR)result);
                break;
        }
    }
    else
    {
        printf("Executable launched successfully!\n");
    }

    return 0;
}
```
