//Store header file

//Assumptions and Implementations
//    -each store has a CustomerDatabase and a (movie)
//          Inventory
//--------------------------Store-----------------------
#ifndef STORE_H
#define STORE_H
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <istream>
#include <string.h>
#include "customerdatabase.h"
#include "inventory.h"

using namespace std;

class Store {
public:
	Store();
	void processCustomerDatabase();
	void processInventory();
	void processCommands();

private:
	CustomerDatabase A;
	Inventory B;
};

#endif 
