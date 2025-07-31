#include <iostream>
#include <string>
#include <windows.h>

bool isDebugged() {
    if (IsDebuggerPresent())
        return true;

    DWORD start = GetTickCount();
    for (volatile int i = 0; i < 1000000; ++i); // artificial delay
    DWORD end = GetTickCount();

    return (end - start > 300); // if debugging, loop takes longer
}

char table[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

uint8_t obf[] = { 18 ^ 0x2A, 4 ^ 0x2A, 2 ^ 0x2A, 17 ^ 0x2A, 4 ^ 0x2A, 19 ^ 0x2A }; // 'secret'

std::string getPassword() {
    std::string result;
    for (int i = 0; i < sizeof(obf); ++i) {
        result += table[obf[i] ^ 0x2A];
    }
    return result;
}

int main() {
    if (isDebugged()) {
        std::cout << "Debugger detected. Exiting.\n";
        return 1;
    }

    std::string input;
    std::cout << "Enter password: ";
    std::cin >> input;

    if (input == getPassword()) {
        std::cout << "Access Granted!\n";
    } else {
        std::cout << "Access Denied.\n";
    }

    return 0;
}
