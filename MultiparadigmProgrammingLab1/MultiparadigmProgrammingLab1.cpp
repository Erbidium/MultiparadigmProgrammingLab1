#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	int numberOfFrequentWordsToDisplay = 25;

	string words[10000];
	int wordOccurences[10000];

	char punctuationMarksAndSymbols[] = { ',', '"', '\'', '.', '!', '?', ':', ';', '(', ')', '{', '}' };
	int numberOfSymbolsToCheck = 12;

	int currentWordIndex = 0;
	string symbolsSequence;

	int i = 0, j = 0;

	ifstream inFile("text.txt");

loopstart:
	if (inFile >> symbolsSequence)
	{
		symbolsSequence += '\0';
		string word;
		i = 0;
	symbolsRemoval:
		if (symbolsSequence[i] != '\0')
		{
			bool validSymbol = true;
			int k = 0;
		checkSymbol:
			if (k < numberOfSymbolsToCheck)
			{
				if (symbolsSequence[i] == punctuationMarksAndSymbols[k])
				{
					validSymbol = false;
					goto endCheckSymbol;
				}
				k++;
				goto checkSymbol;
			}
		endCheckSymbol:
			if (validSymbol)
			{
				word += symbolsSequence[i];
			}
			i++;
			goto symbolsRemoval;
		}

		//process stop words
		if ((word != "the") && (word != "for") && (word != "in"))
		{

			word += '\0';

			i = 0;
		capitalLettersNormalization:
			if (word[i] != '\0')
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

	i = j = 0;
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
	int displayWordsNumber = 0;
	if (numberOfFrequentWordsToDisplay < currentWordIndex)
	{
		displayWordsNumber = numberOfFrequentWordsToDisplay;
	}
	else
	{
		displayWordsNumber = currentWordIndex;
	}
out:
	// show message if no words
	if (i < displayWordsNumber)
	{
		cout << words[i] << " - " << wordOccurences[i] << "\n";
		i++;
		goto out;
	}
}