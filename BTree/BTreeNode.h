/**********************************************
* File: BTreeNode.h
*  
* Implementation of a Templated C++ Class BTreeNode 
*
* Developed from the implementation from CLRS Text
* T. H. et al Cormen, Introduction to algorithms. Cambridge, MA: MIT Press, 2009.
**********************************************/
#ifndef BTREENODE_H
#define BTREENODE_H
 
#include <iostream> 
#include <cstdlib>
  
// A BTree node 
template<class T> 
class BTreeNode 
{ 

	public: 
		int order;					// Order of the tree.
		int degree;      			// Minimum degree (defines the range for number of keys) 
		bool leaf; 					// Is true when node is leaf. Otherwise false 
		int numKeys;     			// Current number of keys 
		T *keys;  					// An array of keys 
		BTreeNode<T> **childPtrs; 	// An array of child pointers 

		/********************************************
		* Function Name  : checkMemory()
		* Pre-conditions : void
		* Post-conditions: void
		* 
		* Checks if the memory was properly allocated
		********************************************/
		void checkMemory(){
			
			if (this == NULL) {
				std::cerr <<  "Out of Memory" << std::endl;
				exit (-1);
			} 	
		}

		/********************************************
		* Function Name  : BTreeNode<T>
		* Pre-conditions : int orderIn, bool isLeaf
		* Post-conditions: none
		* 
		* BTreeNode Constructor 
		********************************************/
		BTreeNode<T>(int orderIn, bool isLeaf) : 
			order(orderIn), degree( (order+1)/2 ), leaf(isLeaf), numKeys(0), 
			keys(new T[order - 1]), childPtrs(new BTreeNode<T>*[order]) { 
			
			checkMemory();
		  
		} 
	   
		/********************************************
		* Function Name  : traverse
		* Pre-conditions : none
		* Post-conditions: none
		* 
		* A function to traverse all nodes in a subtree rooted with this node 
		********************************************/
		void traverse()
		{ 
			int i; 
			for (i = 0; i < numKeys; i++) 
			{ 
				if (leaf == false) 
					childPtrs[i]->traverse(); 
				std::cout << " " << keys[i]; 
			} 
		  
			if (leaf == false) 
				childPtrs[i]->traverse(); 
		} 
	       
		/********************************************
		* Function Name  : search
		* Pre-conditions : T key
		* Post-conditions: BTreeNode<T>*
		* 
		* A function to search a key in the subtree rooted with this node. 
		********************************************/
		BTreeNode<T>* search(T key){ 
			int i = 0; 
			while (i < numKeys && key > keys[i]) 
				i++; 
		  
			if(i < numKeys){
				if (keys[i] == key) 
					return this; 
			}
		  
			if (leaf == true) 
				return NULL; 
		  
			return childPtrs[i]->search(key); 
		}  
		
		/********************************************
		* Function Name  : insertNonFull
		* Pre-conditions : T key
		* Post-conditions: none
		*
		* A utility function to insert a new key in this node 
		* The assumption is, the node must be non-full when this 
		* function is called 
		********************************************/
		void insertNonFull(T key) 
		{ 
			int i = numKeys-1; 
		  
			if (leaf == true) 
			{ 
				while (i >= 0 && keys[i] > key) 
				{ 
					keys[i+1] = keys[i]; 
					i--; 
				} 
		  
				keys[i+1] = key; 
				numKeys = numKeys+1; 
			} 
			else 
			{ 
				while (i >= 0 && keys[i] > key) 
					i--; 
		  
				if (childPtrs[i+1]->numKeys == order-1) 
				{ 
					splitChild(i+1, childPtrs[i+1]); 
		  
					if (keys[i+1] < key) 
						i++; 
				} 
				childPtrs[i+1]->insertNonFull(key); 
			} 
		} 
	  
		/********************************************
		* Function Name  : splitChild
		* Pre-conditions : int i, BTreeNode<T> *y
		* Post-conditions: none
		* 
		* A utility function to split the child y of this node 
		* Note that y must be full when this function is called 
		********************************************/
		void splitChild(int i, BTreeNode<T> *y) 
		{ 

			BTreeNode<T> *z = new BTreeNode<T>(y->order, y->leaf); 
			z->numKeys = degree - 1; 
		  
			for (int j = 0; j < degree-1; j++) 
				z->keys[j] = y->keys[j+degree]; 
		  
			if (y->leaf == false) 
			{ 
				for (int j = 0; j < degree; j++) 
					z->childPtrs[j] = y->childPtrs[j+degree]; 
			} 
		  
			y->numKeys = degree - 1; 
		  
			for (int j = numKeys; j >= i+1; j--) 
				childPtrs[j+1] = childPtrs[j]; 
		  
			childPtrs[i+1] = z; 
		  
			for (int j = numKeys-1; j >= i; j--) 
				keys[j+1] = keys[j]; 
		  
			keys[i] = y->keys[degree-1]; 
		  
			numKeys = numKeys + 1; 
		} 
		
  
		/********************************************
		* Function Name  : fill
		* Pre-conditions : int index
		* Post-conditions: none
		*  
		* A function to fill child childPtrs[index] which has less than t-1 keys
		********************************************/
		void fill(int index) 
		{ 
		  
			if (index!=0 && childPtrs[index-1]->numKeys>=degree) 
				borrowFromPrev(index); 
		  

			else if (index!=numKeys && childPtrs[index+1]->numKeys >= degree) 
				borrowFromNext(index); 
		  
			else
			{ 
				if (index != numKeys) 
					merge(index); 
				else
					merge(index-1); 
			} 
			return; 
		} 
		  
		/********************************************
		* Function Name  : borrowFromPrev
		* Pre-conditions : int index
		* Post-conditions: none
		*  
		* A function to borrow a key from childPtrs[index-1] and insert it 
		* into childPtrs[index] 
		********************************************/
		void borrowFromPrev(int index) 
		{ 
		  
			BTreeNode<T> *child=childPtrs[index]; 
			BTreeNode<T> *sibling=childPtrs[index-1]; 
		  
			for (int i=child->numKeys-1; i>=0; --i) 
				child->keys[i+1] = child->keys[i]; 
		  
			if (!child->leaf) 
			{ 
				for(int i=child->numKeys; i>=0; --i) 
					child->childPtrs[i+1] = child->childPtrs[i]; 
			} 
		  
			child->keys[0] = keys[index-1]; 
		  
			if(!child->leaf) 
				child->childPtrs[0] = sibling->childPtrs[sibling->numKeys]; 
		  
			keys[index-1] = sibling->keys[sibling->numKeys-1]; 
		  
			child->numKeys += 1; 
			sibling->numKeys -= 1; 
		  
			return; 
		} 
		  
		/********************************************
		* Function Name  : borrowFromNext
		* Pre-conditions : int index
		* Post-conditions: none
		* 
		* A function to borrow a key from the childPtrs[index+1] and place 
		* it in childPtrs[index]
		********************************************/
		void borrowFromNext(int index) 
		{ 
		  
			BTreeNode<T>* child = childPtrs[index]; 
			BTreeNode<T>* sibling = childPtrs[index+1]; 
		  
			child->keys[(child->numKeys)] = keys[index]; 
		  
			if (!(child->leaf)) 
				child->childPtrs[(child->numKeys)+1] = sibling->childPtrs[0]; 
		  
			keys[index] = sibling->keys[0]; 
		  
			for (int i=1; i<sibling->numKeys; ++i) 
				sibling->keys[i-1] = sibling->keys[i]; 
		  
			if (!sibling->leaf) 
			{ 
				for(int i=1; i<=sibling->numKeys; ++i) 
					sibling->childPtrs[i-1] = sibling->childPtrs[i]; 
			} 
		  
			child->numKeys += 1; 
			sibling->numKeys -= 1; 
		  
			return; 
		} 
		  
		/********************************************
		* Function Name  : merge
		* Pre-conditions : int index
		* Post-conditions: none
		* 
		* A function to merge childPtrs[index] with childPtrs[index+1] 
		* childPtrs[index+1] is freed after merging 
		********************************************/
		void merge(int index) 
		{ 
			BTreeNode<T> *child = childPtrs[index]; 
			BTreeNode<T> *sibling = childPtrs[index+1]; 
		  
			child->keys[degree-1] = keys[index]; 
		  
			for (int i=0; i<sibling->numKeys; ++i) 
				child->keys[i+degree] = sibling->keys[i]; 
		  
			if (!child->leaf) 
			{ 
				for(int i=0; i<=sibling->numKeys; ++i) 
					child->childPtrs[i+degree] = sibling->childPtrs[i]; 
			} 
		  
			for (int i=index+1; i<numKeys; ++i) 
				keys[i-1] = keys[i]; 
		  
			for (int i=index+2; i<=numKeys; ++i) 
				childPtrs[i-1] = childPtrs[i]; 
		  
			child->numKeys += sibling->numKeys+1; 
			numKeys--; 
		  
			delete(sibling); 
			return; 
		}

		int findKey( T key ) {

			int index = 0;
			while( index < numKeys && keys[index] < key)
				++index;

			return index;
		} 

		T getPred( int index ) {
			
			BTreeNode<T>* cur = childPtrs[index] ;
		
			while (!cur->leaf)
				cur = cur->childPtrs[cur->numKeys] ;

			return cur->keys[cur->numKeys-1];
		}

		T getSucc( int index ) {
			
			BTreeNode<T>* cur = childPtrs[index+1];
			
			while (!cur->leaf)
				cur = cur->childPtrs[0];

			return cur->keys[0] ;
		}

		void removeFromLeaf ( int index )  {
		
			// Move all keys after the index-th pos one place backward
			for( int i = index+1; i < numKeys; ++i)
				keys[i-1] = keys[i] ;

			// Reduce the count of keys
			numKeys--;

			return;
		}

		void removeFromNonLeaf(int index) {
		
			// Step 1
			T key = keys[index] ;

			// Step 2
			if (childPtrs[index]->numKeys >= degree) {
				T pred = getPred(index) ; // 2-1
				keys[index] = pred;       // 2-2
				childPtrs[index]->remove(pred);   // 2-3
			}

			// Step 3
			else if ( childPtrs[index+1]->numKeys >= degree) {
				T succ = getSucc(index) ;   // 3-1
				keys[index] = succ ;        // 3-2
				childPtrs[index+1]->remove(succ);
			}

			// Step 4
			else {
				merge(index) ; // 4-1
				childPtrs[index]->remove(key);   // 4-2
			}
		
			return;
		}

		void remove( T key ) {

			// Step 1
			int index = findKey(key) ;

			// Step 2
			if ( index < numKeys && keys[index] == key ){
				
				if ( leaf ) { removeFromLeaf(index) ; }    // Step 2-1
				else { removeFromNonLeaf(index); }         // Step 2-2
			}

			// Step 3
			else {
		
				// Step 3-1
				if (leaf) {
					std::cout << "The Key " << key << " does not exist in tree\n" ;
					return ;
				}

				// Step 3-2
				bool flag = ( (index==numKeys) ? true : false) ;

				// Step 3-3
				if( childPtrs[index]->numKeys < degree) 
					fill(index);

				// Step 3-4
				if (flag && index > numKeys)
					childPtrs[index-1]->remove(key);
				else
					childPtrs[index]->remove(key);
			}

			return;
		}

		void printFoundNodes(T key) {


			int i = 0;
			while( i < numKeys && key > keys[i] ){
				std::cout << keys[i] << " ";
				++i; 
			}

			if( i < numKeys ) {
				if ( keys[i] == key){
					std::cout << keys[i] << "...key found!" << std::endl;
					return;
				}
			}

			if ( leaf == true){ 
				std::cout << "Node not found :( \n" ;
				return;
			}

			childPtrs[i]->printFoundNodes(key);
		}

}; 

#endif
