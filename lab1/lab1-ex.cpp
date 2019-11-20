//CSE 570 - Compilers
//Winter 2019
//Instructor: Dr. Ernesto Gomez
//Name: Phillip Pascual
//
//Filename: lab1.cpp
//Description: DFA simulation, takes in a string and determines if valid using
//             the following rule:
//             L = (a|b)*abb

#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <array>
#define MAX_ALPHABET_SIZE 2 

using namespace std;

//Function to check whether input string is valid or invalid.  Takes in the
//input string, transition table, and final state table.   Returns true/false 
//based on value in final state table.
bool dfa(string input, const int table[][MAX_ALPHABET_SIZE], const bool fin[])
{
    for (int i = 0; i < input.size(); ++i)
    {
        cout << input[i] << " ";
    }
    cout << endl;
    int index;
    int state= 0;
    for (int i = 0; i < input.size(); ++i)
    {
        index = input[i] - 'a';
        cout << "index = " << index << " ";

        state = table[state][index];
        cout << "State = " << state << endl;
    }
    cout << endl;
    return fin[state];
}

int main() {
//Transition table is a 2D array, row indices are the current state, column
//indices are the input.  The transition table is arranged as follows:
//state         'a'             'b'
//0         NEXT STATE      NEXT STATE
//1         NEXT STATE      NEXT STATE
//2         NEXT STATE      FINAL STATE
//3         NEXT STATE      NEXT STATE
//
//      FOR L = (a|b)*abb
//
//The dfa() function will use this passed in table to determine next state for
//each input and current state.
    const int transitionTable[4][2] = {{1,0}, {1,2}, {1,3}, {1,0}}; 
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            cout << transitionTable[i][j] << " ";
        }
        cout << endl;
    }
        string inputString;

//Final state table is an array, column indices are the final state.  Elements
//are true or false.
    const bool finalState[4] = {0, 0, 0, 1};

    cout << "Enter string to analyze: " << endl;
    cin >> inputString;

    if (dfa(inputString, transitionTable, finalState))
    {
        cout << "String is valid." << endl;
    }
    else
    {
        cout << "String is not valid." << endl;
    }

    return 0;
}

