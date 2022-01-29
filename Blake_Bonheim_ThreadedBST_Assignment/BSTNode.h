// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.

/*
This was modified by Blake Bonheim for CSIS 215
My lab partner was Jarred Patterson
*/


// This is the file to include for access to the complete binary node
// template implementation

#include "book.h"
#include "BinNode.h"

#ifndef BSTNODE_H
#define BSTNODE_H

// Simple binary tree node implementation
template <typename Key, typename E>
class BSTNode : public BinNode<E> {
private:
    Key k;                  // The node's key
    E it;                   // The node's value
    BSTNode* lc;            // Pointer to left child
    BSTNode* rc;            // Pointer to right child

    //THESE SHOULD ALWAYS START TRUE BECAUSE ANY NEW NODE WILL HAVE TWO THREADS (except for nodes on the farthest left or right)
    bool lcThread = false;          //Whether the left pointer is a regular pointer or a thread
    bool rcThread = false;          //Whether the right pointer is a regular pointer or a thread

public:
    // Two constructors -- with and without initial values
    BSTNode() { lc = rc = NULL; }
    BSTNode(Key K, E e, BSTNode* l = NULL, BSTNode* r = NULL)
    {
        k = K; it = e; lc = l; rc = r;
    }
    ~BSTNode() {}             // Destructor

    // Functions to set and return the value and key
    E& element() { return it; }
    void setElement(const E& e) { it = e; }
    Key& key() { return k; }
    void setKey(const Key& K) { k = K; }

    // Functions to set and return the children
    inline BSTNode* left() const { return lc; }
    void setLeft(BinNode<E>* b)
    {
        lc = (BSTNode*)b;
    }
    inline BSTNode* right() const { return rc; }
    void setRight(BinNode<E>* b)
    {
        rc = (BSTNode*)b;
    }

    // gets/sets for threads
    bool isLeftThread() { return lcThread; }
    bool isRightThread() { return rcThread; }
    void setLeftToThread(bool b) { lcThread = b; }
    void setRightToThread(bool b) { rcThread = b; }

    // Return true if it is a leaf, false otherwise
    bool isLeaf()
    {
        if (lc == NULL && rc == NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

#endif