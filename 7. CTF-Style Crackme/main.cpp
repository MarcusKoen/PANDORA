#include <iostream>
#include <string>

using namespace std;

bool validate(const string& input) {
    if (input.length() != 20) return false;

    string xor_key = "supersecretkey12345";
    for (size_t i = 0; i < input.length(); ++i) {
        if ((input[i] ^ xor_key[i % xor_key.length()]) != (10 + i)) {
            return false;
        }
    }

    return true;
}

int main() {
    string userInput;
    cout << "Enter the flag: ";
    cin >> userInput;

    if (validate(userInput)) {
        cout << "🎉 Correct! Flag accepted." << endl;
    } else {
        cout << "❌ Incorrect flag." << endl;
    }

    return 0;
}
