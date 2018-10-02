#include "priorityLL.hpp"

PriorityLL::PriorityLL() {
	head = nullptr;
}

PriorityLL::~PriorityLL() {
	dequeueAll();
}

void PriorityLL::enqueue(patientData pd) {
	priorityNodeLL* currentNode = head;
	bool insert = true;
	priorityNodeLL* newPatient = new priorityNodeLL(pd);

	if (head == nullptr) {
		head = newPatient;
	}
	else if (pd.primaryPriority < head->primaryPriority) { // If patient is new head
		newPatient->next = head;
		head = newPatient;
	}
	else if (pd.primaryPriority == head->primaryPriority) { // If equal, check secondary
		if (pd.treatmentLength < head->secondaryPriority) {
			newPatient->next = head;
			head = newPatient;
		}
		else {
			insert = false;
		}
	}
	else {
		insert = false;
	}

	while (!insert) {
		if (currentNode->next == nullptr) {
			currentNode->next = newPatient;
			insert = true;
		}
		else if (pd.primaryPriority < currentNode->next->primaryPriority) {
			newPatient->next = currentNode->next;
			currentNode->next = newPatient;
			insert = true;
		}
		else if (pd.primaryPriority == currentNode->next->primaryPriority) {
			if (pd.treatmentLength < currentNode->next->secondaryPriority) {
				newPatient->next = currentNode->next;
				currentNode->next = newPatient;
				insert = true;
			}
			else {
				currentNode = currentNode->next;
			}
		}
		else {
			currentNode = currentNode->next;
		}
	}
	return;
}

bool PriorityLL::dequeue() {
	priorityNodeLL* tempNode = head;
	if (tempNode == nullptr) {
		return false;
	}
	head = tempNode->next;
	delete tempNode;
	return true;
}

void PriorityLL::printPQ() {
	priorityNodeLL* tempNode = head;
	int i = 1;
	std::cout << "Rank\tpatient,  Priority,  Treatment" << std::endl;
	while (tempNode != nullptr) {
		std::cout << i << ":\t" << tempNode->patientName << ",  " << tempNode->primaryPriority 
		<< ",  " << tempNode->secondaryPriority << std::endl;
		tempNode = tempNode->next;
		i++;
	}
}
void PriorityLL::dequeueAll() {
	while (dequeue());
}