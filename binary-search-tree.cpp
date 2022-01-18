#include "binary-search-tree.h"
#include <iostream>

#include <queue>
using namespace std;


BinarySearchTree::Node::Node(DataType newval)
{
    val = newval ;
    left = nullptr;
    right = nullptr;


}
BinarySearchTree::BinarySearchTree()
{

    root_ = nullptr;
    size_ = 0;
}
int BinarySearchTree::getNodeDepth(Node *n) const // Optional function that recursively gets the maximum depth for a given node.
{

    int leftDepth = 0;
    int rightDepth = 0;
    if (n == nullptr) return 0;
    leftDepth = getNodeDepth(n->left) + 1;
    rightDepth = getNodeDepth(n->right) + 1;
    if (leftDepth < rightDepth) {
        return rightDepth;
    }
    else {
        return leftDepth;
    }

// Default constructor to initialize the root.
}

void inorderDelete(BinarySearchTree::Node* temp)
{

    if (!temp)//base case
        return;//when temp is null
    inorderDelete(temp->left);

    inorderDelete(temp->right);

    delete temp;

}

// Destructor of the class BinarySearchTree. It deallocates the memory
// space allocated for the binary search tree.
BinarySearchTree::~BinarySearchTree()
{
    queue<Node*> queueSetup;
    Node *currentNode = root_;

    if (root_ != nullptr) queueSetup.push(root_);

    while(!queueSetup.empty()) {
        currentNode = queueSetup.front();
        queueSetup.pop();
        if (currentNode->left != nullptr) queueSetup.push(currentNode->left);
        if (currentNode->right != nullptr) queueSetup.push(currentNode->right);
        delete currentNode;
    }
}



// Returns the number of nodes in the tree.
unsigned int BinarySearchTree::size() const
{
return size_;
}
// Returns the maximum value of a node in the tree. You can assume that
// this function will never be called on an empty tree.
BinarySearchTree::DataType BinarySearchTree::max() const {
    BinarySearchTree::Node*  temp= root_;
    while (temp->right != nullptr){
        temp =  temp->right;
    }
    return temp -> val;
}
// Returns the minimum value of a node in the tree. You can assume that
// this function will never be called on an empty tree.
BinarySearchTree::DataType BinarySearchTree::min() const
{

    BinarySearchTree::Node*  temp= root_;
    while (temp->left != nullptr){
        temp = temp -> left;
    }
    return temp -> val;
}
// Returns the maximum depth of the tree. A tree with only the root node has a
// depth of 0. You can assume that this function will never be called on an
// empty tree.
unsigned int BinarySearchTree::depth() const
{
    return getNodeDepth(root_) -1;
}

void inorderPrint(BinarySearchTree::Node* temp)
{
    if (!temp)
        return;
    inorderPrint(temp->left);
    cout << temp->val << " ";
    inorderPrint(temp->right);
}
//using in-order traversal
void BinarySearchTree::print() const
{
   inorderPrint(root_);
}
// Returns true if a node with the value val exists in the tree; otherwise,
// it returns false.
bool BinarySearchTree::exists(DataType val) const
{
    BinarySearchTree::Node* temp = root_;
    while(temp != nullptr)
    {
        if(temp -> val == val)
        {return true;}
        if(temp -> val > val)
        {temp = temp-> left;}
        else
        {temp = temp ->right;}
    }

    return false;

}
// Returns a pointer to the root node
BinarySearchTree::Node* BinarySearchTree::getRootNode()
{
return root_;
}
// Returns the root node pointer address
BinarySearchTree::Node** BinarySearchTree::getRootNodeAddress()
{
    return &root_;
}


// Inserts the value val into the tree. Returns false if val already exists in
// the tree, and true otherwise.
bool BinarySearchTree::insert(DataType val) {

   if (exists(val)) {

        return false;
    } else {

        if (root_ == nullptr) {
            root_ = new Node(val);

            size_++;
            return true;
        }
        Node *x = root_;
        Node *p;
        while (x != nullptr) {
            p = x;
            if (val < x->val) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        Node *node = new Node(val);
        if (val <= p->val) {
            p->left = node;
        } else {
            p->right = node;
        }

        size_++;
        return true;

    }

}

// Removes the node with the value val from the tree. Returns true if successful,
// and false otherwise.

bool BinarySearchTree::remove(DataType val) {
    if(root_ == nullptr) {

        return false;
    }

    else {
        Node* temp = root_;
        Node* first = root_;
        bool isThere = false;
        bool isLeft = false;

        while(temp != nullptr) {
            if(val == temp->val) {
                isThere = true;
                break;
            }
            else if(val >= temp->val) {
                first = temp;
                temp = temp->right;
                isLeft = false;
            }
            else {
                first = temp;
                temp = temp->left;
                isLeft = true;
            }
        }
        if(!isThere) return false;
        else {
            if(temp->left != nullptr && temp->right != nullptr) {
                Node* predecessor = temp->left;
                while (predecessor->right != nullptr) predecessor = predecessor->right;
                int predecessor_value = predecessor->val;
                remove(predecessor_value);
                temp->val = predecessor_value;
                size_--;

                return true;
            }
            if(temp->left != nullptr) {
                if(temp == root_) root_ = temp->left;
                if(isLeft) first->left = temp->left;
                else first->right = temp->left;
                delete temp;
                size_--;

                return true;
            }
            else if(temp->right != nullptr) {
                if(temp == root_) root_ = temp->right;
                if(isLeft) first->left = temp->right;
                else first->right = temp->right;
                delete temp;
                size_--;

                return true;
            }
            else {
                if(temp == root_) {
                    delete root_;
                    root_ = nullptr;
                    size_--;

                    return true;
                }
                if(isLeft) first->left = nullptr;
                else first->right = nullptr;
                delete temp;

                size_--;
                return true;
            }
        }
    }
    return false;
}
