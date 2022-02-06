#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	int numberOfFrequentWordsToDisplay = 25;
	ifstream inFile("text.txt");
	string words[10000];
	int wordOccurences[10000];
	int currentWordIndex = 0;
	string word;
loopstart:
	if (inFile >> word)
	{
		if ((word != "the") && (word != "for") && (word != "in"))
		{
			int i = 0;
		capitalLettersNormalization:
			if (i < word.length())
			{
				if (word[i] >= 65 && word[i] <= 90)
				{
					word[i] += 32;
				}
				i++;
				goto capitalLettersNormalization;
			}
			i = 0;
			bool wordWasPreviouslyAdded = false;
		checkIfWordWasPreviously:
			if (i < currentWordIndex)
			{
				if (words[i] == word)
				{
					wordWasPreviouslyAdded = true;
					wordOccurences[i]++;
					goto endCheckIfWordWasPreviously;
				}
				i++;
				goto checkIfWordWasPreviously;
			}
		endCheckIfWordWasPreviously:
			if (wordWasPreviouslyAdded == false)
			{
				words[currentWordIndex] = word;
				currentWordIndex++;
			}
		}
		goto loopstart;
	}
	inFile.close();

	int i = 0;
out:
	if (i < currentWordIndex)
	{
		cout << words[i] << "\n";
		i++;
		goto out;
	}
}