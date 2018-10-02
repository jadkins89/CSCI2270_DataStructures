#include <iostream>
#include "priorityHeap.hpp"

#pragma once

struct priorityNodeLL{
    std::string patientName;
    int primaryPriority;
    int secondaryPriority;
    priorityNodeLL* next;
    priorityNodeLL(){};
    
    priorityNodeLL(patientData pd)
    {
        patientName = pd.name;
        primaryPriority = pd.primaryPriority;
        secondaryPriority = pd.treatmentLength;
        next = nullptr;
    };
};

class PriorityLL {
	public:
		// Constructor - Destructor
		PriorityLL();
		~PriorityLL();
		void enqueue(patientData);
		bool dequeue();
		void printPQ();
		void dequeueAll();

	private:
		priorityNodeLL* head;
};