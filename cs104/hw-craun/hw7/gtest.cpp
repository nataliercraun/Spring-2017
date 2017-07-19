#include "avlbst.h"

#include "gtest/gtest.h"

#include <ctime>

#include <cstdlib>

#include <algorithm>

#include <iostream>

#include <iomanip>

#include <set>
#include <vector>



// slightly modified, originally taken from http://www.geeksforgeeks.org/how-to-determine-if-a-binary-tree-is-balanced/



/* The function returns true if root is balanced else false

   The second parameter is to store the height of tree.

   Initially, we need to pass a pointer to a location with value

   as 0. We can also write a wrapper over this function */



template<typename Key, typename Value>

bool isBalanced(Node<Key, Value>* root, int* height)

{

  /* lh --> Height of left subtree

     rh --> Height of right subtree */

  int lh = 0, rh = 0;



  /* l will be true if left subtree is balanced

    and r will be true if right subtree is balanced */

  int l = 0, r = 0;



  if(root == NULL)

  {

    *height = 0;

     return 1;

  }



  /* Get the heights of left and right subtrees in lh and rh

    And store the returned values in l and r */

  l = isBalanced(root->getLeft(), &lh);

  r = isBalanced(root->getRight(),&rh);



  /* Height of current node is max of heights of left and

     right subtrees plus 1*/

  *height = (lh > rh? lh: rh) + 1;



  /* If difference between heights of left and right

     subtrees is more than 2 then this node is not balanced

     so return 0 */

  if((lh - rh >= 2) || (rh - lh >= 2))

    return 0;



  /* If this node is balanced and left and right subtrees

    are balanced then return true */

  else return l&&r;

}



// taken from http://www.randygaul.net/2015/06/15/printing-pretty-ascii-trees/

// modified for compatibility

template<typename Key, typename Value>

void printTree( Node<Key, Value>* tp, int spaces = 0)

{

  int i;



  if( tp != NULL )

  {

    printTree( tp->getRight(), spaces + 3 );

    for( i = 0; i < spaces; i++ )

      std::cout <<' ';

    std::cout << tp->getKey() << std::endl;

    printTree( tp->getLeft(), spaces + 3 );

  }

}



TEST(AVLBST_TEST, InsertInOrder100) {

    AVLTree<int, int> tree;

    for(int i = 0; i < 100; i++){

        tree.insert(std::make_pair(i, i));

    }

    int counter = 0;

    for(AVLTree<int, int>::iterator it = tree.begin(); it != tree.end(); ++it){

        EXPECT_EQ(it->first, counter++);

    }

}



TEST(AVLBST_TEST, InsertEraseInOrder100) {

    AVLTree<int, int> tree;

    for(int i = 0; i < 100; i++){

        tree.insert(std::make_pair(i, i));

    }

    int counter = 0;

    for(AVLTree<int, int>::iterator it = tree.begin(); it != tree.end(); ++it){

        EXPECT_EQ(it->first, counter++);

    }

}



TEST(AVLBST_TEST, RandomInsert100) {

    srand(time(NULL));

    AVLTree<int, int> tree;

    for(int i = 0; i < 100; i++){

        tree.insert(std::make_pair(rand() % 10, i));

    }

    int prev = -1;

    for(AVLTree<int, int>::iterator it = tree.begin(); it != tree.end(); ++it){

        EXPECT_LE(prev, it->first);

        prev = it->first;

    }

}

TEST(AVLBST_TEST, BalanceCheck100x10) {

    srand(time(NULL));

    for(int i = 0; i < 100; i++){

        AVLTree<int, int> tree;

        int height = 0;

        std::set<int> dupes;

        for(int i = 0; i < 10; i++){

            int newKey = rand() % 10;

            dupes.insert(newKey);

            tree.insert(std::make_pair(newKey, i));

        }

        bool balanced = isBalanced(tree.mRoot, &height);

        EXPECT_TRUE(balanced);

        if(!balanced){

            std::cout << "Tree with size of " << (dupes.size()) << " is not balanced!" << std::endl;

            printTree(tree.mRoot);

        }

    }

}



TEST(AVLBST_TEST, BalanceCheck100x100) {

    srand(time(NULL));

    for(int i = 0; i < 1000; i++){

        AVLTree<int, int> tree;

        int height = 0;

        std::set<int> dupes;

        for(int i = 0; i < 1000; i++){

            int newKey = rand() % 1000;

            dupes.insert(newKey);

            tree.insert(std::make_pair(newKey, i));

        }

        bool balanced = isBalanced(tree.mRoot, &height);

        EXPECT_TRUE(balanced);

        if(!balanced){

            std::cout << "Tree with size of " << (dupes.size()) << " is not balanced!" << std::endl;

            printTree(tree.mRoot);

        }

    }

}

/*

TEST(AVLBST_TEST, BalanceCheck100x10000) {

    srand(time(NULL));

    for(int i = 0; i < 100; i++){

        AVLTree<int, int> tree;

        int height = 0;

        std::set<int> dupes;

        for(int i = 0; i < 10000; i++){

            int newKey = rand() % 10000;

            dupes.insert(newKey);

            tree.insert(std::make_pair(newKey, i));

        }

        bool balanced = isBalanced(tree.mRoot, &height);

        EXPECT_TRUE(balanced);

        if(!balanced){

            std::cout << "Tree with size of " << (dupes.size()) << " is not balanced!" << std::endl;

            printTree(tree.mRoot);

        }

    }

}



TEST(AVLBST_TEST, BalanceCheckTiny1000) {

    srand(time(NULL));

    for(int i = 0; i < 1000; i++){

        AVLTree<int, int> tree;

        int height = 0;

        std::set<int> dupes;

        int size = rand() % 5 + 1;

        for(int i = 0; i < size; i++){

            int newKey = rand() % 100;

            dupes.insert(newKey);

            tree.insert(std::make_pair(newKey, i));

        }

        bool balanced = isBalanced(tree.mRoot, &height);

        EXPECT_TRUE(balanced);

        if(!balanced){

            std::cout << "Tree with size of " << (dupes.size()) << " is not balanced!" << std::endl;

            printTree(tree.mRoot);

        }

    }

}



TEST(AVLBST_TEST, RandomErase1000) {

    srand(time(NULL));

    for(int i = 0; i < 1000; i++){

        AVLTree<int, int> tree;

        std::set<int> dupes;

        for(int i = 0; i < 1000; i++){

            int newKey = rand() % 1000;

            dupes.insert(newKey);

            tree.insert(std::make_pair(newKey, i));

        }

        for(std::set<int>::iterator it = dupes.begin(); it != dupes.end(); ++it){

            tree.erase(*it);

        }

        EXPECT_TRUE(tree.mRoot == NULL);

    }

}

*/
/*
TEST(AVLBST_TEST, RandomErase1000SizeCheck) {

    srand(time(NULL));

    for(int i = 0; i < 1000; i++){

        AVLTree<int, int> tree;

        std::set<int> dupes;

        for(int i = 0; i < 100; i++){

            int newKey = rand() % 100;

            dupes.insert(newKey);

            tree.insert(std::make_pair(newKey, i));

        }

        std::vector<int> randomOrderedKeys;



        for(std::set<int>::iterator it = dupes.begin(); it != dupes.end(); ++it){

            randomOrderedKeys.push_back(*it);

        }



        int num = rand() % dupes.size();

        for(int i = 0; i < num; i++){

            tree.erase(randomOrderedKeys[i]);

        }

        int size = 0;

        for(AVLTree<int, int>::iterator it = tree.begin(); it != tree.end(); ++it){

            size++;

        }

        EXPECT_EQ(size, dupes.size() - num);

    }

}



TEST(AVLBST_TEST, RandomEraseMost1000SizeCheck) {

    srand(time(NULL));

    for(int i = 0; i < 1000; i++){

        AVLTree<int, int> tree;

        std::set<int> dupes;

        for(int i = 0; i < 100; i++){

            int newKey = rand() % 100;

            dupes.insert(newKey);

            tree.insert(std::make_pair(newKey, i));

        }

        std::vector<int> randomOrderedKeys;



        for(std::set<int>::iterator it = dupes.begin(); it != dupes.end(); ++it){

            randomOrderedKeys.push_back(*it);

        }



        int num = dupes.size() - (rand() % 10);

        for(int i = 0; i < num; i++){

            tree.erase(randomOrderedKeys[i]);

        }

        int size = 0;

        for(AVLTree<int, int>::iterator it = tree.begin(); it != tree.end(); ++it){

            size++;

        }

        EXPECT_EQ(size, dupes.size() - num);

    }

}



TEST(AVLBST_TEST, RandomErase1000BalanceCheck) {

    srand(time(NULL));

    for(int i = 0; i < 1000; i++){

        AVLTree<int, int> tree;

        std::set<int> dupes;

        for(int i = 0; i < 100; i++){

            int newKey = rand() % 100;

            dupes.insert(newKey);

            tree.insert(std::make_pair(newKey, i));

        }

        std::vector<int> randomOrderedKeys;



        for(std::set<int>::iterator it = dupes.begin(); it != dupes.end(); ++it){

            randomOrderedKeys.push_back(*it);

        }



        int num = rand() % dupes.size();

        for(int i = 0; i < num; i++){

            tree.erase(randomOrderedKeys[i]);

        }

        int height;

        bool balanced = isBalanced(tree.mRoot, &height);

        EXPECT_TRUE(balanced);

        if(!balanced){

            std::cout << "Tree with size of " << (dupes.size()) << " is not balanced!" << std::endl;

            printTree(tree.mRoot);

        }

    }

}



TEST(AVLBST_TEST, RandomEraseMost1000BalanceCheck) {

    srand(time(NULL));

    for(int i = 0; i < 1000; i++){

        AVLTree<int, int> tree;

        std::set<int> dupes;

        for(int i = 0; i < 100; i++){

            int newKey = rand() % 100;

            dupes.insert(newKey);

            tree.insert(std::make_pair(newKey, i));

        }

        std::vector<int> randomOrderedKeys;



        for(std::set<int>::iterator it = dupes.begin(); it != dupes.end(); ++it){

            randomOrderedKeys.push_back(*it);

        }



        int num = dupes.size() - (rand() % 10);

        for(int i = 0; i < num; i++){

            tree.erase(randomOrderedKeys[i]);

        }

        int height;

        bool balanced = isBalanced(tree.mRoot, &height);

        EXPECT_TRUE(balanced);

        if(!balanced){

            std::cout << "Tree with size of " << (dupes.size()) << " is not balanced!" << std::endl;

            printTree(tree.mRoot);

        }

    }

}

*/