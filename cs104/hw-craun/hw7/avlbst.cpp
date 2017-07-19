#include "avlbst.h"
#include <iostream> 

using namespace std; 

int main() {
	
	AVLTree<int, int> avl1;  

	std::pair <int, int> p1 = std::make_pair( 1, 1 );
	std::pair <int, int> p2 = std::make_pair( 2, 2 );
	std::pair <int, int> p3 = std::make_pair( 3, 3 );
	std::pair <int, int> p4 = std::make_pair( 4, 4 );
	std::pair <int, int> p5 = std::make_pair( 5, 5 );
	std::pair <int, int> p6 = std::make_pair( 6, 6 );
	std::pair <int, int> p7 = std::make_pair( 2, 4 );


	avl1.insert(p2); 
	avl1.insert(p1); 
	avl1.insert(p3);
	avl1.erase(2); 
	avl1.insert(p5);
	avl1.erase(3);
	avl1.insert(p7); 
	avl1.erase(5);
	avl1.erase(2);
	avl1.insert(p7); 
	avl1.insert(p5);  
	avl1.insert(p6); 
	avl1.erase(6);

	
	AVLTree<int, int>::iterator it; 

	// Test begin(), end(), and ++

	avl1.print(); 

	for (it = avl1.begin(); it != avl1.end(); ++it) {
		cout << (*it).first << endl; 
	}

	

	return 0; 
}