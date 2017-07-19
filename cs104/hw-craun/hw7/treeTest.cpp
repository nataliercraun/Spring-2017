#include "avlbst.h"
#include "gtest/gtest.h"

class TreeTest : public testing::Test {
protected:
	// You can remove any or all of the following functions if its body is empty.

	TreeTest() {
		// You can do set-up work for each test here.
	}

	virtual ~TreeTest() {
		// You can do clean-up work that doesn't throw exceptions here.		
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:
	virtual void SetUp() {
		std::pair <int, int> p = std::make_pair( 1, 1 ); 
		avl1.insert(p); 
		std::pair <int, int> p2 = std::make_pair( 2, 2 ); 
		avl1.insert(p2); 
		std::pair <int, int> p3 = std::make_pair( 3, 3 ); 
		avl1.insert(p3); 
	}

	virtual void TearDown() {
		// Code here will be called immediately after each test (right
		// before the destructor).
	}

	// Objects declared here can be used by all tests in the test case.
	AVLTree<int, int> avl1; 
};

// Tests 

TEST_F(TreeTest, testInsert) {
	
}

