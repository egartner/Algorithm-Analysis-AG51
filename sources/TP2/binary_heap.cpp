#include <iostream>
#include <cstdlib>
#include <climits>
#include <random>
#include "binary_heap.h"

using namespace std;

/*
	Binary heap constructor: the argument required is the capacity of the heap (i.e. the maximum number of elements the heap can contain
*/
MinHeap::MinHeap(int cap){
	size = 0;
	capacity = cap;
	array = new int[cap];
}

/*
	Binary heap copy constructor: we create a heap identical to the one given as parameter
*/
MinHeap::MinHeap(const MinHeap &heap){
	this->size = heap.size;
	this->capacity = heap.capacity;
	this->array = new int[heap.capacity];

	for(int i=0; i<size; i++){
		this->insert(heap.array[i]);
	}
}

void MinHeap::randomFill(){
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(0,1000);
	for(int i=0; i < capacity-2; ++i){
		this->insert(distr(eng));
	}
}

/*
	Insert a new element into the list
*/
void MinHeap::insert(int k){
	if (size == capacity){
		cout << "Maximum Capacity reached: can not insert" << endl;
		return;
	}
	else{
		size++;
		int i = size-1;
		array[i] = k;
		while (array[parent(i)] > array[i] && i!=0){
			swap(&array[i], &array[parent(i)]);
			i = parent(i);
		}
	}
}

/*
	Remove the minimum element (root) from the heap
*/
int MinHeap::extractRoot(){
	int root = array[0];
	array[0] = array[size-1];
	size--;
	restoreHeap(0);
	
	return root;
}

/*
	Set the value of an element to a new lower value
*/
void MinHeap::decrease(int i, int new_val){
	array[i] = new_val;
	while ( array[i] > array[parent(i)] && i!=0){
		swap(&array[i], &array[parent(i)]);
		i = parent(i);
	}
}

/*
	Delete an element from the heap
*/
void MinHeap::_delete(int i){
	decrease(i, INT_MIN);
	extractRoot();	
}

/*
	Convert a binary subtree (starting at the root i given as argument) into a binary min-heap
*/
void MinHeap::restoreHeap(int i){
	int l = left_child(i);
	int r = right_child(i);
	int smallest = i;
	if (l < size && array[l] < array[i])
		smallest = l;
	if (r < size && array[r] < array[smallest])
		smallest = r;
	if (smallest != i){
		swap(&array[i], &array[smallest]);
		restoreHeap(smallest);
	}
}

/*
	Display the heap
*/
void MinHeap::toString(){
	for(int i=0; i < size; i++){
		cout << array[i] << endl;
	}
}

/*
	Swap two elements
*/
void MinHeap::swap(int *x, int* y){
	int temp = *x;
	*x = *y;
	*y = temp;
}

/*
	Return a sorted array in ascending order
*/
int* MinHeap::sort(){
	int* sorted_array = new int[size];
	MinHeap buffer = *this;
	int i = 0;
	while (buffer.size!=0){
		++i;
		sorted_array[i] = buffer.extractRoot();
	}
	return sorted_array;
}

int MinHeap::getMin(){
	return array[0];
}
