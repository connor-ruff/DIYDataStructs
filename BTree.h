#ifndef BTREE_H
#define BTREE_H

#include<cstdlib>
#include<iostream>
#include "BTreeNode.h"

template<class T>
class BTree {
	
	private:
		BTreeNode<T> *root ;  // Pointer to root node
		int order ;
		int degree;

		void copy( BTreeNode<T>*& destination, BTree<T>*& origin) {
			
			BTreeNode<T>* newNode = new BTreeNode<T>(order, origin->leaf);

			copy(newNode->childPtrs[0], origin->childPtrs[0]) ;
			
			for( unsigned int iter = 0; iter < order -1; ++iter) {
				newNode->values[iter] = origin->values[iter] ;
				copy(newNode->childPtrs[iter+1], origin->childPtrs[iter+1]) ;
			}

			newNode->numVals = origin->numVals ;
			destination = newNode ;
		}

		BTree(const BTree<T>& copyTree) {

			copy( this->root, copyTree->root) ;
		}

		BTree<T>& operator=(const BTree<T>& assign) {
			
			if( this != &assign) {

				if(this->root == NULL) { return *this; }
				
				copy( this->root, assign->root) ;
			}

			return *this;
		}

		// Private method for Destructor
		void deleteTree( BTreeNode<T>*& theNode) {

			// Step 1: check if node is NULL
			if (theNode == NULL) { return; }

			// Step 2: Iterate
			for( unsigned int iter = 0; iter < order; ++iter) {
				deleteTree(theNode->childPtrs[iter] ) ;
				delete theNode->childPtrs[iter] ;
			}
		}
			

	public:
		
		BTree<T>( int orderIn ) : root(NULL), order(orderIn), degree( (order+1) / 2 ) {}

		// Public Method for Destructor
		~BTree() {   deleteTree(root); }

		void insert( T key ) {

			// Case 1: Where Tree is Empty
			if (root == NULL) {
				root = new BTreeNode<T>(order, true);
				root->keys[0] = key; 
				root->numKeys = 1;
			}

			// Case 2: insertNonFull
			else if (root->numKeys < order-1 ) {
				root->insertNonFull( key) ;
			}

			else {
				BTreeNode<T> *s = new BTreeNode<T>(order, false) ;
				s->childPtrs[0] = root;
				s->splitChild(0, root);

				int i = 0;
				if ( s->keys[0] < key ) { ++i; }
				
				s->childPtrs[i]->insertNonFull(key) ;

				root = s;
			}
		}

		void remove( T key) {
			
			// Step 1
			if ( root == NULL) {
				std::cout << "Tree is empty" << std::endl;
				return;
			}

			// Step 2
			root->remove(key);

			// Step 3
			if( root->numKeys == 0) {

				BTreeNode<T> *tmp = root;

				// Step 3-1
				if (root->leaf) { root = NULL; }
		
				// Step 3-2
				else { root = root->childPtrs[0] ; }

				// Step 3-3
				delete tmp;
			}
			return;
		}

		void traverse() {
			if (root != NULL) { root->traverse() ; } 
		}

		BTreeNode<T>* search(T key) {
			return (root == NULL) ? NULL : root->search(key) ;
		}

		void printFoundNodes( T key ) {

			if (root == NULL) { std::cout << "Empty Tree\n" ; }

			else{
				std::cout<< "Seeking " << key << ": " ;
				root->printFoundNodes(key);
			}
		}

			


}; 

#endif
