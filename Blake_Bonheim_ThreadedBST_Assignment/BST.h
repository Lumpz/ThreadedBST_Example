// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.

/*
This was modified by Blake Bonheim for CSIS 215
My lab partner was Jarred Patterson
*/


// This file includes all of the pieces of the BST implementation

// Include the node implementation
#include "BSTNode.h"

// Include the dictionary ADT
#include "dictionary.h"

#ifndef BST_H
#define BST_H

using namespace std;

// Binary Search Tree implementation for the Dictionary ADT
template <typename Key, typename E>
class BST : public Dictionary<Key, E> {
private:
    BSTNode<Key, E>* root;   // Root of the BST
    int nodecount;         // Number of nodes in the BST

    // Private "helper" functions
    void clearhelp(BSTNode<Key, E>*);
    BSTNode<Key, E>* inserthelp(BSTNode<Key, E>*, const Key&, const E&);
    BSTNode<Key, E>* deletemin(BSTNode<Key, E>*);
    BSTNode<Key, E>* getmin(BSTNode<Key, E>*);
    BSTNode<Key, E>* removehelp(BSTNode<Key, E>*, const Key&);
    E* findhelp(BSTNode<Key, E>*, const Key&) const;
    void printhelp(BSTNode<Key, E>*, int) const;
    void inorderPrint(BSTNode<Key, E>* root) const;
    void reverseOrder(BSTNode<Key, E>* root) const;
    void vist(BSTNode<Key, E>*) const;

public:
    BST()      // Constructor
    {
        root = NULL;
        nodecount = 0;
    }

    //Note from Prof Sipantzi -- I've commented out the destructor
    //since you would have to change clearhelp() to make it work with
    //doubly-threaded trees and that is not part of the assignment.
    //~BST() { clearhelp(root); }            // Destructor

    void clear()   // Reinitialize tree
    {
        clearhelp(root); root = NULL; nodecount = 0;
    }

    // Insert a record into the tree.
    // k Key value of the record.
    // e The record to insert.
    void insert(const Key& k, const E& e) {
        root = inserthelp(root, k, e);
        nodecount++;
    }
    int getSize() { return nodecount; }

    // Remove a record from the tree.
    // k Key value of record to remove.
    // Return: The record removed, or NULL if there is none.
    E* remove(const Key& k) {
        E* temp = findhelp(root, k);   // First find it
        if (temp != NULL) {
            root = removehelp(root, k);
            nodecount--;
        }
        return temp;
    }
    // Remove and return the root node from the dictionary.
    // Return: The record removed, null if tree is empty.
    E* removeAny() {  // Delete min value
        if (root != NULL) {
            E* temp = new E;
            *temp = root->element();
            root = removehelp(root, root->key());
            nodecount--;
            return temp;
        }
        else return NULL;
    }

    // Return Record with key value k, NULL if none exist.
    // k: The key value to find. */
    // Return some record matching "k".
    // Return true if such exists, false otherwise. If
    // multiple records match "k", return an arbitrary one.
    E* find(const Key& k) const { return findhelp(root, k); }

    // Return the number of records in the dictionary.
    int size() { return nodecount; }

    void print() const { // Print the contents of the BST
        if (root == NULL) cout << "The BST is empty.\n";
        else
        {
            std::cout << "My tree's structure is (tests my changes to the print function: " << std::endl;
            printhelp(root, 0);
            std::cout << std::endl;

            inorderPrint(root);
            reverseOrder(root);

        }
    }

};

// Visit -- prints out root
template <typename Key, typename E>
void BST<Key, E>::vist(BSTNode<Key, E>* r) const {
    cout << "Node - " << r->element() << endl;
}

// Clean up BST by releasing space back free store
template <typename Key, typename E>
void BST<Key, E>::
clearhelp(BSTNode<Key, E>* root) {
    if (root == NULL) return;
    clearhelp(root->left());
    clearhelp(root->right());
    delete root;
}

// Insert a node into the BST, returning the updated tree
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::inserthelp(BSTNode<Key, E>* root, const Key& k, const E& it)
{
   
    if (root == NULL) //create first node of tree
    {
        return new BSTNode<Key, E>(k, it, NULL, NULL); //return first node of tree
    }

    if (k < root->key()) //GO LEFT
    {
        if (root->left() == NULL || root->isLeftThread() == true) //check if there is not a left child
        {
            if (root->left() == NULL)
            {
                root->setLeft(new BSTNode<Key, E>(k, it, NULL, root)); // If the root is the 'Left-most' node of the tree, the new child will have a NULL left pointer
                root->left()->setLeftToThread(false);
                root->left()->setRightToThread(true);

                //the root's left pointers will remain false as a thread

                return root;
            }
            else
            {
                root->setLeft(new BSTNode<Key, E>(k, it, root->left(), root));
                root->left()->setLeftToThread(true);
                root->left()->setRightToThread(true);

                root->setLeftToThread(false); //update the current node to not have a left thread, it instead points to a child
                return root;
            }
        }
        else //if there is a left child
        {
            //root = inserthelp(root->left(), k, it);   

            root->setLeft(inserthelp(root->left(), k, it));
            return root;
        }

    }
    else //GO RIGHT
    {
        if (root->right() == NULL || root->isRightThread() == true) //check if there is not a right child
        {
            if (root->right() == NULL)
            {
                root->setRight(new BSTNode<Key, E>(k, it, root, NULL)); // If the root is the 'Right-most' node of the tree, the new child will have a NULL right pointer
                root->right()->setLeftToThread(true);
                root->right()->setRightToThread(false);

                //the root's right pointers will remain false as a thread

                return root;
            }
            else
            {
                root->setRight(new BSTNode<Key, E>(k, it, root, root->right()));
                root->right()->setLeftToThread(true);       //set the new node's left and right pointers correctly
                root->right()->setRightToThread(true);

                root->setRightToThread(false); //update the current node to not have a right thread, it instead points to a child
                return root;
            }
        }
        else //if there is a right child
        {
            //root = inserthelp(root->right(), k, it);   

            root->setRight(inserthelp(root->right(), k, it));
            return root;
        }

    }



}



// Delete the minimum value from the BST, returning the revised BST
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::
getmin(BSTNode<Key, E>* rt) {
    if (rt->left() == NULL)
        return rt;
    else return getmin(rt->left());
}
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::
deletemin(BSTNode<Key, E>* rt) {
    if (rt->left() == NULL) // Found min
        return rt->right();
    else {                      // Continue left
        rt->setLeft(deletemin(rt->left()));
        return rt;
    }
}

// Remove a node with key value k
// Return: The tree with the node removed
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::
removehelp(BSTNode<Key, E>* rt, const Key& k) {
    if (rt == NULL) return NULL;    // k is not in tree
    else if (k < rt->key())
        rt->setLeft(removehelp(rt->left(), k));
    else if (k > rt->key())
        rt->setRight(removehelp(rt->right(), k));
    else {                            // Found: remove it
        BSTNode<Key, E>* temp = rt;
        if (rt->left() == NULL) {     // Only a right child
            rt = rt->right();         //  so point to right
            delete temp;
        }
        else if (rt->right() == NULL) { // Only a left child
            rt = rt->left();          //  so point to left
            delete temp;
        }
        else {                    // Both children are non-empty
            BSTNode<Key, E>* temp = getmin(rt->right());
            rt->setElement(temp->element());
            rt->setKey(temp->key());
            rt->setRight(deletemin(rt->right()));
            delete temp;
        }
    }
    return rt;
}

// Find a node with the given key value
template <typename Key, typename E>
E* BST<Key, E>::findhelp(BSTNode<Key, E>* root,
    const Key& k) const {
    if (root == NULL) return NULL;          // Empty tree
    if (k < root->key())
        return findhelp(root->left(), k);   // Check left
    else if (k > root->key())
        return findhelp(root->right(), k);  // Check right
    else {
        E* temp = new E;
        *temp = root->element();
        return temp;  // Found it
    }
}

// Print out a BST
template <typename Key, typename E>
void BST<Key, E>::printhelp(BSTNode<Key, E>* root, int level) const
{


    if (root == NULL) return;           // Empty tree

    if (root->isLeftThread() == false && root->left() != NULL)
    {
        printhelp(root->left(), level + 1);   // Do left subtree
    }


    for (int i = 0; i < level; i++)         // Indent to level
        cout << "  ";
    cout << root->key() << "\n";        // Print node value

    if (root->isRightThread() == false && root->left() != NULL)
    {
        printhelp(root->right(), level + 1);  // Do right subtree
    }

    return;
}

// Print out a BST using threads in-order
template <typename Key, typename E>
void BST<Key, E>::inorderPrint(BSTNode<Key, E>* root) const
{
    std::cout << "Inorder printing of my tree " << std::endl << "(tests my right threads and printInorder function):" << std::endl;
    BSTNode<Key, E>* temp = root;


    if (nodecount == 1) //if there is one node in the tree
    {
        cout << temp->element() << endl;
    }
    else
    {
        while (temp->left() != NULL) //Navigate to the 'Left-Most- Node
        {
            temp = temp->left();
        }

        while (temp->right() != NULL) //As long as it hasnt reached the end
        {
            //Following a thread
            if (temp->isRightThread() == true)
            {
                std::cout << temp->element() << endl; //print self and follow thread
                temp = temp->right();
                std::cout << temp->element() << endl; //print node after thread, then always traverse right
                if (temp->isRightThread() == true)
                {
                    temp = temp->right();
                    std::cout << temp->element() << endl;
                    temp = temp->right();
                }
                else if (temp->right() != NULL)
                {
                    temp = temp->right();
                }
            }
            else //if following a child pointer
            {
                if (temp->isLeftThread() == false && temp->left() != NULL) //if left child is not empty, go left
                {
                    temp = temp->left();
                }
                else //if not, print
                {
                    std::cout << temp->element() << endl;
                    temp = temp->right();
                    while (temp->left() != NULL && temp->isLeftThread() == false)
                    {
                        temp = temp->left();
                    }
                }
            }
        }

    }
    cout << endl;

}

// Print out a BST using threads in reverse order
template <typename Key, typename E>
void BST<Key, E>::reverseOrder(BSTNode<Key, E>* root) const
{
    std::cout << "Reverse order printing of my tree " << std::endl << "(tests my left threads and printReverse function):" << std::endl;

    BSTNode<Key, E>* temp = root;


    if (nodecount == 1) //if there is one node in the tree
    {
        cout << temp->element() << endl;
    }
    else
    {
        while (temp->right() != NULL) //Navigate to the 'Right-Most- Node
        {
            temp = temp->right();
        }

        while (temp->left() != NULL) //As long as it hasnt reached the end
        {
            //Following a thread
            if (temp->isLeftThread() == true)
            {
                std::cout << temp->element() << endl; //print self and follow thread
                temp = temp->left();
                std::cout << temp->element() << endl; //print node after thread, then always traverse left
                if (temp->isLeftThread() == true)
                {
                    temp = temp->left();
                    std::cout << temp->element() << endl;
                    temp = temp->left();
                }
                else if (temp->left() != NULL)
                {
                    temp = temp->left();
                }
            }
            else //if following a child pointer
            {
               
                if (temp->isRightThread() == false && temp->right() != NULL) //if right child is not empty, go right
                {
                    temp = temp->right();
                }

                else if (temp->isLeftThread() == false && temp->left() != NULL)//if left child is a pointer and not empty
                {
                    std::cout << temp->element() << endl;
                    temp = temp->left();
                    while (temp->right() != NULL && temp->isRightThread() == false)
                    {
                        temp = temp->right();
                    }
                }
            }
        }

    }
    cout << endl;

}


#endif