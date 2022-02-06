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
			if (!wordWasPreviouslyAdded)
			{
				words[currentWordIndex] = word;
				wordOccurences[currentWordIndex] = 1;
				currentWordIndex++;
			}
		}
		goto loopstart;
	}

	int i = 0, j = 0;
outerSortingLoop:
	if (i < currentWordIndex - 1)
	{
		j = 0;
	innerSortingLoop:
		if (j < currentWordIndex - i - 1)
		{
			if (wordOccurences[j] < wordOccurences[j + 1])
			{
				string temp = words[j];
				words[j] = words[j + 1];
				words[j + 1] = temp;
				int tempOccurences = wordOccurences[j];
				wordOccurences[j] = wordOccurences[j + 1];
				wordOccurences[j + 1] = tempOccurences;
			}
			j++;
			goto innerSortingLoop;
		}
		i++;
		goto outerSortingLoop;
	}

	i = 0;
out:
	if (i < currentWordIndex)
	{
		cout << words[i] << " - " << wordOccurences[i] << "\n";
		i++;
		goto out;
	}
}