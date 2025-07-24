#include <iostream>
using namespace std;

int main() {
    int input;
    cout << "Enter the code: ";
    cin >> input;

    // Obfuscated logic
    int a = (input ^ 1337) + 42;
    int b = a - 1379;
    int c = ((b * 3) + 7) / 3;

    if (((c == 0 || c == 1) && c != 1) || c == 1337) { // Opaque
        if (input == 12345) {
            cout << "Too obvious!" << endl;
        } else {
            cout << "Nope!" << endl;
        }
    }

    if ((input ^ 1337) == 1337) {
        cout << "Nice try!" << endl;
        return 0;
    }

    if ((((input ^ 1337) + 42 - 1379) * 3 + 7) / 3 == 0) {
        cout << "Congrats!" << endl;
    } else {
        cout << "Wrong code!" << endl;
    }

    return 0;
}
