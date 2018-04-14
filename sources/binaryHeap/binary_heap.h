#include <iostream>
#include <cstdlib>

class MinHeap{
	int *array;
	int size;
	int capacity;

public:
	MinHeap(int capacity);
	MinHeap(const MinHeap &heap);

	int parent(int i) { return (i-1)/2; }
	int left_child(int i){ return i*2 + 1; }
	int right_child(int i){ return i*2 + 2; }

	void randomFill();
	int extractRoot(); 
	void _delete (int i);
	void insert (int k);
	void restoreHeap (int i);
	void decrease (int i, int new_val);
	void toString();
	int* sort();
	void swap(int *x, int *y);
	int getMin();
};
