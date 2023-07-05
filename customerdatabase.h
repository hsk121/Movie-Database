//Customer Database header file

//Implentations and Assumptions
//-customer info is one line per customer
//		-data is formatted correctly
//-uses hashtable for customer data
//-transactions will be recorded in customer history in same format as command, using the two sorting attributes
//-------------------------------------------------------Customer Database----------------------------------------------------------------
#ifndef CUSTOMERDATABASE_H
#define CUSTOMERDATABASE_H
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int const CUST_HISTORY_MAX = 150;  //customer tranaction history max spaces

class CustomerDatabase {
public:
	CustomerDatabase(); //constructor
	void buildDatabase(ifstream&);
	bool transaction(int, const string, char, const string, string);  //processes borrows and returns
	void displayCustomerHistory(int);
	bool customerExists(int);

private:

	struct CustomerNode {
		int custID;
		string name;
		string history[CUST_HISTORY_MAX]; //holds transaction history
		CustomerNode* nextCustomer; //points to next Customer 
	};

	struct DatabaseNode {
		CustomerNode* head;
	};

	DatabaseNode D[10]; //there will be 10 buckets

};


#endif
