#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates  
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
	typename std::set<T>::iterator s1_it; 
	typename std::set<T>::iterator s2_it; 
	typename std::set<T> intersect; 

	for (s1_it = s1.begin(); s1_it != s1.end(); ++s1_it) {
		for (s2_it = s2.begin(); s2_it != s2.end(); ++s2_it) {
			if (*s1_it == *s2_it) {
				intersect.insert(*s1_it); 
			}
		}
	}

	return intersect; 
}

template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
	typename std::set<T>::iterator s1_it; 
	typename std::set<T>::iterator s2_it; 
	typename std::set<T> uni;  

	// Adds all of the items in S1 that aren't in S2 AND the items in common between S1 and S2
	for (s1_it = s1.begin(); s1_it != s1.end(); ++s1_it) {
		bool in_common1 = false; 
		for (s2_it = s2.begin(); s2_it != s2.end(); ++s2_it) {
			if (*s1_it == *s2_it) {
				in_common1 = true; 
				uni.insert(*s1_it);  
			}
		}
		if ( !(in_common1) ) {
			uni.insert(*s1_it); 
		}
	}

	// Adds all of the items in S2 that aren't in S1
	for (s2_it = s2.begin(); s2_it != s2.end(); ++s2_it) {
		bool in_common2 = false; 
		for (s1_it = s1.begin(); s1_it != s1.end(); ++s1_it) {
			if (*s1_it == *s2_it) {
				in_common2 = true;  
			}
		}
		if ( !(in_common2) ) {
			uni.insert(*s2_it); 
			//std::cout << *s2_it << std::endl; 
		}
	}

	return uni; 
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) ;

// trim from end
std::string &rtrim(std::string &s) ;

// trim from both ends
std::string &trim(std::string &s) ;
#endif
