#include <iostream>
#include <string>

int generateSerial(const std::string& name) {
    int sum = 0;
    for (char c : name) {
        sum += static_cast<int>(c);
    }
    return (sum * 3) + 1337;
}

int main() {
    std::string name;
    std::string serialInput;

    std::cout << "Enter your name: ";
    std::getline(std::cin, name);

    std::cout << "Enter your serial: ";
    std::getline(std::cin, serialInput);

    int correctSerial = generateSerial(name);

    if (std::to_string(correctSerial) == serialInput) {
        std::cout << "Access Granted!" << std::endl;
    } else {
        std::cout << "Access Denied." << std::endl;
    }

    return 0;
}
