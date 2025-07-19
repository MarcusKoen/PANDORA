#include <iostream>
using namespace std;

int main()
{
    int code = 8008;
    int test = 0;
    cout << "Please enter the code" << endl;

    while(test != code)
    {
        cin >> test;
        cout << "Wrong code!" << endl;
    }
        cout << "Congrats" << endl;

    return 0;
}
