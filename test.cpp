//File that tests all requirements

//Assumptions and Implementation
//  -Will not print out successful commands, only errors
//       -I did not count borrowing the same movie as 
//          an error as people can technically do that
//  -Inventory outputs comedy, drama, then classic movies
//  -Each category is sorted as required
//  -Each of the processes below processes the three given 
//        text files
#include "store.h"

int main() {
	Store s;
	s.processCustomerDatabase(); 
	s.processInventory();
	s.processCommands();
	return 0;
}
