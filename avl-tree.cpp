#include "avl-tree.h"

#include <cstdlib>

#include <algorithm>

int height(BinarySearchTree::Node *N)
{
    if(N == nullptr) return -1;
    else if (N->left == nullptr && N->right == nullptr) return 0;
    else {
        return 1 + std::max(height(N->left), height(N->right) );
    }
}

void SingleRightRotation(BinarySearchTree::Node **pT, BinarySearchTree::Node *alpha){
    //Input is alpha
    //A is alpha’'s left
    BinarySearchTree::Node *A = alpha->left;
    //alpha’s left = A’'s right
    alpha->left = A->right;
    //A’'s right = alpha
    A->right= alpha;
    //If alpha was the root of the whole tree, make A to be the new root.
    if (*pT == alpha) {
        *pT = A;
    }
    else {
        //Let alpha’'s parent take A as the new child.
        //find     alpha’s parent
        BinarySearchTree::Node *temp = *pT;
        BinarySearchTree::Node **parentPointerToAlpha = nullptr;
        do{
            if(alpha->val > temp->val)  {
                parentPointerToAlpha = &temp->right;
                temp = temp->right;
            }
            else if (alpha->val < temp->val) {
                parentPointerToAlpha = &temp->left;
                temp = temp->left;
            }
        }
        while (temp->val != alpha->val);
        *parentPointerToAlpha = A;
    }
}




void SingleLeftRotation(BinarySearchTree::Node **pT, BinarySearchTree::Node *alpha){
    //Input is alpha
    //A is alpha's right
    BinarySearchTree::Node *A = alpha->right;
    //alpha's right = A's left
    alpha->right = A->left;
    //A's left = alpha
    A->left = alpha;
    //If alpha was the root of the whole tree, make A to be the new root.
    if (*pT == alpha) {
        *pT = A; // why isnt this updating the root tree
    }
    else {
        //Let alpha’'s parent take A as the new child.
        //find     alpha’s parent
        BinarySearchTree::Node *temp = *pT;
        BinarySearchTree::Node **parentPointerToAlpha = nullptr;
        do{
            if(alpha->val > temp->val)  {
                parentPointerToAlpha = &temp->right;
                temp = temp->right;
            }
            else if (alpha->val < temp->val) {
                parentPointerToAlpha = &temp->left;
                temp = temp->left;
            }
        }
        while (temp->val != alpha->val);
        *parentPointerToAlpha = A;
    }
}


void LeftRightRotation(BinarySearchTree::Node **pT, BinarySearchTree::Node *alpha){
    //Input is alpha
    //A is alpha'’s left
    BinarySearchTree::Node *A = alpha->left;
    //B is A’'s right
    //Call single left rotation with input (A)
    SingleLeftRotation(pT, A);
    //Call single right rotation with input (alpha)
    SingleRightRotation(pT, alpha);
}





BinarySearchTree::Node RightLeftRotation(BinarySearchTree::Node **pT, BinarySearchTree::Node *alpha){
    //Input is alpha
    BinarySearchTree::Node *A = alpha->right;
    //B is A’'s left
    //Call single right rotation with input (A)
    SingleRightRotation(pT, A);
    //Call single left rotation with input (alpha)
    SingleLeftRotation(pT, alpha);
}






bool AVLTree::insert(DataType val) // rotations arent actually updating the tree
{
//may want to call the BST version of insert and remove
// then keep tree balanced by applying appropriate AVL tree rotations
    bool result = BinarySearchTree::insert(val);
    if (result == false ) return false; // return false if the val does not insert
    // find it is unbalanced or not. if not, return
    // find the pointer to the unbalanced ancestor that is closest to the new node
    BinarySearchTree::Node *root;
    root = BinarySearchTree::getRootNode(); // i want it to take the address
    BinarySearchTree::Node **addressRoot;
    addressRoot = BinarySearchTree::getRootNodeAddress();
    // if N is at root node, nothing is unbalanced, just return
    if(root->val == val) return true;
    BinarySearchTree::Node *temp;
    temp = root;
    BinarySearchTree::Node *tempParent;
    BinarySearchTree::Node *alpha = nullptr;
    do {
        tempParent = temp;
        if(val>temp->val) temp = temp->right;
        else if (val<temp->val) temp = temp->left;
        // now check if tem&pParent is unbalanced
        int leftHeight = height(tempParent->left);
        int rightHeight = height(tempParent->right);
        if(abs(leftHeight - rightHeight) >= 2 ) alpha = tempParent;
    } while (temp->val != val);

    if(!alpha) return true;
    if (val < alpha->val && val<alpha->left->val){ // single right rotation
        SingleRightRotation(addressRoot,alpha);
    }  else if (val > alpha->val && val > alpha->right->val ){// single left rotation
        SingleLeftRotation(addressRoot,alpha);
    }
    else if ( val < alpha->val && val > alpha->left->val ) {// left right
        LeftRightRotation(addressRoot,alpha);
    }
    else if (val > alpha->val && val < alpha->right->val ) {//right left
        RightLeftRotation(addressRoot, alpha);
    }
    return true;
}


bool AVLTree::remove(DataType val)
{
    bool result = BinarySearchTree::remove(val);
    if (result == false) return false;
    BinarySearchTree::Node *root;
    root = BinarySearchTree::getRootNode();
    BinarySearchTree::Node **addressRoot;
    addressRoot = BinarySearchTree::getRootNodeAddress();
    // if N is at root node, nothing is unbalanced, just return
    if(root->val == val) return true;
    BinarySearchTree::Node *temp;
    temp = root;
    BinarySearchTree::Node *tempParent;
    BinarySearchTree::Node *alpha = nullptr;
    do {
        tempParent = temp;
        if(val>temp->val) temp = temp->right;
        else if (val<temp->val) temp = temp->left;

        // now check if tempParent is unbalanced
        int leftHeight = height(tempParent->left);
        int rightHeight = height(tempParent->right);
        if(abs(leftHeight - rightHeight) >= 2 ) alpha = tempParent;

        if(abs(leftHeight-rightHeight) >=2) alpha = tempParent;

        if (temp == nullptr) return true; // if its null then its balanced? -- idk

    } while (temp->val != val );
    if(!alpha) return true;
    if (val < alpha->val && val<alpha->left->val){ // single right rotation
        SingleRightRotation(addressRoot,alpha);
    }  else if (val > alpha->val && val > alpha->right->val ){// single left rotation
        SingleLeftRotation(addressRoot,alpha);
    }
    else if ( val < alpha->val && val > alpha->left->val ) {// left right
        LeftRightRotation(addressRoot,alpha);
    }
    else if (val > alpha->val && val < alpha->right->val ) {//right left
        RightLeftRotation(addressRoot, alpha);
    }
}

