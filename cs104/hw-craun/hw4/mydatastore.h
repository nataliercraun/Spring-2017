#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include <map>
#include <queue> 
#include "product.h"
#include "user.h"

class MyDataStore : public DataStore {

public: 

	MyDataStore(); 

	virtual ~MyDataStore(); 

    /**
     * Adds a product to the data store
     */
    virtual void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    virtual void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    virtual std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    virtual void dump(std::ostream& ofile);

    /**
     * Allows user to add to cart 
    */
    void AddtoCart(std::string username, Product* p);

    /**
     * Allows user to view cart 
     */
    void ViewCart(std::string username); 

     /**
     * Allows user to buy all available products in cart 
     * Decrement product quantity (if 0, don't let user buy it) --> subtractQty(int num);
     * Decrement user balance --> deductAmount(double amt);
     */
    void BuyCart(std::string username);

private: 

	/**
	* Map that holds users and carts 
	 */ 
	std::map<std::string, std::vector<Product*> > carts_;
	/**
     * Set to hold all unique users:  
     */
	std::map<std::string, User*> users_;

	/**
     * Vector to hold all products: 
     */
	std::vector<Product*> products_; 
	/** 
	* Map to hold all of products with a unique keyword
	 */
	std::map<std::string, std::set<Product*> > keys_; 
	 
}; 

#endif