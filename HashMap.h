#ifndef HASHMAP_H
#define HASHMAP_H

#include<iostream>
#include<vector>

enum States = {EMPTY, ACTIVE, DELETED};

template<class Key, class Value>
class HashMap {

	private:
		
		struct HashEntry {
			Key key;
			Value val;

			HashEntry() : key(), val(), state(EMPTY) {}
			HashEntry(std::pair<Key, Value> entry) : key(entry.first), val(entry.second), state(ACTIVE) {}
		}

		unsigned int numEntries; // Total Entries
		std::vector<HashEntry> array; // Vector of Entries

		// Returns Current Capacity of HashTable
		long unsigned int capacity() const{
			return array.capacity() ; // Built In <vector> method
		}
	
	public:
		
		HashMap(const unsigned int size =0) : numEntries(size), array() {
			array.resize( nextPrime(size) ); // TODO: NEXTPRIME FUNC
		}


};
