#include <queue>
#include "priorityHeap.hpp"

#pragma once

struct compare {
	bool operator()(const patientData &a, const patientData &b) {
		if (a.primaryPriority > b.primaryPriority) {
			return true;
		}
		else if (a.primaryPriority == b.primaryPriority) {
			if (a.treatmentLength > b.treatmentLength) {
				return true;
			}
		}
		return false;
	}
};

class PrioritySTL {
	public:
		PrioritySTL();
		~PrioritySTL();
		void enqueue(patientData);
		void dequeue();
		void dequeueAll();
		void dequeueAndPrint();
	private:
		std::priority_queue<patientData, std::vector<patientData>, compare> pqSTL;
};