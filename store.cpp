//Store implementation file
// 
//---------------------Store------------------------------
#include "store.h"

//----------------constructor--------------------------
Store::Store()
{

}

//-----------------processCustomerDatabase----------------
void Store::processCustomerDatabase()
{
	ifstream infile1("data4customers.txt");
	if (!infile1) {
		cout << "File could not be opened." << endl;
	}
	A.buildDatabase(infile1);
}

//---------------processInventory------------------------
void Store::processInventory()
{
	ifstream infile2("data4movies.txt");
	if (!infile2) {
		cout << "File could not be opened." << endl;
	}
	B.buildInventory(infile2);
	//B.displayTotalInventory();
}

//---------------processCommands------------------------
void Store::processCommands()
{
	ifstream infile3("data4commands.txt");
	if (!infile3) {
		cout << "File could not be opened." << endl;
	}

	string s;
	while (getline(infile3, s)) {
		istringstream sstream(s);
		char aType;
		sstream >> aType;
		int custID;
		char dvd;
		char mType;
		sstream >> custID >> dvd >> mType;
		string movieDescrip;
		getline(sstream, movieDescrip);
		if (!((aType == 'B') || (aType == 'R') || (aType == 'I') || (aType == 'H'))) {
			cout << "Invalid Action Code: " << aType << "     FROM ENTRY: " << s << endl;
			cout << endl;
		}
		else if (aType == 'I') {
			cout << "Total Movie Inventory:" << endl;
			B.displayTotalInventory();

		}
		else if (!(A.customerExists(custID))) {
			cout << "Incorrect Customer Code: " << custID << "     FROM ENTRY: " << s << endl;
			cout << endl;
		}
		else if (aType == 'H') { //customer history
			cout << "Customer ID # " << custID << " History: " << endl;
			A.displayCustomerHistory(custID);
			cout << endl;
		}
		else if (dvd != 'D') {
			cout << "Invalid DVD Code: " << dvd << "     FROM ENTRY: " << s << endl;
			cout << endl;
		}
		else if (!((mType == 'C') || (mType == 'D') || (mType == 'F'))) {
			cout << "Invalid Movie Type: " << mType << "     FROM ENTRY: " << s << endl;
			cout << endl;
		}
		else if (aType == 'B') {
			string transacSwitch = B.inventoryTransaction(mType, movieDescrip, aType);		
			istringstream scanner(transacSwitch);
			string transacOK;
			scanner >> transacOK; 
			string movieD;
			getline(scanner, movieD);
			//only if transaction goes through in movie inventory does it also go through
			//customer history, movie needs to be in stock and exist
			if (transacOK == "T") { 
				A.transaction(custID, s, aType, movieDescrip, movieD);
			} 
		}
		else { //aType == 'R'
			string noswitch = "";
			//only if transaction goes through in customer history does it also go through
			//movie inventory, movie needs to have been borrowed to be returned
			if (A.transaction(custID, s, aType, movieDescrip, noswitch)) {
				B.inventoryTransaction(mType, movieDescrip, aType);
			}
		}
	}
}



