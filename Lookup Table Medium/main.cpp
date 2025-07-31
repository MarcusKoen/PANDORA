#include <iostream>
#include <string>

char lookupTable[] = { 'x', 's', 'e', 'c', 'r', 't', '1', '2', '3' };  // useful letters mixed with junk
uint8_t encoded[] = { 1 ^ 0x55, 2 ^ 0x55, 3 ^ 0x55, 4 ^ 0x55, 2 ^ 0x55, 5 ^ 0x55 }; // 'secret'

std::string getPassword() {
    std::string result;
    for (auto code : encoded) {
        uint8_t index = code ^ 0x55;
        result += lookupTable[index];
    }
    return result;
}

int main() {
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
