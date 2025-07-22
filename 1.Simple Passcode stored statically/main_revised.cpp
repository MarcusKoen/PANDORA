#include <iostream>
using namespace std;

int main()
{
    int code = 80085;
    int test = 0;
    char choice;

    do {
        cout << "Please enter the code" << endl;
        bool correct = false;

        while (!correct) {
            cin >> test;

            if (test != code) {
                cout << "Wrong code!" << endl;
            } else {
                cout << "Congrats" << endl;
                correct = true;
            }
        }

        cout << "Do you want to try again? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    cout << "Program exiting..." << endl;
    return 0;
}
