//
//  MovieTree.hpp
//  Assignment-6    
//  CSCI 2270
//

#ifndef MOVIETREE_H
#define MOVIETREE_H

#include <string>

struct MovieNodeLL{
    int ranking;
    std::string title;
    int year;
    int quantity;
    MovieNodeLL* next;
    MovieNodeLL(){};
    
    MovieNodeLL(int in_ranking, std::string in_title, int in_year, int in_quantity)
    {
        ranking = in_ranking;
        title = in_title;
        year = in_year;
        quantity = in_quantity;
        next = NULL;
    };
};

struct MovieNodeBST{
    char letter;
    MovieNodeBST* parent;
    MovieNodeBST* leftChild;
    MovieNodeBST* rightChild;
    MovieNodeLL* head;
    
    MovieNodeBST(){};
    
    MovieNodeBST(char in_letter)
    {
        letter = in_letter;
        parent = NULL;
        leftChild = NULL;
        rightChild = NULL;
        head = NULL;
    };
    
};

class MovieTree
{
    
public:
    MovieTree();
    ~MovieTree();
    void printMovieInventory();
    int countMovieNodes();
    void deleteMovieNode(std::string title);
    void addMovieNode(int ranking, std::string title, int releaseYear, int quantity);
    void findMovie(std::string title);
    void rentMovie(std::string title);
    
protected:
    
private:
    void DeleteAll(MovieNodeBST* node); //use this for the post-order traversal deletion of the tree
    void printMovieInventory(MovieNodeBST* node);
    void countMovieNodes(MovieNodeBST* node, int *c);
    MovieNodeBST* searchBST(MovieNodeBST *node, std::string title); //use this recursive function to find a pointer to a node in the BST, given a MOVIE TITLE
    MovieNodeLL* searchLL(MovieNodeLL* head, std::string title); //use this to return a pointer to a node in a linked list, given a MOVIE TITLE and the head of the linked list
    MovieNodeBST* treeMinimum(MovieNodeBST *node); //use this to find the left most leaf node of the BST, you'll need this in the delete function
    MovieNodeBST* root;
};

#endif // MOVIETREE_H
