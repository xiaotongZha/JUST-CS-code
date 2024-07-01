#include <windows.h>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>

#define SLEEP(x) std::this_thread::sleep_for(std::chrono::seconds(x))
#define SLEEP_MILLI(x) std::this_thread::sleep_for(std::chrono::milliseconds(x))

#define WORK 1
#define EXIT 0

int state = WORK;
std::mutex mtx;

void workChild1ToChild2(HANDLE readPipe, HANDLE writePipe) {
    char buffer[1024];
    while (true) {
        mtx.lock();
        if (state == EXIT) {
            mtx.unlock();
            break;
        }
        mtx.unlock();
        DWORD bytesRead, bytesWritten;
        memset(buffer, 0, sizeof(buffer));
        while (ReadFile(readPipe, buffer, sizeof(buffer), &bytesRead, NULL) && bytesRead != 0) {
            std::cout << buffer << '\n';
            WriteFile(writePipe, buffer, bytesRead, &bytesWritten, NULL);
            break;
        }
    }
}

void workChild2ToChild1(HANDLE readPipe, HANDLE writePipe) {
    char buffer[1024];
    while (true) {
        mtx.lock();
        if (state == EXIT) {
            mtx.unlock();
            break;
        }
        mtx.unlock();
        DWORD bytesRead, bytesWritten;
        memset(buffer, 0, sizeof(buffer));
        while (ReadFile(readPipe, buffer, sizeof(buffer), &bytesRead, NULL) && bytesRead != 0) {
            if (strncmp(buffer, "exit", 4) == 0) {
                mtx.lock();
                state = EXIT;
                mtx.unlock();
            }
            WriteFile(writePipe, buffer, bytesRead, &bytesWritten, NULL);
            break;
        }
    }
}


int main() {
    // 创建四个管道
    HANDLE hChild1StdinRd, hChild1StdinWr, hChild1StdoutRd, hChild1StdoutWr;
    HANDLE hChild2StdinRd, hChild2StdinWr, hChild2StdoutRd, hChild2StdoutWr;

    SECURITY_ATTRIBUTES saAttr = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };

    CreatePipe(&hChild1StdoutRd, &hChild1StdoutWr, &saAttr, 0);
    SetHandleInformation(hChild1StdoutRd, HANDLE_FLAG_INHERIT, 0);
    CreatePipe(&hChild1StdinRd, &hChild1StdinWr, &saAttr, 0);
    SetHandleInformation(hChild1StdinWr, HANDLE_FLAG_INHERIT, 0);

    CreatePipe(&hChild2StdoutRd, &hChild2StdoutWr, &saAttr, 0);
    SetHandleInformation(hChild2StdoutRd, HANDLE_FLAG_INHERIT, 0);
    CreatePipe(&hChild2StdinRd, &hChild2StdinWr, &saAttr, 0);
    SetHandleInformation(hChild2StdinWr, HANDLE_FLAG_INHERIT, 0);

    // 启动程序1
    STARTUPINFO si1 = { sizeof(STARTUPINFO) };
    PROCESS_INFORMATION pi1;
    si1.hStdError = hChild1StdoutWr;
    si1.hStdOutput = hChild1StdoutWr;
    si1.hStdInput = hChild1StdinRd;
    si1.dwFlags |= STARTF_USESTDHANDLES;

    wchar_t program1[] = L"circuit.exe";
    if (!CreateProcess(NULL, program1, NULL, NULL, TRUE, 0, NULL, NULL, &si1, &pi1)) {
        std::cerr << "Error creating process 1\n";
        return 1;
    }

    // 启动程序2
    STARTUPINFO si2 = { sizeof(STARTUPINFO) };
    PROCESS_INFORMATION pi2;
    si2.hStdError = hChild2StdoutWr;
    si2.hStdOutput = hChild2StdoutWr;
    si2.hStdInput = hChild2StdinRd;
    si2.dwFlags |= STARTF_USESTDHANDLES;

    //const wchar_t* pythonExe = L"python.exe";
    //const wchar_t* pythonScript = L"draw.py";

    //wchar_t commandLine[60];
    //swprintf_s(commandLine, L"%s %s", pythonExe, pythonScript);

    wchar_t program2[] = L"draw.exe";
    if (!CreateProcess(NULL, program2, NULL, NULL, TRUE, 0, NULL, NULL, &si2, &pi2)) {
        std::cerr << "Error creating process 2\n";
        return 1;
    }

    // 关闭不需要的句柄
    CloseHandle(hChild1StdoutWr);
    CloseHandle(hChild1StdinRd);
    CloseHandle(hChild2StdoutWr);
    CloseHandle(hChild2StdinRd);

    std::thread threadChild1ToChild2(workChild1ToChild2, hChild1StdoutRd, hChild2StdinWr);
    std::thread threadChild2ToChild1(workChild2ToChild1, hChild2StdoutRd, hChild1StdinWr);


    // 等待线程结束
    threadChild1ToChild2.join();
    threadChild2ToChild1.join();

    // 关闭剩余的句柄
    CloseHandle(hChild1StdoutRd);
    CloseHandle(hChild2StdoutRd);

    // 等待子进程退出
    WaitForSingleObject(pi1.hProcess, INFINITE);
    WaitForSingleObject(pi2.hProcess, INFINITE);

    // 关闭进程和线程句柄
    CloseHandle(pi1.hProcess);
    CloseHandle(pi1.hThread);
    CloseHandle(pi2.hProcess);
    CloseHandle(pi2.hThread);

    return 0;
}
