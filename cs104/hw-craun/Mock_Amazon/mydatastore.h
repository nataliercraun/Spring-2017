#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include <map>
#include <queue> 
#include "product.h"
#include "user.h"
#include "review.h"

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
     /** 
     * Adds a review 
     */
    virtual void addReview(Review* r);
     /** 
     * Returns a vector of all users
     */
    std::map<std::string, User*> getUsers(); 
    /** 
     * Returns a vector of all products
     */
    std::vector<Product*> getProducts(); 
    /** 
     * Returns a vector of all of a given user's reviews 
     */
    std::vector<Review*> getUserReviews(std::string username); 
    /** 
     * Returns a vector of products that are in a given user's cart 
     */
    std::vector<Product*> getCart(User* curr); 
    /** 
    * Updates cart based on removal of items 
     */ 
    void updateCart(User* curr, std::vector<Product*>); 
    /**
    * Returns average rating for a given product 
     */ 
    double getAvg(Product* p); 
    /**
    * Returns the reviews for a given product 
     */ 
    std::vector<Review*> getReview(Product* p); 
    /**
    * Returns the basic similarity between two users 
     */ 
    double getSim(User* user1, User* user2); 
    /**
    * Returns a vector of all possible products in sorted order from highest rating to lowest rating 
     */ 
    std::vector<std::pair<std::string, double> > makeSuggestion(std::string currentUser);

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
	* Map to hold all products with a unique keyword
	 */
	std::map<std::string, std::set<Product*> > keys_; 
    /** 
    * Map to hold all reviews for each product 
     */ 
    std::map<Product*, std::vector<Review*> > reviews_; 
    /** 
    * Vector to hold all orphaned reviews
     */ 
    std::vector<Review*> orphans_; 
    /**
    * Map to hold all reviews for each user 
     */
    std::map<std::string, std::vector<Review*> > userviews_; 
    /**
    * Map to store user similarities 
     */
    std::map<User*, std::pair<User*, double> > userSims_; 
	 
}; 

#endif