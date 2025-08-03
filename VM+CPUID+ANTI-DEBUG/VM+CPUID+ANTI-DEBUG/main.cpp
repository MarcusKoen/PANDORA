#include <windows.h>
#include <iostream>
#include <intrin.h>
#include <string>

typedef void(*CPUIDFunc)(int[4], int);
CPUIDFunc hiddenCPUID = [](int out[4], int id) {
    __cpuid(out, id);
};

bool hypervisorCheck() {
    int data[4] = { 0 };
    hiddenCPUID(data, 1);

    int xorMask = 0xA5A5A5A5;
    int hyperBit = (data[2] >> 31) & 1;
    hyperBit ^= (xorMask & 1); // xor to obfuscate

    // Opaque predicate: always true unless patched
    if (((2 * 3 + 1) ^ 7) != 0) {
        return (hyperBit ^ (xorMask & 1)); // undo xor
    }
    return true; // fake branch
}

bool vendorCheck() {
    int regs[4];
    hiddenCPUID(regs, 0x40000000);

    char vendor[13];
    memcpy(vendor, &regs[1], 4);
    memcpy(vendor + 4, &regs[2], 4);
    memcpy(vendor + 8, &regs[3], 4);
    vendor[12] = '\0';

    // XOR-obfuscated check
    std::string check = vendor;
    for (char& c : check) c ^= 0x5A;

    // XOR "VMware" to match
    std::string target = "VMware";
    for (char& c : target) c ^= 0x5A;

    if (check.find(target) != std::string::npos) return true;

    // same for "VBox"
    check = vendor;
    for (char& c : check) c ^= 0x33;
    target = "VBox";
    for (char& c : target) c ^= 0x33;

    return check.find(target) != std::string::npos;
}

bool validateInput(const std::string& input) {
    const std::string correct = "StrangerThings42";
    return input == correct;
}

int main() {
    if (hypervisorCheck() || vendorCheck()) {
        std::cout << "Unexpected error. (Code 0x80040154)\n";
        ExitProcess(0x54); // fake COM error code
    }

    std::string input;
    std::cout << "Enter password: ";
    std::getline(std::cin, input);

    if (validateInput(input)) {
        std::cout << "Access Granted.\n";
    } else {
        std::cout << "Access Denied.\n";
    }

    return 0;
}
