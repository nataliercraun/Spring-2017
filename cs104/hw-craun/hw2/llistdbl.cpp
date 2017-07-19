#include "llistdbl.h"
#include <cstdlib>
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
void LListDbl::remove(int loc)
{

  Item *temp = head_; 
  Item *temp2 = tail_; 
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



