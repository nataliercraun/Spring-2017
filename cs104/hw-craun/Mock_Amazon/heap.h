#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <unordered_map>
template <
         typename T,
         typename TComparator = std::equal_to<T>,
         typename PComparator = std::less<double>,
         typename Hasher = std::hash<T> 
class Heap
{
public:
    /// Constructs an m-ary heap. M should be >= 2
    Heap(int m = 2,
         const PComparator& c = PComparator(),
         const Hasher& hash = Hasher(),
         const TComparator& tcomp = TComparator()  );

    /// Destructor as needed
    ~Heap();

    /// Adds an item with the provided priority
    void push(double pri, const T& item);

    /// returns the element at the top of the heap
    ///  max (if max-heap) or min (if min-heap)
   std::pair<double, T> const & top() const;

    /// Removes the top element
    void pop();

    /// returns true if the heap is empty
    bool empty() const;

    /// decreaseKey reduces the current priority of
    /// item to newpri, moving it up in the heap
    /// as appropriate.
    void decreaseKey(double newpri, const T& item);

    void trickleUp(int index); 

    void trickleDown(int index); 

    std::vector< std::pair<double, T> > getHeap(); 

private:
    /// Add whatever helper functions you need below


    // These should be all the data members you need.
    std::vector< std::pair<double, T> > store_;
    int m_;
    PComparator c_;
    std::unordered_map<T, size_t, Hasher, TComparator> keyToLocation_;

};

// Complete
template <typename T, typename TComparator, typename PComparator, typename Hasher >
Heap<T,TComparator,PComparator,Hasher>::Heap(
    int m,
    const PComparator& c,
    const Hasher& hash,
    const TComparator& tcomp ) :

    store_(),
    m_(m),
    c_(c),
    keyToLocation_(100, hash, tcomp) 

{

}

// Complete
template <typename T, typename TComparator, typename PComparator, typename Hasher >
Heap<T,TComparator,PComparator,Hasher>::~Heap()
{

}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::push(double priority, const T& item)
{
    store_.push_back(std::make_pair(priority, item)); 
    keyToLocation_.insert(std::make_pair(item, store_.size()-1)); 
    trickleUp(store_.size()-1);   
}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::trickleUp(int index) {

    if (index == 0) {
        return; 
    }

    int parent = (index-1) / m_;
    while (parent >= 0 && c_( store_[index].first, store_[parent].first )) {      
        int tempindex = keyToLocation_[store_[index].second]; // gets the locations of the item in the array 
        keyToLocation_[store_[index].second] = keyToLocation_[store_[parent].second]; // switches item location with parent location 
        keyToLocation_[store_[parent].second] = tempindex; // switches parent location to item's location 
        std::swap(store_[parent], store_[index]); 
        index = parent; 
        parent = (index-1) / m_;  
    }
}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::decreaseKey(double priority, const T& item)
{

    store_[keyToLocation_[item]].first = priority; 
    trickleUp(keyToLocation_[item]); 
}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
std::pair<double, T> const & Heap<T,TComparator,PComparator,Hasher>::top() const
{
    // Here we use exceptions to handle the case of trying
    // to access the top element of an empty heap
    if(empty()) {
        throw std::logic_error("can't top an empty heap");
    }
    return store_.front(); 
}

/// Removes the top element
template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::pop()
{
  store_[0] = store_[store_.size()-1]; 
  keyToLocation_.erase(store_[store_.size()-1].second); 
  store_.pop_back(); 
  trickleDown(0);
}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::trickleDown(int index) {

    int smallerChild = m_*index + 1; 
  if (store_.size() > m_*index + 1) {
      for (int i = 0; i < (m_-1); i++) {
        int nextChild = smallerChild + 1; 
        if ( c_(store_[nextChild].first, store_[smallerChild].first) ) {
          smallerChild = nextChild; 
        }
    }

    if ( c_(store_[smallerChild].first, store_[index].first) ) {
      int tempindex = keyToLocation_[store_[index].second]; // gets the locations of the item in the array 
      keyToLocation_[store_[index].second] = keyToLocation_[store_[smallerChild].second]; // switches item location with smaller child location 
      keyToLocation_[store_[smallerChild].second] = tempindex; // switches child's location to item's location 
      std::swap(store_[index], store_[smallerChild]); 
      trickleDown(smallerChild); 
    }   
  } 
} 
  
/// returns true if the heap is empty
template <typename T, typename TComparator, typename PComparator, typename Hasher >
bool Heap<T,TComparator,PComparator,Hasher>::empty() const
{
    return store_.empty();
}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
std::vector< std::pair<double, T> > Heap<T,TComparator,PComparator,Hasher>::getHeap() {
  return store_; 
}


#endif

