/*
	Prototypes of the sorting functions
*/

void fill_array(int* array,int size);
void swap(int* a, int* b);
void selection_sort(int* array, int size);
void insertion_sort(int* array, int size);
void bubble_sort(int* array, int size);
void shell_sort(int* array, int size);
int partitioning(int* array, int p, int r);
void quick_sort(int* array, int p, int r);
void merge_sort(int* array, int left, int right);
void merge(int* array, int left, int m, int right);
void heap_sort(int* array, int size);
void display(int* array, int size);
