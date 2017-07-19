#include "llistint.h"
#include <cstdlib>
#include <iostream>
using namespace std;

LListInt::LListInt()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

LListInt::~LListInt()
{
  clear();
}

bool LListInt::empty() const
{
  return size_ == 0;
}

int LListInt::size() const
{
  return size_;
}

/**
 * Complete the following function
 */
void LListInt::insert(int loc, const int& val)
{

  if (loc < 0 || loc > size_) {
    return; 
  }
 
  Item* newptr = new Item;  
  newptr->val = val;
  newptr->next = NULL;
  newptr->prev = NULL;   
  
  if (head_ == NULL) { 
    head_ = newptr;
    tail_ = newptr; 
    size_++; 
  }

  else {

    Item *temp = head_; 
    if (loc >= 0 && loc <= size_) {

      if (loc == 0) {
        newptr->next = head_; 
        head_ = newptr; 
        head_->next->prev = newptr; 
      }   

      else {

        if (size_ == loc) {
          while (temp != NULL && loc > 1) {
          temp = temp->next; 
          loc--; 
          }

          temp->next = newptr; 
          newptr->prev = temp;
          tail_ = newptr;  
        }

        else {
          while (temp != NULL && loc > 0) {
          temp = temp->next; 
          loc--; 
          }

          newptr->prev = temp->prev; 
          newptr->next = temp; 
          temp->prev->next = newptr; 
          temp->prev = newptr;
        } 
      } 
      size_++;     
    }

    else {
      return; 
    }  
  }  
}

/**
 * Complete the following function
 */
void LListInt::remove(int loc)
{

  Item *temp = head_; 
  Item *temp2 = tail_; 

  // edge case added for size = 1 

  if (size_ == 1 && loc == 0) {
    temp = NULL; 
    temp2 = NULL; 
    size_ = 0; 
  }

  else {

    if (loc >= 0 && loc < size_) { 
      if (loc == 0) {
        head_ = temp->next; 
        head_->prev = NULL;
        delete temp;
      }
      else if (loc == size_-1) {
        tail_ = temp2->prev; 
        tail_->next = NULL;  
        delete temp2; 
      }
      else {
        Item* del = getNodeAt(loc); 
        del->prev->next = del->next; 
        del->next->prev = del->prev; 
        delete del; 
      }  
      size_--;   
    }

    else {
      return; 
    }
  }
}


void LListInt::set(int loc, const int& val)
{
  Item *temp = getNodeAt(loc);
  temp->val = val;
}

int& LListInt::get(int loc)
{
  Item *temp = getNodeAt(loc);
  return temp->val;
}

int const & LListInt::get(int loc) const
{
  Item *temp = getNodeAt(loc);
  return temp->val;
}

void LListInt::clear()
{
   //return;  
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}


LListInt::Item* LListInt::getNodeAt(int loc) const
{
  Item *temp = head_;
  if(loc >= 0 && loc < size_){
    while(temp != NULL && loc > 0){
      temp = temp->next;
      loc--;
    }
    return temp;
  }
  else {
    //throw std::invalid_argument("bad location");
    return NULL;
  }
}

/**
   * Copy constructor [must run in O(n) where n=size of other]
   *   Be careful you don't give us an O(n^2) implementation
   */

  LListInt::LListInt(const LListInt& other) {

    head_= NULL; 
    tail_ = NULL; 
    size_ = 0; 

    Item* temp = other.head_; 
    while (temp != NULL) {
      push_back(temp->val); 
      temp = temp->next; 
     }

    size_ = other.size_; 
   }

  /**
   * Assignment Operator (must run in O(n + m) where
   *   n is the size of this list & m is the size of other
   *   Be careful you don't give us an O(n^2) or O(m^2) implementation
   */

  LListInt& LListInt::operator=(const LListInt& other) {

   if (head_ != NULL) clear(); 

   if (this == &other) return *this; 

   Item* temp = other.head_; 
   while (temp != NULL) {
      push_back(temp->val); 
      temp = temp->next; 
   } 
   size_ = other.size_; 
   return *this; 
  }

  /**
   * Adds an item to the back of the list in O(1) time
   */

  void LListInt::push_back(const int& val) {
    Item* newptr = new Item; 
    newptr->val = val; 
    newptr->next = NULL; 
    newptr->prev = NULL; 
 
    if (empty()) { 
      head_= newptr;  
      tail_ = newptr;  
    }
  
   else {
      newptr->prev = tail_; 
      tail_->next = newptr; 
      tail_ = newptr;  
    }  

    size_++;  
  }

  LListInt& LListInt::operator +=(LListInt& rhs) {         

    // rhs.head_, tail_, size_ are for mylist2 
    // head_, tail_, and size_ are for mylist1 

    if (rhs.head_ == NULL || this == &rhs) {
      return *this; 
    } 

    Item* temp = rhs.head_; 

    if (head_ == NULL) {
      head_ = temp; 
      tail_ = rhs.tail_; 
    }

    else {
      temp->prev = tail_; // sets mylist2's previous to mylist1's tail 
      tail_->next = temp; // sets mylist1's tail_->next to mylist2's head
      tail_ = rhs.tail_; // sets mylist1's new tail to mylist2's tail 
      size_ = size_ + rhs.size_; 
    }

    rhs.size_ = 0; // sets mylist2's head = to NULL, leaving it empty 
    rhs.head_ = NULL; 
    rhs.tail_ = NULL; 
   
    return *this; 
  }

  /**
   * operator+=
   *
   * Write an appropriate operator overload function to support the following:
   *    LListInt mylist1, mylist2;  mylist1 += mylist2;
   * This operation should remove all elements from mylist2 in FIFO order and 
   * add them the back of mylist1 without allocating or freeing memory 
   *  (i.e. take the elements from mylist2 and just link them in to mylist 1)
   *
   * This function must run in O(1) and mylist2 should be empty upon completion.
   *
   * Note:  mylist1 += mylist2 += mylist3 should also work and produce the
   *        in mylist1 the concatenation of all 3 lists, leaving mylist2 and 
   *        mylist3 empty.  
   */
   // You determine the signature

   ostream& operator<<(ostream &os, const LListInt &list) {

    int count = 0; 
    LListInt::Item* temp = list.head_; 

    while (temp != NULL) {

      if (count == 10) {
        os << endl; 
        count = 0; 
      }

      else { 
        os << temp->val << " "; 
        temp = temp->next; 
        count++; 
      }
    }

    os << "...that's all the numbers!"; 

    return os; 
  }

  /**
   * Ostream operator << should Output the contents of the list 10 per line
   *  (separated by spaces) to the given ostream object
   *
   *  cout << mylist << "...that's all the numbers!" << endl;
   *
   * Must run in O(n) and NOT O(n^2)
   */
   // You determine the signature



