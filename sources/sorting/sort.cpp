#include <stdio.h>
#include <stdlib.h>
#include <random>
#include <iostream>
#include <limits>
#include "sort.h"

using namespace std;

/*
	Fill an array with random numbers
*/
void fill_array(int * array, int size){

	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(0,1000);
	for(int i = 0; i <= size; ++i){
		array[i] = distr(eng);
	}

}

/*
	Swap two values inside an array using their positions given in parameters
*/ 
void swap(int * array, int i, int j){

	int buffer = array[i];
	array[i] = array[j];
	array[j] = buffer;

}

/*
	Sort an array in ascending order using the selection sort algorithm
*/
void selection_sort(int * array, int size){

	int N = size;
	int i,j;
	int min;

	for (i = 0; i <= N-2; ++i){
		min = i;
		for (j = i+1; j <= N-1; ++j){
			if (array[j] < array[min])
				min = j;
		}
		if (min != i)
			swap(array, i, min);
	}
}

/*
	Sort an array in ascending order using the insertion sort algorithm
*/
void insertion_sort(int * array, int size){

	int i, j;
	int val;
	int N = size;

	for (i=1; i<= N-1; ++i){
		j = i;
		val = array[i];
		while(j > 0 && array[j-1] > val){
			array[j] = array[j-1];
			j = j-1;
		}
		array[j] = val;
	}
}

/*
	Sort an array in ascending order using the bubble sort algorithm
*/
void bubble_sort(int * array, int size){

	int N = size;
	int i,j,k;

	i = N-1;
	while (i >= 1){
		k = 0;
		for(j = 1; j <= i; ++j){
			if(array[j-1] > array[j]){
				swap(array, j-1, j);
				k = j-1;
			}
		}
		i = k;
	}
}

/*
	Sort an array in ascending order using the shell sort algorithm
*/
void shell_sort(int * array, int size){

	int N = size;
	int pas, i, j, val;

	pas=0;
	while(pas < N){
		pas = 3 * pas + 1;
	}

	while (pas != 0){
		pas = pas/3;
		for(i = pas; i < N; ++i){
			val = array[i];
			j = i;
			while( (j > (pas-1)) && (array[j-pas] > val)){
				array[j] = array[j-pas];
				j = j-pas;
			}
			array[j] = val;
		}
	}
}

/*
	Divide an array into two sub-arrays: the value returned is the position at which the array will be "cut" into two sub-arrays in the quick_sort function. 
*/
int partitioning(int * array, int p, int r){
	int i, j;
	int pivot = array[p];
	i = p;
	j = r;

	while (array[j] > pivot){
		--j;
	}

	while (i < j){
		if(i < j){
			swap(array, i, j);
			i++;
			j--;
		}

		while(array[j] > pivot){
			--j;
		}

		while(array[i] < pivot){
			++i;
		}
	}

	return j;
}

/*
	Sort an array in ascending order using the quick sort algorithm.
*/
void quick_sort(int * array, int p, int r){

	int q;
	if (p < r){
		q = partitioning(array, p, r);
		quick_sort(array, p, q);
		quick_sort(array, q+1, r);
	}
}

/*
	Sort an array in ascending order using the merge sort algorithm
*/
void merge_sort(int * array, int left, int right){
	if(left < right){
		int m = (left+right)/2;
	
		merge_sort(array, left, m);
		merge_sort(array, m+1, right);
		merge(array, left, m, right);
	}
}

/*
	Merge two sorted arrays into one sorted array (ascending order).
*/
void merge(int *array, int l, int m, int r){
	int size_left = m - l + 1;
	int size_right = r - m;
	int i, j, k;
	int *array_left = new int[size_left + 1];
	int *array_right = new int[size_right + 1];
	
	for(i = 0; i < size_left ; ++i){
		array_left[i] = array[l + i];
	}
	for(j = 0; j < size_right; ++j){
		array_right[j] = array[m + j + 1];
	}

	array_left[size_left] = std::numeric_limits<int>::max();
	array_right[size_right] = std::numeric_limits<int>::max();	

	i = 0;
	j = 0;
	for (k = l; k <= r; k++){
		if(array_left[i] < array_right[j]){
			array[k] = array_left[i];
			i++;
		}
		else{
			array[k] = array_right[j];
			j++;
		}
	}
}

/*
	Build a binary heap at root i in a given array.
*/
void heapify(int * array, int size, int i){
	int max = i;
	int left_child = 2*i+1;
	int right_child = 2*i+2;
	if(left_child < size && array[left_child] > array[max])
		max = left_child;
	if(right_child < size && array[right_child] > array[max])
		max = right_child;

	if(max != i){
		swap(array, i, max);
		heapify(array, size, max);
	}
}

/*
	Sort an array in ascending order using the heap sort algorithm.
*/
void heap_sort(int * array, int size){
	for(int i = (size/2)-1 ; i >= 0 ; i--){
		heapify(array, size, i);
	}
	
	for(int i = size-1 ; i>= 0 ; i--){
		swap(array[0], array[i]);
		heapify(array, i, 0);
	}
}

/*
	Display the content of an array.
*/
void display(int * array, int size){
	for(int i=0; i<size; ++i){
		std::cout << array[i] << std::endl;
	}
}
