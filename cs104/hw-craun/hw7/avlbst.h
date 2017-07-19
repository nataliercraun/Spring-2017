#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "bst.h"

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    char getBalance () const;
    void setBalance (char balance);
    void updateBalance(char diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    char balance_;
};

/*
--------------------------------------------
Begin implementations for the AVLNode class.
--------------------------------------------
*/

/**
* Constructor for an AVLNode. Nodes are initialized with a balance of 0.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent)
    : Node<Key, Value>(key, value, parent),
      balance_(0)
{

}

/**
* Destructor.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
char AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(char balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(char diff)
{
    balance_ += diff;
}

/**
* Getter function for the parent. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mParent);
}

/**
* Getter function for the left child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mLeft);
}

/**
* Getter function for the right child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mRight);
}

/*
------------------------------------------
End implementations for the AVLNode class.
------------------------------------------
*/

/**
* A templated balanced binary search tree implemented as an AVL tree.
*/
template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    // Methods for inserting/erasing (removing) elements from the tree. 
    // You must implement both of these methods.
    virtual void insert(const std::pair<Key, Value>& keyValuePair) override;
    virtual void erase(const Key& key);

private:
    /* Helper functions are strongly encouraged to help separate the problem
       into smaller pieces. You should not need additional data members. */

    /* You should write these helpers for sure.  You may add others. */
    void rotateLeft (AVLNode<Key, Value> *parent, AVLNode<Key, Value> *child);
    void rotateRight (AVLNode<Key, Value> *parent, AVLNode<Key, Value> *child);
    void insertFix(AVLNode<Key, Value>* p, AVLNode<Key, Value>* n);
    void removeFix(AVLNode<Key, Value>* p, int diff);

    /* A provided helper function to swap 2 nodes location in the tree */
    void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);
};

/*
--------------------------------------------
Begin implementations for the AVLTree class.
--------------------------------------------
*/

/**
* Insert function for a key value pair. Finds location to insert the node and then balances the tree.
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
    // If empty tree => set as root, b(n) = 0, done! 

    if (this->mRoot == NULL) { 
        AVLNode<Key, Value>* ptr = new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
        this->mRoot = ptr; 
        ptr->setBalance(0); 
        return; 
    }

    AVLNode<Key, Value>* parent = NULL; 
    AVLNode<Key, Value>* next = static_cast<AVLNode<Key, Value>*>(this->mRoot);
    AVLNode<Key, Value>* ptr; 

    while(next != NULL) {
        parent = next; 
        if (keyValuePair.first < parent->getKey()) {
            if (parent->getLeft() == NULL) {
                ptr = new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, parent);
                parent->setLeft(ptr); 
                break;
            }
            next = parent->getLeft(); 
        }
        else {
            if (parent->getRight() == NULL) {
                ptr = new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, parent);
                parent->setRight(ptr); 
                break;
            }
            next = parent->getRight(); 
        }
    }

    // update balance from parent
    if (parent->getBalance() == -1 || parent->getBalance() == 1) {
        parent->setBalance(0);

    } 
    else {
        if (parent->getLeft() == ptr) {
            parent->setBalance(-1);
        } 
        else {
            parent->setBalance(1);
        }
        insertFix(parent, ptr);
    }
}

/**
* Insert-fix function to perform rotations and re-balance tree after the insertion of a new node
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* child) {


    if (parent == NULL || parent->getParent() == NULL) {
        return;
    }

    AVLNode<Key, Value>* grandparent = parent->getParent();

    if (parent == grandparent->getLeft()) { 
        grandparent->updateBalance(-1);

        if (grandparent->getBalance() == 0) {
            return; 
        }

        if (grandparent->getBalance() == -1) {
            insertFix(grandparent, parent);
            return;
        }

        
        if (child == parent->getLeft()) { 
            rotateRight(grandparent, parent);
            parent->setBalance(0);
            grandparent->setBalance(0);

        } else { 
            rotateLeft(parent, child);
            rotateRight(grandparent, child);

            if (child->getBalance() == -1) {
                parent->setBalance(0);
                grandparent->setBalance(1);

            } else if (child->getBalance() == 0) {
                parent->setBalance(0);
                grandparent->setBalance(0);

            } else {
                parent->setBalance(-1);
                grandparent->setBalance(0);
            }
            child->setBalance(0);
        }

    } else { 
        grandparent->updateBalance(1);

        if (grandparent->getBalance() == 0) {
            return; 
        }

        if (grandparent->getBalance() == 1) {
            insertFix(grandparent, parent);
            return;
        }


        if (child == parent->getRight()) { 
            rotateLeft(grandparent, parent);
            parent->setBalance(0);
            grandparent->setBalance(0);

        } else { 
            rotateRight(parent, child);
            rotateLeft(grandparent, child);

            if (child->getBalance() == 1) {
                parent->setBalance(0);
                grandparent->setBalance(-1);

            } else if (child->getBalance() == 0) {
                parent->setBalance(0);
                grandparent->setBalance(0);

            } else {
                parent->setBalance(1);
                grandparent->setBalance(0);
            }
            child->setBalance(0);
        }
    }
}

/**
* Erase function for a given key. Finds the node, reattaches pointers, and then balances when finished.
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::erase(const Key& key)
{

    AVLNode<Key, Value>* node = static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key,Value>::internalFind(key));  

    if (node == NULL) {
        return;  
    }

    if (node->getLeft() != NULL && node->getRight() != NULL) {
        AVLNode<Key, Value>* successor = static_cast<AVLNode<Key, Value>*>(node->getSuccessor()); 
        nodeSwap(node, successor); 
    }

    AVLNode<Key, Value>* child = node->getLeft();
    if (node->getRight() != NULL) {
        child = node->getRight();
    }

    AVLNode<Key, Value>* parent = node->getParent();
    if (child != NULL) {
        child->setParent(parent);
    }

    int diff;
    if (parent == NULL) {
        this->mRoot = child;
    } else {
        if (node == parent->getLeft()) {
            parent->setLeft(child);
            diff = 1;
        } else {
            parent->setRight(child);
            diff = -1;
        }
    }

    delete node;
    removeFix(parent, diff);
}

/**
* Remove-fix function to perform rotations and re-balance tree after the removal of a new node
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value>* node, int diff) {

    if (node == NULL) {
        return;
    }

    AVLNode<Key, Value>* parent = node->getParent();
    int ndiff = -1;
    if (parent != NULL && node == parent->getLeft()) {
        ndiff = 1;
    }

    if (node->getBalance() == -1 && diff == -1) { 
        AVLNode<Key, Value>* child = node->getLeft();
        if (child->getBalance() <= 0) { 
            rotateRight(node, child);

            if (child->getBalance() == -1) {
                node->setBalance(0); 
                child->setBalance(0); 
                removeFix(parent, ndiff);
            } 
            else { 
                node->setBalance(-1);
                child->setBalance(1);
            }

        } 
        else { 
            AVLNode<Key, Value>* grandchild = child->getRight();
            rotateLeft(child, grandchild);
            rotateRight(node, grandchild);

            if (grandchild->getBalance() == 1) {
                node->setBalance(0);
                child->setBalance(-1);

            } 
            else if (grandchild->getBalance() == 0) {
                node->setBalance(0); 
                child->setBalance(0);
            } 
            else {
                node->setBalance(1);
                child->setBalance(0);
            }
            grandchild->setBalance(0);
            removeFix(parent, ndiff);
        }

    } 
    else if (node->getBalance() == 1 && diff == 1) { 
        AVLNode<Key, Value>* child = node->getRight();
        if (child->getBalance() >= 0) { 
            rotateLeft(node, child);

            if (child->getBalance() == 1) {
                node->setBalance(0);
                child->setBalance(0);
                removeFix(parent, ndiff);

            } 
            else { 
                node->setBalance(1);
                child->setBalance(-1);
            }

        } 
        else { 
            AVLNode<Key, Value>* grandchild = child->getLeft();
            rotateRight(child, grandchild);
            rotateLeft(node, grandchild);

            if (grandchild->getBalance() == -1) {
                node->setBalance(0);
                child->setBalance(1);

            } 
            else if (grandchild->getBalance() == 0) {
                node->setBalance(0);
                child->setBalance(0);

            } 
            else {
                node->setBalance(-1);
                child->setBalance(0);
            }
            grandchild->setBalance(0);
            removeFix(parent, ndiff);
        }

    } 
    else {
        if (node->getBalance() == 0) {
            node->updateBalance(diff);
            return;

        } 
        else {
            node->setBalance(0);
        }
        removeFix(parent, ndiff);
    }
}

/**
* Rotates a parent down and to the left 
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::rotateLeft (AVLNode<Key, Value> *parent, AVLNode<Key, Value> *child)
{
    if (parent->getParent() == NULL) {
        this->mRoot = child;
    } 
    else {
        if (parent == parent->getParent()->getLeft()) { // left child
            parent->getParent()->setLeft(child);
        } 
        else { 
            parent->getParent()->setRight(child);
        }
    }

    child->setParent(parent->getParent());
    parent->setParent(child);
    parent->setRight(child->getLeft());
    if (child->getLeft() != NULL) {
        child->getLeft()->setParent(parent);
    }
    child->setLeft(parent);
}

/**
* Rotates a parent down and to the right 
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::rotateRight (AVLNode<Key, Value> *parent, AVLNode<Key, Value> *child)
{
    if (parent->getParent() == NULL) {
        this->mRoot = child;
    } 
    else {
        if (parent == parent->getParent()->getLeft()) { 
            parent->getParent()->setLeft(child);
        } 
        else { 
            parent->getParent()->setRight(child);
        }
    }

    child->setParent(parent->getParent());
    parent->setParent(child);
    parent->setLeft(child->getRight());
    if (child->getRight() != NULL) {
        child->getRight()->setParent(parent);
    }
    child->setRight(parent); 
}

/**
 * Given a correct AVL tree, this functions relinks the tree in such a way that
 * the nodes swap positions in the tree.  Balances are also swapped.
 */
template<typename Key, typename Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    char temp2 = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(temp2);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->mRoot == n1) {
        this->mRoot = n2;
    }
    else if(this->mRoot == n2) {
        this->mRoot = n1;
    }
}

/*
------------------------------------------
End implementations for the AVLTree class.
------------------------------------------
*/

#endif
