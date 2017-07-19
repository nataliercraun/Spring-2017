#include "product.h"
#include "book.h"
#include "util.h"
#include <iostream> 
#include <sstream> 

using namespace std; 

Book::Book(std::string ISBN, std::string author, std::string category, std::string name, double price, int qty) 
	: Product(category, name, price, qty) 
{
	ISBN_ = ISBN; 
	author_ = author; 
}

Book::~Book() 
{

}

std::set<std::string> Book::keywords() const 
{
	std::set<std::string> name_keys;
	std::set<std::string> author_keys;
	std::set<std::string> keys; 
	name_keys = parseStringToWords(name_); 
	author_keys = parseStringToWords(author_); 
	keys = setUnion(name_keys, author_keys); 
	keys.insert(ISBN_); 
	return keys; 
} 

std::string Book::displayString() const 
{
	stringstream ss; 
	ss << name_ << endl; 
	ss << "Author: " << author_ << " "; 
	ss << "ISBN: " << ISBN_ << endl; 
	ss << price_ << " "; 
	ss << qty_ << " left." << endl; 
	return ss.str(); 
} 

void Book::dump(std::ostream& os) const {

	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_; 
	os << "\n" << ISBN_ << "\n" << author_ << endl; 
}