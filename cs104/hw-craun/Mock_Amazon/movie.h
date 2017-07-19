#ifndef MOVIE_H
#define MOVIE_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>


class Movie : public Product { 
public: 

	Movie(std::string genre, std::string rating, std::string category, std::string name, double price, int qty); 
	virtual ~Movie(); 
	virtual std::set<std::string> keywords() const; 
	virtual std::string displayString() const;  
	virtual void dump(std::ostream& os) const;

private: 
	std::string genre_; 
	std::string rating_; 
}; 

#endif 