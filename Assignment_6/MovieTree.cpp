#include <iostream>
#include "MovieTree.hpp"

// Helper Functions

MovieNodeBST* treeMaximum(MovieNodeBST* node) {
	if (node->rightChild != nullptr) {
		return treeMaximum(node->rightChild);
	}
	return node;
}

void printMovieInfo(MovieNodeLL* node) {
	std::cout << "Movie Info:" << std::endl;
	std::cout << "===========" << std::endl;
	std::cout << "Ranking:" << node->ranking << std::endl; 
	std::cout << "Title:" << node->title << std::endl;
	std::cout << "Year:" << node->year << std::endl;
	std::cout << "Quantity:" << node->quantity << std::endl;
	return;
}

// Constructor / Destructor

MovieTree::MovieTree() {
	root = nullptr;
}

MovieTree::~MovieTree() {
	DeleteAll(root);
}

// Public Methods

void MovieTree::printMovieInventory() {
	printMovieInventory(root);
}

int MovieTree::countMovieNodes() {
	int counter;
	counter = 0;
	countMovieNodes(root, &counter);
	return counter;
}


void MovieTree::deleteMovieNode(std::string title) {
	MovieNodeBST* tempNodeBST = searchBST(root, title);
	MovieNodeLL* tempNodeLL = nullptr;
	
	if (tempNodeBST != nullptr){ //character found in tree
		tempNodeLL = searchLL(tempNodeBST->head, title);
	}

	if (tempNodeLL != nullptr) { //movie found
		MovieNodeLL* searchNodeLL = tempNodeBST->head; //used to find previous node
		if (tempNodeLL == tempNodeBST->head) { //if deletion is the head node
			tempNodeBST->head = tempNodeLL->next;
			delete tempNodeLL;
			if (tempNodeBST->head == nullptr) {
				if (tempNodeBST->leftChild == nullptr && tempNodeBST->rightChild == nullptr) { // no children
					if (tempNodeBST == root) {
						root = nullptr;
					}
					else {
						if (tempNodeBST->parent->letter > tempNodeBST->letter) { // if node to be deleted is a left child
							tempNodeBST->parent->leftChild = nullptr;
						}
						else {
							tempNodeBST->parent->rightChild = nullptr;
						}
					}
					delete tempNodeBST;
				}
				else if (tempNodeBST->rightChild != nullptr) { // check the right side
					MovieNodeBST* minRight = treeMinimum(tempNodeBST->rightChild);

					if (minRight->rightChild != nullptr) { // If min node has a right child
						minRight->rightChild->parent = minRight->parent;

						if (minRight->parent->letter > minRight->letter) {
							minRight->parent->leftChild = minRight->rightChild;
						}
						else {
							minRight->parent->rightChild = minRight->rightChild;
						}
					}
					else {
						if (minRight->parent->letter > minRight->letter) {
							minRight->parent->leftChild = nullptr;
						}
						else {
							minRight->parent->rightChild = nullptr;
						}
					}
					tempNodeBST->letter = minRight->letter;
					tempNodeBST->head = minRight->head;
					delete minRight;
				}
				else { // check the left side
					MovieNodeBST* maxLeft = treeMaximum(tempNodeBST->leftChild);
					if (maxLeft->leftChild != nullptr) { // If max node has a left child
						maxLeft->leftChild->parent = maxLeft->parent;

						if (maxLeft->parent->letter > maxLeft->letter) {
							maxLeft->parent->leftChild = maxLeft->rightChild;
						}
						else {
							maxLeft->parent->rightChild = maxLeft->rightChild;
						}
					}
					else {
						if (maxLeft->parent->letter > maxLeft->letter) {
							maxLeft->parent->leftChild = nullptr;
						}
						else {
							maxLeft->parent->rightChild = nullptr;
						}
					}
					tempNodeBST->letter = maxLeft->letter;
					tempNodeBST->head = maxLeft->head;
					delete maxLeft;
				}
			}
		}
		else { // find the previous node, reassign its next position and delete
			while (searchNodeLL->next != tempNodeLL) { // find previous
				searchNodeLL = searchNodeLL->next;
			}
			searchNodeLL->next = tempNodeLL->next;
			delete tempNodeLL;
		}
	}
	else {
		std::cout << "Movie not found." << std::endl;
	}
}


void MovieTree::addMovieNode(int ranking, std::string title, int releaseYear, int quantity) {
	MovieNodeLL* newMovie = new MovieNodeLL(ranking, title, releaseYear, quantity);
	MovieNodeBST* currentBSTNode = nullptr;

	if (root == nullptr) {
		MovieNodeBST* rootNode = new MovieNodeBST(title[0]);
		root = rootNode;
		currentBSTNode = root;
	}
	else {
		currentBSTNode = searchBST(root, title);
		if (currentBSTNode == nullptr) {
			MovieNodeBST* newNode = new MovieNodeBST(title[0]); // New character node for tree
			currentBSTNode = root;
			bool insert = false;
			while (!insert) {
				if (currentBSTNode->letter > title[0]) {
					if (currentBSTNode->leftChild == nullptr) {
						currentBSTNode->leftChild = newNode;
						newNode->parent = currentBSTNode;
						currentBSTNode = newNode;
						insert = true;
					}
					else {
						currentBSTNode = currentBSTNode->leftChild;
					}
				}
				else { // currentBSTNode->letter < title[0]
					if (currentBSTNode->rightChild == nullptr) {
						currentBSTNode->rightChild = newNode;
						newNode->parent = currentBSTNode;
						currentBSTNode = newNode;
						insert = true;
					}
					else {
						currentBSTNode = currentBSTNode->rightChild;
					}
				}
			}
		}
	}

	if (currentBSTNode->head == nullptr) {
		currentBSTNode->head = newMovie;
		return;
	}
	MovieNodeLL* currentLLNode = nullptr;
	currentLLNode = searchLL(currentBSTNode->head, title);
	if (currentLLNode == nullptr) { //
		if (title < currentBSTNode->head->title) { // inserting new head
			newMovie->next = currentBSTNode->head;
			currentBSTNode->head = newMovie;
			return;			
		}
		currentLLNode = currentBSTNode->head;
		while (true) {
			if (currentLLNode->next == nullptr) { // new tail
				currentLLNode->next = newMovie;
				return;
			}
			else if (title < currentLLNode->next->title) { //insertion point
				newMovie->next = currentLLNode->next;
				currentLLNode->next = newMovie;
				return;
			}
			else {
				currentLLNode = currentLLNode->next;
			}
		}
	}
	else if (currentLLNode->title == title) { // If new movie already exists
		currentLLNode->quantity++;
		return;
	}
	return;
}


void MovieTree::findMovie(std::string title) {
	MovieNodeBST* tempNodeBST = searchBST(root, title);
	MovieNodeLL* tempNodeLL = nullptr;
	if (tempNodeBST != nullptr) {
		tempNodeLL = searchLL(tempNodeBST->head, title);
	}

	if (tempNodeLL != nullptr) {
		printMovieInfo(tempNodeLL);
	}
	else {
		std::cout << "Movie not found." << std::endl;
	}
}

void MovieTree::rentMovie(std::string title) {
	MovieNodeBST* tempNodeBST = searchBST(root, title);
	MovieNodeLL* tempNodeLL = nullptr;
	if (tempNodeBST != nullptr) {
		tempNodeLL = searchLL(tempNodeBST->head, title);
	}

	if (tempNodeLL != nullptr) {
		tempNodeLL->quantity--;
		std::cout << "Movie has been rented." << std::endl;
		printMovieInfo(tempNodeLL);
		if (tempNodeLL->quantity == 0) {
			deleteMovieNode(tempNodeLL->title);
		}
	}
	else {
		std::cout << "Movie not found." << std::endl;
	}
}

// Private Methods

void MovieTree::DeleteAll(MovieNodeBST* node) { //use this for the post-order traversal deletion of the tree
	if (node != nullptr) {
		if (node->leftChild != nullptr) {
			DeleteAll(node->leftChild);
		}
		if (node->rightChild != nullptr) {
			DeleteAll(node->rightChild);
		}
		MovieNodeLL* tempNodeLL = node->head;
		while (tempNodeLL != nullptr) {
			tempNodeLL = tempNodeLL->next;
			std::cout << "Deleting: " << node->head->title << std::endl;
			delete node->head;
			node->head = tempNodeLL;
		}
		delete node;
	}
}

void MovieTree::printMovieInventory(MovieNodeBST* node) {
	if (node != nullptr) {
		if (node->leftChild != nullptr) {
			printMovieInventory(node->leftChild);
		}
		MovieNodeLL* tempNodeLL = node->head;
		while (tempNodeLL != nullptr) {
			std::cout << "Movie: " << tempNodeLL->title << " " << tempNodeLL->quantity << std::endl;
			tempNodeLL = tempNodeLL->next;
		}
		if (node->rightChild != nullptr) {
			printMovieInventory(node->rightChild);
		}
	}
}

void MovieTree::countMovieNodes(MovieNodeBST* node, int* c) {
	if (node != nullptr) {
		if (node->leftChild != nullptr) {
			countMovieNodes(node->leftChild, c);
		}
		MovieNodeLL* tempNodeLL = node->head;
		while (tempNodeLL != nullptr) {
			(*c)++;
			tempNodeLL = tempNodeLL->next;
		}
		if (node->rightChild != nullptr) {
			countMovieNodes(node->rightChild, c);
		}
	}
}

//use this recursive function to find a pointer to a node in the BST, given a MOVIE TITLE
MovieNodeBST* MovieTree::searchBST(MovieNodeBST* node, std::string title) {
	char firstLetter = title[0];
	
	if (node->letter == firstLetter) {
		return node; //returns pointer to already created character node
	}
	else if (node->letter > firstLetter && node->leftChild != nullptr) {
		return searchBST(node->leftChild, title);
	}
	else if (node->letter < firstLetter && node->rightChild != nullptr) {
		return searchBST(node->rightChild, title);
	}
	else { // Not Found
		return nullptr;
	}
}

//use this to return a pointer to a node in a linked list, given a MOVIE TITLE and the head of the linked list
MovieNodeLL* MovieTree::searchLL(MovieNodeLL* head, std::string title) {
	MovieNodeLL* currentNode = head;
	while (currentNode != nullptr) { // Check to see if it is the new head (fix this)
		if (currentNode->title == title) { // We've landed on the title
			return currentNode; // returns pointer to title node
		}
		else {
			currentNode = currentNode->next;
		}
	}
	return nullptr;
}

//use this to find the left most leaf node of the BST, you'll need this in the delete function
MovieNodeBST* MovieTree::treeMinimum(MovieNodeBST* node) {
	if (node->leftChild != nullptr) {
		return treeMinimum(node->leftChild);
	}
	return node;
}		