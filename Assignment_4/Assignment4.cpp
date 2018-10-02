// Author: Justin Adkins
// Homework #4
// Instructor: Jason Zietz

#include <iostream>
#include "CommunicationNetwork.h"

// Helper Function Declarations
void printMenu();
void mainMenu(char*);

int main(int argc, char* argv[]) {
	mainMenu(argv[1]); // Runs program

	return 0;
}

void printMenu() {
	std::cout << "======Main Menu======" << std::endl;
	std::cout << "1. Build Network" << std::endl;
	std::cout << "2. Print Network Path" << std::endl;
	std::cout << "3. Transmit Message Coast-To-Coast-To-Coast" << std::endl;
	std::cout << "4. Add City" << std::endl;
	std::cout << "5. Delete City" << std::endl;
	std::cout << "6. Clear Network" << std::endl;
	std::cout << "7. Quit" << std::endl;
}

void mainMenu(char* filename) {
	std::string userInput;
	CommunicationNetwork theNetwork;

	do {
		printMenu(); // Runs print menu function to display text to user
		bool valid = false;
		while (!valid) { // Checking validity of user input
			getline(std::cin, userInput);
			if (userInput.length() == 1 && userInput > "0" && userInput < "8") {
				valid = true;
			}
			else {
				std::cout << "Incorrect input. Please try again: " << std::endl;
			}
		}
		if (userInput == "1") { 		// Build Network
			theNetwork.buildNetwork();
		}
		else if (userInput == "2") { 	// Print Network Path
			theNetwork.printNetwork();
		}
		else if (userInput == "3") { 	// Transmit Message Coast-to-Coast
			theNetwork.transmitMsg(filename);
		}
		else if (userInput == "4") {	// Add City
			std::string cityNew, cityPrevious;
			std::cout << "Enter a city name: " << std::endl; 
			getline(std::cin, cityNew);
			std::cout << "Enter a previous city name: " << std::endl;
			getline(std::cin, cityPrevious);
			theNetwork.addCity(cityNew, cityPrevious);
		}
		else if (userInput == "5") { // Delete City
			std::string cityToDelete;
			std::cout << "Enter a city name: " << std::endl;
			getline(std::cin, cityToDelete);
			theNetwork.deleteCity(cityToDelete);
		}
		else if (userInput == "6") { // Delete Network
			theNetwork.deleteNetwork();
		}
	} while (userInput != "7");

	std::cout << "Goodbye!" << std::endl; // Quit
}











