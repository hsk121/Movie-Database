//Inventory header file

//Implementation and Assumptions
//        - the three genres are categorized in separate binary search trees
//        - inventory is responsible for creating those trees and displaying each inventory

//------------------------------------Inventory------------------------------------------
#ifndef INVENTORY_H
#define INVENTORY_H
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string.h>
#include <istream>
using namespace std;

#include "movie.h"
#include "moviefactory.h"
class Inventory {
private:
	struct Node {
		Movie* movieData = NULL;					// pointer to data object
		Node* left = NULL;					// left subtree pointer
		Node* right = NULL;				// right subtree pointer
	};
	Node* dramaRoot;
	Node* comedyRoot;
	Node* classicRoot;

	bool insert(Movie*, Node**); //inserts node into tree
	bool insertAt(Movie*, Node**); //helper method for insert

	bool checkIfRepeat(Node**, Movie*); //checks if an entry already exists in the inventory
	void movieReturn(Movie*, Node*); //processes return transaction
	string movieBorrow(Movie*, Node*, char, string); //processes borrow transaction
	Node* movieBorrowHelper(Movie*, Node*); //helper for movieBorrow
	

public:
	Inventory(); //constructor
	void buildInventory(ifstream&); //builds whole inventory
	void displayInventory(Node*); //displays one inventory
	void displayTotalInventory(); //displays all inventories
	string inventoryTransaction(char, string, char); //transaction method that occurs before the borrow or return method
};

#endif 

