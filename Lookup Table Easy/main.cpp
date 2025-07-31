#include <iostream>
#include <string>

char lookupTable[] = "abcdefghijklmnopqrstuvwxyz0123456789";

std::string getPassword() {
    int indices[] = {18, 4, 2, 17, 4, 19}; // 'secret'
    std::string password;
    for (int i = 0; i < sizeof(indices)/sizeof(indices[0]); ++i) {
        password += lookupTable[indices[i]];
    }
    return password;
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
