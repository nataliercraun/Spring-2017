#include "llistint.h"
#include "gtest/gtest.h"
#include <sstream> 
#include <string> 

class LListTest : public testing::Test {
protected:
	// You can remove any or all of the following functions if its body is empty.

	LListTest() {
		// You can do set-up work for each test here.
	}

	virtual ~LListTest() {
		// You can do clean-up work that doesn't throw exceptions here.		
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:
	virtual void SetUp() {
		list.insert(0, 1); 
		list.insert(1, 2); 
		list.insert(2, 3); 
	}

	virtual void TearDown() {
		// Code here will be called immediately after each test (right
		// before the destructor).
	}

	// Objects declared here can be used by all tests in the test case.
	LListInt list;
	LListInt list2; 
	LListInt list3; 
};

TEST_F(LListTest, GetNominal) {
	// Exepct 0th element to be 1, 1st elemnt to be 2, etc.
	for (int i = 0 ; i < 3; i++) {
		EXPECT_EQ(i + 1, list.get(i));
	}
}

// Tests push_back function 

TEST_F(LListTest, AddNominal) {
	// Expect 3rd element to be 4
	list.push_back(4); 
	EXPECT_EQ(4, list.get(3)); 
	EXPECT_EQ(4, list.size()); 

	// Expect list2 0th element to be 1
	list2.push_back(5); 
	EXPECT_EQ(5, list2.get(0)); 
	list2.push_back(6); 
	EXPECT_EQ(6, list2.get(1));
}

// Tests += operator overload function with two populated lists 

TEST_F(LListTest, AddLists) {

	list2.push_back(4); 
	list += list2; 

	EXPECT_EQ(4, list.get(3)); 
	EXPECT_EQ(4, list.size());
}

// Tests += with one empty list 

TEST_F(LListTest, AddEmptyList) {

	list += list2; 

	EXPECT_EQ(3, list.get(2)); 
	EXPECT_EQ(3, list.size());
}

// Tests += with both empty lists 

TEST_F(LListTest, AddTwoEmptyLists) {

	list2 += list3; 

	EXPECT_EQ(0, list2.size());
}

// Tests assignment operator function 

TEST_F(LListTest, AssignList) {

	list2 = list; 

	EXPECT_EQ(1, list2.get(0)); 
	EXPECT_EQ(3, list2.size()); 
}

// Tests ostream operator function 

TEST_F(LListTest, OutputList) {

	stringstream ss;
	ss << list; 
	string test = ss.str(); 

	EXPECT_EQ("1 2 3 ...that's all the numbers!", test); 

	list.push_back(4); 
	list.push_back(5); 
	list.push_back(6);
	list.push_back(7);
	list.push_back(8);
	list.push_back(9);
	list.push_back(10);
	list.push_back(11); 

	stringstream tt; 
	tt << list; 
	string test2 = tt.str(); 

	EXPECT_EQ("1 2 3 4 5 6 7 8 9 10 \n11 ...that's all the numbers!", test2); 
}

// Test copy constructor 

TEST_F(LListTest, CopyList) {

	LListInt list3(list); 

	EXPECT_EQ(1, list3.get(0)); 
	EXPECT_EQ(3, list3.size()); 
}








