#include <iostream>
#include <Windows.h>
#include <string> 

int main()
{
    std::string fileName;
    std::cout << "[+] Enter the name of the file : ";
    std::cin >> fileName;

    std::cin.ignore();

    HANDLE fileHandle = CreateFileA(
        fileName.c_str(),
        FILE_APPEND_DATA | FILE_READ_ACCESS | FILE_WRITE_ACCESS,
        0,
        NULL,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
    if (fileHandle == INVALID_HANDLE_VALUE) {
        std::cout << "[-] CreateFile function failed :)" << std::endl;
        return 1;
    }
    else {
        std::cout << "[+] CreateFile created the file <3" << std::endl;
    }

    std::cout << "[+] Two options:" << std::endl;
    std::cout << "[+] 1. WriteFile" << std::endl;
    std::cout << "[+] 2. ReadFile" << std::endl;
    std::cout << "[+] Choose 1/2: ";
    int option;
    std::cin >> option;
    std::cin.ignore();

    if (option == 1) {
        std::string buffer;
        std::cout << "[+] Enter the data to write into file : ";
        std::getline(std::cin, buffer);
        buffer += '\n';
        size_t length = buffer.size();
        BOOL fileWrite = WriteFile(
            fileHandle,
            buffer.c_str(),
            static_cast<DWORD>(length),
            NULL,
            NULL
        );
        if (!fileWrite) {
            std::cout << "[-] WriteFile function failed :)" << std::endl;
            CloseHandle(fileHandle);
            return 1;
        }
        else {
            std::cout << "[+] Buffer written to file <3" << std::endl;
        }
    }
    else if (option == 2) {
        const int bufferSize = 1024;
        char lpbuffer[bufferSize] = { 0 };
        DWORD bytesRead;
        BOOL fileRead = ReadFile(
            fileHandle,
            lpbuffer,
            bufferSize - 1,
            &bytesRead,
            NULL
        );
        if (fileRead) {
            std::cout << "[+] ReadFile function succeeded <3" << std::endl;
        }
        else {
            std::cout << "[-] ReadFile function failed : " << GetLastError() << std::endl;
            CloseHandle(fileHandle);
            return 1;
        }
        lpbuffer[bytesRead] = '\0';
        std::cout << "[+] File content : " << lpbuffer << std::endl;

    }
    CloseHandle(fileHandle);

    return 0;
}
