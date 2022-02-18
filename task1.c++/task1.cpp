#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
	cout << "Enter number of frequent words to display(N): ";
	int numberOfFrequentWordsToDisplay;
	cin >> numberOfFrequentWordsToDisplay;
	cout << "Enter name of file with text: ";
	string fileName;
	cin >> fileName;

	int wordsCapacity = 10;
	string* words = new string[wordsCapacity];
	int* wordOccurrences = new int[wordsCapacity];

	char punctuationMarksAndSymbols[] = { ',', '"', '\'', '.', '!', '?', ':', ';', '(', ')', '{', '}' };
	int numberOfSymbolsToCheck = 12;

	string stopWords[] = { "the", "for", "in", "at", "on", "by", "of", "with", "a", "but", "to", "am", "is", "are", "and"};
	int stopWordsNuber = 15;

	int currentWordIndex = 0;
	string symbolsSequence;

	int i = 0, j = 0;

	ifstream inFile(fileName);

loopstart:
	if (inFile >> symbolsSequence)
	{
		if (wordsCapacity == currentWordIndex)
		{
			wordsCapacity *= 2;
			string* newWords = new string[wordsCapacity];
			int* newWordOccurrences = new int[wordsCapacity];

			i = 0;
		copyWord:
			if (i < wordsCapacity / 2)
			{
				newWords[i] = words[i];
				newWordOccurrences[i] = wordOccurrences[i];
				i++;
				goto copyWord;
			}

			delete[] words;
			words = newWords;

			delete[] wordOccurrences;
			wordOccurrences = newWordOccurrences;
		}


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

		bool isStopWord = false;
		i = 0;
	checkStopWord:
		if (i < stopWordsNuber)
		{
			if (word == stopWords[i] + '\0')
			{
				isStopWord = true;
				goto endCheckStopWord;
			}
			i++;
			goto checkStopWord;
		}
	endCheckStopWord:

		bool isValidWord = true;
		i = 0;
	checkValidWord:
		if (word[i] != '\0')
		{
			if (!((word[i] >= 97 && word[i] <= 122) || (word[i] == '-') || (word[i] == '\'')))
			{
				isValidWord = false;
				goto endCheckValidWord;
			}
			i++;
			goto checkValidWord;
		}
	endCheckValidWord:

		if (word == "" || word == "'" || word == "-")
		{
			isValidWord = false;
		}

		if (!isStopWord && isValidWord)
		{
			i = 0;
			bool wordWasPreviouslyAdded = false;
		checkIfWordWasPreviously:
			if (i < currentWordIndex)
			{
				if (words[i] == word)
				{
					wordWasPreviouslyAdded = true;
					wordOccurrences[i]++;
					goto endCheckIfWordWasPreviously;
				}
				i++;
				goto checkIfWordWasPreviously;
			}
		endCheckIfWordWasPreviously:
			if (!wordWasPreviouslyAdded)
			{
				words[currentWordIndex] = word;
				wordOccurrences[currentWordIndex] = 1;
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
			if (wordOccurrences[j] < wordOccurrences[j + 1])
			{
				string temp = words[j];
				words[j] = words[j + 1];
				words[j + 1] = temp;
				int tempOccurences = wordOccurrences[j];
				wordOccurrences[j] = wordOccurrences[j + 1];
				wordOccurrences[j + 1] = tempOccurences;
			}
			j++;
			goto innerSortingLoop;
		}
		i++;
		goto outerSortingLoop;
	}

	int displayWordsNumber = 0;
	if (numberOfFrequentWordsToDisplay < currentWordIndex)
	{
		displayWordsNumber = numberOfFrequentWordsToDisplay;
	}
	else
	{
		displayWordsNumber = currentWordIndex;
	}

	if (displayWordsNumber == 0)
	{
		cout << "No words!";
	}
	else
	{
		i = 0;
	out:
		if (i < displayWordsNumber)
		{
			cout << std::setw(8) << std::left << words[i] << " - " << wordOccurrences[i] << "\n";
			i++;
			goto out;
		}
	}

	delete[] words;
	delete[] wordOccurrences;
}