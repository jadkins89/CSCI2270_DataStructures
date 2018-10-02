#include "prioritySTL.hpp"

PrioritySTL::PrioritySTL() {}

PrioritySTL::~PrioritySTL() {}

void PrioritySTL::enqueue(patientData newPatient) {
	pqSTL.push(newPatient);
}

void PrioritySTL::dequeue() {
	pqSTL.pop();
}

void PrioritySTL::dequeueAll() {
	while (!pqSTL.empty()) {
		dequeue();
	}
}

void PrioritySTL::dequeueAndPrint() {
	int i = 1;
	while (!pqSTL.empty()) {
		std::cout << i << ":\t" << pqSTL.top().name << ",  " << pqSTL.top().primaryPriority
		<< ",  " << pqSTL.top().treatmentLength << std::endl;
		dequeue();
		i++;
	}
}
