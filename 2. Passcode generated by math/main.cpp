//Absolutely horrid coding
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{

    int test = 0;
    string code;

    srand(time(0));
    int ranNumber = rand() % 5; //random number between 0 and 4


    int arrayEvenNum[5] = {0,2,4,6,8};
    int arrayOddNum[5] = {1,3,5,7,9};
    char arrayChars[2] = {'A', 'F'};

    int ranEven = arrayEvenNum[ranNumber];
    int ranOdd = arrayOddNum[ranNumber];
    char ranChar = arrayChars[rand() % 2];

    code = to_string(ranEven)+ranChar+ to_string(3) +to_string(ranOdd);


    cout << code << endl;

   /* string text = "herllo";
    cout << text[2] << endl;
    rand();

    // Get a different random number each time the program runs


    // Generate a random number between 0 and 100
    int randomNum = rand() % 101;

    cout << randomNum;
*/
    /*
    cout << "Please enter the code" << endl;

    while(test != code)
    {
        cin >> test;
        cout << "Wrong code!" << endl;
    }
        cout << "Congrats" << endl;
*/
    return 0;
}
