#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
	cout << "Enter name of file with text: ";
	string fileName;
	cin >> fileName;

	int wordsCapacity = 10;
	string* words = new string[wordsCapacity];
	int* wordOccurrences = new int[wordsCapacity];
	int** wordsPages = new int* [wordsCapacity];

	int i = 0, j = 0;

memoryAlloc:
	if (i < wordsCapacity)
	{
		wordsPages[i] = new int[101];
		i++;
		goto memoryAlloc;
	}

	char punctuationMarksAndSymbols[] = { ',', '"', '\'', '.', '!', '?', ':', ';', '(', ')', '{', '}' };
	int numberOfSymbolsToCheck = 12;

	string stopWords[] = { "the", "for", "in", "at", "on", "by", "of", "with", "a", "but", "to", "am", "is", "are" };
	int stopWordsNumber = 14;

	int currentWordIndex = 0;
	string symbolsSequence;

	ifstream inFile(fileName);

loopstart:
	if (inFile >> symbolsSequence)
	{
		if (wordsCapacity == currentWordIndex)
		{
			wordsCapacity *= 2;
			string* newWords = new string[wordsCapacity];
			int* newWordOccurrences = new int[wordsCapacity];
			int** newWordsPages = new int* [wordsCapacity];

			i = wordsCapacity / 2;
		newMemoryAlloc:
			if (i < wordsCapacity)
			{
				newWordsPages[i] = new int[101];
				i++;
				goto newMemoryAlloc;
			}

			i = 0;
		copyWord:
			if (i < wordsCapacity / 2)
			{
				newWords[i] = words[i];
				newWordOccurrences[i] = wordOccurrences[i];
				newWordsPages[i] = wordsPages[i];
				i++;
				goto copyWord;
			}

			delete[] words;
			words = newWords;

			delete[] wordOccurrences;
			wordOccurrences = newWordOccurrences;

			delete[] wordsPages;
			wordsPages = newWordsPages;
		}

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
		if (i < stopWordsNumber)
		{
			if (word == stopWords[i])
			{
				isStopWord = true;
				goto endCheckStopWord;
			}
			i++;
			goto checkStopWord;
		}
	endCheckStopWord:
		if (!isStopWord)
		{
			i = 0;
			bool wordWasPreviouslyAdded = false;
		checkIfWordWasPreviously:
			if (i < currentWordIndex)
			{
				if (words[i] == word)
				{
					wordWasPreviouslyAdded = true;
					if (wordOccurrences[i] < 100)
					{
						wordsPages[i][wordOccurrences[i]] = 5;
					}
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
				wordsPages[currentWordIndex][0] = 5;
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
			bool makeWordsSwap = false;

			int f = 0;
		wordsComparison:
			if (words[j][f] < words[j + 1][f])
			{
				goto endWordsComparison;
			}
			if (words[j][f] > words[j + 1][f])
			{
				makeWordsSwap = true;
				goto endWordsComparison;
			}
			if (words[j][f] != '\0' && words[j + 1][f] != '\0')
			{
				f++;
				goto wordsComparison;
			}
		endWordsComparison:
			if (makeWordsSwap)
			{
				string temp = words[j];
				words[j] = words[j + 1];
				words[j + 1] = temp;

				int tempOccurences = wordOccurrences[j];
				wordOccurrences[j] = wordOccurrences[j + 1];
				wordOccurrences[j + 1] = tempOccurences;

				int* tempPages = wordsPages[j];
				wordsPages[j] = wordsPages[j + 1];
				wordsPages[j + 1] = tempPages;
			}
			j++;
			goto innerSortingLoop;
		}
		i++;
		goto outerSortingLoop;
	}

	if (currentWordIndex == 0)
	{
		cout << "No words!";
	}
	else
	{
		i = 0;
	out:
		if (i < currentWordIndex)
		{
			if (wordOccurrences[i] <= 100)
			{
				cout << std::setw(8) << std::left << words[i] << " - ";

				j = 0;
			printPages:
				if (j < wordOccurrences[i])
				{
					cout << wordsPages[i][j];
					j++;
					if (j < wordOccurrences[i])
					{
						cout << ", ";
					}
					goto printPages;
				}
				cout << '\n';
			}
			i++;
			goto out;
		}
	}

	delete[] words;
	delete[] wordOccurrences;

	i = 0;
clearMemory:
	if (i < wordsCapacity)
	{
		delete[] wordsPages[i];
		i++;
		goto clearMemory;
	}
	delete[] wordsPages;
}