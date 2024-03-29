#include <windows.h>
#include <iostream>

DWORD WINAPI threadFunc(LPVOID lpParam){
    std::cout << "[+] Thread executed." << std::endl;
    return 0;
}

int main(){
    DWORD threadID;

    HANDLE threadHandle = CreateThread(
        NULL,
        0,
        threadFunc,
        NULL,
        0,
        &threadID
    );

    LPCONTEXT threadContext;

    if(!GetThreadContext(threadHandle, threadContext)){
        std::cout << "[-] GetThreadContext failed :)" << std::endl;
    }

    std::cout << "[+] ContextFlags : " << std::hex << "0x" << threadContext->ContextFlags << std::endl;
    std::cout << "[+] EFlags : " << std::hex << "0x" << threadContext->EFlags << std::endl;
    std::cout << "[+] Rax : " << std::hex << "0x" << threadContext->Rax << std::endl;
    std::cout << "[+] Rcx : " << std::hex << "0x" << threadContext->Rcx << std::endl;
    std::cout << "[+] Rdx : " << std::hex << "0x" << threadContext->Rdx << std::endl;
    std::cout << "[+] Rip : " << std::hex << "0x" << threadContext->Rip << std::endl;
    std::cout << "[+] DebugControl : " << std::hex << "0x" << threadContext->DebugControl << std::endl;

    WaitForSingleObject(threadHandle, INFINITE);
    CloseHandle(threadHandle);
    return 0;
}
