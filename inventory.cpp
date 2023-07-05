//Inventory implementation file

//---------------------------------Inventory--------------------------------------------------
#include "inventory.h"


//---------------------------------constructor--------------------------------------------------
Inventory::Inventory()
{
	dramaRoot = NULL;
	comedyRoot = NULL;
	classicRoot = NULL;
}

//----------------------------------build Inventory------------------------------------------------
void Inventory::buildInventory(ifstream& infile)
{
	string s;
	while (getline(infile, s)) {
		istringstream sstream(s); //using istringstream to separate the values into variables
		char type;
		sstream >> type;
		Movie* m = MovieFactory::createMovie(type);
		string buffer;
		string stock;
		string director;
		string title;
		getline(sstream, buffer, ',');
		getline(sstream, stock, ',');
		getline(sstream, director, ',');
		director = director.substr(1, director.length());
		getline(sstream, title, ',');
		title = title.substr(1, title.length());
		int stockInt = stoi(stock);

		if (type == 'F' || type == 'D') {
			string year;
			getline(sstream, year, ',');
			year = year.substr(1, year.length());
			m->setData(type, stockInt, director, title, year, "N/A", "N/A"); //sets data into m
			if (type == 'F') {
				insert(m, &comedyRoot); //inserts m into comedy bst because it is of type F
			}
			else { //type == 'D'
				insert(m, &dramaRoot); //inserts m into drama bst
			}
		}
		if (type == 'C') {
			string actorAndReleaseDate;
			getline(sstream, actorAndReleaseDate);
			actorAndReleaseDate = actorAndReleaseDate.substr(1, actorAndReleaseDate.length());
			int digitIndex = -1;
			for (int i = 0; i < actorAndReleaseDate.length(); i++) {
				if (isdigit(actorAndReleaseDate.at(i))) {
					digitIndex = i;
					break;
				}
			}
			string releaseDate = actorAndReleaseDate.substr(digitIndex, actorAndReleaseDate.length() - digitIndex);
			actorAndReleaseDate.resize(digitIndex);
			string actor = actorAndReleaseDate;
			actor = actor.substr(0, actor.length() - 1);
			m->setData(type, stockInt, director, title, "N/A", actor, releaseDate);
			insert(m, &classicRoot); //inserts m into classic bst
		}
	}
}

//------------------------------------display Inventory---------------------------------------------------------
void Inventory::displayInventory(Node* current)
{
	if (current != NULL) {
		displayInventory(current->left);
		current->movieData->display();
		displayInventory(current->right);
	}
}

//-----------------------------------displays Total Inventory----------------------------------------------------
void Inventory::displayTotalInventory()
{
	displayInventory(comedyRoot);
	displayInventory(dramaRoot);
	displayInventory(classicRoot);
	cout << endl;
}

//--------------------------------------inventory Transaction------------------------------------------------------
//this method organizes the transaction data before calling a return or borrow method
string Inventory::inventoryTransaction(char mType, string descrip, char aType)
{
	string s;
	istringstream sstream(descrip);
	if (mType == 'C') {
		string cMonth;
		string cYear;
		string actor;
		sstream >> cMonth >> cYear;
		getline(sstream, actor);
		actor = actor.substr(1, actor.length());
		string releaseD = cMonth + " " + cYear;
		Classic c;
		c.setActor(actor);
		c.setReleaseDate(releaseD);
		Classic* cP = &c;
		if (aType == 'R') {
			movieReturn(cP, classicRoot);
		}
		else { //borrow
			return movieBorrow(cP, classicRoot, mType, descrip);
		}
	}
	else if (mType == 'D') {
		string dDirector;
		string dTitle;
		getline(sstream, dDirector, ',');
		dDirector = dDirector.substr(1, dDirector.length());
		getline(sstream, dTitle, ',');
		dTitle = dTitle.substr(1, dTitle.length());
		Drama d;
		d.addDirector(dDirector);
		d.addTitle(dTitle);
		Drama* dP = &d;
		if (aType == 'R') {
			movieReturn(dP, dramaRoot);
		}
		else { //borrow
			return movieBorrow(dP, dramaRoot, mType, descrip);
		}
	}
	else { //type = 'F'
		string fTitle;
		string fYear;
		getline(sstream, fTitle, ',');
		getline(sstream, fYear, ',');
		fTitle = fTitle.substr(1, fTitle.length());
		fYear = fYear.substr(1, fYear.length());
		Comedy f;
		f.addTitle(fTitle);
		f.setReleaseYear(fYear);
		Comedy* fP = &f;
		if (aType == 'R') {
			movieReturn(fP, comedyRoot);
		}
		else {
			return movieBorrow(fP, comedyRoot, mType, descrip);
		}
	}
	if (aType == 'R') { // return transaction is already tested for in customer inventory transaction so all will go through/"T"
		s = "T";
		return s;
	}
	return s;//
}

//--------------------------------movie Borrow--------------------------------------------------------------
string Inventory::movieBorrow(Movie* c, Node* root, char mType, string descrip) //found is root
{
	string s;
	Node* found = movieBorrowHelper(c, root);  //found is where the movie exists on its bst
	movieBorrowHelper(c, found);
	if (found == NULL) {
		cout << "Movie does not Exist in Inventory: " << descrip << endl;
		cout << endl;
		s = "F";
		return s;
	}
	else { 
		int curStock = found->movieData->getStock();
		if (mType == 'D' || mType == 'F') {
			if (curStock <= 0) { //if type of movie is drama or comedy and current stock is less than or equal to 0
				cout << "Movie: " << descrip << " is out of stock. Cannot be borrowed." << endl;
				cout << endl;
				s = "F";
				return s;
			}
			else { //if current stock is more than 0, can process transaction
				found->movieData->addStock(curStock - 1);
				string x = "T";
				return x;
			}
		}
		if (mType == 'C') { //if movie is a classic and out of stock, need to check if there is other listing of same movie with different actor that can be borrowed
			if (curStock <= 0) {
				//check bst to right for match
				if (found->right != nullptr && ((found->right->movieData->getTitle() == found->movieData->getTitle()) && found->right->movieData->getStock() > 0))
				{
					found->right->movieData->addStock(curStock - 1);
					s = "T";
					Classic* x = dynamic_cast<Classic*>(found->right->movieData);
					s = s + " " + (*x).getReleaseDate() + " " + (*x).getActor(); //need to return description of movie listing that will be borrowed instead
					return s;
				}
				//check bst to left for match
				if ((((found->left->movieData->getTitle() == found->movieData->getTitle()) && found->left->movieData->getStock() > 0))&& found->left != nullptr)
				{
					found->left->movieData->addStock(curStock - 1);
					s = "T";
					Classic* x = dynamic_cast<Classic*>(found->left->movieData);
					s = s + (*x).getReleaseDate()  + " " + (*x).getActor();  //need to return description of movie listing that will be borrowed instead
					return s;
				}
				cout << "Movie: " << descrip << " is out of stock. Cannot be borrowed." << endl;
				cout << endl;
				s = "F";
				return s;
			}
			else { //there are enough classic movies of given listing in stock
				found->movieData->addStock(curStock - 1);
				s = "T";
				return s;
			}
		}
	}
	return s;//
}


//-----------------------------movie Borrow Helper---------------------------------------------------------------------------------------------
//returns where in its bst the movie is stored
Inventory:: Node* Inventory::movieBorrowHelper(Movie* c, Node* root)
{
	if ((root == NULL) || ((*c).equalsTo(c, root->movieData))) {
		return root;
	}
	else if ((*c).lessThan(c, root->movieData)) {
		return movieBorrowHelper(c, root->left);
	}
	else { //if c is bigger than root->movieData
		return movieBorrowHelper(c, root->right);
	}

}

//------------------------------insert ------------------------------------------------------------------------------------------------------
//inserts movie into its bst
bool Inventory::insert(Movie* m, Node** typeOfRoot)
{
	if (*typeOfRoot == NULL) {
		*typeOfRoot = new Node;
		(*typeOfRoot)->movieData = m;
		(*typeOfRoot)->left = NULL;
		(*typeOfRoot)->right = NULL;
		return true;
	}
	else {
		return insertAt(m, typeOfRoot);
	}
}

//-------------------------------insertAt---------------------------------------------------------------------------------------------
//helper method for insert method
bool Inventory::insertAt(Movie* m, Node** cur)
{
	if ((checkIfRepeat(cur, m)) == true) {
		return false;
	}
	//at this point no repeats, and root is not null

	if ((*m).lessThan(m, (*cur)->movieData)) {
		if ((*cur)->left == NULL) {
			(*cur)->left = new Node;
			(*cur)->left->movieData = m;
			(*cur)->left->left = NULL;
			(*cur)->left->right = NULL;
		}
		else {
			insertAt(m, &((*cur)->left));
		}
	}
	else { //m > cur->movieData
		if ((*cur)->right == NULL) {
			(*cur)->right = new Node;
			(*cur)->right->movieData = m;
			(*cur)->right->left = NULL;
			(*cur)->right->right = NULL;
		}
		else {
			insertAt(m, &((*cur)->right));
		}
	}
	return true;
}

//-------------------------checkIfRepeat-------------------------------------------------------------------------------------
//checks if listing already exists in the tree
bool Inventory::checkIfRepeat(Node** original, Movie* check)
{
	if ((*original)->movieData == check) {
		return true;
	}
	else {
		if ((*original)->right != NULL && ((*original)->right->movieData < check || (*original)->right->movieData == check)) {
			return checkIfRepeat(&((*original)->right), check);
		}
		if ((*original)->left != NULL && !((*original)->left->movieData < check)) {
			return checkIfRepeat(&((*original)->left), check);
		}
	}
	return false;
}

//------------------------------------movieReturn--------------------------------------------------------------------------
//processes return of movie 
void Inventory::movieReturn(Movie* c, Node* root)
{
	if (root == NULL) {
	}
	else if ((*c).equalsTo(c,root->movieData )) {
		int curStock = root->movieData->getStock();
		root->movieData->addStock(curStock + 1);
	}
	else if ((*c).lessThan(c, root->movieData)) {
		movieReturn(c, root->left);
	}
	else { //if c is bigger than root->movieData
		movieReturn(c, root->right);
	}
}
