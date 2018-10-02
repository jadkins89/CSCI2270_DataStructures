#include <iostream>
#include "definitions.hpp"

#pragma once

class PriorityHeap {
	public:
		// Constructor - Destructor
		PriorityHeap();
		PriorityHeap(int listLength);
		~PriorityHeap();
		// Class Methods
		void enqueue(patientData);
		bool dequeue();
		void dequeueAll();
		void dequeueAndPrint();
		void printPQ();
		patientData* peek();

	private:
		int lastIndex;
		int maxIndex = PINDEX + 1;
		patientData* pq[PINDEX + 1];
};