#include "splaytree.h"
#include <iostream> 

using namespace std; 

int main() {
	
	SplayTree<int, int> splay;  

	std::pair <int, int> p1 = std::make_pair( 1, 1 );
	std::pair <int, int> p2 = std::make_pair( 2, 2 );
	std::pair <int, int> p3 = std::make_pair( 3, 3 );
	std::pair <int, int> p4 = std::make_pair( 4, 4 );
	std::pair <int, int> p5 = std::make_pair( 5, 5 );
	std::pair <int, int> p6 = std::make_pair( 6, 6 );

	splay.insert(p1); 
	splay.insert(p2); 
	splay.insert(p3); 
	splay.insert(p4); 
	splay.insert(p5);
	splay.insert(p6);  

	cout << "INSERTED 6, SHOULD HAVE SIZE 6" << endl; 
	cout << "SIZE: " << splay.size() << endl;

	SplayTree<int, int>::iterator it; 
	cout << "FIND KEY 1, SHOULD HAVE VALUE 1" << endl; 
	std::pair<const int, int>* temp = splay.find(p1.first); 
	cout << "VALUE: " << temp->second << endl; 

	splay.erase(1); 

	return 0; 
}