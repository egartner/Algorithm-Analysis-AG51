#include <cstdlib>
#include <iostream>
#include <utility>
#include <random>
#include <mutex>

#include "hashmap.h"

using namespace std;

/* Constructor */
HashTable::HashTable(int size){
	this->size = size;
	bucket = new std::pair<int,int>[size];
}

/* Hash function */
int HashTable::hash (int key){
	return key % this->size;
}

/* Randomly fill the hash table */
void HashTable::randomFill(int n){
	//std::lock_guard<std::mutex> lock(mutex);
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(0,n/2);

	for(int i = 0; i < n ; ++i){
		this->insert(distr(eng));
	}

	cout << "Filled the hash table" << endl;
}

/* Insertion */
void HashTable::insert(int key){
	//std::lock_guard<std::mutex> lock(mutex);

	int hash_value = hash(key);
	int i = hash_value;

	while(bucket[i].second == 1){
		if(bucket[i].first == key){
			cout << " Duplicate item " << endl;
			break;
		}
		i = HashTable::hash(i + i * i);
		if(i == hash_value){
			cout << "No space left in the table" << endl;
			break;
		}
	}

	bucket[i].first = key;
	bucket[i].second = 1;
}

/* Search */
int HashTable::search(int key){
	//std::lock_guard<std::mutex> lock(mutex);
	int hash_value = hash(key);
	int i = hash_value;	

	while(bucket[i].first != key){
		i = HashTable::hash(i + i * i);
		cout << i << endl;
		if(i == hash_value || i == 0){
			cout << "This element does not exist" << endl;
			break;
		}
	}
	
	if (bucket[i].second != 0){
		return i;
	}
	else return -1;
}

/* Delete */
void HashTable::_delete(int key){
	//std::lock_guard<std::mutex> lock(mutex);
	int i = search(key);
	bucket[i].second = 0;
}

void HashTable::display(){
	for(int i=0 ; i<this->size ; i++){
		cout << " Adresse N° : " << i << " Clé : " << bucket[i].first << endl;
	}
}
