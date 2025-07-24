#include <windows.h>
#include <iostream>

using namespace std;

bool detectDebugger() {
    // Method 1: Standard API
    if (IsDebuggerPresent()) return true;

    // Method 2: Timing attack
    DWORD start = GetTickCount();
    for (volatile int i = 0; i < 1000000; ++i); // delay loop
    DWORD elapsed = GetTickCount() - start;
    return elapsed > 500; // too slow? probably breakpoint
}

int obfuscated(int input) {
    return (((input * 1337) + 42069) % 10000) - 337;
}

int main() {
    if (detectDebugger()) {
        cout << "Debugger detected. Exiting..." << endl;
        return 1;
    }

    int code;
    cout << "Enter the secret code: ";
    cin >> code;

    if (obfuscated(code) == 8008) {
        cout << "Access Granted!" << endl;
    } else {
        cout << "Wrong code." << endl;
    }

    return 0;
}
