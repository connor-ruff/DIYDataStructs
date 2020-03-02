/**********************************************
* File: DLList.h
* Author: Matthew Morrison
* Email: matt.morrison@nd.edu
* 
* This file contains the function definitions and 
* structs for a Linked List Data structure 
**********************************************/

#ifndef DLLIST_H
#define DLLIST_H

#include <cstdlib>
#include <iostream>
#include <unordered_map>

template<class T>
class DLList{
	
	private:
	
		/* NODE contains the data and a pointer to the next node */
		struct node
		{
			T     data;
			node* next;
			node* prev;
			
			void checkMemory(){
				
				if (this == NULL)
				{
					std::cerr <<  "Out of Memory" << std::endl;
					exit (-1);
				} 
				
			}
			
			node() : data(), next(NULL), prev(NULL) {
				
				// Check to ensure address properly allocated
				checkMemory();
				
			}
			
			
			node(T dataIn) : data(dataIn), next(NULL), prev(NULL) {
				
				// Check to ensure address properly allocated				
				checkMemory();
				
			}
			

			~node(){
				
				delete next;
				
			}
			

			node(const node& copy){
				data = copy.data;
				next = copy.next;
				prev = copy.prev;
			}
			
			
			node& operator=(const node& assign){
				
				if(this != &assign){
					this->data = assign.data;
					this->next = assign.next;
					this->prev = assign.prev;
				}
				return *this;
			}
			
			
			node* operator=(const node* assign){
				
				if(this != (void *)&assign){
					this->data = assign->data;
					this->next = assign->next;
					this->prev = assign->prev;
				}
				return *this;
			}
			
			
			bool operator!=(const node* rhs){
				
				return this != (void *)&rhs;
				
			}
			
		};
		
		node* head;	// Head pointer for Singly-Linked List
		node* tail; // Tail point for Doubly-Linked List
		
	public:
	
		DLList() : head(NULL), tail(NULL) {}
		
		
		~DLList(){
			
			delete head;

		}
		
		
		DLList(const DLList<T>& copy) : head(NULL), tail(NULL) {
			
			node* prev = NULL;
			node* curr = copy.head;
			
			while(curr != NULL){
				
				Insert(curr->data);
					
				prev = curr;
				curr = curr->next;
				
			}

		}
	
		DLList<T>& operator=(const DLList<T>& assign){
				
			if(this != &assign){
				
				node* prev = NULL;
				node* curr = assign.head;
				
				while(curr != NULL){
					
					this->Insert(curr->data);
						
					prev = curr;
					curr = curr->next;
					
				}
			}
			return *this;
			
		}

		void Insert (T value)
		{
		   node* temp = new node(value);

		   if ( IsEmpty() )
		   {
			   head = temp;
			   tail = temp;
		   }
		   else
		   {
			  node* prev =  NULL;
			  node* curr = head;

			  /* traverse the list until the end */
			  while (curr != NULL)
			  {
				 prev = curr;
				 curr = curr->next;
			  }
		  
			  /* insert the node, temp, at the end */
			  prev -> next = temp;
			  
			  /* Allocate the previous node */
			  prev -> next -> prev = prev;
			  
			  /* Allocate tail */
			  tail = prev -> next;
		   }
		}
		
		
		void push_front(T value){
			
			// Create new node
			node* temp = new node(value);
			
			// Set temp->next = head
			temp -> next = head;
			
			// Set head equal to temp
			head = temp;
			
		}
		
		
		void push_back(T value){
			
			if( IsEmpty() ){
				Insert( value );
			}
			else{
				
				node* temp = new node(value);
				
				temp->prev = tail;
				
				tail->next = temp;
				
				tail = temp;
				
			}
			
			
		}


		bool Delete (T target)
		{
		   node* temp = new node(); node* prev = new node(); node* curr = new node();

		   if (IsEmpty ())
		   {
			  std::cout << "Can't delete from an empty list" << std::endl;
			  return (-1);
		   }

		   /* if the target value is the first in the list, move head */
		   else if (target == head -> data)
		   {
			   
			   if( head == tail ){
				   temp = head;
				   head = NULL;
				   tail = NULL;
				   free(temp);
				   return true;
			   }
			   else{
			   
				  temp = head;
				  head = head -> next;
				  head->prev = NULL;
				  free (temp);
				  return true;
			  
			   }
		   }
		   
		   /* traverse the list until the target value is found */
		   else
		   {
			  prev = head;
			  curr = head -> next;

			  while (curr != NULL && curr -> data != target)
			  {
				 prev = curr;
				 curr = curr -> next;
			  }
			  
			  if(curr != NULL)
			  {
				/* delete the node the contains the target value */
				temp = curr;
				
				if(curr == tail){
					tail = prev;
				}
				
				prev -> next = curr -> next;
				free(temp);
				
				if(prev->next != NULL){
					
					prev->next->prev = prev;
				}
				
				return true;
			  }
			  else
			  {
				std::cout << target << " was not in the list" << std::endl;
				return false;
			  }
		   }      
		}


		bool IsEmpty () const{
			
			return head == NULL && tail == NULL;
		   
		}
		
		
		bool contains(const T& searchVal) const{

		   if (IsEmpty()) {
			   
			  return false;
			  
			}
			else{
				
				node* prev =  NULL;
				node* curr = head;
				
				while (curr != NULL && curr -> data != searchVal){
					prev = curr;
					curr = curr -> next;
				}

				return curr != NULL;
			}
		}
		
		
		// Student Code Goes Here
		void merge(DLList<T>& mergeList){
			
			if(this->IsEmpty() || mergeList.IsEmpty() ){
				
				std::cout << "A list is empty. No merge" << std::endl;
				return;
			}
			
			node* first_curr = this->head;
			node *second_curr = mergeList.head;
			
			mergeList.head = NULL;
			
			node* first_next;
			node* second_next;

			while(first_curr != NULL && second_curr != NULL){
			
				first_next = first_curr->next;
				second_next = second_curr->next;
				
				// Update the previous nodes 
				second_curr->prev = first_curr;
				
				// Update next nodes 
				first_curr->next = second_curr;
				
				if( first_next != NULL ){
					second_curr->next = first_next;
					first_next->prev = second_curr;
				}

				
				// Update curr and prev 
				first_curr = first_next;
				second_curr = second_next;
			
			}
			
			if( first_curr != this->tail ){
				this->tail = mergeList.tail;
			}
			
			mergeList.tail = NULL;
			
		}

		friend std::ostream& operator<<( std::ostream& output, const DLList<T>& theList ){
			
		   node* curr;

		   if (theList.IsEmpty())
		   {
			  output << "The list is empty";
		   }
		   else
		   {
			  /* set the current pointer to the first
			  ** node of the list */
			  curr = theList.head;

			  /* Until the end of the list */
			  while (curr != NULL)
			  {
				  /* print the current data item */
				  output << curr->data << " ";

				  /* move to the next node */
				  curr = curr -> next;
			  }
		   } 

		   return output;
		}

};

#endif
