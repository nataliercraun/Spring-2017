#include "datastore.h"
#include "mydatastore.h"
#include "product.h"
#include "user.h"
#include "util.h"
#include "review.h"
#include "heap.h"
#include "msort.h"
#include <string>
#include <set>
#include <vector>
#include <map> 
#include <cmath> 
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

	std::map<Product*, std::vector<Review*> >::iterator it; 
	for (it = reviews_.begin(); it != reviews_.end(); ++it) {
		std::vector<Review*> temp = it->second; 
		for (unsigned int i = 0; i < temp.size(); i++) {
			delete temp[i]; 
		}
	}

	for (unsigned int i = 0; i < orphans_.size(); i++) {
		delete orphans_[i];
	}

}

/**
 * Adds a product to the data store
 */
void MyDataStore::addProduct(Product* p) {

	products_.push_back(p); 

	// Adds product to review map 
	vector<Review*> new_vec; 
	reviews_.insert( make_pair(p, new_vec) ); 
 
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
	std::vector<Review*> views;   
	users_.insert( make_pair(u->getName(), u) ); 
	carts_.insert( make_pair(u->getName(), empty_cart) );
	userviews_.insert( make_pair(u->getName(), views) ); 
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

	ofile << "<reviews>" << endl; 

	std::map<Product*, std::vector<Review*> >::iterator rev; 
	for (rev = reviews_.begin(); rev != reviews_.end(); ++rev) { 
		std::vector<Review*> temp = rev->second; 
		for (unsigned int i = 0; i < temp.size(); i++) {
			ofile << rev->first->getName() << endl;
			ofile << temp[i]->rating << " " << temp[i]->username << " "; 
			ofile << temp[i]->date << " "; 
			ofile << temp[i]->reviewText << endl; 
		}
	}

	for (unsigned int i = 0; i < orphans_.size(); i++) {
		ofile << orphans_[i]->reviewText << endl; 
	}

	ofile << "</reviews>" << endl; 
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

void MyDataStore::addReview(Review* r) {
 
	std::string name = r->prodName; 
	std::map<Product*, std::vector<Review*> >::iterator map_it; 
	std::map<std::string, std::vector<Review*> >:: iterator user_it; 
	bool orphan = true; 

	for (unsigned int i = 0; i < products_.size(); i++) { 	
		if (products_[i]->getName() == name) { 		
			map_it = reviews_.find(products_[i]); 	
			map_it->second.push_back(r); 
			string user = r->username; 
			user_it = userviews_.find(user); 
			user_it->second.push_back(r); 	
			orphan = false; 									  			  		
		}
	}

	if (orphan) {
		orphans_.push_back(r); 
	}
}

std::map<std::string, User*> MyDataStore::getUsers() {
	return users_; 
}

std::vector<Product*> MyDataStore::getProducts() {
	return products_; 
}

std::vector<Product*> MyDataStore::getCart(User* curr) {
	std::map<std::string, vector<Product*> >::iterator it; 
	it = carts_.find(curr->getName()); 
	return it->second; 
} 

void MyDataStore::updateCart(User* curr, std::vector<Product*> update) {
	std::map<std::string, std::vector<Product*> >::iterator it; 
	it = carts_.find(curr->getName());
	it->second = update;  
}

double MyDataStore::getAvg(Product* p) {

	std::map<Product*, std::vector<Review*> >::iterator it;
	it = reviews_.find(p); 
	double total = 0; 
	double avg = 0; 
	vector<Review*> revs = it->second; 

	if (revs.size() == 0) {
		return 0.0; 
	}

	for (unsigned int i = 0; i < revs.size(); i++) {
		total += revs[i]->rating; 
	}
	avg = total / revs.size(); 
	return avg; 
}

vector<Review*> MyDataStore::getReview(Product* p) {

	std::map<Product*, std::vector<Review*> >::iterator it;
	it = reviews_.find(p);
	return it->second; 
}

std::vector<Review*> MyDataStore::getUserReviews(std::string user) {

	std::map<std::string, std::vector<Review*> >::iterator it; 
	it = userviews_.find(user); 
	return it->second; 
}

double MyDataStore::getSim(User* user1, User* user2) {

	std::map<std::string, std::vector<Review*> >::iterator it1; 
	std::map<std::string, std::vector<Review*> >::iterator it2; 
	it1 = userviews_.find(user1->getName());
	it2 = userviews_.find(user2->getName());

	std::vector<Review*> vec1 = it1->second; 
	std::vector<Review*> vec2 = it2->second; 

	std::set<string> set1; 
	std::set<string> set2; 
 
	for (unsigned int i = 0; i < vec1.size(); i++) {
		set1.insert(vec1[i]->prodName); 
	}

	for (unsigned int i = 0; i < vec2.size(); i++) {
		set2.insert(vec2[i]->prodName); 
	}

	std::set<string> common; 

	common = setIntersection(set1, set2); 

	if (common.empty()) {
		return 1.0; 
	}

	double temp = 0.0;
	double total = 0.0; 
	int count = 0; 

	for (unsigned int i = 0; i < vec1.size(); i++) {
		for (unsigned int j = 0; j < vec2.size(); j++) {

			if (vec1[i]->prodName == vec2[j]->prodName) {
				temp += abs( (double)vec1[i]->rating - (double)vec2[j]->rating ) / 4; 
				count++; 
			}
		}
	}

	total = temp / (double)count; 
	return total; 
}

struct RateComp {
	bool operator()(std::pair<std::string, double> lhs, std::pair<std::string, double> rhs) {
		return lhs.second > rhs.second; 
	}

}; 

std::vector<std::pair<std::string, double> > MyDataStore::makeSuggestion(std::string currentUser) {


	std::map< string, std::map<string, double> > lookup; 
	std::map<string, User*>::iterator it; 
	vector<User*> vecUsers; 

	for (it = users_.begin(); it != users_.end(); ++it) {
		vecUsers.push_back(it->second); 
	}

	// Calculates the 'basic' similarity between all pairs of users 
	for (unsigned int i = 0; i < vecUsers.size(); i++) {

		std::map<string, double> temp; 

		for (unsigned int j = 0; j < vecUsers.size(); j++) {

			if (vecUsers[i]->getName() != vecUsers[j]->getName()) {
				
				temp.insert( make_pair(vecUsers[j]->getName(), getSim(vecUsers[i], vecUsers[j])) ); 
			}	
		}
		lookup.insert( make_pair(vecUsers[i]->getName(), temp) ); 
	}

	

	Heap<string> myHeap(2);
	std::map<string, std::map<string, double> >::iterator mapit; 
	std::map<string, double>::iterator connect; 
	mapit = lookup.find(currentUser); 

	for (connect = mapit->second.begin(); connect != mapit->second.end(); ++connect) {

		myHeap.push(connect->second, connect->first); 
	}

	
	
	vector<std::pair<double, string> > test = myHeap.getHeap(); 

	std::map<string, double> refined;  
	double priority = 0.0;  

	while (myHeap.empty() == false) {

		std::pair<double, string> parent = myHeap.top();
		myHeap.pop(); 
		priority = parent.first;  
		refined.insert( make_pair(parent.second, parent.first) );

		// Find parent in lookup map 
		std::map<string, std::map<string, double> >::iterator find_parent; 
		find_parent = lookup.find(parent.second); 

		// Get map of parent's neighbors 
		std::map<string, double> neighbors = find_parent->second; 
		std::map<string, double>::iterator neighb_it; 

		// Find current user in lookup map 
		std::map<string, std::map<string, double> >::iterator currentPriority; 
		currentPriority = lookup.find(currentUser);

		// Get map of current user's neighbors 
		std::map<string, double> currmap = currentPriority->second; 
		std::map<string, double>::iterator cur; 

		for (neighb_it = neighbors.begin(); neighb_it != neighbors.end(); ++neighb_it) {

			// Find parent's neighbor in current user's map of neighbors
			cur = currmap.find(neighb_it->first); 

			if ( (priority + neighb_it->second) < cur->second) {

				myHeap.decreaseKey( (priority + neighb_it->second) , neighb_it->first); 
				cur->second = priority + neighb_it->second; 
				currentPriority->second = currmap; 
			}
		}
	}

	std::map<string, double>::iterator ref_it; 

	vector<Review*> myReviews = getUserReviews(currentUser); 
	vector<Product*> NotReviewed; 

	for (unsigned int i = 0; i < products_.size(); i++) {
		bool alreadyReviewed = false; 
		for (unsigned int j = 0; j < myReviews.size(); j++) {
			if (products_[i]->getName() == myReviews[j]->prodName) {
				alreadyReviewed = true; 
			}
		}
		if (alreadyReviewed == false) {
			vector<Review*> check = getReview(products_[i]); 
			if (check.size() > 0) {
				NotReviewed.push_back(products_[i]); 
			}
		}
	}
 
 	double rating = 0.0; 
 	std::vector<std::pair<std::string, double> > ratings; 

	for (unsigned int i = 0; i < NotReviewed.size(); i++) {

		double rp = 0.0; 
		double w = 0.0;
		double SBA = 0.0;
		double RBP = 0.0;

		vector<Review*> tempviews = getReview(NotReviewed[i]); 

		for (unsigned int j = 0; j < tempviews.size(); j++) {

			string revuser = tempviews[j]->username; 
			ref_it = refined.find(revuser);
			if (ref_it != refined.end()) {
				SBA = ref_it->second; 
			}

			RBP = (double)tempviews[j]->rating; 

			rp += (1.0-SBA) * RBP; 
			w += (1.0-SBA); 
		}

		if (w == 0) {
			rating = 0.0; 
		}

		else {
			rating = (rp / w); 
		}

		ratings.push_back( make_pair(NotReviewed[i]->getName(), rating) ); 
	}

	RateComp comp1;  
	mergeSort(ratings, comp1); 

	// Sort from highest rating (at index 0) to lowest rating (at the back) using 
	// MergeSort implemenation that will sort using a comparator that will sort pairs
	// based on thair rating 

	return ratings; 
}