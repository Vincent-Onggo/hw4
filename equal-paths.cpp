#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
int getHeight(Node* root){
    if(root == nullptr){
        return 0;
    }
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    if(leftHeight > rightHeight){
        return 1 + leftHeight;
    }else{
        return 1 + rightHeight;
    }
}

bool equalPaths(Node * root)
{
    // Add your code below
    if(root == nullptr){
        return true;
    }
    if(getHeight(root->left) == getHeight(root->right)){
        Node* left_node = root->left;
        Node* right_node = root->right;
        return equalPaths(left_node) && equalPaths(right_node);
    }else{
        return false;
    }
}

