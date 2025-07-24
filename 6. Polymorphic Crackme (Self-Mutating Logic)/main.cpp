#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    // Randomize key logic at compile/run time
    int op = rand() % 3; // 0=add, 1=sub, 2=xor
    int key = rand() % 5000 + 1000;
    int result = rand() % 5000 + 1000;

    cout << "Enter the secret code: ";
    int input;
    cin >> input;

    bool success = false;

    switch (op) {
        case 0:
            success = ((input + key) == result);
            break;
        case 1:
            success = ((input - key) == result);
            break;
        case 2:
            success = ((input ^ key) == result);
            break;
    }

    if (success) {
        cout << "✅ Success! Code accepted." << endl;
    } else {
        cout << "❌ Incorrect code." << endl;
    }

    // Print misleading junk logic (obfuscation)
    int junk = (input * 3) ^ (key >> 1);
    if (junk % 7 == 0 && junk > 42) {
        cout << "Debug path triggered!" << endl;
    }

    return 0;
}
