//Movie implementation file

//----------------------------------------------Movie--------------------------------
#include "movie.h"

//------------------------------constructor-----------------------------------------
Movie::Movie()
{
	stock = 0;
	director = "N/A";
	title = "N/A";
}

//-----------------------------less Than------------------------------------------------
bool Movie::lessThan(Movie*, Movie*)
{
	return false;
}

//--------------------------------display------------------------------------------------
void Movie::display()
{
	cout << stock << ", " << director << ", " << title << endl;
}

//--------------------------------add Type---------------------------------------------
void Movie::addType(char type)
{
	this->type = type;
}

//---------------------------add Stock---------------------------------------------------
void Movie::addStock(int stock)
{
	this->stock = stock;
}

//----------------------------add Director----------------------------------------------
void Movie::addDirector(string director)
{
	this->director = director;
}

//-----------------------------add Title--------------------------------------------
void Movie::addTitle(string title)
{
	this->title = title;
}

//--------------------------------get Stock-------------------------------------
int Movie::getStock()
{
	return this->stock;
}

//------------------------------get Director------------------------------------
string Movie::getDirector()
{
	return this->director;
}

//--------------------------------get Title---------------------------------------
string Movie::getTitle()
{
	return this->title;
}

//--------------------------------get Type----------------------------------
char Movie::getType()
{
	return this->type;
}
