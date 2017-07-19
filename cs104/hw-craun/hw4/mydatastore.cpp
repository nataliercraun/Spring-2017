#include "datastore.h"
#include "mydatastore.h"
#include "product.h"
#include "user.h"
#include "util.h"
#include <string>
#include <set>
#include <vector>
#include <map> 
#include <sstream> 
#include <iostream> 


using namespace std; 

MyDataStore::MyDataStore() 
{

}

MyDataStore::~MyDataStore() 
{
	std::map<std::string, User*>::iterator user_it; 
	for (user_it = users_.begin(); user_it != users_.end(); ++user_it) {
		delete user_it->second; 
	}

	std::vector<Product*>::iterator prod_it;  
	for (prod_it = products_.begin(); prod_it != products_.end(); ++prod_it) {
		delete *prod_it; 
	}

}

/**
 * Adds a product to the data store
 */
void MyDataStore::addProduct(Product* p) {

	products_.push_back(p); 

	std::set<std::string> keywords = p->keywords(); 
	std::set<std::string>::iterator key_it;  
	std::map<std::string, std::set<Product*> >::iterator map_it;  

	for (key_it = keywords.begin(); key_it != keywords.end(); ++key_it) {   
		if (keys_.find(*key_it) == keys_.end()) {						  
			std::set<Product*> new_set;									 
			new_set.insert(p);  								  			   
			keys_.insert( make_pair(*key_it, new_set) );				   
		}
		else {
			for (map_it = keys_.begin(); map_it != keys_.end(); ++map_it) {  
				if (*key_it == map_it->first) {								
					map_it->second.insert(p); 								
				}
			}
		}
	}

}
	

/**
 * Adds a user to the data store
 */
void MyDataStore::addUser(User* u) {

	std::vector<Product*> empty_cart;  
	users_.insert( make_pair(u->getName(), u) ); 
	carts_.insert( make_pair(u->getName(), empty_cart) );
}

/**
 * Performs a search of products whose keywords match the given "terms"
 *  type 0 = AND search (intersection of results for each term) while
 *  type 1 = OR search (union of results for each term)
 */
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {

	std::set<Product*> hits; 
	std::map<std::string, std::set<Product*> >::iterator map_it; 
 
	if (type == 1) {
		for (unsigned int i = 0; i < terms.size(); i++) {
			for (map_it = keys_.begin(); map_it != keys_.end(); ++map_it) {
				std::set<Product*> set2;
				if (map_it->first == terms[i]) {
					set2 = map_it->second;  
				}
				hits = setUnion(hits, set2); 
			}
		}
	}

	if (type == 0) {
		for (unsigned int i = 0; i < terms.size(); i++) {
			for (map_it = keys_.begin(); map_it != keys_.end(); ++map_it) {
				std::set<Product*> set2;
				if (map_it->first == terms[i]) {
					set2 = map_it->second; 
					if (i == 0) {
						hits = setIntersection(set2, set2); 
					}
				
					else { 
						hits = setIntersection(hits, set2); 
					} 
				}
			}
		}
	}

	std::set<Product*>::iterator hit_it;
	std::vector<Product*> hits_vec;  
	for (hit_it = hits.begin(); hit_it != hits.end(); ++hit_it) {
		hits_vec.push_back(*hit_it); 
	}

	return hits_vec; 
}

/**
 * Reproduce the database file from the current Products and User values
 */
void MyDataStore::dump(std::ostream& ofile) {

	ofile << "<products>" << endl; 

	for (unsigned int i = 0; i < products_.size(); i++) {
		products_[i]->dump(ofile); 
	}

	ofile << "</products>" << endl; 
	ofile << "<users>" << endl; 

	std::map<std::string, User*>::iterator it; 

	for (it = users_.begin(); it != users_.end(); ++it) {
		it->second->dump(ofile); 
	}

	ofile << "</users>" << endl; 
}

/**
 * Allows user to add to cart 
*/
void MyDataStore::AddtoCart(std::string username, Product* p) {

	std::map<std::string, std::vector<Product*> >::iterator it; 
	it = carts_.find(username); 
	if (it == carts_.end()) {
		cout << "Invalid request" << endl; 
		return; 
	}
	it->second.push_back(p); 
}

/**
* Allows user to view cart 
*/
void MyDataStore::ViewCart(std::string username) {

	std::map<std::string, std::vector<Product*> >::iterator it; 
	it = carts_.find(username); 
	if (it == carts_.end()) {
		cout << "Invalid username" << endl; 
		return; 
	}

	else {
		std::vector<Product*>::iterator vec; 
		int count = 1; 
		for (vec = it->second.begin(); vec != it->second.end(); ++vec) {
			cout << "Item " << count << endl;   
			cout << (*vec)->displayString() << endl;  
			count++;  
		} 		
	}
}

/**
* Allows user to buy all available products in cart 
*/
void MyDataStore::BuyCart(std::string username) {

	std::map<std::string, User*>::iterator user; 
	user = users_.find(username); 
	std::map<std::string, std::vector<Product*> >::iterator it; 
	it = carts_.find(username);   
	if (it == carts_.end()) {
		cout << "Invalid username" << endl; 
		return; 
	}

	vector<Product*>::iterator pro = it->second.begin(); 

	while (pro != it->second.end()) {
		if ((*pro)->getQty() > 0 && user->second->getBalance() >= (*pro)->getPrice()) {
			user->second->deductAmount((*pro)->getPrice());
			(*pro)->subtractQty(1);  
			pro = it->second.erase(pro); 
			// iterator now positioned at the item after the deleted item  
		}
		else {
			pro++; 
		}
	}


}