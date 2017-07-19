#include "llistdbl.h"
#include <cstdlib>

// take this out later 

#include <iostream>

using namespace std;

LListDbl::LListDbl()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

LListDbl::~LListDbl()
{
  clear();
}

bool LListDbl::empty() const
{
  return size_ == 0;
}

int LListDbl::size() const
{
  return size_;
}

/**
 * Complete the following function
 */
void LListDbl::insert(int loc, const double& val)
{
 
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
void LListDbl::remove(int loc)
{

  Item *temp = head_; 
  Item *temp2 = tail_; 
  if (loc >= 0 && loc < size_) { 

    if (loc == 0) {
      head_ = temp->next; 
    }
    if (loc == size_-1) {
      tail_ = temp2->prev;  
    }
    else {
      Item* del = getNodeAt(loc); 
      del->prev->next = del->next; 
    }  
    size_--;  
  }

  else {
    return; 
  }
}


void LListDbl::set(int loc, const double& val)
{
  Item *temp = getNodeAt(loc);
  temp->val = val;
}

double& LListDbl::get(int loc)
{
  Item *temp = getNodeAt(loc);
  return temp->val;
}

double const & LListDbl::get(int loc) const
{
  Item *temp = getNodeAt(loc);
  return temp->val;
}

void LListDbl::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}


LListDbl::Item* LListDbl::getNodeAt(int loc) const
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


int main() {
  LListDbl list;

  // Check if the list is initially empty.
  if (list.empty()) {
    cout << "SUCCESS: List is empty initially." << endl;
  } else {
    cout << "FAIL: List is not empty initially when it should be." << endl;
  }

  // Insert an item at the head.
  list.insert(0, 3.5);

  // Check if the list is still empty.
  if (!list.empty()) {
    cout << "SUCCESS: List is not empty after one insertion." << endl;
  } else {
    cout << "FAIL: List is empty after one insertion." << endl;
  }

  if (list.size() == 1) {
    cout << "SUCCESS: List has size 1 after one insertion." << endl;
  } else {
    cout << "FAIL: List has size " << list.size() << " after one insertion.";
    cout << endl;
  }

  // Check if the value is correct.
  if (list.get(0) == 3.5) {
    cout << "SUCCESS: 3.5 is at the 0th index of the list." << endl;
  } else {
    cout << "FAIL: 3.5 is not at the 0th index of the list, " << list.get(0);
    cout << " is instead." << endl;
  }

  // Insert item at position 1 (aka at the end of the list)
  list.insert(1, 6);

  if (list.size() == 2) {
    cout << "SUCCESS: List has size 2 after two insertions" << endl; 
  } else {
      cout << "FAIL: List has size " << list.size() << " after two insertions" << endl; 
  }

  if (list.get(1) == 6) {
    cout << "SUCCESS: 6 is at the 1st index of the list." << endl;
  } else {
    cout << "FAIL: 6 is not at the 1st index of the list, " << list.get(0);
    cout << " is instead." << endl;
  } 

  // Insert item in the middle of the list 
  list.insert(1, 7); 

  if (list.size() == 3) {
    cout << "SUCCESS: List has size 3 after three insertions" << endl; 
  } else {
      cout << "FAIL: List has size " << list.size() << " after three insertions" << endl; 
  }

  if (list.get(1) == 7) {
    cout << "SUCCESS: 7 is at the 1st index of the list." << endl;
  } else {
    cout << "FAIL: 7 is not at the 1st index of the list, " << list.get(0);
    cout << " is instead." << endl;
  } 

  // Insert item at the end of the list 
  list.insert(3, 8); 

  if (list.size() == 4) {
    cout << "SUCCESS: List has size 4 after four insertions" << endl; 
  } else {
      cout << "FAIL: List has size " << list.size() << " after four insertions" << endl; 
  }

  if (list.get(3) == 8) {
    cout << "SUCCESS: 8 is at the 3rd index of the list." << endl;
  } else {
    cout << "FAIL: 8 is not at the 3rd index of the list, " << list.get(0);
    cout << " is instead." << endl;
  } 

  // Remove first item in the list
  list.remove(0); 

  if (list.size() == 3) {
    cout << "SUCCESS: List has size 3 after one removal" << endl; 
  } else {
      cout << "FAIL: List has size " << list.size() << " after one removal" << endl; 
  }

  if (list.get(0) == 7) {
    cout << "SUCCESS: 7 is at the 0th index of the list." << endl;
  } else {
    cout << "FAIL: 7 is not at the 0th index of the list, " << list.get(0);
    cout << " is instead." << endl;
  } 

  // Remove middle item

  list.remove(1); 

  if (list.size() == 2) {
    cout << "SUCCESS: List has size 2 after two removals" << endl; 
  } else {
      cout << "FAIL: List has size " << list.size() << " after two removals" << endl; 
  }

  if (list.get(1) == 8) {
    cout << "SUCCESS: 8 is at the 1st index of the list." << endl;
  } else {
    cout << "FAIL: 8 is not at the 1st index of the list, " << list.get(0);
    cout << " is instead." << endl;
  } 

  // Remove last item in the list 
  list.remove(1); 

  if (list.size() == 1) {
    cout << "SUCCESS: List has size 2 after two removals" << endl; 
  } else {
      cout << "FAIL: List has size " << list.size() << " after two removals" << endl; 
  }

  if (list.get(0) == 7) {
    cout << "SUCCESS: 7 is at the 0th index of the list." << endl;
  } else {
    cout << "FAIL: 7 is not at the 0th index of the list, " << list.get(0);
    cout << " is instead." << endl;
  } 


  return 0;
}


