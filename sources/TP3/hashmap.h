#include <cstdlib>
#include <utility>
#include <vector>
#include <mutex>

class HashTable {
	int size;
	std::pair<int, int> *bucket;
	mutable std::mutex mutex;

public:
	HashTable (int size);
	int hash (int key);
	void insert(int key);
	void _delete(int key);
	int search(int key);
	void display();
	void randomFill (int n);
};
