//Classic implementation file

//-----------------------------Classic--------------------------------------------------
#include "classic.h"

//---------------------------constructor-----------------------------------------------
Classic::Classic()
{
	this->actor = "N/A";
	this->monthYearReleaseDate = "N/A";
}

//----------------------------less Than--------------------------------------------------
bool Classic::lessThan(Movie* a, Movie* b)
{
	Classic* x = dynamic_cast<Classic*>(a);
	Classic* y = dynamic_cast<Classic*>(b);
	istringstream sstream((*x).monthYearReleaseDate);
	int amonth;
	int ayear;
	sstream >> amonth >> ayear;

	istringstream sstream2((*y).monthYearReleaseDate);
	int bmonth;
	int byear;
	sstream2 >> bmonth >> byear;

	if (amonth == bmonth && ayear == byear) {
		return (*x).actor < (*y).actor;
	}
	else {
		if (ayear == byear) {
			return amonth < bmonth;
		}
		else {
			return ayear < byear;
		}
	}
}

//----------------------------equals To----------------------------------------------------
bool Classic::equalsTo(Movie* a, Movie* b)
{
	Classic* x = dynamic_cast<Classic*>(a);
	Classic* y = dynamic_cast<Classic*>(b);
	istringstream sstream((*x).monthYearReleaseDate);
	int amonth;
	int ayear;
	sstream >> amonth >> ayear;

	istringstream sstream2((*y).monthYearReleaseDate);
	int bmonth;
	int byear;
	sstream2 >> bmonth >> byear;
	return  (amonth == bmonth) && (ayear == byear) && ((*x).actor == (*y).actor);
		
}

//--------------------------------display---------------------------------------------
void Classic::display()
{
	cout << "C, " << this->getStock() << ", " << this->getDirector() << ", " << this->getTitle() << ", "
		<< actor << " " << monthYearReleaseDate << endl;
}

//---------------------------------setData--------------------------------------------------------------------------------------------
void Classic::setData(char type, int stock, string director, string title, string releaseYear, string actor, string mYearRelease)
{
	this->addType(type);
	this->addStock(stock);
	this->addDirector(director);
	this->addTitle(title);
	this->actor = actor;
	this->monthYearReleaseDate = mYearRelease;

}

//-----------------------------setActor------------------------------------
void Classic::setActor(string actor)
{
	this->actor = actor;
}

//-------------------------------setReleaseDate-----------------------------------------
void Classic::setReleaseDate(string date)
{
	this->monthYearReleaseDate = date;
}

//------------------------------------getActor-----------------------------------------
string Classic::getActor()
{
	return this->actor;
}

//------------------------------getReleaseDate-------------------------------------------
string Classic::getReleaseDate()
{
	return this->monthYearReleaseDate;
}
