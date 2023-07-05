//Comedy header file

//Assumptions and Implentation
//-comedy movies are sorted by title then year released
//-is a child of Movie

//-------------------------------------------Comedy-------------------------------------------------
#ifndef COMEDY_H
#define COMEDY_H
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

#include "movie.h"

class Comedy : public Movie {
public:
	Comedy(); //constructor
	bool lessThan(Movie*, Movie*); // <
	bool equalsTo(Movie*, Movie*); // = 
	void display();

	//setters
	void setData(char, int, string, string, string, string, string);
	void setReleaseYear(string);

private:
	string releaseYear;
};

#endif 
