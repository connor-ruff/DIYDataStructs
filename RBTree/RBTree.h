#ifndef RBTREE_H
#define RBTREE_H 

#include "RBTreeNode.h"
#include <queue>		// Level Order Traversal only

template<class T> 
class RBTree { 

	private:

		// Red-Black Tree root node 
		RBTNode<T> *root; 
			
		/********************************************
		* Function Name	: leftRotate
		* Pre-conditions : RBTNode<T> *x
		* Post-conditions: none
		* 
		* left rotates the given node	
		********************************************/
		void leftRotate(RBTNode<T>*& x) { 
			// new parent will be node's right child 
			RBTNode<T> *nParent = x->right; 
			
			// update root if current node is root 
			if (x == root) 
				root = nParent; 
			
			x->moveDown(nParent); 
			
			// connect x with new parent's left element 
			x->right = nParent->left; 
			// connect new parent's left element with node 
			// if it is not null 
			if (nParent->left != NULL) 
				nParent->left->parent = x; 
			
			// connect new parent with x 
			nParent->left = x; 
		} 
			
		/********************************************
		* Function Name	: rightRotate
		* Pre-conditions : RBTNode<T> *x
		* Post-conditions: none
		* 
		* Performs right rotation on the node 
		********************************************/
		void rightRotate(RBTNode<T>*& x) { 
			// new parent will be node's left child 
			RBTNode<T> *nParent = x->left; 
			
			// update root if current node is root 
			if (x == root) 
				root = nParent; 
			
			x->moveDown(nParent); 
			
			// connect x with new parent's right element 
			x->left = nParent->right; 
			// connect new parent's right element with node 
			// if it is not null 
			if (nParent->right != NULL) 
				nParent->right->parent = x; 
			
			// connect new parent with x 
			nParent->right = x; 
		} 
			
		/********************************************
		* Function Name	: swapColors
		* Pre-conditions : RBTNode<T> *x1, RBTNode<T> *x2
		* Post-conditions: none
		* 
		* Swaps the colors of the two input nodes
		********************************************/
		void swapColors(RBTNode<T>*& x1, RBTNode<T>*& x2) { 
			COLOR temp; 
			temp = x1->color; 
			x1->color = x2->color; 
			x2->color = temp; 
		} 
			
		/********************************************
		* Function Name	: swapValues
		* Pre-conditions : RBTNode<T> *u, RBTNode<T> *v
		* Post-conditions: none
		*	
		********************************************/
		void swapValues(RBTNode<T>*& u, RBTNode<T>*& v) { 
			T temp; 
			temp = u->value; 
			u->value = v->value; 
			v->value = temp; 
		} 
			
		/********************************************
		* Function Name	: fixRedRed
		* Pre-conditions : RBTNode<T> *x
		* Post-conditions: none
		* 
		* fix red red at given node
		********************************************/
		void fixRedRed(RBTNode<T>*& x) { 
			// if x is root color it black and return 
			if (x == root) { 
				x->color = BLACK; 
				return; 
			} 
			
			// initialize parent, grandparent, uncle 
			RBTNode<T> *parent = x->parent, *grandparent = parent->parent, 
				 *uncle = x->uncle(); 
			
			if (parent->color != BLACK) { 
				if (uncle != NULL && uncle->color == RED) { 
					// uncle red, perform recoloring and recurse 
					parent->color = BLACK; 
					uncle->color = BLACK; 
					grandparent->color = RED; 
					fixRedRed(grandparent); 
				} 
				else { 
					// Else perform LR, LL, RL, RR 
					if (parent->isOnLeft()) { 
						if (x->isOnLeft()) { 
							// for left right 
							swapColors(parent, grandparent); 
						} 
						else { 
							leftRotate(parent); 
							swapColors(x, grandparent); 
						} 
						// for left left and left right 
						rightRotate(grandparent); 
					} 
					else { 
						if (x->isOnLeft()) { 
							// for right left 
							rightRotate(parent); 
							swapColors(x, grandparent); 
						} else { 
							swapColors(parent, grandparent); 
						} 
				
						// for right right and right left 
						leftRotate(grandparent); 
					} 
				} 
			} 
		} 
			
			
		/********************************************
		* Function Name	: levelOrder
		* Pre-conditions : RBTNode<T> *x
		* Post-conditions: none
		* 
		* Prints level order for given node
		********************************************/
		void levelOrder(RBTNode<T>*& x) { 
			if (x == NULL) 
			// return if node is null 
				return; 
			
			// queue for level order 
			std::queue<RBTNode<T> *> q; 
			RBTNode<T> *curr; 
			
			// push x 
			q.push(x); 
			
			while (!q.empty()) { 
			// while q is not empty 
			// dequeue 
				curr = q.front(); 
				q.pop(); 
			
			// print node value 
				std::cout << curr->value << " "; 
			
			// push children to queue 
				if (curr->left != NULL) 
					q.push(curr->left); 
				if (curr->right != NULL) 
					q.push(curr->right);
			} 

		} 
			
		/********************************************
		* Function Name	: inorder
		* Pre-conditions : RBTNode<T> *x
		* Post-conditions: none
		* 
		* Prints inorder recursively 
		********************************************/
		void inorder(RBTNode<T>*& x) { 
			if (x == NULL) 
				return; 
			inorder(x->left); 
			std::cout << x->value << " "; 
			inorder(x->right); 
		}

		void fixDoubleBlack(RBTNode<T>*& x) {

			// Step 1 - Return if the root
			if (x == root)
				return;

			// Step 2
			RBTNode<T> *sibling = x->sibling(), *parent = x->parent ;

			// Step 3
			if (sibling == NULL) {
				// No sibling, double black pushed up
				fixDoubleBlack(parent);
			}

			// Ze Four Scenarios
			else {

				// Scenario 1 - If Sibling is Red
				if (sibling->color == RED) {
					
					// Scenario 1-1
					parent->color = RED;
					sibling->color = BLACK;

					// Scenario 1-2
					if(sibling->isOnLeft()) 
						rightRotate(parent);

					// Scenario 1-3
					else
						leftRotate(parent);

					// Scenario 1-4
					fixDoubleBlack(x);
				}

				else {
			
					// Sibling has a red child
					if ( sibling->hasRedChild() ) {

						// Scenario 2 - Sibling's red child is the left child
						if ( sibling->left != NULL && sibling->left->color == RED) {

							// Sibling & Sibling's child from left Zig-Zig
							if (sibling->isOnLeft()){

								sibling->left->color = sibling->color ;
								sibling->color = parent->color;
								
								// Rotate parent opposite (right)
								rightRotate(parent);
							}

							// Sibling & Sibling's child from leftr Zig-Zag
							else {
						
								sibling->left->color = parent->color ;

								// Rotate opposite (right) on sibling
								rightRotate(sibling);
								// Rotate same (left) on parent
								leftRotate(parent);
							}
						}
					
						// Scenario 3 - The Sibling's red child is the right child
						else {
						
							// Sibling & sibling's red child is the right child
							if (sibling->isOnLeft()){
								sibling->right->color = parent->color ;
		
								// Rotate opposite (left) on sibling
								leftRotate(sibling);

								// Rotate same (left) on parent
								rightRotate(parent);
							}
		
							// Sibling & Sibling's CHild Form Right Zig-Zig
							else {
								// Sibling's left child = sibling & sibling - parent's COLOR
								sibling->right->color = sibling->color ;
								sibling->color = parent->color ;

								// Rotate parent opposite (left)
								leftRotate(parent);
							}
						}
						parent->color = BLACK ;
					}

					// Scenario 4 - The sibling has two Black children
					else {
						sibling->color = RED;
						if (parent->color == BLACK)
							fixDoubleBlack(parent);
						else
							parent->color = BLACK ;
					}
				}
			}
		}

		void deleteNode(RBTNode<T>*& u) {

			RBTNode<T>* v = BSTreplace(u);

			bool uvBlack = (  (v==NULL) || v->color == BLACK) && ( u->color == BLACK ) ;
			RBTNode<T>* parent = u->parent;

			if ( v==NULL){
				
				if ( u == root) {
					root = NULL ;
				}
				else{

					if (uvBlack)
						fixDoubleBlack(u);
					else {
						if (u->sibling() != NULL)
							u->sibling()->color = RED;
					}

					if (u->isOnLeft())
						parent->left = NULL;
					else
						parent->right = NULL;
				
				}

				delete u;
				return;	
			}

			// When v is not NULL
			
			if (u->left == NULL || u->right == NULL) {

				if ( u == root) {

					u->value = v->value;
					u->left = u->right = NULL ;
			 		delete v;
				}

				else{

					if ( u->isOnLeft())
						parent->left = v;

					else
						parent->right = v;

					delete u;

					v->parent = parent;

					if (uvBlack) 
						fixDoubleBlack(v);

					else
						v->color = BLACK;
				}

				return;
			}

			swapValues(u,v);
			deleteNode(v);
		}
		
	public: 
		/********************************************
		* Function Name	: RBTree
		* Pre-conditions : none
		* Post-conditions: none
		*	
		* Constructor. Initializes root to NULL
		********************************************/
		RBTree() : root(NULL) { } 
			
		/********************************************
		* Function Name	: getRoot
		* Pre-conditions : none
		* Post-conditions: RBTNode<T>*
		* 
			
		********************************************/
		RBTNode<T>* getRoot() { return root; } 
			
 
		/********************************************
		* Function Name	: search
		* Pre-conditions : T n
		* Post-conditions: RBTNode<T>*
		*
		* searches for given value 
		* if found returns the node (used for delete) 
		* else returns the last node while traversing (used in insert)		
		********************************************/
		RBTNode<T>* search(T n) { 
			RBTNode<T> *temp = root; 
			while (temp != NULL) { 
				if (n < temp->value) { 
				if (temp->left == NULL) 
					break; 
				else
					temp = temp->left; 
			} else if (n == temp->value) { 
				break; 
			} else { 
				if (temp->right == NULL) 
					break; 
				else
					temp = temp->right; 
			} 
			} 
			
			return temp; 
		} 
			
		/********************************************
		* Function Name	: insert
		* Pre-conditions : T n
		* Post-conditions: none
		* 
		* Inserts the given value to tree 
		********************************************/
		void insert(T n) { 
			RBTNode<T> *newNode = new RBTNode<T>(n); 
			if (root == NULL) { 
			// when root is null 
			// simply insert value at root 
				newNode->color = BLACK; 
				root = newNode; 
			} else { 
			RBTNode<T> *temp = search(n); 
			
				if (temp->value == n) { 
				// return if value already exists 
				return; 
			} 
			
			// if value is not found, search returns the node 
			// where the value is to be inserted 
			
			// connect new node to correct node 
				newNode->parent = temp; 
			
				if (n < temp->value) 
				temp->left = newNode; 
				else
					temp->right = newNode; 
			
			// fix red red voilaton if exists 
				fixRedRed(newNode); 
			} 
		} 
			
		/********************************************
		* Function Name	: printInOrder
		* Pre-conditions : none
		* Post-conditions: none
		* 
		* Prints an in-order traversal of the tree
		********************************************/
		void printInOrder() { 
			std::cout << "Inorder: " << std::endl; 
			if (root == NULL) 
				std::cout << "Tree is empty" << std::endl; 
			else
				inorder(root); 
			std::cout << std::endl; 
		} 
			
		/********************************************
		* Function Name	: printLevelOrder
		* Pre-conditions : none
		* Post-conditions: none
		* 
		* Prints level order of the tree 
		********************************************/
		void printLevelOrder() { 
			std::cout << "Level order: " << std::endl; 
			if (root == NULL) 
				std::cout << "Tree is empty" << std::endl; 
			else
				levelOrder(root); 
			std::cout << std::endl; 
		}

		void deleteByVal(T n) {

			if (root==NULL)
				return;

			RBTNode<T> *u = search(n);

	 		if (u->value != n) {
				std::cout << "No node found to delete with value: " << n << std::endl;
				return;
			}

			deleteNode(u);
		}

		RBTNode<T>* successor(RBTNode<T>*& x ) {

			RBTNode<T> *temp = x;

			while( temp->left != NULL)
				temp = temp->left ;

			return temp;
		}

		RBTNode<T>* BSTreplace(RBTNode<T>*& x ) {
		
			// when nodes have 2 children, recursively call right successor
			if (x->left != NULL and x->right != NULL)
				return successor(x->right);

			// when leaf
			if (x->left == NULL and x->right == NULL)
				return NULL;

			// when single child
			if (x->left != NULL)
				return x->left;
			else
				return x->right ;
		} 
};

#endif
