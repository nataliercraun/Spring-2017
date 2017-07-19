#include "product.h"
#include "clothing.h"
#include "util.h"
#include <iostream> 
#include <sstream> 

using namespace std; 

Clothing::Clothing(std::string size, std::string brand, std::string category, std::string name, double price, int qty) 
	: Product(category, name, price, qty) 
{
	size_ = size; 
	brand_ = brand; 
}

Clothing::~Clothing() 
{

}

std::set<std::string> Clothing::keywords() const 
{
	std::set<std::string> name_keys;
	std::set<std::string> brand_keys;
	std::set<std::string> keys; 
	name_keys = parseStringToWords(name_); 
	brand_keys = parseStringToWords(brand_); 
	keys = setUnion(name_keys, brand_keys); 
	return keys; 
} 

std::string Clothing::displayString() const 
{
	stringstream ss; 
	ss << name_ << endl; 
	ss << "brand: " << brand_ << " ";  
	ss << "size: " << size_ << endl; 
	ss << price_ << " "; 
	ss << qty_ << " left." << endl; 
	return ss.str(); 
} 

void Clothing::dump(std::ostream& os) const 
{

	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_; 
	os << "\n" << size_ << "\n" << brand_ << endl; 
}