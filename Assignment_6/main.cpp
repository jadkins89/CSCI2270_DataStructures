#include <iostream>
#include "MovieTree.hpp"
#include <fstream>
#include <sstream>

//Function Declarations
void printMenu();
void mainMenu(MovieTree &theTree);

int main(int argc, char* argv[]) {
	MovieTree testTree;
	char* filename = argv[1];
	std::ifstream documentStream(filename, std::ios::in);

	if (documentStream.fail()) {
		return -1;
	}

	std::string currentLine;
	while (getline(documentStream, currentLine)) {
		std::stringstream ss(currentLine);
		std::string lineArray[4];
		int index = 0;

		while (getline(ss, lineArray[index], ',')) {
			index++;
		}
		int ranking = stoi(lineArray[0]);
		std::string title = lineArray[1];
		int releaseYear = stoi(lineArray[2]);
		int quantity = stoi(lineArray[3]);
		testTree.addMovieNode(ranking, title, releaseYear, quantity);
	}
	documentStream.close();

	mainMenu(testTree);

	return 0;
}

void printMenu() {
	std::cout << "======Main Menu======" << std::endl; 
	std::cout << "1. Find a movie" << std::endl;
	std::cout << "2. Rent a movie" << std::endl;	
	std::cout << "3. Print the inventory" << std::endl;
	std::cout << "4. Delete a movie" << std::endl; 
	std::cout << "5. Count the movies" << std::endl; 
	std::cout << "6. Quit" << std::endl;
}

void mainMenu(MovieTree &theTree) {
	std::string userInput;

	do {
		printMenu(); // Runs print menu function to display text to user
		bool valid = false;
		while (!valid) { // Checking validity of user input
			getline(std::cin, userInput);
			if (userInput.length() == 1 && userInput > "0" && userInput < "7") {
				valid = true;
			}
			else {
				std::cout << "Incorrect input. Please try again: " << std::endl;
			}
		}
		if (userInput == "1") {
			std::cout << "Enter title:" << std::endl;
			std::string title;
			getline(std::cin, title);
			theTree.findMovie(title);
		}
		else if (userInput == "2") {
			std::cout <<"Enter title:" << std::endl;
			std::string title;
			getline(std::cin, title);
			theTree.rentMovie(title);
		}
		else if (userInput == "3") {
			theTree.printMovieInventory();
		}
		else if (userInput == "4") {
			std::cout << "Enter title:" << std::endl;
			std::string title;
			getline(std::cin, title);
			theTree.deleteMovieNode(title);
		}
		else if (userInput == "5") {
			std::cout << "Tree contains: " << theTree.countMovieNodes() << " movies." << std::endl;
		}
	}
	while (userInput != "6");
	std::cout << "Goodbye!" << std::endl;
}