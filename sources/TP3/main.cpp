#include <iostream>
#include <cstdlib>
#include <thread>
#include <mutex>
#include <chrono>
#include <fstream>
#include <vector>
#include <random>
#include <string>
#include <unordered_map>

#include "hashmap.h" 

void read(){
}

void write(){
}

using namespace std;

int main(int argc, char *argv[]){
	/* Create the hashtable, vector and std hashtable */
	int size = atoi(argv[1]) * 1000;
	HashTable *h = new HashTable(size);
	//h->randomFill(size); //Randomly fill the hashtable
	std::vector<int> array(size+1);
	std::unordered_map<string,int> map;

	for (int i = 0 ; i < size ; ++i){
		array.push_back(i);
		map.emplace(std::to_string(i),i);
	}

	ofstream result;

	/* Use this for thread synchronization
	
	std::thread reader(read);
	std::thread writer(write);

	reader.join();
	writer.join();*/

	/*
	 * Complexity measures and output
	 */
	auto start = std::chrono::high_resolution_clock::now();
	map.erase(std::to_string(size/2));
	auto finish = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsed = finish - start;

	result.open("C++map_delete.csv", std::ios_base::app | std::ios_base::out);
	result << size << ", " << elapsed.count() << "\n";
	result.close();

	return 0;
}
