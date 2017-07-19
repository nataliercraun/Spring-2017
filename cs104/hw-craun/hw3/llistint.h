#ifndef LLISTINT_H
#define LLISTINT_H
#include <iostream> 

using namespace std; 

class LListInt {
 public:
  struct Item {
    int val;
    Item *prev;
    Item *next;
  };

  /**
   * Default constructor - empty list
   */
  LListInt();

  /**
   * Destructor
   */
  ~LListInt();

  /**
   * Returns the current number of items in the list 
   */
  int size() const;

  /**
   * Returns true if the list is empty, false otherwise
   */
  bool empty() const;

  /**
   * Inserts val so it appears at index, pos
   */
  void insert(int pos, const int& val);

  /**
   * Removes the value at index, pos
   */
  void remove(int pos);

  /**
   * Overwrites the old value at index, pos, with val
   */
  void set(int pos, const int& val);

  /**
   * Returns the value at index, pos
   */
  int& get(int pos);

  /**
   * Returns the value at index, pos
   */
  int const & get(int pos) const;

  /**
   * Deletes all items in the list
   */
  void clear();

  // New functions added 

  LListInt(const LListInt& other);

  LListInt& operator=(const LListInt& other);

  void push_back(const int& val);

  LListInt& operator +=(LListInt& rhs); 

  // use friend function so LHS can be diff type but still access private data 

  friend ostream& operator<<(std::ostream &os, const LListInt &list); 

 private:
  /** 
   * Returns a pointer to the item at index, pos
   *  and NULL otherwise
   */
  Item* getNodeAt(int pos) const;

  /**
   * Data members
   */
  Item* head_;
  Item* tail_;
  int size_;
};

#endif
