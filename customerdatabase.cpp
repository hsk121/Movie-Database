//Customer Database implementation file
// 

//----------------------------------Customer Database---------------------------------------------------------------
#include "customerdatabase.h"

//--------------------------------------constructor------------------------------------------------------------------------
CustomerDatabase::CustomerDatabase()
{
	for (int i = 0; i < 10; i++) {
		D[i].head = new CustomerNode;
		D[i].head->nextCustomer = NULL;
		D[i].head->custID = -1;
		D[i].head->name = "";
	}
}

//----------------------------------------buildDatabase-----------------------------------------------------------------
//there are 10 buckets in hashtable
void CustomerDatabase::buildDatabase(ifstream& infile)
{
	string s;
	while (getline(infile, s)) {
		istringstream sstream(s);
		int currentId;
		string currentName;
		sstream >> currentId >> currentName;
		CustomerNode* incoming = new CustomerNode;
		incoming->custID = currentId;
		incoming->name = currentName;
		incoming->history[0] = "";
		incoming->nextCustomer = D[currentId % 10].head->nextCustomer;
		D[currentId % 10].head->nextCustomer = incoming;
	}
}

//----------------------------------------transaction------------------------------------------------------------------
bool CustomerDatabase::transaction(int id, const string tEntry, char tType, string movieDescrip, string switched)
{
	int index = id % 10;
	bool custFound = false;
	CustomerNode* search = D[index].head->nextCustomer; //will search for where the customer is in the hashtable
	while (search != NULL) {
		if (search->custID == id) {
			custFound = true;
			break;
		}
		search = search->nextCustomer;
	}
	int opening = 0;
	while (search->history[opening] != "") { //finding opening in the customer's history to put down the transaction
		opening++;
	}
	if (custFound == true) {
		if (tType == 'R') { //if a return
			bool tFound = false;
			string tester = "B" + movieDescrip; //need to check if it was borrowed first
			for (int i = 0; i < CUST_HISTORY_MAX; i++) {
				if (search->history[i] == tester) {
					tFound = true;
				}
			}
			if (!tFound) { //if no record of borrowing this movie
				cout << "Invalid Return of:  " << movieDescrip << ".  Movie was not borrowed by Customer # " << id << endl;
				return false;
			}
			
			search->history[opening] = "R" + movieDescrip; //at this point we have confirmed that the movie was borrowed so can return
			return true;
		}
		else { //tType is borrow
			if (switched != "") { //if we are in situation where we lent out a copy of same movie but different actor than requested, need to put down proper
				                        //transaction of the listing of the different actor
				search->history[opening] = "B" + switched;
			}
			else { //we did not do any switching of listings
				search->history[opening] = "B" + movieDescrip;
			}
			return true;
		}
	}
	else {
		cout << "Incorrect Customer Code: Not Found" << endl;
		return false;
	}
}

//--------------------------------------------displayCustomerHistory-----------------------------------------------------
void CustomerDatabase::displayCustomerHistory(int id)
{
	int index = id % 10;
	bool found = false;
	CustomerNode* search = D[index].head->nextCustomer;
	while (search != NULL) {
		if (search->custID == id) {
			found = true;
			break;
		}
		search = search->nextCustomer;
	}
	if (found == true) {
		for (int i = 0; i < CUST_HISTORY_MAX; i++) {
			if (search->history[i] != "") {
				cout << search->history[i] << endl;
			}
		}
	}
	else {
		cout << "Incorrect Customer Code: Not Found" << endl;
	}
}

//-------------------------------------------customerExists------------------------------------------------------------
bool CustomerDatabase::customerExists(int id)
{
	int index = id % 10;
	CustomerNode* search = D[index].head->nextCustomer;
	while (search != NULL) {
		if (search->custID == id) {
			return true;
		}
		search = search->nextCustomer;
	}
	return false;
}


