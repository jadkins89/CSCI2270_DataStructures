// Author: Justin Adkins
// Homework #1
// Instructor: Jason Zietz

#include <iostream>
#include <fstream> // using ifstream
#include <sstream> // using stringstream

using namespace std;

// Struct Declaration
struct item{
	string type;
	bool trade;
	int price;
};

// Function Prototypes
int readCommBoard(item itemArray[], string filename, int index);
int checkMatch(item itemArray[], int index);
int deleteArrayElement(item itemArray[], int position, int index);
void printArray(item itemArray[], int index);


int main(int argc, char *argv[]) {
	item itemArray[100];
	int index = 0;

	string filename = argv[1];

	index = readCommBoard(itemArray, filename, index);

	cout << "#" << endl;

	printArray(itemArray, index);

	cout << "#" << endl;
	return 0;
}

/* 	readCommBoard takes in an item struct array, a string file name, and the index of our array.
	The function then opens the file, reading it line by line and storing the information in the
	array. It will only be temporarily stored unless no match is found using the checkMatch function.
	If it is found, the deleteArrayElement function is run to delete the matched element. Otherwise,
	the index is increased. When the file is done being read, it is closed and the function returns
	the final index of the array.
*/
int readCommBoard(item itemArray[], string filename, int index) {
	ifstream garageSale(filename, ios::in);
	
	if (garageSale.fail()) {
		return -1;
	}

	string tempLine; // Used to store lines before parced into struct
	
	while (getline(garageSale, tempLine)) {
		string tempLineArray[3];
		stringstream stream(tempLine);
		bool wanted = true;

		int i = 0;
		string currentElement;
		while (getline(stream, currentElement, ',')) {
			tempLineArray[i] = currentElement;
			stream >> ws; // gets rid of leading whitespace
			i++;
		}

		if (tempLineArray[1] == "for sale"){
			wanted = false; // for sale
		}

		itemArray[index] = {tempLineArray[0], wanted, stoi(tempLineArray[2])};
		int position = checkMatch(itemArray, index);
		if (position == -1) { // if no match, increase index to avoid overwriting
			index++;
		}
		else { // if match, delete sold item and decrease index by 1
			index = deleteArrayElement(itemArray, position, index);
		}
	}

	garageSale.close();
	return index;
}

/* 	checkMatch takes an item struct array and its index as parameters and checks the last element in the
	array against all other elements in the array. If an appropriate match is found, the items sale is 
	printed to the terminal and the position of the sale in the array is returned. Else, -1 is returned.
*/
int checkMatch(item itemArray[], int index) {
	for (int i = 0; i < index; i++) {
		if ((itemArray[index].type == itemArray[i].type) && (itemArray[index].trade != itemArray[i].trade)) {
			if (itemArray[index].trade == true) { // The item being compared is wanted
				if (itemArray[index].price >= itemArray[i].price) { // Is the item wanted priced greater than or equal to the sale price
					cout << itemArray[i].type << " " << itemArray[i].price << endl;
					return i;
				}
			}
			else { // The item being compared is for sale
				if (itemArray[index].price <= itemArray[i].price) {
					cout << itemArray[index].type << " " << itemArray[index].price << endl;
					return i;
				}
			}
		}
	}
	return -1;
}

/*	deleteArrayElement takes an item struct array, the position in the array being deleted, and the current index
	as parameters. The array is modified to deleted the element in the given position and shift all other elements
	in. The new index is returned.
*/
int deleteArrayElement(item itemArray[], int position, int index) {
	for (int i = position; i < index - 1; i++) {
		itemArray[i] = itemArray[i + 1];
	}
	return index - 1;
}

//	This function simply takes an item struct array, and walks through it. Printing information from each element.
void printArray(item itemArray[], int index){
	for (int i = 0; i < index; i++) {
		if (itemArray[i].trade) {
			cout << itemArray[i].type << ", " << "wanted" << ", " << itemArray[i].price << endl;
		}
		else {
			cout << itemArray[i].type << ", " << "for sale" << ", " << itemArray[i].price << endl;
		}
	}
}