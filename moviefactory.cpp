//Movie factory implentation file
#include "moviefactory.h"

//--------------------------------Movie Factory------------------------------------------
//--------------------createMovie---------------------------------------------------------
Movie* MovieFactory::createMovie(char type)
{
	Movie* t;
	switch (type) {
	case 'F':
		t = new Comedy();
		return t;
	case 'D':
		t = new Drama();
		return t;
	case 'C':
		t = new Classic();
		return t;
	default:
		cout << "In data4movies.txt, Invalid movie type entry: " << type << endl;
		cout << endl;
		t = NULL;
		return t;
	}
}
