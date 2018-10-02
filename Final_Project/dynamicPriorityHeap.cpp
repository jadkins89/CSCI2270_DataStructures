#include "dynamicPriorityHeap.hpp"

DynamicPriorityHeap::DynamicPriorityHeap() {
	lastIndex = 0;
	pqDynamic = new patientData*[length];
	for (int i = 0; i < length; i++) {
		pqDynamic[i] = nullptr;
	}
}

DynamicPriorityHeap::~DynamicPriorityHeap() {
	for (int i = 0; i < length; i++) {
		if (pqDynamic[i] != nullptr) {
			delete pqDynamic[i];
		}
	}
}

void DynamicPriorityHeap::resizeArray(float multiplier) {
	int newLength = length * multiplier;
	patientData** newArray = new patientData*[newLength];
	if (multiplier < 1) {
		for (int i = 0; i < newLength; i++) {
			if (i <= lastIndex) {
				newArray[i] = pqDynamic[i];
			}
			else {
				newArray[i] = nullptr;
			}
		}
	}
	else {
		for (int i = 0; i < length; i++) {
			if (i <= lastIndex) {
				newArray[i] = pqDynamic[i];
			}
			else {
				newArray[i] = nullptr;
			}
		}
	}
	delete[] pqDynamic;
	pqDynamic = newArray;
	length = newLength;
}

void DynamicPriorityHeap::enqueueDynamic(patientData pd) {
	patientData* newPatient = new patientData;
	newPatient->name = pd.name;
	newPatient->primaryPriority = pd.primaryPriority;
	newPatient->treatmentLength = pd.treatmentLength;
	lastIndex++;
	if (lastIndex == length) {
		resizeArray(2.0); // Double array size
	}
	pqDynamic[lastIndex] = newPatient;
	// reheap up
	int currentIndex = lastIndex;
	bool itemSwapped = true;

	while (currentIndex > 1 && itemSwapped) {
		if (pqDynamic[currentIndex]->primaryPriority < pqDynamic[currentIndex / 2]->primaryPriority) {
			// swap time
			patientData* temp = pqDynamic[currentIndex / 2];
			pqDynamic[currentIndex / 2] = pqDynamic[currentIndex];
			pqDynamic[currentIndex] = temp;
			currentIndex = currentIndex / 2;
		}
		else if (pqDynamic[currentIndex]->primaryPriority == pqDynamic[currentIndex / 2]->primaryPriority) {
			if (pqDynamic[currentIndex]->treatmentLength < pqDynamic[currentIndex / 2]->treatmentLength) {
				// swap time
				patientData* temp = pqDynamic[currentIndex / 2];
				pqDynamic[currentIndex / 2] = pqDynamic[currentIndex];
				pqDynamic[currentIndex] = temp;
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

bool DynamicPriorityHeap::dequeueDynamic() {
	if (lastIndex > 0) {
		delete pqDynamic[1];

		if (lastIndex == 1) {
			lastIndex = 0;
			pqDynamic[1] = nullptr;
		}
		else {
			if (lastIndex < (0.5 * length) && START_LENGTH <= (0.5 * length)) {
				resizeArray(0.5);
			}
			pqDynamic[1] = pqDynamic[lastIndex];
			pqDynamic[lastIndex] = nullptr;
			lastIndex--;
			// reheap down
			int currentIndex = 1;
			int leftChild, rightChild, minChild;
			bool itemSwapped = true;
			while (itemSwapped) {
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
						if (pqDynamic[leftChild]->primaryPriority < pqDynamic[rightChild]->primaryPriority) {
							minChild = leftChild;
						}
						else if (pqDynamic[leftChild]->primaryPriority == pqDynamic[rightChild]->primaryPriority) {
							if (pqDynamic[leftChild]->treatmentLength < pqDynamic[rightChild]->treatmentLength) {
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
					if (pqDynamic[currentIndex]->primaryPriority > pqDynamic[minChild]->primaryPriority) {
						// swap time
						patientData* temp = pqDynamic[minChild];
						pqDynamic[minChild] = pqDynamic[currentIndex];
						pqDynamic[currentIndex] = temp;
						currentIndex = minChild;
					}
					else if (pqDynamic[currentIndex]->primaryPriority == pqDynamic[minChild]->primaryPriority) {
						if (pqDynamic[currentIndex]->treatmentLength > pqDynamic[minChild]->treatmentLength) {
							// swap time
							patientData* temp = pqDynamic[minChild];
							pqDynamic[minChild] = pqDynamic[currentIndex];
							pqDynamic[currentIndex] = temp;
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

void DynamicPriorityHeap::dequeueAllDynamic() {
		while (lastIndex != 0) {
		dequeueDynamic();
	}
}

void DynamicPriorityHeap::dequeueAndPrint() {
		int i = 1;
		while (lastIndex != 0) {
		patientData* temp = peek();
		std::cout << i << ":\t" << temp->name << ",  " << temp->primaryPriority 
		<< ",  " << temp->treatmentLength << std::endl;
		dequeueDynamic();
		i++;
	}
}

patientData* DynamicPriorityHeap::peek() {
	if (lastIndex != 0) {
		return pqDynamic[1];
	}
	else {
		return pqDynamic[0];
	}
}
