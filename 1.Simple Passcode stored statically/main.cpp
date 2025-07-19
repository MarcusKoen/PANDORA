#include <iostream>
using namespace std;

int main()
{
    int code = 8008;
    int test = 0;
    cout << "Please enter the code" << endl;
    cin >> test;

    if(test != code)
    {
        cout << "Wrong code!" << endl;
    }
    else
    {
        cout << "Congrats" << endl;
    }
    return 0;
}
