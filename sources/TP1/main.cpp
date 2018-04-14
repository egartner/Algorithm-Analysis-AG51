#include <cstdlib>
#include <iostream>
#include <fstream>
#include <chrono>

#include "sort.h"
#define N 2000 // size of the array to be sorted

using namespace std;

int main(int argc, const char * argv[]){
	
	/* Create a table filled with random numbers */
	int size = atoi(argv[1]) * 1000;
	int *array = new int[size];
	fill_array(array, size);
	ofstream result;
	
	/* Measure the execution time of a sorting algorithm on the array */
	auto start = std::chrono::high_resolution_clock::now();
	heap_sort(array, size);
	auto finish = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsed = finish - start;
	
	/* Write the result in a file */
	result.open("heap.csv", std::ios_base::app | std::ios_base::out);
	result << size << ", " <<  elapsed.count() << "\n";
	result.close();
}
