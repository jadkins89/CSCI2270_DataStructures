#include "Queue.hpp"
#include <iostream>
#include <sstream>

Queue::Queue(int qs) {
	queueSize = qs;
	arrayQueue = new std::string[queueSize]; 
	queueHead = 0;
	queueTail = 0;
	queueCount = 0;
}


Queue::~Queue() {
	delete [] arrayQueue; 
	arrayQueue = nullptr;
}

void Queue::enqueue(std::string word) {
	if (queueIsFull()) {
		std::cout << "Queue is full" << std::endl;
		return;
	}
	arrayQueue[queueTail] = word;
	std::cout << "E: " << arrayQueue[queueTail] << std::endl;
	if (queueTail == queueSize - 1) {
		queueTail = 0;
	}
	else {
		queueTail++;
	}
	queueCount++;
	std::cout << "H: " << queueHead << std::endl;
	std::cout << "T: " << queueTail << std::endl;
}


void Queue::dequeue() {
	if (queueIsEmpty()) {
		std::cout << "Queue is empty" << std::endl;
		return;
	}
	std::string dequeueWord = arrayQueue[queueHead];
	if (queueHead == queueSize - 1) {
		queueHead = 0;
	}
	else {
		queueHead++;
	}
	queueCount--;
	std::cout << "H: " << queueHead << std::endl;
	std::cout << "T: " << queueTail << std::endl;
	std::cout << "word: " << dequeueWord << std::endl;
}


void Queue::printQueue() {
	if (queueCount == 0) {
		std::cout << "Empty" << std::endl;
	}
	int position = queueHead;
	for (int i = 0; i < queueCount; i++) {
		if (position == queueSize) {
			position = 0;
		}
		std::cout << position << ": " << arrayQueue[position] << std::endl;
		position++;
	}
}


void Queue::enqueueSentence(std::string sentence) {
	std::stringstream ss(sentence);
	std::string word = "";
	while (ss >> word) {
		enqueue(word);
	}
}


bool Queue::queueIsFull() {
	if (queueCount == queueSize) {
		return true;
	}
	return false;
}


bool Queue::queueIsEmpty() {
	if (queueCount == 0) {
		return true;
	}
	return false;
}