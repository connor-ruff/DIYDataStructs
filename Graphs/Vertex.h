#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include <iostream>
#include "Edge.h"

template<class T>
class Vertex{

	private:
	
		std::vector< Edge > edges;
		T data;
	
	public:
	
		Vertex( const T& dataIn ) : edges(), data( dataIn ) {}
		
		void add_edge( unsigned int destin, int weight ){
			
			edges.push_back( Edge(destin, weight) );
			
		}
		
		bool remove_edge( unsigned int edgeLoc ){
			
			bool deleted = false;
			
			for(unsigned int i = 0; i < edges.size(); i++){
				
				if( edges.at(i).destin == edgeLoc ){
					edges.erase(edges.begin()+i);
					deleted = true;
				}
			}
			
			return deleted;
		}
		
		T get_vertex_value() const{
			
			return data;
		}
		
		void set_vertex_value(const T& dataIn){
			
			data = dataIn;
		}
		
		Edge get_edge( unsigned int edgeOrder ) const{
			
			return edges.at( edgeOrder );
		}

		void removeAndUpdateEdges( unsigned int vertexLoc ){

			for(unsigned int i = 0; i < edges.size(); i++){
				
				if( edges.at(i).destin == vertexLoc){
					
					edges.erase( edges.begin() + i );
					i--;
				}
				else if ( edges.at(i).destin > vertexLoc ){
					
					edges.at(i).destin--;
				}
				
			}

		}
		
		unsigned int num_edges() const{
			
			return (unsigned int)edges.size();
		}
		
		bool get_edge_value( unsigned int destin, int& weight) const{
			
			bool edgeFound = false;
			
			for( unsigned int i = 0; i < edges.size(); i++){
				
				if( edges.at(i).destin == destin ){

					edgeFound = true;
					weight = edges.at(i).weight;
				}					
				
			}
			
			return edgeFound;
		}
		
		bool set_edge_value( unsigned int destin, int weight) {
			
			bool edgeFound = false;
			
			for( unsigned int i = 0; i < edges.size(); i++){
				
				if( edges.at(i).destin == destin ){

					edgeFound = true;
					edges.at(i).weight = weight;
				}					
				
			}
			
			return edgeFound;
		}


		

};

#endif
