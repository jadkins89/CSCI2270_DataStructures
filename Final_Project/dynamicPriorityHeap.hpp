#include <iostream>
#include "definitions.hpp"

#pragma once

class DynamicPriorityHeap {
	public:
		// Constructor - Destructor
		DynamicPriorityHeap();
		~DynamicPriorityHeap();
		// Dynamic Class Methods
		void resizeArray(float);
		void enqueueDynamic(patientData);
		bool dequeueDynamic();
		void dequeueAllDynamic();
		void dequeueAndPrint();
		patientData* peek();

	private:
		int lastIndex;
		// Dynamic class variables
		patientData** pqDynamic;
		int length = START_LENGTH;
};