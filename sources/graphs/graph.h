#include <cstdlib>
#include <list>
#include <utility>
#include <vector>
#include <tuple>
#include <iostream>
#include <climits>
#include <algorithm>
#include <queue>
#include <functional>
#include <stack>
#include <random>
#include <fstream>
#include <chrono>

enum Color {WHITE, GRAY, BLACK};

struct Vertex{
	Color color;
	int distance;
	int predecessor;
};

struct set
{
	int rep;
	int rank;
};

class DisjointSets{
	struct set *subsets;
public:
	DisjointSets(int n);
	void makeSet(int x);
	int findSet(int x);
	void _union(int x, int y);
	void link (int x, int y);
};

class Graph {
	int nbVertex;
	int nbEdge;
	Vertex *vertex;
		
	std::list<std::pair<int,int>> *adj;
	std::vector<std::tuple<int,int,int>> edgeVector;
	
public:
	Graph(int size);
	void randomGen();
	void DFSInit(int n);
	void DFS(int n);
	void DFSVisit(int n, int time);
	void BFS(int n);
	void addEdge(int v, int w, int cost);
	std::vector<std::tuple<int,int,int>> sortEdges();
	static int compare(std::tuple<int,int,int> a, std::tuple<int,int,int> b);
	void kruskal(int s);
	void prim(int vertex);
};
