﻿#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream inFile("text.txt");
    string word;
    loopstart:
    if(inFile >> word)
    {
        if((word != "the") && (word != "for"))
        {
            cout << word << endl;
            goto loopstart;
        }
    }
}