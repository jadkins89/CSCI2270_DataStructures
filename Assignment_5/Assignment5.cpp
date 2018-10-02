#include "Queue.hpp"
#include <iostream>

const int SIZE = 10;

void printMenu();
void mainMenu();

int main() {
	mainMenu();
	return 0;
}

void printMenu() {
	std::cout << "======Main Menu=====" << std::endl;
	std::cout << "1. Enqueue word" << std::endl;
	std::cout << "2. Dequeue word" << std::endl;
	std::cout << "3. Print queue" << std::endl;
	std::cout << "4. Enqueue sentence" << std::endl;
	std::cout << "5. Quit" << std::endl;
}

void mainMenu() {
	std::string userInput;
	Queue theQueue(SIZE);

	do {
		printMenu(); // Runs print menu function to display text to user
		bool valid = false;
		while (!valid) { // Checking validity of user input
			getline(std::cin, userInput);
			if (userInput.length() == 1 && userInput > "0" && userInput < "6") {
				valid = true;
			}
			else {
				std::cout << "Incorrect input. Please try again: " << std::endl;
			}
		}
		if (userInput == "1") { 		// Enqueue
			std::cout << "word: ";
			getline(std::cin, userInput);
			theQueue.enqueue(userInput);
		}
		else if (userInput == "2") { 	//Dequeue
			theQueue.dequeue();
		}
		else if (userInput == "3") { 	// Print queue
			theQueue.printQueue();
		}
		else if (userInput == "4") {	// Enqueue Sentence
			std::cout << "sentence: ";
			getline(std::cin, userInput);
			theQueue.enqueueSentence(userInput);
		}
	} while (userInput != "5");

	std::cout << "Goodbye!" << std::endl; // Quit
}