#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

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
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    int getHeight(AVLNode<Key, Value>* root);
    void insertFix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* node);
    void rotateRight(AVLNode<Key, Value>* node);
    void rotateLeft(AVLNode<Key, Value>* node);


};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
int AVLTree<Key, Value>::getHeight(AVLNode<Key, Value>* root){
    if(root == nullptr){
        return 0;
    }
    int leftHeight = getHeight(root->getLeft());
    int rightHeight = getHeight(root->getRight());
    return 1 + std::max(leftHeight, rightHeight);
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value> *node) {
    // check that all nodes exist and structure is correct
    if(node == nullptr){
        return;
    }
    AVLNode<Key, Value>* parent = node->getParent();
    if(parent == nullptr or parent->getLeft() != node){
        return;
    }
    AVLNode<Key, Value>* gParent = parent->getParent();
    if(gParent == nullptr or gParent->getLeft() != parent){

        return;
    }

    // set child pointers

    AVLNode<Key, Value>* a = node->getLeft();
    AVLNode<Key, Value>* b = node->getRight();
    AVLNode<Key, Value>* c = parent->getRight();
    AVLNode<Key, Value>* d = gParent->getRight();

    // performing rotation
    nodeSwap(parent, gParent);
    nodeSwap(node, gParent);
    parent->setRight(gParent);
    gParent->setParent(parent);
    node->setLeft(a);
    node->setRight(b);
    gParent->setLeft(c);
    gParent->setRight(d);
    if(a != nullptr) a->setParent(node);
    if(b != nullptr) b->setParent(node);
    if(c != nullptr) c->setParent(gParent);
    if(d != nullptr) d->setParent(gParent);
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value> *node) {
    // check that all nodes exist and structure is correct
    if(node == nullptr){
        return;
    }
    AVLNode<Key, Value>* parent = node->getParent();
    if(parent == nullptr or parent->getRight() != node){
        return;
    }
    AVLNode<Key, Value>* gParent = parent->getParent();
    if(gParent == nullptr or gParent->getRight() != parent){
        return;
    }

    // set child pointers
    AVLNode<Key, Value>* a = gParent->getLeft();
    AVLNode<Key, Value>* b = parent->getRight();
    AVLNode<Key, Value>* c = node->getRight();
    AVLNode<Key, Value>* d = node->getRight();

    // performing rotation
    nodeSwap(parent, gParent);
    nodeSwap(node, gParent);
    parent->setLeft(gParent);
    gParent->setParent(parent);
    node->setLeft(c);
    node->setRight(d);
    gParent->setLeft(a);
    gParent->setRight(b);
    if(a != nullptr) a->setParent(gParent);
    if(b != nullptr) b->setParent(gParent);
    if(c != nullptr) c->setParent(node);
    if(d != nullptr) d->setParent(node);
}

template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr); // balance is default to zero
    if(BinarySearchTree<Key, Value>::root_ == nullptr) {  // when tree is empty
        BinarySearchTree<Key, Value>:: root_ = newNode;
    }else{
        AVLNode<Key, Value>* curr = static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key, Value>::root_);
        AVLNode<Key, Value>* parent = nullptr;
        while(curr != nullptr){
            parent = curr;
            if(new_item.first < curr->getKey()){
                curr = curr->getLeft(); // move left
            } else if(new_item.first > curr->getKey()){
                curr = curr->getRight();
            }else{ // if key value exists
                curr->setValue(new_item.second);
                delete newNode;
                return;
            }
        }
        if(new_item.first < parent->getKey()){ // fix parent pointers
            parent->setLeft(newNode);
        }else{
            parent->setRight(newNode);
        }
        newNode->setParent(parent);
//         balancing
        if(abs(parent->getBalance()) == 1){
            parent->setBalance(0);
        }else if(parent->getBalance() == 0){
            parent->setBalance(getHeight(parent->getRight()) - getHeight(parent->getLeft()));
            insertFix(parent, newNode);
        }
    }
}
template <class Key, class Value>
void  AVLTree<Key, Value>::insertFix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* node){
    if(parent == nullptr or parent->getParent() == nullptr){
        return;
    }
    AVLNode<Key, Value>* gParent = parent->getParent();
    if(gParent->getLeft() == parent){ // if p is a left child of g
        gParent->updateBalance(-1);
        if(gParent->getBalance() == 0){
            return;
        }else if(gParent->getBalance() == -1){
            insertFix(gParent, parent);
        }else if(gParent->getBalance() == -2){
            if(parent->getLeft() == node){ // if zig zig
                rotateRight(node);
                parent->setBalance(0);
                gParent->setBalance(0);
            }else{ // zig zag
                rotateLeft(parent);
                rotateRight(gParent);
                if(node->getBalance() == -1){
                    parent->setBalance(0);
                    gParent->updateBalance(1);
                    node->setBalance(0);
                }else if(node->getBalance() == 0){
                    parent->setBalance(0);
                    gParent->setBalance(0);
                    node->setBalance(0);
                }else if(node->getBalance() == 1){
                    parent->setBalance(-1);
                    gParent->setBalance(0);
                    node->setBalance(0);
                }
            }
;        }
    }

}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO

}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
