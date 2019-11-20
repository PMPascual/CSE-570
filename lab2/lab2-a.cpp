//CSE 570
//Winter 2019
//Phillip Pascual
//Filename: lab2-a.cpp
//Description: Takes in a file of nonterminals and productions.  Stores
//nonterminals, terminals, and productions into separate vectors and displays.
//Then computes the First and Follow sets for all terminals and nonterminals
//and displays.

#include <fstream>
#include <iostream>
#include <set>
#include <vector>
#include <cstring>

using namespace std;

//Displays all the sets.  Takes in the set to be displayed.
void display(set<char> firsts[])
{
    for (int i = 0; i < 128; ++i)
    {
        if (!firsts[i].empty())
        {
            cout << "Firsts(" << (char)i << ") = {";
            for (set<char>::iterator j = firsts[i].begin(); j != firsts[i].end();
                 ++j)
            {
                cout << *j << " ";
            }
            cout << "}" <<  endl;
        }
    }
}

void displayFollows(set<char> follows[])
{
    for (int i = 0; i < 128; ++i)
    {
        if (!follows[i].empty())
        {
            cout << "Follows(" << (char)i << ") = {";
            for (set<char>::iterator j = follows[i].begin(); j != follows[i].end();
                 ++j)
            {
                cout << *j << " ";
            }
            cout << "}" << endl;
        }
    }
}

int main()
{
    string toCheck;
    char initChar;
    vector<char> terminals;
    vector<char> nonterminals;
    vector<string> productions;

    set<char> firsts[128];          //To hold firsts, char's ASCII will
                                    //correspond to index in firsts
    set<char> follows[128];         //To hold follows, char's ASCII will
                                    //correspond to index in follows

    fstream input;
    input.open("g419", ios::in);

    input >> initChar;

    //Adding terminals to vector
    while (initChar != '$')
    {
        terminals.push_back(initChar);
        input >> initChar;
    }

    input >> toCheck;

    //Adding nonterminals to vector
    while (toCheck != "$")
    {
        initChar = toCheck[0];
        
        nonterminals.push_back(initChar);
        productions.push_back(toCheck);
        input >> toCheck;
    }

    //To display terminals
    cout << "Terminals: " << endl;
    for (int i = 0; i < terminals.size(); ++i) 
    {
        cout << terminals[i] << " ";
    }
    cout << endl;
    cout << endl;

    //To display nonterminals
    cout << "Nonterminals: " << endl;
    for (int i = 0; i < nonterminals.size(); ++i)
    {
        cout << nonterminals[i] << " ";
    }
    cout << endl;
    cout << endl;

    //To display productions
    cout << "Productions: " << endl;
    for (int i = 0; i < productions.size(); ++i)
    {
        cout << productions[i] << endl;
    }
    cout << endl;
        
    //Rule 1 of First Sets: If X is nonterminal, then First(X) = {X}
    //So, adding terminals to their own index in firsts[]
    for (int i = 0; i < terminals.size(); ++i)
    {
        firsts[terminals[i]].insert(terminals[i]);
    }

    bool change, isTerminal, derivesEpsilon;
    int oldSize, newSize, checkIndex;
    do
    {
        change = true;
        for (int i = 0; i < productions.size(); ++i)
        {
            string toCheck = productions[i];
            //cout << "toCheck = " << toCheck << endl;

            char expression = toCheck[0];
            //cout << "expression = " << expression << endl;

            for (int j = 3; j < toCheck.size(); ++j)
            {
                derivesEpsilon = false;
                //cout << "toCheck[j] = " << toCheck[j] << endl;
                
                //Checks to see if character being checked is a terminal
                isTerminal = false;
                for (int i = 0; i < terminals.size(); ++i)
                {
                    if (terminals[i] == toCheck[j])
                    {
                        isTerminal = true;
                    }
                }
                if (toCheck[j] == 'e' && j == 3)
                {
                    firsts[expression].insert('e');
                    change = true;
                    break;
                    //cout << "Adding e" << endl;
                }
                if (!firsts[toCheck[j]].empty())
                {
                    //cout << "Adding..." << endl;
                    oldSize = firsts[expression].size();
                    for (set<char>::iterator it = firsts[toCheck[j]].begin();
                         it != firsts[toCheck[j]].end(); it++)
                    {
                        if (*it != 'e')
                        {
                            firsts[expression].insert(*it);
                        }
                        else if (*it == 'e')
                        {
                            derivesEpsilon = true;
                        }
                    }
                    newSize = firsts[expression].size();
                    if (oldSize == newSize)
                    {
                        change = false;
                    }
                }
                if (isTerminal || !derivesEpsilon)
                {
                    break;
                }
            }
        }
    } while (change);

    //Traverses table from bottom up to make sure that all firsts are moved
    //to appropriate elements where rules apply
    for (int i = productions.size(); i >= 0; --i)
    {
        string toCheck = productions[i];
        //cout << "toCheck = " << toCheck << endl;

        char expression = toCheck[0];
        //cout << "expression = " << expression << endl;

        for (int j = 3; j < toCheck.size(); ++j)
        {
            derivesEpsilon = false;
            //cout << "toCheck[j] = " << toCheck[j] << endl;
                
            //Checks to see if character being checked is a terminal
            isTerminal = false;
            for (int i = 0; i < terminals.size(); ++i)
            {
                if (terminals[i] == toCheck[j])
                {
                    isTerminal = true;
                }
            }
            if (toCheck[j] == 'e' && j == 3)
            {
                firsts[expression].insert('e');
                change = true;
                break;
                //cout << "Adding e" << endl;
            }
            if (!firsts[toCheck[j]].empty())
            {
                //cout << "Adding..." << endl;
                oldSize = firsts[expression].size();
                for (set<char>::iterator it = firsts[toCheck[j]].begin();
                    it != firsts[toCheck[j]].end(); it++)
                {
                    if (*it != 'e')
                    {
                        firsts[expression].insert(*it);
                    }
                    else if (*it == 'e')
                    {
                        derivesEpsilon = true;
                    }
                }
                newSize = firsts[expression].size();
                if (oldSize == newSize)
                {
                    change = false;
                }
            }
            if (isTerminal || !derivesEpsilon)
            {
                break;
            }
        }
    }
    display(firsts);
    cout << endl;
    cout << endl;
    bool hasEpsilon[128];  //Creating an array of bools to hold whether the 
                           //first set has an epsilon (e) in it or not.
    
    //Goes through array of firsts, if index has firsts, iterates through
    //firsts.  If any first is epsilon, sets hasEpsilon bool at index to true.
    for (int i = 0; i < 128; ++i)
    {
        if (!firsts[i].empty())
        {
            for (set<char>::iterator it = firsts[i].begin(); it != firsts[i].end();
                 ++it)
            {
                if (*it == 'e')
                {
                    hasEpsilon[i] = true;
                }
            }
        }
    }

    //Rule one of follows, placing $ in start symbol of G
    string followCheck = productions[0];
    //cout << "followCheck = " << followCheck << endl;
    char fChar = followCheck[0];
    //cout << "fChar = " << fChar << endl;
    follows[fChar].insert('$');

    do
    {
        change = true;
        for (int i = 0; i < productions.size(); ++i)
        {
            followCheck = productions[i];
            fChar = followCheck[0];
            if (followCheck.size() == 6 && followCheck[5] != 'e')
            {
                oldSize = follows[followCheck[4]].size();
                for (set<char>::iterator it = firsts[followCheck[5]].begin();
                     it != firsts[followCheck[5]].end(); ++it)
                {
                    if (*it != 'e')
                    {
                        follows[followCheck[4]].insert(*it);
                    }
                }
                newSize = follows[followCheck[4]].size();
                if (newSize == oldSize)
                {
                    change = false;
                }
            }
            if (followCheck.size() == 6 && hasEpsilon[followCheck[5]])
            {
                oldSize = follows[followCheck[4]].size();
                for (set<char>::iterator it = follows[fChar].begin();
                     it != follows[fChar].end(); ++it)
                {
                    follows[followCheck[4]].insert(*it);
                }
                newSize = follows[followCheck[4]].size();
                if (newSize == oldSize)
                {
                    change = false;
                }
            }
            if (followCheck.size() == 5 && followCheck[4] != 'e')
            {
                oldSize = follows[followCheck[4]].size();
                for (set<char>::iterator it = follows[fChar].begin();
                     it != follows[fChar].end(); ++it)
                {
                    follows[followCheck[4]].insert(*it);
                }
                newSize = follows[followCheck[4]].size();
                if (newSize == oldSize)
                {
                    change = false;
                }
            }
        }
    } while (change);

    for (int i = productions.size(); i >= 0; --i)
    {
        followCheck = productions[i];
        fChar = followCheck[0];
        if (followCheck.size() >= 6 && followCheck[5] != 'e')
        {
            oldSize = follows[followCheck[4]].size();
            for (set<char>::iterator it = firsts[followCheck[5]].begin();
                it != firsts[followCheck[5]].end(); ++it)
            {
                if (*it != 'e')
                {
                    follows[followCheck[4]].insert(*it);
                }
            }
            newSize = follows[followCheck[4]].size();
        }
        if (followCheck.size() >= 6 && hasEpsilon[followCheck[5]])
        {
            oldSize = follows[followCheck[4]].size();
            for (set<char>::iterator it = follows[fChar].begin();
                it != follows[fChar].end(); ++it)
            {
                follows[followCheck[4]].insert(*it);
            }
            newSize = follows[followCheck[4]].size();
            if (newSize == oldSize)
            {
                change = false;
            }
        }
        if (followCheck.size() == 5 && followCheck[4] != 'e')
        {
            oldSize = follows[followCheck[4]].size();
            for (set<char>::iterator it = follows[fChar].begin();
                it != follows[fChar].end(); ++it)
            {
                follows[followCheck[4]].insert(*it);
            }
            newSize = follows[followCheck[4]].size();
            if (newSize == oldSize)
            {
                change = false;
            }
        }
    }

    displayFollows(follows);
}
