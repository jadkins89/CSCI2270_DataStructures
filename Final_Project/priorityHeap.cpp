#include "priorityHeap.hpp"

PriorityHeap::PriorityHeap() {
	lastIndex = 0;
	for (int i = 0; i < maxIndex; i++) {
		pq[i] = nullptr;
	}
}

PriorityHeap::PriorityHeap(int listLength) {
	lastIndex = 0;
	maxIndex = listLength + 1;
	for (int i = 0; i < maxIndex; i++) {
		pq[i] = nullptr;
	}
}

PriorityHeap::~PriorityHeap() {
	for (int i = 0; i < maxIndex; i++) {
		if (pq[i] != nullptr) {
			delete pq[i];
		}
	}
}

void PriorityHeap::enqueue(patientData pd) {
	if (lastIndex < maxIndex) {
		patientData* newPatient = new patientData;
		newPatient->name = pd.name;
		newPatient->primaryPriority = pd.primaryPriority;
		newPatient->treatmentLength = pd.treatmentLength;
		lastIndex++;
		pq[lastIndex] = newPatient;
		// reheap up
		int currentIndex = lastIndex;
		bool itemSwapped = true;

		while (currentIndex > 1 && itemSwapped) {
			if (pq[currentIndex]->primaryPriority < pq[currentIndex / 2]->primaryPriority) {
				// swap time
				patientData* temp = pq[currentIndex / 2];
				pq[currentIndex / 2] = pq[currentIndex];
				pq[currentIndex] = temp;
				currentIndex = currentIndex / 2;
			}
			else if (pq[currentIndex]->primaryPriority == pq[currentIndex / 2]->primaryPriority) {
				if (pq[currentIndex]->treatmentLength < pq[currentIndex / 2]->treatmentLength) {
					// swap time
					patientData* temp = pq[currentIndex / 2];
					pq[currentIndex / 2] = pq[currentIndex];
					pq[currentIndex] = temp;
					currentIndex = currentIndex / 2;
				}
				else {
					itemSwapped = false;
				}
			}
			else {
				itemSwapped = false;
			}
		}
	}
}

bool PriorityHeap::dequeue() {
	if (lastIndex > 0) {
		delete pq[1];

		if (lastIndex == 1) {
			lastIndex = 0;
			pq[1] = nullptr;
		}
		else {
			pq[1] = pq[lastIndex];
			pq[lastIndex] = nullptr;
			lastIndex--;
			// reheap down
			int currentIndex = 1;
			int leftChild, rightChild, minChild;
			bool itemSwapped = true;
			while (currentIndex < maxIndex && itemSwapped) {
				leftChild = currentIndex * 2;
				rightChild = currentIndex * 2 + 1;

				if (leftChild > lastIndex) { // Indicates no children
					itemSwapped = false;
				}
				else {
					if (rightChild > lastIndex) { // rightChild doesn't exist
						minChild = leftChild;
					}
					else {
						if (pq[leftChild]->primaryPriority < pq[rightChild]->primaryPriority) {
							minChild = leftChild;
						}
						else if (pq[leftChild]->primaryPriority == pq[rightChild]->primaryPriority) {
							if (pq[leftChild]->treatmentLength < pq[rightChild]->treatmentLength) {
								minChild = leftChild;
							}
							else {
								minChild = rightChild;
							}
						}
						else {
							minChild = rightChild;
						}
					}
					// Now we know which child is smaller
					if (pq[currentIndex]->primaryPriority > pq[minChild]->primaryPriority) {
						// swap time
						patientData* temp = pq[minChild];
						pq[minChild] = pq[currentIndex];
						pq[currentIndex] = temp;
						currentIndex = minChild;
					}
					else if (pq[currentIndex]->primaryPriority == pq[minChild]->primaryPriority) {
						if (pq[currentIndex]->treatmentLength > pq[minChild]->treatmentLength) {
							// swap time
							patientData* temp = pq[minChild];
							pq[minChild] = pq[currentIndex];
							pq[currentIndex] = temp;
							currentIndex = minChild;
						}
						else {
							itemSwapped = false;
						}
					}
					else {
						itemSwapped = false;
					}

				}
			}
		}
		return true;
	}
	else {
		return false; // empty queue
	}
}

void PriorityHeap::dequeueAll() {
	while (lastIndex != 0) {
		dequeue();
	}
}

void PriorityHeap::dequeueAndPrint() {
		int i = 1;
		while (lastIndex != 0) {
		patientData* temp = peek();
		std::cout << i << ":\t" << temp->name << ",  " << temp->primaryPriority 
		<< ",  " << temp->treatmentLength << std::endl;
		dequeue();
		i++;
	}
}

void PriorityHeap::printPQ() {
	if (lastIndex == 0) {
		std::cout << "Nothing in queue" << std::endl;
	}
	else {
		std::cout << "Rank\tpatient,  Priority,  Treatment" << std::endl;
		for (int i = 1; i <= lastIndex; i++) {
			std::cout << i << ":\t" << pq[i]->name << ",  " << pq[i]->primaryPriority 
			<< ",  " << pq[i]->treatmentLength << std::endl;
		}
	}
}

patientData* PriorityHeap::peek() {
	if (lastIndex != 0) {
		return pq[1];
	}
	else {
		return pq[0];
	}
}





