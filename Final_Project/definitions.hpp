#include <iostream>
//This file is used for easy access to commonly manipulated variables
#pragma once

#define PINDEX 880 // Max length of queue
#define TIMES_RUN 2000 // Number of times to run equeue / dequeue
#define STEP_COUNT 200 // Size increase per test
#define OUTPUT_FILE "finalProject10000_2000.csv"
#define START_LENGTH 100 // Initial size of dynamically allocated array for heap

struct patientData {
	std::string name;
	int primaryPriority;
	int treatmentLength;
};