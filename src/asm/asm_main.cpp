#include <iostream>
#include "assembler.cpp"

using namespace std;

int main(int argc, char** argv) {
    if(argc == 1) {
        cout << "Specify .ily file(s) in ./in/ to assemble" << endl;
        exit(0);
    }

    if(*(argv[1]) == '*') { // Assemble every file in ./in/
        // TODO: this is just gonna be iterating over every directory entry instead of argv
    }
    else { // Assemble just what they specify
        for(int i = 1; argv[i] != NULL; i++)
            assemble(argv[i]);
    }

    return 0;
}

