#ifndef CLOTHING_H
#define CLOTHING_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>


class Clothing : public Product { 
public: 

	Clothing(std::string size, std::string brand, std::string category, std::string name, double price, int qty); 
	virtual ~Clothing(); 
	virtual std::set<std::string> keywords() const; 
	virtual std::string displayString() const;  
	virtual void dump(std::ostream& os) const;

private: 
	std::string size_; 
	std::string brand_; 
}; 

#endif 