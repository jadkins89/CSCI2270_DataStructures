// Assignment 4
// Implementation File: CommunicationNetwork.cpp

#include <iostream>
#include <fstream>
#include "CommunicationNetwork.h"

CommunicationNetwork::CommunicationNetwork() {
	head = nullptr;
	tail = nullptr;
	printDelete = true;
}

CommunicationNetwork::~CommunicationNetwork() {
	deleteNetwork();
}


void CommunicationNetwork::addCity(std::string newCityName, std::string previousCityName) {
	if (head == nullptr) {
		insertCityAtEnd(newCityName);
	}
	else if (previousCityName == "First") {
		City* newCity = createCity(newCityName, nullptr, head);
		newCity->next->previous = newCity;
		head = newCity;
	}
	else if (previousCityName == "") {
		insertCityAtEnd(newCityName);
	}
	else {
		City* prevCityPointer = head;
		while (prevCityPointer->cityName != previousCityName) { // point to previous city
			if (prevCityPointer == tail) { // if previous city name doesn't exist
				insertCityAtEnd(newCityName);
				return;
			}
			prevCityPointer = prevCityPointer->next;
		}
		City* newCity = createCity(newCityName, prevCityPointer, prevCityPointer->next); //creates new city and adjusts pointers
		newCity->previous->next = newCity; //modifies next pointer for city behind new city
		newCity->next->previous = newCity; //modifies prev pointer for city in front of new city
	}
}


City* CommunicationNetwork::createCity(std::string cityName, City* prev, City* next) {
	City* newCity = new City;
	newCity->cityName = cityName;
	newCity->message = ""; // Empty string as initialized message
	newCity->next = next;
	newCity->previous = prev;

	return newCity;
}


bool CommunicationNetwork::insertCityAtEnd(std::string cityName) {
	if (head == nullptr) {
		//nothing in the list
		head = createCity(cityName, nullptr, nullptr);
		tail = head;
	}
	else {
		City* newCity = createCity(cityName, tail, nullptr);
		tail->next = newCity;
		tail = newCity;
	}
	return true;
}


void CommunicationNetwork::buildNetwork() {
	printDelete = false;
	deleteNetwork();
	printDelete = true;

	insertCityAtEnd("Los Angeles");
	insertCityAtEnd("Phoenix");
	insertCityAtEnd("Denver");
	insertCityAtEnd("Dallas");
	insertCityAtEnd("St. Louis");
	insertCityAtEnd("Chicago");
	insertCityAtEnd("Atlanta");
	insertCityAtEnd("Washington, D.C.");
	insertCityAtEnd("New York");
	insertCityAtEnd("Boston");
	printNetwork();
}


void CommunicationNetwork::transmitMsg(char* filename) {
	if (head == nullptr) {
		std::cout << "Empty List" << std::endl;
	}
	else {
		std::ifstream fileStream(filename, std::ios::in);
		if (fileStream.fail()) {
			std::cout << "Error: file didn't open." << std::endl;
		}
		std::string currentWord;

		while (fileStream >> currentWord) {
			City* currentCity = head;
			currentCity->message = currentWord;
			bool hitTail = false;

			while (currentCity != nullptr) {
				std::cout <<currentCity->cityName <<" received "<< currentCity->message << std::endl;
				if (!hitTail) {
					currentCity->next->message = currentCity->message;
					currentCity->message = "";
					currentCity = currentCity->next;
					if (currentCity == tail) {
						hitTail = true;
					}
				}
				else { //We've reached the tail
					if (currentCity != head) {
						currentCity->previous->message = currentCity->message;
					}
					currentCity->message = "";
					currentCity = currentCity->previous;
				}
			}
		}
		fileStream.close();
	}
}


void CommunicationNetwork::printNetwork() {
	if (head == nullptr) {
		return;
	}
	City* tmp = head;
	std::cout << "===CURRENT PATH===" << std::endl; 
	std::cout << "NULL <- ";
	while (tmp != tail) {
		std::cout << tmp->cityName << " <-> "; //for all nodes in network
		tmp = tmp->next;
	}
	std::cout << tail->cityName << " -> NULL" << std::endl;
	std::cout << "==================" << std::endl;
}


void CommunicationNetwork::deleteCity(std::string cityName) {
	City* deleteCityPointer = head;
	while (deleteCityPointer->cityName != cityName) { // point to city to be deleted
		if (deleteCityPointer == tail) { // In case a name of a city is given that doesn't exist in the list
			std::cout << cityName << " not found" << std::endl;
			return;
		}
		deleteCityPointer = deleteCityPointer->next;
	}
	if (deleteCityPointer != head) {
		deleteCityPointer->previous->next = deleteCityPointer->next;
	}
	else {
		head = deleteCityPointer->next;
	}
	if (deleteCityPointer != tail) {
		deleteCityPointer->next->previous = deleteCityPointer->previous;
	}
	else {
		tail = deleteCityPointer->previous;
	}
	delete deleteCityPointer;
}


void CommunicationNetwork::deleteNetwork() {
	City* currentCity = head;
	while (currentCity != nullptr) {
		currentCity = currentCity->next;
		if (printDelete) {
			std::cout << "deleting " << head->cityName << std::endl;
		}
		delete head;
		head = currentCity;
	}
	tail = nullptr;
}