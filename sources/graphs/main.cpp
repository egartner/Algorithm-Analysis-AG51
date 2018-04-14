#include <cstdlib>
#include <iostream>
#include <fstream>
#include <chrono>
#include <random>

#include "graph.h"

using namespace std;

int main (int argc, char * argv[]){
	int size = atoi(argv[1]);
	ofstream result;

	Graph graph(size);

	/*
	 * Initialize a random graph
	 */
	auto gen = std::bind(std::uniform_int_distribution<>(0,1),std::default_random_engine());
	auto genw = std::bind(std::uniform_int_distribution<>(0,100),std::default_random_engine());
	for (int i = 0; i < size; ++i){
		for (int j = i+1 ; j < size ; ++j){
			bool b = gen();
			int w = genw();
			if (b == true){
				graph.addEdge(i, j, w);
			}
		}
	}

	graph.kruskal(size);
	/*
	 * Complexity measures and output
	 *
	 
	auto start = std::chrono::high_resolution_clock::now();
	graph.kruskal();
	auto finish = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsed = finish - start;
	result.open("kruskal_sort.csv", std::ios_base::app | std::ios_base::out);
	result << size << ", " << elapsed.count() << "\n";
	result.close();
	*/

	return 0;
}
