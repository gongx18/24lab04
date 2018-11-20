// intbst.cpp
// Implements class IntBST
// YOUR NAME(S), DATE

#include "intbst.h"

#include <iostream>
#include <stack>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() : root(0) { }

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    if (n) {
	clear(n->left);
	clear(n->right);
	delete n;
    }
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    // handle special case of empty tree first
    if (!root) {
	root = new Node(value);
	return true;
    }
    // otherwise use recursive helper
    return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    if (value == n->info)
	return false;
    if (value < n->info) {
	if (n->left)
	    return insert(value, n->left);
	else {
	    n->left = new Node(value);
	    n->left->parent = n;
	    return true;
	}
    }
    else {
	if (n->right)
	    return insert(value, n->right);
	else {
	    n->right = new Node(value);
	    n->right->parent = n;
	    return true;
	}
    }
}

// print tree data pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if (n) {
	cout << n->info << " ";
	printPreOrder(n->left);
	printPreOrder(n->right);
    }
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
}

 void IntBST::printInOrder(Node *n) const {
    stack <Node *n> s; 
    Node *cur = root; 

    while(!s.empty() || cur != NULL){
        while(cur != NULL){
            s.push(cur);
            cur = cur->left; 
        }
        cur = s.pop();
        cout << cur->info; 
        cur = cur->right; 
    }
 }

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
}

void IntBST::printPostOrder(Node *n) const {
    if(n == NULL) return;
    printPostOrder(n->left);
    printPostOrder(n->right);
    cout << n->info << " ";
}

// return sum of values in tree
int IntBST::sum() const {
    return sum(root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    if(n == NULL) return 0;
    return n->info + sum(n->right) + sum(n->left); 
}

// return count of values
int IntBST::count() const {
    return count(root);
}

// recursive helper for count
int IntBST::count(Node *n) const {
    if(n == NULL)
        return 0;
    return 1 + count(n->right) + count(n->left); 
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
    if(n == NULL) return NULL; 
    if(n->info == value || n == NULL)
        return n; 
    if(n->info > value) return getNodeFor(value, n->left); 
    return getNodeFor(value, n->right); 
}


// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
    Node *cur = root; 
    while(cur != NULL){
        if(cur->info == value){
            return true;
        }
        else{
            if(value > cur->info) 
                cur = cur->right; 
            else 
                cur = cur->left; 
        }
    }
    return false; 
}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
    if(root == NULL) return NULL; 
    Node *temp = root; 
    Node *pre = NULL;
    while(temp != NULL){
        if(temp->info >= value){
            temp = temp->left; 
        }
        else{
            pre = temp; 
            temp = temp->right; 
        }
    }
    return pre; 
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
    bool b = false; //boolean b denotes whether "value" is the smallest value in tree, i.e, no Predecessor;  
    if(root == NULL) return 0; 
    Node *temp = root; 
    Node *pre = NULL;
    while(temp != NULL){
        if(temp->info >= value){
            temp = temp->left; 
        }
        else{
            pre = temp; 
            temp = temp->right;
            b = true;  
        }
    }
    if(b) return 0;
    else return pre->info; 
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
    if(root == NULL) return NULL; 
    Node *temp = root; 
    Node *pre = NULL;
    while(temp != NULL){
        if(temp->info <= value){
            temp = temp->right; 
        }else{
            pre = temp; 
            temp = temp->left;
        }
    }
    return pre;
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
    bool b = false; //boolean b denotes whether "value" is the smallest value in tree, i.e, no Predecessor;  
    if(root == NULL) return 0; 
    Node *temp = root; 
    Node *pre = NULL;
    while(temp != NULL){
        if(temp->info >= value){
            temp = temp->left; 
        }
        else{
            pre = temp; 
            temp = temp->right;
            b = true; //i.e, has predecessor  
        }
    }
    if(b) return pre->info;
    else return 0; 
}

//helper function for remove; 
void deleteNode(Node *root, int value){
        if(root == NULL){
            return NULL; 
        }
        if(root->val == key){
            if(! root->left ){
                return root -> right; 
            }
            if(! root->right){
                return root -> left; 
            }
            
            int c = getSuccessorNode(root) -> val; 
            root->val = c; 
            root->right = deleteNode(root -> right, c); 
            return root; 
        }
        
        if(root->val < key){
            root->right = deleteNode(root -> right, key);  //note: deteleNode would return itself if root.right isn't key
        }else{
            root->left = deleteNode(root -> left, key);
        }
}   

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value){
    if(contains(value) == false) return false;
    
    deleteNode(root, value);
    if(contains(value) == false) return true;
    else return false; 
}
