//Drama implentation file

//--------------------------------------Drama---------------------------------------------------------------
#include "drama.h"

//--------------------------------constructor------------------------------------------------------------
Drama::Drama()
{
	releaseYear = -1;
}

//---------------------------------------setData-----------------------------------------------------------------------------------
void Drama::setData(char type, int stock, string director, string title, string releaseYear, string actor, string mYearRelease)
{
	this->addType(type);
	this->addStock(stock);
	this->addDirector(director);
	this->addTitle(title);
	this->releaseYear = releaseYear;
}

//--------------------------------------lessThan---------------------------------------------------
bool Drama::lessThan(Movie* a, Movie* b)
{
	Drama* x = dynamic_cast<Drama*>(a);
	Drama* y = dynamic_cast<Drama*>(b);
	if ((*x).getDirector() == (*y).getDirector()) {
		return (*x).getTitle() < (*y).getTitle();
	}
	else {
		return (*x).getDirector() < (*y).getDirector();
	}
}

//---------------------------------------equalsTo------------------------------------------------------------
bool Drama::equalsTo(Movie* a, Movie* b)
{
	Drama* x = dynamic_cast<Drama*>(a);
	Drama* y = dynamic_cast<Drama*>(b);
	return ((*x).getTitle() == (*y).getTitle()) && ((*x).getDirector() == (*y).getDirector());
}

//-------------------------------------display---------------------------------------------------------------
void Drama::display()
{
	cout << "D, " << this->getStock() << ", " << this->getDirector() << ", " << this->getTitle()
		<< ", " << releaseYear << endl;
}
