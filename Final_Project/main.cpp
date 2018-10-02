// Justin Adkins
// CSCI 2270
// FINAL PROJECT

#include <fstream>
#include <sstream>
#include <chrono>	// For chrono / timing
#include <cmath>	// For pow / sqrt
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()
#include "definitions.hpp"
#include "priorityLL.hpp"
#include "priorityHeap.hpp"
#include "prioritySTL.hpp"
#include "dynamicPriorityHeap.hpp"

// Prototypes
bool dataRetrieval(std::string fileName, patientData pd[]);
void testHeap(patientData* pd, std::ofstream& outputFile, int listLength);
void testDynamicHeap(patientData* pd, std::ofstream& outputFile, int listLength);
void testLL(patientData* pd, std::ofstream& outputFile, int listLength);
void testSTL(patientData* pd, std::ofstream& outputFile, int listLength);
void createMassiveData();

/*  DRIVER */
int main (int argc, char* argv[]) {
	patientData pd[PINDEX];
	dataRetrieval(argv[1], pd);

	//createMassiveData();

	std::ofstream outputFile(OUTPUT_FILE, std::ofstream::out);
	outputFile << "HEAP PRIORITY QUEUE DATA\n" << std::endl;
	outputFile << "Length,Mean,Std Dev" << std::endl;
	for (int i = STEP_COUNT; i <= PINDEX; i += STEP_COUNT) {
		outputFile << i << ",";
		testHeap(pd, outputFile, i);
	}
	outputFile << "\n\nDYNAMIC HEAP PRIORITY QUEUE DATA\n" << std::endl;
	outputFile << "Length,Mean,Std Dev" << std::endl;
	for (int i = STEP_COUNT; i <= PINDEX; i += STEP_COUNT) {
		outputFile << i << ",";
		testDynamicHeap(pd, outputFile, i);
	}
	outputFile << "\n\nSTL PRIORITY QUEUE DATA\n" << std::endl;
	outputFile << "Length,Mean,Std Dev" << std::endl;
	for (int i = STEP_COUNT; i <= PINDEX; i += STEP_COUNT) {
		outputFile << i << ",";
		testSTL(pd, outputFile, i);
	}
	outputFile << "\n\nLINKED LIST PRIORITY QUEUE DATA\n" << std::endl;
	outputFile << "Length,Mean,Std Dev" << std::endl;
	for (int i = STEP_COUNT; i <= PINDEX; i += STEP_COUNT) {
		outputFile << i << ",";
		testLL(pd, outputFile, i);
	}
	outputFile.close();

	return 0;
}

/* Function used to retrieve the data from a file and place it into an array */
bool dataRetrieval(std::string fileName, patientData pd[]) {
	std::ifstream patientStream(fileName, std::ios::in);
	int index = 0;
	std::string currentLine;
	getline(patientStream, currentLine); //Throw out first line
	while (getline(patientStream, currentLine) && index < PINDEX) {
		std::stringstream ss(currentLine);
		std::string currentElement;
		getline(ss, currentElement, ',');
		pd[index].name = currentElement;
		getline(ss, currentElement, ',');
		pd[index].primaryPriority = stoi(currentElement);
		getline(ss, currentElement);
		pd[index].treatmentLength = stoi(currentElement);
		index++;
	}
	patientStream.close();
	return true;
}

/* Used to copy array for use inside helper functions */
void copyPatientData(patientData* pd, patientData localPD[], int listLength) {
	for (int i = 0; i < listLength; i++) {
		localPD[i].name = pd[i].name;
		localPD[i].primaryPriority = pd[i].primaryPriority;
		localPD[i].treatmentLength = pd[i].treatmentLength;
	}
}

/* This function takes in a pointer to an array of data, a reference to an output
stream, and the max length (list length) of the queue. It copies the data for local
use and runs a sequence of tests (TIME_RUN times) on an increasingly larger queue
length. Each time the test has run an appropriate number of times, the data average
is output to a file. */
void testHeap(patientData* pd, std::ofstream& outputFile, int listLength) {
	patientData localPD[listLength];
	float runTime[TIMES_RUN];
	copyPatientData(pd, localPD, listLength);
	float heapDataSum = 0.0;
	for (int i = 0; i < TIMES_RUN; i++) {
		PriorityHeap ph(listLength);
		// Start timer
		auto start = std::chrono::system_clock::now();
		for (int j = 0; j < listLength; j++) {
			ph.enqueue(localPD[j]);
		}
		ph.dequeueAll();
		auto end = std::chrono::system_clock::now();
		auto timeElapsed = std::chrono::duration<float, std::milli>(end - start);
		heapDataSum += (float)timeElapsed.count();
		runTime[i] = timeElapsed.count();
	}
	float mean = heapDataSum / TIMES_RUN;
	// Calculate Standard Deviation
	float sqrSum = 0.0;
	for (int i = 0; i < TIMES_RUN; i++) {
		sqrSum += pow((runTime[i] - mean), 2);
	}
	float stdDev = sqrt(sqrSum / TIMES_RUN);

	outputFile << std::fixed << mean << "," 
	<< stdDev << std::endl;
}

/* Similiar to testHeap function but using DynamicHeap object */
void testDynamicHeap(patientData* pd, std::ofstream& outputFile, int listLength) {
	patientData localPD[listLength];
	float runTime[TIMES_RUN];
	copyPatientData(pd, localPD, listLength);
	float heapDataSum = 0.0;
	for (int i = 0; i < TIMES_RUN; i++) {
		DynamicPriorityHeap ph;
		// Start timer
		auto start = std::chrono::system_clock::now();
		for (int j = 0; j < listLength; j++) {
			ph.enqueueDynamic(localPD[j]);
		}
		ph.dequeueAllDynamic();
		auto end = std::chrono::system_clock::now();
		auto timeElapsed = std::chrono::duration<float, std::milli>(end - start);
		heapDataSum += (float)timeElapsed.count();
		runTime[i] = timeElapsed.count();
	}
	float mean = heapDataSum / TIMES_RUN;
	// Calculate Standard Deviation
	float sqrSum = 0.0;
	for (int i = 0; i < TIMES_RUN; i++) {
		sqrSum += pow((runTime[i] - mean), 2);
	}
	float stdDev = sqrt(sqrSum / TIMES_RUN);

	outputFile << std::fixed << mean << "," 
	<< stdDev << std::endl;
}

/* Similiar to testHeap function but using priorityLL object */
void testLL(patientData* pd, std::ofstream& outputFile, int listLength) {
	patientData localPD[listLength];
	float runTime[TIMES_RUN];
	copyPatientData(pd, localPD, listLength);
	PriorityLL pl;
	float llDataSum = 0.0;
	for (int i = 0; i < TIMES_RUN; i++) {
		// Start timer
		auto start = std::chrono::system_clock::now();
		for (int j = 0; j < listLength; j++) {
			pl.enqueue(localPD[j]);
		}
		pl.dequeueAll();
		auto end = std::chrono::system_clock::now();
		auto timeElapsed = std::chrono::duration<float, std::milli>(end - start);
		llDataSum += (float)timeElapsed.count();
		runTime[i] = timeElapsed.count();
	}
	float mean = llDataSum / TIMES_RUN;
	// Calculate Standard Deviation
	float sqrSum = 0.0;
	for (int i = 0; i < TIMES_RUN; i++) {
		sqrSum += pow((runTime[i] - mean), 2);
	}
	float stdDev = sqrt(sqrSum / TIMES_RUN);

	outputFile << std::fixed << mean << "," 
	<< stdDev << std::endl;
}

/* Similiar to testHeap function but using PrioritySTL object */
void testSTL(patientData* pd, std::ofstream& outputFile, int listLength) {
	patientData localPD[listLength];
	float runTime[TIMES_RUN];
	copyPatientData(pd, localPD, listLength);
	PrioritySTL pSTL;
	float STLDataSum = 0.0;
	for (int i = 0; i < TIMES_RUN; i++) {
		// Start timer
		auto start = std::chrono::system_clock::now();
		for (int j = 0; j < listLength; j++) {
			pSTL.enqueue(localPD[j]);
		}
		pSTL.dequeueAll();
		auto end = std::chrono::system_clock::now();
		auto timeElapsed = std::chrono::duration<float, std::milli>(end - start);
		STLDataSum += (float)timeElapsed.count();
		runTime[i] = timeElapsed.count();
	}
	float mean = STLDataSum / TIMES_RUN;
	// Calculate Standard Deviation
	float sqrSum = 0.0;
	for (int i = 0; i < TIMES_RUN; i++) {
		sqrSum += pow((runTime[i] - mean), 2);
	}
	float stdDev = sqrt(sqrSum / TIMES_RUN);

	outputFile << std::fixed << mean << "," 
	<< stdDev << std::endl;
}

// Helper function to create a massive data set
void createMassiveData() {
	std::ofstream massive("SuperMassivePatientData.csv", std::ofstream::out);
	srand(time(0));
	for (int i = 0; i < 100000; i++) {
		massive << "Name" << i + 1 << ",";
		int primaryPriority = (rand() % 300) + 1;
		int treatmentLength = (rand() % 100) + 1;
		massive << primaryPriority << "," << treatmentLength << std::endl;
	}
	massive.close();
}

