#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    set<string> the_keys; // set that will hold keywords that will be returned 
    stringstream ss; 
    rawWords = convToLower(rawWords); 
    ss << rawWords; // place string into string stream 
    string temp; 
     
    while (ss >> temp) { // read string from string stream into temp string 
        bool no_punc = true;
        if (temp.size() >= 2) { // check if the strings size is greater than two 
            for (unsigned int i = 0; i < temp.size(); i++) { 
                if ( ispunct(temp[i]) ) { // check if there is punctuation in the string  
                    string sub = temp.substr(0, i); // create a sub-string containing everything before the punctuation 
                    if (sub.size() >= 2) { // if the sub-string is greater than two, add it as a key word 
                        the_keys.insert(sub); 
                    }
                    string sub2 = temp.substr(i+1, temp.size()-(i+1)); // create sub-string containing everyting after the puncutation 
                    if (sub2.size() >= 2) { // if the sub-string is greater than two, add it as a key word 
                        the_keys.insert(sub2); 
                    }
                    no_punc = false;
                    temp.erase(i, 1);
                }         
            }      
            if (no_punc) { // if there is no punctuation in the string, add it as a key word   
                the_keys.insert(temp); 
            }
        }
    }

    return the_keys; 
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes white space from a string 
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}


/******* 
TAKE THIS OUT LATER 
********/
/*int main() {

    return 0; 
}*/