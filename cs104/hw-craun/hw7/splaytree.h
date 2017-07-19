#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "bst.h"


template <typename K, typename V, typename Comp = std::less<K> >
class SplayTree : public BinarySearchTree<K, V, Comp>
{
    public: 
    // If the K is already present, update the V
    void insert(const std::pair<const K, V>& item); 
    // Return NULL if the K doesn't exist in the map
    std::pair<const K,V>* find(const K& key); 
    // Do nothing if the K does not exist
    void splay(Node<K, V>* node); 
    void erase(const K& key); 
    size_t size() const;
    bool empty() const;

    private: 
    void rotateLeft (Node<K, V> *parent, Node<K, V> *child);
    void rotateRight (Node<K, V> *parent, Node<K, V> *child);
    void nodeSwap( Node<K,V>* n1, Node<K,V>* n2); 


};

template <typename K, typename V, typename Comp>
void SplayTree<K, V, Comp>::insert(const std::pair<const K,V>& item) {

    if (this->mRoot == NULL) { 
        Node<K, V>* new_node = new Node<K, V>(item.first, item.second, NULL);
        this->mRoot = new_node; 
        return; 
    }

    Node<K, V>* parent = NULL; 
    Node<K, V>* next = this->mRoot; 
    Node<K, V>* new_node; 

    while(next != NULL) {
        parent = next; 
        if ( this->c_(item.first, parent->getValue()) ) {
            if (parent->getLeft() == NULL) {
                new_node = new Node<K, V>(item.first, item.second, parent);
                parent->setLeft(new_node); 
                break;
            }
            next = parent->getLeft(); 
        }
        else {
            if (parent->getRight() == NULL) {
                new_node = new Node<K, V>(item.first, item.second, parent);
                parent->setRight(new_node); 
                break;
            }
            next = parent->getRight(); 
        }
    }
    splay(new_node); 
}

template <typename K, typename V, typename Comp>
std::pair<const K,V>* SplayTree<K, V, Comp>::find(const K& key) {

    Node<K, V>* curr = this->mRoot;
    Node<K, V>* saved; 
    while (curr)
    {
        saved = curr; 
        if (curr->getKey() == key)
        {
            std::pair<const K, V> item = std::make_pair(key, curr->getKey());
            std::pair<const K, V>* ptr = &item; 
            return ptr; 
        }
        else if (key < curr->getKey())
        {
            curr = curr->getLeft();
        }
        else
        {
            curr = curr->getRight();
        }
    }

    if (curr == NULL) {
        splay(saved); 
    }

    else {
        splay(curr); 
    }
    return NULL; 
}

template <typename K, typename V, typename Comp>
void SplayTree<K, V, Comp>::erase(const K& key) {

    Node<K, V>* node = BinarySearchTree<K,V>::internalFind(key); 

    // If node is the root, delete and return 
    if (node == this->mRoot) {
        delete node; 
        return; 
    }

    splay(node); 
    
    if (node->getSuccessor() != NULL) {



        Node<K, V>* successor = node->getSuccessor(); 
        Node<K, V>* parent = successor->getParent(); 
        Node<K, V>* succ_right = successor->getRight(); 
        Node<K, V>* succ_left = successor->getLeft();
        node->setValue(successor->getValue()); 
        if (parent->getLeft() == successor) {
            if (succ_right != NULL) {
                parent->setLeft(succ_right); 
                parent->getLeft()->setLeft(succ_left); 
            }
            else {
                parent->setLeft(succ_left); 
            }    
        } 
        else {
            if (succ_left != NULL) {
                parent->setRight(succ_left); 
                parent->getRight()->setRight(succ_right); 
            }
            else {
                parent->setLeft(succ_right); 
            }   
        }
        delete successor; 
    }

    else {
        Node<K, V>* predecessor = node->getPredecessor(); 
        Node<K, V>* parent = predecessor->getParent(); 
        Node<K, V>* pred_right = predecessor->getRight(); 
        Node<K, V>* pred_left = predecessor->getLeft(); 
        node->setValue(predecessor->getValue()); 
        if (parent->getLeft() == predecessor) {
            if (pred_right != NULL) {
                parent->setLeft(pred_right); 
                parent->getLeft()->setLeft(pred_left); 
            }
            else {
                parent->setLeft(pred_left); 
            }    
        } 
        else {
            if (pred_left != NULL) {
                parent->setRight(pred_left); 
                parent->getRight()->setRight(pred_right); 
            }
            else {
                parent->setLeft(pred_right); 
            }   
        }
        delete predecessor; 
    }
}

template <typename K, typename V, typename Comp>
size_t SplayTree<K, V, Comp>::size() const {

    Node<K, V>* left_tree = this->mRoot; 
    Node<K, V>* right_tree = this->mRoot; 

    if (left_tree == NULL) {
        return 0; 
    }

    int count = 1; 

    while (left_tree->getLeft() != NULL) {
        count++; 
        left_tree = left_tree->getLeft(); 
        if (left_tree->getRight() != NULL) {
            Node<K, V>* temp = left_tree->getRight();
            while (temp->getRight() != NULL) {
                count++; 
                temp = left_tree->getRight(); 
            } 
        }
    }

    while (right_tree->getRight() != NULL) {
        count++; 
        right_tree = right_tree->getRight();
        if (right_tree->getLeft() != NULL) {
            Node<K, V>* temp = left_tree->getLeft();  
            while (temp->getLeft() != NULL) {
                count++; 
                temp = right_tree->getLeft(); 
            }
        }
    }

    return count; 
}

template <typename K, typename V, typename Comp>
bool SplayTree<K, V, Comp>::empty() const {
    if (this->mRoot == NULL) {
        return true; 
    }
    else {
        return false; 
    }
}

template <typename K, typename V, typename Comp>
void SplayTree<K, V, Comp>::splay(Node<K, V>* node) {

    if (node == this->mRoot) {
        return; 
    }

    Node<K, V>* parent = node->getParent(); 

    if (parent->getParent() == NULL) {
        if (parent->getLeft() == node) {
            rotateRight(parent, node); 
        }
        else {
            rotateLeft(parent, node); 
        }
        return; 
    }

    else {
        Node<K, V>* gparent = parent->getParent(); 
        if (parent->getRight() == node) {
            if (gparent->getRight() == parent) {
                rotateLeft(gparent, parent); 
                rotateLeft(parent, node); 
                splay(node); 
            }
            else {
                rotateLeft(parent, node); 
                rotateLeft(gparent, parent); 
                splay(node); 
            }
        }
        else {
            if (gparent->getRight() == parent) {
                rotateRight(parent, node); 
                rotateLeft(gparent, parent); 
                splay(node); 
            }
            else {
                rotateRight(gparent, parent); 
                rotateLeft(parent, node); 
                splay(node);
            }
        }
    }
}

/**
* Rotates a parent down and to the left 
*/
template <typename K, typename V, typename Comp>
void SplayTree<K, V, Comp>::rotateLeft (Node<K, V> *parent, Node<K, V> *child)
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
template <typename K, typename V, typename Comp>
void SplayTree<K, V, Comp>::rotateRight (Node<K, V> *parent, Node<K, V> *child)
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
template <typename K, typename V, typename Comp>
void SplayTree<K, V, Comp>::nodeSwap( Node<K,V>* n1, Node<K,V>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<K, V>* n1p = n1->getParent();
    Node<K, V>* n1r = n1->getRight();
    Node<K, V>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<K, V>* n2p = n2->getParent();
    Node<K, V>* n2r = n2->getRight();
    Node<K, V>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<K, V>* temp;
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

#endif