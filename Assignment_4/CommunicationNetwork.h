#pragma once

#include <iostream>

struct City{
    std::string cityName;
    std::string message;
    City *next;
    City *previous;

    City(){}; // default constructor

    City(std::string initName, City *initNext, City *initPrevious, std::string initMessage)
    {
        cityName = initName;
        next = initNext;
        previous = initPrevious;
        message = initMessage;
    }
};

class CommunicationNetwork
{
    public:
        // Constructor - Destructors
        CommunicationNetwork();
        ~CommunicationNetwork();
        void addCity(std::string, std::string);
        void buildNetwork();
        void transmitMsg(char *); //this is like a string
        void printNetwork();
        void deleteCity(std::string);
        void deleteNetwork();
    private:
        // Helper Methods
        City* createCity(std::string, City*, City*);
        bool insertCityAtEnd(std::string);
        City *head;
        City *tail;
        bool printDelete;
};