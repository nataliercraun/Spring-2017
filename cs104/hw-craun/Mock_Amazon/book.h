#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>


class Book : public Product { 
public: 

	Book(std::string ISBN, std::string author, std::string category, std::string name, double price, int qty); 
	virtual ~Book(); 
	virtual std::set<std::string> keywords() const; 
	virtual std::string displayString() const; 
	virtual void dump(std::ostream& os) const;

private: 
	std::string ISBN_; 
	std::string author_; 
}; 

#endif 