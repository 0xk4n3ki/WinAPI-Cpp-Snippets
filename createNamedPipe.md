# Pipes

Client-Server Communication: Pipes can be employed to establish communication channels between client and server processes. The server process listens on a named pipe, and clients can connect to it to send requests and receive responses. This is commonly used in client-server architectures for various applications, such as interprocess communication in distributed systems.


## <span style="color:red">Server Code</span>

[CreateNamedPipe](https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-createnamedpipea) -> [ConnectNamedPipe](https://learn.microsoft.com/en-us/windows/win32/api/namedpipeapi/nf-namedpipeapi-connectnamedpipe) -> [ReadFile](https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-readfile) -> [WriteFile](https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-writefile) -> [DisconnectNamedPipe](https://learn.microsoft.com/en-us/windows/win32/api/namedpipeapi/nf-namedpipeapi-disconnectnamedpipe) -> [CloseHandle](https://learn.microsoft.com/en-us/windows/win32/api/handleapi/nf-handleapi-closehandle)
```cpp
#include <iostream>
#include <windows.h>

#define BUFFER_SIZE 1024

int main()
{
    HANDLE hPipe;
    char buffer[BUFFER_SIZE];
    DWORD bytesRead;

    hPipe = CreateNamedPipeA(
        "\\\\.\\pipe\\myPipe",
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_BYTE | PIPE_WAIT,
        1,
        BUFFER_SIZE,
        BUFFER_SIZE,
        0,
        NULL
    );

    if(hPipe == INVALID_HANDLE_VALUE)
    {
        std::cout << "[+] Failed to create pipe. Error: " << GetLastError() << std::endl;
        return 1;
    }

    if(ConnectNamedPipe(hPipe, NULL))
    {
        std::cout << "[+] Client connected to the pipe." << std::endl;
        Sleep(5000);

        if(ReadFile(hPipe, buffer, BUFFER_SIZE, &bytesRead, NULL))
        {
            std::cout << "[+] Data received from client: " << buffer << std::endl;
            Sleep(5000);
        }
        else
        {
            std::cout << "[+] Failed to read data from the pipe. Error: " << GetLastError() << std::endl;
        }

        const char* response = "Hello, client!";
        if(WriteFile(hPipe, response, strlen(response)+1, NULL, NULL))
        {
            std::cout << "[+] Response sent to the client." << std::endl;
        }
        else
        {
            std::cout << "[+] Failed to write data to the pipe. Error: " << GetLastError() << std::endl;
        }

        DisconnectNamedPipe(hPipe);
    }
    else
    {
        std::cout << "Failed to connect to the pipe. Error: " << GetLastError() << std::endl;
    }

    CloseHandle(hPipe);

    return 0;
}
```

Client Code

[CreateFileA](https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilea) -> [WriteFile](https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-writefile) -> [ReadFile](https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-readfile) -> [CloseHandle](https://learn.microsoft.com/en-us/windows/win32/api/handleapi/nf-handleapi-closehandle)
```cpp
#include <iostream>
#include <windows.h>

#define BUFFER_SIZE 1024

int main()
{
    HANDLE hPipe;
    char buffer[BUFFER_SIZE];
    DWORD bytesRead;

    hPipe = CreateFileA(
        "\\\\.\\pipe\\myPipe",
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    if(hPipe == INVALID_HANDLE_VALUE)
    {
        std::cout << "[+] Failed to connect to the pipe. Error: " << GetLastError() << std::endl;
        return 1;
    }

    const char* message = "Hello, server!";
    if(WriteFile(hPipe, message, strlen(message)+1, NULL, NULL))
    {
        std::cout << "[+] Data sent to server." << std::endl;
        Sleep(5000);
    }
    else
    {
        std::cout << "[+] Failed to write data to the pipe. Error: " << GetLastError() << std::endl;
    }

    if(ReadFile(hPipe, buffer, BUFFER_SIZE, &bytesRead, NULL))
    {
        std::cout << "[+] Response received from server: " << buffer << std::endl;
    }
    else
    {
        std::cout << "[+] Failed to read data from the pipe. Error: " << GetLastError() << std::endl;
    }

    CloseHandle(hPipe);

    return 0;
}
```
