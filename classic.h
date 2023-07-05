//Classic header file

//Implementations and Assumptions
//-classic movies are sorted by release date, then major actor
//-is child class of Movie

//-----------------------------Classic--------------------------------------------
#ifndef CLASSIC_H
#define CLASSIC_H
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

#include "movie.h"

class Classic : public Movie {
public:
	Classic(); //constructor
	bool lessThan(Movie*, Movie*); // <
	bool equalsTo(Movie*, Movie*); // =

	void display();

	//setters
	void setData(char, int, string, string, string, string, string);
	void setActor(string);
	void setReleaseDate(string);

	//getters
	string getActor();
	string getReleaseDate();

private:
	string actor;
	string monthYearReleaseDate;
};

#endif 
