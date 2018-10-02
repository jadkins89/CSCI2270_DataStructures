#include <iostream>
#include "Graph.h"
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
    std::cout << "2. Vertex adjacent" << std::endl;
    std::cout << "3. Quit" << std::endl;
}

void runMenu(Graph* zombieMap) {
	std::string input;
	do {
		printMenu();
		input = "0";
		while (input < "1" || input > "3") {
			getline(std::cin, input);
		}
		if (input == "1") {
			zombieMap->displayEdges();
		}
		else if (input == "2") {
			std::string city1, city2;
			std::cout << "Enter first city:" << std::endl;
			getline(std::cin, city1);
	     	std::cout << "Enter second city:" << std::endl;
	     	getline(std::cin, city2);
	     	if (zombieMap->isAdjacent(city1, city2)) {
	     		std::cout << "True" << std::endl;
	     	}
	     	else {
	     		std::cout << "False" << std::endl;
	     	}
		}
	}
	while (input != "3");
	std::cout << "Goodbye!" << std::endl;
}