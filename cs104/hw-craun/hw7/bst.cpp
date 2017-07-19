#include "bst.h" 
#include <iostream> 

using namespace std; 

int main() {

	// Test insert 

	BinarySearchTree<int, int> bst1;  
	std::pair <int, int> p1 = std::make_pair( 1, 1 ); 
	std::pair <int, int> p7 = std::make_pair( 7, 7 ); 
	std::pair <int, int> p3 = std::make_pair( 3, 3 );
	std::pair <int, int> p2 = std::make_pair( 2, 2 ); 
	std::pair <int, int> p4 = std::make_pair( 4, 4 ); 
	
 
	bst1.insert(p1); 
	bst1.insert(p7); 
	bst1.insert(p3); 
	bst1.insert(p2); 
	bst1.insert(p4); 
	

	BinarySearchTree<int, int>::iterator it; 

	// Test begin(), end(), and ++

	for (it = bst1.begin(); it != bst1.end(); ++it) {
		cout << (*it).first << endl; 
	}



	bst1.print(); 

	return 0; 
}