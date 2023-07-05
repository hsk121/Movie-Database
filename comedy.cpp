//Comedy implementation file

//-------------------------------------Comedy----------------------------------------------------------------------------------

#include "comedy.h"

//---------------------------------------constructor-----------------------------------------------------------------------------
Comedy::Comedy()
{
	releaseYear = -1;
}

//--------------------------------setData----------------------------------------------------------------------------------------------
void Comedy::setData(char type, int stock, string director, string title, string releaseYear, string actor, string myearRelease)
{
	this->addType(type);
	this->addStock(stock);
	this->addDirector(director);
	this->addTitle(title);
	this->releaseYear = releaseYear;
}

//-------------------------------lessThan-------------------------------------------------------------------------------------------
bool Comedy::lessThan(Movie* a, Movie* b)
{
	Comedy* x = dynamic_cast<Comedy*>(a);
	Comedy* y = dynamic_cast<Comedy*>(b);
	//cout << "hello" << endl;
	if ((*x).getTitle() == (*y).getTitle()) {
		return (*x).releaseYear < (*y).releaseYear;
	}
	else {
		return(*x).getTitle() < (*y).getTitle();
	}
	return false;
}

//--------------------------------equalsTo-----------------------------------------------------------------
bool Comedy::equalsTo(Movie* a, Movie* b)
{
	Comedy* x = dynamic_cast<Comedy*>(a);
	Comedy* y = dynamic_cast<Comedy*>(b);
	return ((*x).getTitle() == (*y).getTitle()) && ((*x).releaseYear == (*y).releaseYear);
}

//---------------------------------display--------------------------------------------------------------------
void Comedy::display()
{
	cout << "F, " << this->getStock() << ", " << this->getDirector() << ", " << this->getTitle()
		<< ", " << releaseYear << endl;
}

//------------------------------------setReleaseYear----------------------------------------------
void Comedy::setReleaseYear(string rYear)
{
	this->releaseYear = rYear;
}
