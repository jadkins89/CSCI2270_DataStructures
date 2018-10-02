#include <iostream>
#include "Graph.hpp"
#include <vector>
#include <sstream>
#include <fstream>

void printMenu();
void runMenu(Graph* zombieMap);

int main(int argc, char* argv[]) {
	std::ifstream graphFile(argv[1], std::ios::in);

	Graph zMap;

	if (graphFile.fail()) {
		return -1;
	}

	std::string currentLine;
	getline(graphFile, currentLine);
	std::stringstream ss(currentLine);

	ss.ignore(256, ','); //skips over title words

	std::vector<std::string> vertexName;
	int counter = 0;
	std::string cityName;

	while (getline(ss, cityName, ',')) {
		vertexName.push_back(cityName);
		zMap.addVertex(vertexName[counter]);
		counter++;
	}

	while (getline(graphFile, currentLine)) {
		std::string currentVertex;
		std::stringstream ss2(currentLine);
		getline(ss2, currentVertex, ','); // Current line in matrix
		std::string currentWeight;

		for (int i = 0; i < counter; i++) {
			getline(ss2, currentWeight, ',');
			if (stoi(currentWeight) > 0) {
				zMap.addEdge(currentVertex, vertexName[i], stoi(currentWeight));
			}
		}
	}
	graphFile.close();

	runMenu(&zMap);

	return 0;
}

void printMenu() {
	std::cout << "======Main Menu======" << std::endl;
    std::cout << "1. Print vertices" << std::endl;
    std::cout << "2. Find districts" << std::endl;
    std::cout << "3. Find shortest path" << std::endl;
    std::cout << "4. Find shortest weighted path" << std::endl;
    std::cout << "5. Quit" << std::endl;
}

void runMenu(Graph* zombieMap) {
	std::string input;
	do {
		printMenu();
		input = "0";
		while (input < "1" || input > "5") {
			getline(std::cin, input);
		}
		if (input == "1") {
			zombieMap->displayEdges();
		}
		else if (input == "2") {
			zombieMap->assignDistricts();
		}
		else if (input == "3") {
			std::string city1, city2;
			std::cout << "Enter a starting city:" << std::endl;
			getline(std::cin, city1);
	     	std::cout << "Enter an ending city:" << std::endl;
	     	getline(std::cin, city2);
			zombieMap->shortestPath(city1, city2);
		}
		else if (input == "4") {
			std::string city1, city2;
			std::cout << "Enter a starting city:" << std::endl;
			getline(std::cin, city1);
	     	std::cout << "Enter an ending city:" << std::endl;
	     	getline(std::cin, city2);
	     	zombieMap->shortestWeightedPath(city1, city2);
		}
	}
	while (input != "5");
	std::cout << "Goodbye!" << std::endl;
}