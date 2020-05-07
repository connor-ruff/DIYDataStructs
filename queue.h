#ifndef QUEUE_H
#define QUEUE_H

#include<list>

template< class T >
class queue{

	private:
		std::list<T> list;
		unsigned int max_len;
		unsigned int queueSize;

	public:
		
		// Default Constructor
		queue() : list(), max_len(-1), queueSize(0) {}

		// Constructor With Limited Queue Size
		queue(unsigned int max) : list(), max_len(max), queueSize(0) {}

		// Accessor Methods
		unsigned int max_size() {
			return max_len ; 
		}
		unsigned int size() {
			return queueSize;
		}
		bool empty(){
			return queueSize == 0;
		}

		// Push Method
		void push( T elem) {
			if (queueSize < max_len) {
				list.push_back(elem);
				queueSize++;
			}
		}

		// Pop Method
		void pop() {
			if ( queueSize > 0){
				list.pop_front();
				queueSize--;
			}
		}

		// Front and Back Methods
		T& front() {
			return list.front();
		}
		T& back() {
			return list.back();
		}

};
#endif
