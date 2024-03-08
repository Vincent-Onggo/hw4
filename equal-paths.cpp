#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
bool depthCheck(Node* root, int currDepth, int& pathDepth){
    // Base case
    if(root == nullptr){
        return true;
    }
    // Case 1: root is a leaf node
    if(root->left == nullptr and root->right == nullptr){
        if(pathDepth == -1){ // if no paths checked yet
            pathDepth = currDepth;
            return true;
        }
        // or not check if depth matches other pathDepths
        return pathDepth == currDepth;
    }
    // Case 2: if not a leaf node check both left and right nodes
    return depthCheck(root->left, currDepth + 1, pathDepth) and depthCheck(root->right, currDepth + 1, pathDepth);
}
bool equalPaths(Node * root)
{
    // Add your code below
    int pathDepth = -1;
    return depthCheck(root, 1, pathDepth);
}

