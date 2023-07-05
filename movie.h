//Movie header file

//Implementation and Assumptions:
//  - Movie is parent of Classic, Comedy, Drama
//  - There is a Movie Factory that creates a movie depending on genre given

//-------------------------------Movie--------------------------------------------
#ifndef MOVIE_H
#define MOVIE_H
#include <string>
#include <iostream>

using namespace std;

class Movie {
public:
	Movie(); //constructor
	virtual bool equalsTo(Movie*, Movie*) = 0; //= operator, virtual
	virtual bool lessThan(Movie*, Movie*);     //< operator, virtual

	virtual void display(); //displays movie, virtual

	//setters
	virtual void setData(char, int, string, string, string, string, string) = 0; //sets movie with given data, virtual
	void addType(char);
	void addStock(int);
	void addDirector(string);
	void addTitle(string);

	//getters
	int getStock();
	string getDirector();
	string getTitle();
	char getType();

private: 
		int stock;
		string director;
		string title;
		char type;
};

#endif 
