#ifndef STACK_H
#define STACK_H

#include<forward_list>

template<class T>
class stack {

	private:

		std::forward_list<T> list;
		unsigned int max_len ;
		unsigned int stackSize ;

	public:

		// Default
		stack() : list(), max_len(-1), stackSize(0) {}
		// Constructor
		stack(unsigned int max) : list(), max_len(max), stackSize(0) {}

		unsigned int max_size() {
			return max_len ;
		}

		unsigned int size() {
			return stackSize ;
		}

		bool empty() {
			return stackSize == 0;
		}

		void push( T elem) {

			if (stackSize < max_len) {
				list.push_front(elem);
				++stackSize;
			}
		}

		void pop() {
			if (stackSize > 0) {
				list.pop_front();
				stackSize--;
			}
		}

		T& top() {
			return list.front();
		}




};

#endif
