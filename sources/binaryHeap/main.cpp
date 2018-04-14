#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <vector>
#include <algorithm>
#include "binary_heap.h"

using namespace std;

int main(int argc, char *argv[]){
	int size = atoi(argv[1]) * 1000;
	MinHeap priority_queue(size); // Priority queue implemented with a min heap
	priority_queue.randomFill(); // Random fill of the heap
	std::vector<int> priority_queue_array(size); // Priority queue implemented with an array
	ofstream result;

	/* Random fill of the array */
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(0,1000);
	for(int i = 0; i < size-2 ; ++i){
		priority_queue_array[i] = distr(eng); 
	}
	/* Sort the array */
	std::sort(priority_queue_array.begin(), priority_queue_array.end());
	
	/* Measure execution time */
	auto start = std::chrono::high_resolution_clock::now();
	priority_queue_array.erase(priority_queue_array.begin()+size/2);
	std::sort(priority_queue_array.begin(), priority_queue_array.end());
	auto finish = std::chrono::high_resolution_clock::now();
	
	std::chrono::duration<double> elapsed = finish - start;
	
	/* Write the results in a file */
	result.open("ArrDelete.csv", std::ios_base::app | std::ios_base::out);
	result << size << ", " << elapsed.count() << "\n";
	result.close();

	return 0;
}
