/**********************************************
* File: RBTreeNode.h
* Author: Matthew Morrison
* Email: matt.morrison@nd.edu
* 
* Class constructor for an Red-Black Tree Node 
**********************************************/
#ifndef RBTNODE_H
#define RBTNODE_H

#include <iostream> 
  
enum COLOR { RED, BLACK }; 
  
template<class T>
class RBTNode { 

public: 
 
 	T value; 
  	COLOR color; 
  	RBTNode<T> *left, *right, *parent; 
 
  	/********************************************
  	* Function Name  : RBTNode<T>
  	* Pre-conditions : val
  	* Post-conditions: none
  	*  
	* Constructs an RBTNode use a passed value
  	********************************************/
  	RBTNode<T>(T valueIn) : value(valueIn), color(RED), left(NULL), right(NULL), parent(NULL) { } 
	
	~RBTNode() {}
	
	RBTNode<T>(const RBTNode<T>& copy){
		
		
		if(this != &copy){
			
			this->value = copy->value;
			this->color = copy->color;
			
		}
		
		
	}
	
	
	RBTNode<T>& operator=(const RBTNode<T>& assign){
		
		
		if(this != &assign){
			
			this->value = assign->value;
			this->color = assign->color;
			
		}
		
		return *this;
		
	}
  
  // returns pointer to uncle 
  /********************************************
  * Function Name  :  
  * Pre-conditions : 
  * Post-conditions: 
  *  
  ********************************************/
  RBTNode<T> *uncle() { 
    // If no parent or grandparent, then no uncle 
    if (parent == NULL or parent->parent == NULL) 
      return NULL; 
  
    if (parent->isOnLeft()) 
      // uncle on right 
      return parent->parent->right; 
    else
      // uncle on left 
      return parent->parent->left; 
  }
  
  // check if node is left child of parent 
  /********************************************
  * Function Name  : isOnLeft
  * Pre-conditions : none
  * Post-conditions: bool
  *  
  ********************************************/
  bool isOnLeft() { return this == parent->left; } 
  
   bool isOnRight() { return this == parent->right; } 
  
  // returns pointer to sibling 
  /********************************************
  * Function Name  :  
  * Pre-conditions : 
  * Post-conditions: 
  *  
  ********************************************/
  RBTNode<T> *sibling() { 
    // sibling null if no parent 
    if (parent == NULL) 
      return NULL; 
  
    if (isOnLeft()) 
      return parent->right; 
  
    return parent->left; 
  } 
  
  // moves node down and moves given node in its place 
  /********************************************
  * Function Name  : moveDown
  * Pre-conditions : RBTNode<T> *nParent
  * Post-conditions: none
  *  
  ********************************************/
  void moveDown(RBTNode<T> *nParent) { 
    if (parent != NULL) { 
      if (isOnLeft()) { 
        parent->left = nParent; 
      } else { 
        parent->right = nParent; 
      } 
    } 
    nParent->parent = parent; 
    parent = nParent; 
  } 
  
  /********************************************
  * Function Name  : hasRedChild
  * Pre-conditions : none
  * Post-conditions: bool
  * 
  * Checks if the node has a red child 
  ********************************************/
  bool hasRedChild() { 
    return (left != NULL and left->color == RED) or 
           (right != NULL and right->color == RED); 
  } 
}; 

#endif
