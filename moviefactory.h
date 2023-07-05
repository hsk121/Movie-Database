//Movie Factory header file

//Implentation and assumptions
// -will create a movie depending on type of movie
//-----------------------------------------Movie Factory------------------------------------------------------
#ifndef MOVIEFACTORY_H
#define MOVIEFACTORY_H
#include <string>
#include <iostream>
using namespace std;

#include "movie.h"
#include "comedy.h"
#include "drama.h"
#include "classic.h"

class MovieFactory {
public:
	static Movie* createMovie(char);
};

#endif 
