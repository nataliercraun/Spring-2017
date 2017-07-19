#ifndef MSORT_H
#define MSORT_H
#include <vector> 
#include <iostream> 

using namespace std; 

template <class T, class Comparator>
void helpMergeSort(std::vector<T>& output, int start, int end, Comparator comp); 
template <class T, class Comparator>
void merge(std::vector<T>& myvec, int s1, int e1, int s2, int e2, Comparator comp); 


template <class T, class Comparator>
void mergeSort (std::vector<T>& myvec, Comparator comp) { 

	helpMergeSort(myvec, 0, myvec.size()-1, comp); 
}


template <class T, class Comparator>
void helpMergeSort(std::vector<T>& output, int start, int end, Comparator comp) {

	// base case 
	if (start >= end) { 
		return; 
	}	

	// recursive calls  
	int mid = (start + end) / 2;
	helpMergeSort(output, start, mid, comp);  
	helpMergeSort(output, mid+1, end, comp); 
	merge(output, start, mid, mid+1, end, comp);   
}

template <class T, class Comparator>
void merge(std::vector<T>& myvec, int s1, int e1, int s2, int e2, Comparator comp) {
 
	std::vector<T> temp; 
	int low = s1; 
	
	while (s1 <= e1 && s2 <= e2) {

		if ( comp(myvec[s1], myvec[s2]) == true) {
			temp.push_back(myvec[s1]); 
			s1++; 
			 
		}
		else {
			temp.push_back(myvec[s2]); 
			s2++; 
			
		}
	}
 
	while (s1 <= e1) {
		
		temp.push_back(myvec[s1]); 
		s1++;  
	}
	while (s2 <= e2) {
		
		temp.push_back(myvec[s2]); 
		s2++;  
	}
 
	for (int i = 0; i < temp.size(); i++) { 
		myvec[low] = temp[i]; 
		low++; 
	}   
}

#endif 