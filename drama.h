//Drama header file

//Assumptions and Implentation
//-drama movies are sorted by director then title
//-is a child of Movie
//------------------------------------------Drama----------------------------------------------------
#ifndef DRAMA_H
#define DRAMA_H
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

#include "movie.h"

class Drama : public Movie {
public:
	Drama(); //constructor
	bool lessThan(Movie*, Movie*); // <
	bool equalsTo(Movie*, Movie*); // =
	void display(); 

	//setter
	void setData(char, int, string, string, string, string, string);

private:
	string releaseYear;
};

#endif 
