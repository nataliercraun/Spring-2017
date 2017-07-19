#include "product.h"
#include "movie.h"
#include "util.h"
#include <iostream> 
#include <sstream> 

using namespace std; 

Movie::Movie(std::string genre, std::string rating, std::string category, std::string name, double price, int qty) 
	: Product(category, name, price, qty) 
{
	genre_ = genre; 
	rating_ = rating; 
}

Movie::~Movie() 
{

}

std::set<std::string> Movie::keywords() const 
{
	std::set<std::string> keys; 
	keys = parseStringToWords(name_); 
	std::set<std::string> genre; 
	genre = parseStringToWords(genre_); 
	std::set<std::string> combine; 
	combine = setUnion(keys, genre);  
	return combine; 
} 

std::string Movie::displayString() const 
{
	stringstream ss; 
	ss << name_ << endl; 
	ss << "Genre: " << genre_ << " ";  
	ss << "Rating: " << rating_ << endl; 
	ss << price_ << " "; 
	ss << qty_ << " left." << endl; 
	return ss.str(); 
} 

void Movie::dump(std::ostream& os) const {

	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_; 
	os << "\n" << genre_ << "\n" << rating_ << endl; 
}