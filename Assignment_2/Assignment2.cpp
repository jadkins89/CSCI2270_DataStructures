// Author: Justin Adkins
// Homework #2
// Instructor: Jason Zietz

#include <iostream>
#include <fstream>

/*
1. Find top n words (n is a command line argument) and the number of times each word was found
2. The total number of unique words
3. The total number of words
4. The number of array doublings to store all unique words in the file

Start with array size of 100.

*/
#define IGNOREINDEX 50

struct wordItem {
	std::string uniqueWord;
	int count = 1;
};

// Function Prototypes
/*
* Function name: doubleArraySize
* Purpose: double array size by utilization of dynamically allocated memory
* @param &arrayPtr - a reference to the wordItem array pointer
* @param length - a pointer to the length of the array
* @return - none
*/
void doubleArraySize(wordItem* &arrayPtr, int* length);
/*
* Function name: getStopWords
* Purpose: read stop word list from file and store into an array
* @param ignoreWordFile - filename (the file storing ignore words) 
* @param ignoreWords - store ignore words from the file (pass by reference) 
* @return - none
* Note: The number of words is fixed to 50
*/
void getStopWords(char *ignoreWordFileName, std::string ignoreWords[]);
/*
* Function name: isStopWord
* Purpose: to see if a word is a stop word
* @param word - a word (which you want to check if it is a stop word)
* @param ignoreWords - the array of strings storing ignore/stop words 
* @return - true (if word is a stop word), or false (otherwise)
*/
bool isStopWord(std::string word, std::string ignoreWords[]);
/*
* Function name: getTotalNumberNonStopWords
* Purpose: compute the total number of words saved in the words array (including repeated words)
* @param list - an array of wordItems containing non-stopwords
* @param length - the length of the words array
* @return - the total number of words in the words array (including repeated words multiple times)
*/
int getTotalNumberNonStopWords(wordItem list[], int length);
/*
* Function name: arraySort
* Purpose: sort an array of wordItems, increasing by their count fields 
* @param list - an array of wordItems to be sorted
* @param length - the length of the words array
*/
void arraySort(wordItem* &list, int length);
/*
* Function name: printTopN
* Purpose: to print the top N high frequency words
* @param wordItemList - a pointer that points to a *sorted* array of wordItems 
* @param topN - the number of top frequency words to print 
* @return none
*/
void printTopN(wordItem wordItemList[], int topN);


int main(int argc, char* argv[]) {
	std::string ignoreWords[IGNOREINDEX];

	getStopWords(argv[3], ignoreWords);

	std::ifstream documentStream(argv[2], std::ios::in);

	if (documentStream.fail()) {
		return -1;
	}

	int length = 100;
	int index = 0;
	int numDoublings = 0;
	wordItem* documentArray = new wordItem[length];
	std::string currentWord;

	while (documentStream >> currentWord) {
		bool repeatWord = false;
		if (!isStopWord(currentWord, ignoreWords)) {
			for (int i = 0; i < index; i++) {
				if (documentArray[i].uniqueWord == currentWord) {
					documentArray[i].count++;
					repeatWord = true;
					break;
				}
			}
			if (index == length) {
				doubleArraySize(documentArray, &length);
				numDoublings++;
			}
			if (!repeatWord) {
				documentArray[index++].uniqueWord = currentWord;
				repeatWord = false;
			}
		}
	}
	documentStream.close();

	arraySort(documentArray, index);

	printTopN(documentArray, std::stoi(argv[1])); // Possible error if n is larger than index
	std::cout << "#" << std::endl;
	std::cout << "Array doubled: " << numDoublings << std::endl;
	std::cout << "#" << std::endl;
	std::cout << "Unique non-common words: " << index << std::endl;
	std::cout << "#" << std::endl;
	std::cout << "Total non-common words: " << getTotalNumberNonStopWords(documentArray, index) << std::endl;
	return 0;
}


void doubleArraySize(wordItem* &arrayPtr, int* length) {
	int newLength = *length * 2;
	wordItem* newArray = new wordItem[newLength];
	for (int i = 0; i < *length; i++) {
		newArray[i] = arrayPtr[i];
	}
	delete[] arrayPtr;
	arrayPtr = newArray;
	*length = newLength;
}


void getStopWords(char *ignoreWordFileName, std::string ignoreWords[]) {
	std::ifstream ignoreStream(ignoreWordFileName, std::ios::in);

	if (ignoreStream.fail()) { //Check to see if file exists / opened correctly
		return;
	}

	std::string tempLine;
	int index = 0;
	while (getline(ignoreStream, tempLine) && index < IGNOREINDEX) {
		ignoreWords[index] = tempLine;
		index++;
	}
	ignoreStream.close();
}


bool isStopWord(std::string word, std::string ignoreWords[]) {
	for (int i = 0; i < IGNOREINDEX; i++) {
		if (ignoreWords[i] == word) {
			return true;
		}
	}
	return false;
}


int getTotalNumberNonStopWords(wordItem list[], int length) {
	int total = 0;
	for (int i = 0; i < length; i++) {
		total += list[i].count;
	}
	return total;
}


void arraySort(wordItem* &list, int length) { // Using insertion sort algorithm
	for (int j = 1; j < length; j++) {
        int intKey = list[j].count;
        wordItem key = list[j];
        int i = j - 1;

        while (i >= 0 && list[i].count < intKey)
        {
            list[i+1] = list[i];
            i--;
        }
        list[i+1] = key;
	}
}


void printTopN(wordItem wordItemList[], int topN) {
	for (int i = 0; i < topN; i++) {
		std::cout << wordItemList[i].count << " - " << wordItemList[i].uniqueWord << std::endl;
	}
}