#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "Vertex.h"
#include "MSTElem.h"

#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include<unordered_map>

template<class T>
class Graph{
	
	private:
	
		std::vector< Vertex< T > > verticies;
		bool bi_directional;
	
	public:
	
		Graph( bool bi_direct ) : verticies(), bi_directional(bi_direct) {}
		
		
		void add_vertex( T vertexData ){
			
			Vertex<T> theVertex( vertexData );
			
			verticies.push_back( theVertex );
			
		}
		
		
		void add_edge(unsigned int origin, unsigned int destin, int weight ){
			
			if( origin < verticies.size() && destin < verticies.size() ){
			
				verticies.at(origin).add_edge( destin, weight );
				
				if( bi_directional ){
					
					verticies.at(destin).add_edge( origin, weight );
				}
			}
			else{
				std::cout << "Unable to add edge. Edge outside graph bounds\n";
			}
		}
		
		
		bool get_vertex_value( unsigned int vertex, T& value ){
			
			bool validVertex = false;
			
			if( vertex < verticies.size() ){
				
				validVertex = true;
				value = verticies.at(vertex).get_vertex_value();
				
			}
			
			return validVertex;
			
		}
		
		
		void set_vertex_value( unsigned int vertex, T& value ){
						
			if( vertex < verticies.size() ){
				
				value = verticies.at(vertex).set_vertex_value( value );
				
			}
						
		}
		
		bool adjacent( unsigned int origin, unsigned int destin ){
			
			if( origin < verticies.size() && destin < verticies.size() ){
				
				for(unsigned int i = 0; i < verticies.at(origin).num_edges(); i++){
					
					if(verticies.at(origin).get_edge().destin == destin){
						
						return true;
					}
				}
				
				return false;
			}
			else{
				
				return false;
			}
			
		}
		
		
		void neighbors( unsigned int vertex ){
			
			if( vertex < verticies.size() ){
				
				std::cout << "Vertex " << vertex << " had edges going to: ";
				
				for(unsigned int i = 0; i < verticies.at(vertex).num_edges(); i++){
					
					std::cout << verticies.at(vertex).get_edge().destin << ", ";

				}	
				std::cout << std::endl;
				
			}
			else{
				
				std::cout << vertex << " exceeds graph capacity\n";
			}
			
		}


		bool get_edge_value( unsigned int origin, unsigned int destin,
			int& weight){
				
			if( origin < verticies.size() && destin < verticies.size() ){
				
				verticies.at(origin).get_edge_value( destin, weight );
				return true;
				
			}
			
			return false;
				
		}

		bool set_edge_value( unsigned int origin, unsigned int destin,
			int weight){
				
			if( origin < verticies.size() && destin < verticies.size() ){
				
				verticies.at(origin).set_edge_value( destin, weight );
				
				if( bi_directional ) {
					
					verticies.at(destin).set_edge_value( origin, weight );

				}
				
				return true;
				
			}
			
			return false;
				
		}
		
		
		void remove_edge( unsigned int origin, unsigned int destin){
				
			if( origin < verticies.size() && destin < verticies.size() ){
				
				verticies.at(origin).remove_edge( destin );
				
				if( bi_directional ) {
					
					verticies.at(destin).remove_edge( origin );

				}
				
				return;
				
			}
			
			return;
				
		}
		
	
		friend std::ostream& operator<<( std::ostream& out, const Graph<T>& g){
			
			for( unsigned int i = 0; i < g.verticies.size(); i++ ){
				
				out << "{" << i << ", " << g.verticies.at(i).get_vertex_value() << "} ";
				
				for( unsigned int j = 0; j < g.verticies.at(i).num_edges(); j++ ){
					
					Edge tempEdge = g.verticies.at(i).get_edge(j);
					
					std::cout << "(" << tempEdge.destin << ", ";
					std::cout << tempEdge.weight << "), ";
				}
				
				out << std::endl;
			}
			
			return out;
		}

		void remove_vertex(unsigned int vertexLoc){

			if( vertexLoc < verticies.size() ) {

				verticies.erase(verticies.begin() + vertexLoc ) ;

				for (unsigned int i =0; i < verticies.size(); i++){

					verticies.at(i).removeAndUpdateEdges(vertexLoc);
				}
			}
		}

		void BFS(unsigned int destin) {

			// Check if graph is valid
			if (destin < verticies.size() && verticies.size() > 0) {

				// Strucutres to be used for the BFS traversal
				std::queue<unsigned int > theQueue;
				unsigned int * parents = new unsigned int[verticies.size()] ;
				bool * visited = new bool[verticies.size()];
				std::stack< unsigned int > finalPath;

				// Initialize Search
				bool found = false;
				theQueue.push(0);
				parents[0] = -1;
				visited[0] = true;

				// Destination is origin
				if(destin == 0){
					found = true;
					finalPath.push(0);
				}

				// Destination is not origin in node
				while ( !found && theQueue.size() < verticies.size()){

					unsigned int vertex = theQueue.front();
					theQueue.pop();

					for(unsigned int i =0; i < verticies.at(vertex).num_edges(); i++){

						Edge tempEdge = verticies.at(vertex).get_edge(i);

						if (!visited[tempEdge.destin]  ) {
	
							visited[tempEdge.destin] = true;
							parents[tempEdge.destin] = vertex ;

							if(tempEdge.destin == destin){
								found = true ;
								finalPath.push(destin) ;
								break ;
							}
							else
								theQueue.push(tempEdge.destin);
						}
					}
				}


				// Print exisiting path
				if(found){
					unsigned int parent = parents[destin];

					while( parent != -1){
						finalPath.push(parent);
						parent = parents[parent];
					}

					std::cout << "The path from " << verticies.at(0).get_vertex_value();
					std::cout << " to " << verticies.at(destin).get_vertex_value() << " is: " ;


					while ( !finalPath.empty()){
						std::cout << verticies.at(finalPath.top()).get_vertex_value() << ", ";
						finalPath.pop();
					}

					std::cout << std::endl;
				}
				else
					std::cout << "No Path Exists\n";
			

			}
			else
				std::cout << "Vertex " << destin << " is not a valid vertex in the graph\n";
		}


		Graph<T> MST() {

			Graph<T> MSTGraph(false) ;
			std::priority_queue< MSTElem> MST_PQ ;
			std::unordered_map< unsigned int, bool> frontier ;
			unsigned int* parents = new unsigned int [verticies.size()];
			int* weights = new int[verticies.size()];

			// Initialize Values
			MSTElem origin(0, 0);
			MST_PQ.push(origin);
			frontier.insert( {0, true} );
			parents[0] = -1;
			weights[0] = -2147483648 ;
			
			for( unsigned int i = 1; i < verticies.size(); ++i) {
				MSTElem temp(i, 2147483647 );
				weights[i] = 2147483647 ;
				MST_PQ.push(temp);
				frontier.insert( {i, true} );
			}

			while ( !MST_PQ.empty() ) {
				
				MSTElem currElem = MST_PQ.top() ;
				Vertex<T> currVert = verticies.at(currElem.index) ;
				MST_PQ.pop();

				frontier[currElem.index] = false ;

				for( unsigned int i = 0; i < currVert.num_edges(); ++i){

					Edge currEdge = currVert.get_edge(i);
					
					if (currEdge.weight < weights[currEdge.destin] && frontier[currEdge.destin] ) {
					
						weights[currEdge.destin] = currEdge.weight;
						parents[currEdge.destin] = currElem.index;

						MSTElem pushElem(currEdge.destin, currEdge.weight) ;
						MST_PQ.push(pushElem);
					}
				}
			}

			// Create MST

			for(unsigned int i = 0; i < verticies.size(); ++i){
				MSTGraph.add_vertex( verticies.at(i).get_vertex_value() ) ;
			}

			for(unsigned int i = 0; i < verticies.size(); ++i){
				if( parents[i] != -1) {
					MSTGraph.add_edge(parents[i], i, weights[i] );
				}
			}


			return MSTGraph;
		}	
	
};

#endif
