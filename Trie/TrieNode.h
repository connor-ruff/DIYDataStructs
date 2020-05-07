#ifndef TRIENODE_H
#define TRIENODE_H

#include "SorDynArr.h"

class TrieNode{

	private:
		char trieLetter;
		SorDynArr<TrieNode> childNodes;

	public:
		TrieNode(): trieLetter(), childNodes(0) {}
		TrieNode(char charIn) : trieLetter(charIn), childNodes(0) {}

		void addChild(char childChar){

			TrieNode temp(childChar);

			for(unsigned int iter=0; iter<childNodes.length(); iter++){

				if(childNodes[iter].getLetter() == childChar)
					return;
			}
			childNodes.Insert(temp);
		}


		TrieNode* getChildPtr(char childChar) {
			for(unsigned int iter = 0; iter < childNodes.length(); iter++)
				if(childNodes[iter].getLetter() == childChar)
					return &childNodes[iter] ;

			return NULL;
		}

		TrieNode* getChildPtrOrder(unsigned int index){
			return &childNodes[index];
		}

		char getLetter() const{
			return trieLetter;
		}

		unsigned int numChildren() const{
			return childNodes.length();
		}

		bool operator<(const TrieNode& rhs) const{
			return trieLetter < rhs.trieLetter;
		}
		bool operator<=(const TrieNode& rhs) const{
			return trieLetter <= rhs.trieLetter;
		}
		bool operator>(const TrieNode& rhs) const{
			return trieLetter > rhs.trieLetter;
		}
		bool operator>=(const TrieNode& rhs) const{
			return trieLetter >= rhs.trieLetter;
		}
		bool operator==(const TrieNode& rhs) const{
			return trieLetter == rhs.trieLetter;
		}

		friend std::ostream& operator<<(std::ostream& output, const TrieNode& TN){
			output << TN.trieLetter << " ";
			return output;
		}

};

#endif
