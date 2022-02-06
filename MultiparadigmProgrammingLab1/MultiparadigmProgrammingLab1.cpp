#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    int numberOfFrequentWordsToDisplay = 25;
    ifstream inFile("text.txt");
    string words[10000];
    int currentWordIndex = 0;
    string word;
    loopstart:
    if (inFile >> word)
    {
        if ((word != "the") && (word != "for") && (word != "in"))
        {
            words[currentWordIndex] = word;
            //cout<<word;
            currentWordIndex++;
        }
        goto loopstart;
    }
    inFile.close();

    int i=0;
    out:
    if(i < currentWordIndex)
    {
        cout << words[i] << "\n";
        i++;
        goto out;
    }
}