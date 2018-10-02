// Author: Justin Adkins
// Homework #2
// Instructor: Jason Zietz

#include <iostream>
#include <fstream>

struct city{
	std::string cityName;
	std::string message;
	city *next;
	city(){}; // default constructor
	city(std::string initName, city *initNext, std::string initMessage) {
		cityName = initName; 
		next = initNext; 
		message = initMessage;
	}
};
// Function Declarations
/*
* Function name: printMenu
* Purpose: A simple print function that prints the main menu
* @return - none
*/
void printMenu();
/*
* Function name: mainMenu
* Purpose: Runs the main program, calling on other functions based on user input
* @return - none
*/
void mainMenu();
/*
* Function name: buildNetwork
* Purpose: Builds the initial network with pre-determined cities
* @return - the head of the linked list created
*/
city* buildNetwork();
/*
* Function name: createCity
* Purpose: Creates a new node of the city object
* @param nextCity - This will be assigned to the new nodes "next" position for placement in a list
* @param cityName - This is a string that identifies the city
* @return - a pointer to the new city node
*/
city* createCity(city* nextCity, std::string cityName);
/*
* Function name: addCity
* Purpose: adds a city to an already created linked list
* @param head - the head of the linked list
* @param previous - a pointer to the previous node in the list
* @param cityName - This is a string that identifies the city
* @return - a pointer to the head of the list
*/
city* addCity(city* head, city* previous, std::string cityName);
/*
* Function name: transmitMsg
* Purpose: Sends a message through the entire linked list, printing at each location a receive message
* @param head - the head of the linked list
* @return - none
*/
void transmitMsg(city* head);
/*
* Function name: printPath
* Purpose: prints the current path of the network (linked list)
* @param head - the head of the linked list
* @return - none
*/
void printPath(city* head);
/*
* Function name: deleteLinkedList
* Purpose: Walk through each element of the list and delete the allocated memory
* @param head - a pointer to the head of the linked list
* @return - none
*/
void deleteLinkedList(city* head);

int main () {
	mainMenu(); // runs program

	return 0;
}

void printMenu() {
	std::cout << "======Main Menu======" << std::endl;
	std::cout << "1. Build Network" << std::endl;
	std::cout << "2. Print Network Path" << std::endl;
	std::cout << "3. Transmit Message Coast-To-Coast" << std::endl;
	std::cout << "4. Add City" << std::endl;
	std::cout << "5. Quit" << std::endl;
}

void mainMenu() {
	std::string userInput;
	city* head = nullptr;

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
		if (userInput == "1") { 		// Build Network
			deleteLinkedList(head);
			head = buildNetwork();
		}
		else if (userInput == "2") { 	// Print Network Path
			printPath(head);
		}
		else if (userInput == "3") { 	// Transmit Message Coast-to-Coast
			transmitMsg(head);
		}
		else if (userInput == "4") {	// Add City
			std::string cityNew, cityPrevious;
			city* previous; 			// pointer for location of previous city

			std::cout << "Enter a City name: " << std::endl; 
			getline(std::cin, cityNew);
			std::cout << "Enter a previous City name: " << std::endl;
			getline(std::cin, cityPrevious);

			if (cityPrevious == "First") {
				previous = nullptr;
			}
			else if (cityPrevious == "") {
				previous = head;
				while (previous->next != nullptr) {
					previous = previous->next;
				}
			}
			else {
				previous = head;
				while (previous->cityName != cityPrevious) {
					previous = previous->next;
				}
			}
			head = addCity(head, previous, cityNew);
		}
	} while (userInput != "5");

	std::cout << "Goodbye!" << std::endl; // Quit
}

city* buildNetwork() {
	city* BOS = createCity(nullptr, "Boston"); 
	city* NY = createCity(BOS, "New York"); 
	city* DC = createCity(NY, "Washington, D.C."); 
	city* ATL = createCity(DC, "Atlanta"); 
	city* CHI = createCity(ATL, "Chicago"); 
	city* STL = createCity(CHI, "St. Louis"); 
	city* DAL = createCity(STL, "Dallas"); 
	city* DEN = createCity(DAL, "Denver"); 
	city* PHX = createCity(DEN, "Phoenix");
	city* LA = createCity(PHX, "Los Angeles");
	city* head = LA;
	return head;
}

city* createCity(city* nextCity, std::string cityName) {
	city* newCity = new city;
	newCity->cityName = cityName;
	newCity->next = nextCity;
	return newCity;
}

city* addCity(city* head, city* previous, std::string cityName) {
	{
	city* newCity = createCity(nullptr, cityName);
	// Check if head is null / the list is empty list
	if (head == nullptr) {
		head = newCity;
	}
	else if (previous == nullptr) {			// insert new head
		newCity->next = head;
	    head = newCity;
	}
	else {
		city* currentCity = head;
		//traverse to the end of the list
		while (currentCity->next != nullptr && currentCity != previous) {
			currentCity = currentCity->next;
		}
		newCity->next = currentCity->next; 	// Set the new city "next" position to the previous or end city "next" 
		currentCity->next = newCity; 		// Set the previous or end city "next" position to the new city

	}
	return head;
	}
}

void transmitMsg(city* head) {
	//if network not built yet 
	if(head == nullptr) {
		std::cout << "Empty list" << std::endl;
	}
	else {
		std::string fileName = "messageIn.txt";
		std::ifstream fileStream(fileName, std::ios::in);
		if (!fileStream.is_open()) {
			std::cout << "Error: file didn't open." << std::endl;
		}
		std::string currentWord;

		while (fileStream >> currentWord) {
			city* currentCity = head;
			currentCity->message = currentWord;

			while (currentCity != nullptr) {
				std::cout <<currentCity->cityName <<" received "<< currentCity->message << std::endl;
				if (currentCity->next != nullptr) {
					currentCity->next->message = currentCity->message;
				}
				currentCity->message = ""; // Deleting message now that it has been sent
				currentCity = currentCity->next;			
			}
		}
		fileStream.close();
	}
}

void printPath(city* head) {
	if (head == nullptr) {
		std::cout << "Empty List" << std::endl;
	}
	else {
		city* currentCity = head;
		std::cout << "===CURRENT PATH===" << std::endl;
		while (currentCity != nullptr) {
			std::cout << currentCity->cityName << " -> ";
			currentCity = currentCity->next;
		}
		std::cout << " NULL" << std::endl;
		std::cout << "==================" << std::endl;
	}
}

void deleteLinkedList(city* head) {
	city* currentCity = head;
	while (currentCity != nullptr) {
		currentCity = head->next;
		delete head;
		head = currentCity;
	}
}