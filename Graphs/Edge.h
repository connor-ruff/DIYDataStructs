#ifndef EDGE_H
#define EDGE_H

struct Edge{
	
	unsigned int destin;
	int weight;

	Edge() : destin(), weight() {}

	Edge( unsigned int dest, int weightIn ) : destin(dest), weight(weightIn) {}
		
	
};

#endif