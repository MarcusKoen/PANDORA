Crackme 3: Custom VM-Based Challenge (Step-by-Step)
🎯 Goal:

Create a VM interpreter to hide logic from static analysis.
Step 1: Define a Bytecode Language

enum OpCode {
    LOAD = 1,
    ADD = 2,
    SUB = 3,
    CMP = 4,
    JMP = 5,
    JZ  = 6,
    END = 255
};

Step 2: Create a Mini Interpreter

#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<unsigned char> bytecode = {
        LOAD, 0,     // load 0 into reg
        ADD, 5,      // add 5
        SUB, 2,      // subtract 2
        CMP, 3,      // compare to 3
        JZ, 10,      // jump to 10 if zero
        JMP, 0,      // else restart
        END          // end
    };

    int pc = 0;
    int reg = 0;
    bool running = true;
    int cmp = 0;

    while (running) {
        unsigned char op = bytecode[pc++];
        switch (op) {
            case LOAD: reg = bytecode[pc++]; break;
            case ADD: reg += bytecode[pc++]; break;
            case SUB: reg -= bytecode[pc++]; break;
            case CMP: cmp = reg - bytecode[pc++]; break;
            case JZ: if (cmp == 0) pc = bytecode[pc]; else pc++; break;
            case JMP: pc = bytecode[pc]; break;
            case END:
                running = false;
                cout << "Congrats, you beat the VM crackme!" << endl;
                break;
        }
    }

    return 0;
}

Step 3: Make It a Challenge

    Hide or encrypt the bytecode

    Allow user input to affect bytecode validation

    Move the bytecode to .data or allocate it dynamically

Step 4: Challenge Idea

vector<unsigned char> bytecode = {
    LOAD, 0, ADD, 7, CMP, 7, JZ, 10, END
};

Make the user enter the number 0 to trigger a sequence resulting in 7 → success.
