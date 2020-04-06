#ifndef DYNARR_H
#define DYNARR_H

template<class T>
class DynArr{
	
		private:
		
			unsigned int size;
			unsigned int capac;
			T* data;	
			

			void copy(T* destin, T* origin, int len){
				
				for(unsigned int iter = 0; iter < len; ++iter){
					
					*(destin+iter) = origin[iter];
				}
			}

		
		public:

			// Constructor
			DynArr(const int sizeIn = 0) : 
				size(sizeIn), capac(sizeIn ? sizeIn : 8),
				data(new T[capac]) { }

			// Destructor
			~DynArr() {   
		   		delete [] data;	}

			// Assign Operator
			DynArr<T>& operator=(const DynArr<T>& assign) {
				if ( this != &assign) {
					size = assign.size;
					capac = assign.capac;
					data = new T[capac] ;

					copy(data, assign.data, size);
				}

				return *this;
			}

			// Copy Constructor
			DynArr(const DynArr<T>& C) : 
				size(C.size), capac(C.capac),data(new T[capac]) {
					copy(data, C.data, C.size);
				}



			T& begin(){
				
				return data[0];
			}
			
			const T& begin() const{
				
				return data[0];
			}

			T& end(){
				
				return data[size - 1];
			}
			
			const T& end() const{
				
				return data[size-1];
			}	
			
			unsigned int length() const{
				return size;
			}
			
			unsigned int capacity() const{
				return capac;
			}
			
			// Access Operator
			T& operator[](const unsigned int i) {
				return data[i];
			}
			const T& operator[](const unsigned int i) const{
				return data[i];
			}

			void push_back(const T& value){
				if(size >= capac) {
					capac = capac*2;
					T* tmp = new T[capac];
					copy(tmp,data,size);
					delete [] data;
					data = tmp;
				}

			data[size] = value;
			size ++;
			}

			void erase(unsigned int e) {

				//Check If We Are In Proper Range
				if (e >= size) { return; }
				// Cut capacity in half if we can
				if (size-1 == capac /2) {capac = capac /2; }

				T* temp = new T[capac];

				// Erase the Element
				unsigned int temp_iter = 0;
				for(unsigned int data_iter = 0; data_iter < capac; ++data_iter){
					//
					if( data_iter != e) {
						temp[temp_iter] = data[data_iter] ;
						temp_iter++;
					}
				}

				delete [] data;
				data = temp;
				--size;
			}

	
};

#endif
