#include "graph.h"

using namespace std;

/* The following methods implements disjoint set forests using union by rank and path compression */
DisjointSets::DisjointSets(int n){
	subsets = new struct set[n];
}

void DisjointSets::makeSet(int x){
	subsets[x].rep = x;
	subsets[x].rank = 0;
}

int DisjointSets::findSet(int x){
	if(subsets[x].rep != x)
		subsets[x].rep = findSet(subsets[x].rep);
	return subsets[x].rep;
}

void DisjointSets::_union(int x, int y){
	link(findSet(x), findSet(y));
}

void DisjointSets::link(int x, int y){
	if(subsets[x].rank > subsets[y].rank)
		subsets[y].rep = x;
	else{
		subsets[x].rep = y;
		if(subsets[x].rank == subsets[y].rank)
			subsets[y].rank++;
	}
}

Graph::Graph(int size){
	this->nbVertex = size;
	this->nbEdge = 0;
	this->vertex = new Vertex[nbVertex];
	this->adj = new std::list< std::pair<int,int> >[nbVertex];
}

void Graph::addEdge(int v, int w, int cost){
	adj[v].push_back(std::make_pair(w, cost));
	adj[w].push_back(std::make_pair(v, cost));
	edgeVector.push_back(std::make_tuple(v,w,cost));
	nbEdge++;
}

void Graph::randomGen(){
	
}

/*
 * Browse the graph using Depth First Search
 */
void Graph::DFS(int n){
	int time;
	for(int i = 0 ; i < nbVertex ; ++i){
		vertex[i].color = WHITE;
		vertex[i].predecessor = -1;
	}
	time = 0;
	for (int i = 0 ; i < nbVertex ; ++i){
		if(vertex[i].color == WHITE)
			DFSVisit(i, time);
	}
}

void Graph::DFSVisit(int n, int t){
	int time = t + 1 ;
	vertex[n].distance = time;
	vertex[n].color = GRAY;

	cout << n << endl;

	for(std::list< std::pair<int,int> >::iterator it=adj[n].begin(); it != adj[n].end(); ++it){
		if(vertex[(*it).first].color == WHITE){
			vertex[(*it).first].predecessor = n;
			DFSVisit((*it).first, time);
		}
	}
	vertex[n].color = BLACK;
	time++;
	vertex[n].distance = time;
}

/*
 * Browse the graph using Breadth First Search
 */
void Graph::BFS(int n){
	std::queue<int> queue;
	int u;
	/*
	 * Initialization : the unexplored nodes are white
	 */
	for(int i = 0 ; i < nbVertex ; ++i){
		vertex[i].color = WHITE;
		vertex[i].distance = std::numeric_limits<int>::max();
		vertex[i].predecessor = -1;
	}

	vertex[n].color = GRAY;
	vertex[n].distance = 0;
	vertex[n].predecessor = -1;

	queue.push(n);

	while (!queue.empty()){
		u = queue.front();
		queue.pop();

		cout << u << endl;
		/*
		 * Browse the adjacency list of the current edge: if a neighboring edge is unexplored, we enqueue it
		 */
		for(std::list< std::pair<int, int> >::iterator it=adj[u].begin(); it != adj[u].end(); ++it){
			if(vertex[(*it).first].color == WHITE){
				vertex[(*it).first].color = GRAY;
				vertex[(*it).first].distance += 1;
				vertex[(*it).first].predecessor = u;

				queue.push((*it).first);
			}
		}
		/*
		 * Once all the unvisited adjacent edges have been enqueued, we mark the current edge as explored
		 */
		vertex[u].color = BLACK;
	}
	cout << "Finished BFS" << endl;	
}

std::vector < std::tuple<int,int,int> > Graph::sortEdges(){
	std::vector < std::tuple<int,int,int> > sortedEdges;

	for(std::vector < std::tuple<int,int,int> >::iterator it = edgeVector.begin(); it != edgeVector.end() ; ++it){
		sortedEdges.push_back(*it);
	}
	std::sort(sortedEdges.begin(), sortedEdges.end(), compare);

	return sortedEdges;
}

int Graph::compare(std::tuple<int,int,int> a, std::tuple<int,int,int> b){
	return (std::get<2>(a) < std::get<2>(b));
}

/* Kruskal algorithm */
void Graph::kruskal(int s){
	std::vector < std::tuple<int,int,int> > sortedEdges = sortEdges();
	std::vector < std::tuple<int,int,int> > spanningTree;

	DisjointSets forest(this->nbEdge);

	for(int i = 0; i < nbVertex ; ++i){
		forest.makeSet(i);
	}
	
	for(std::vector < std::tuple<int,int,int> >::iterator it = sortedEdges.begin(); it != sortedEdges.end(); ++it){
		if(forest.findSet(std::get<0>(*it)) != forest.findSet(std::get<1>(*it))){
			forest._union(std::get<0>(*it),std::get<1>(*it));
			spanningTree.push_back(*it);	
		}
	}

	/*
	for(std::vector < std::tuple<int,int,int> >::iterator it = spanningTree.begin(); it != spanningTree.end(); ++it){
		cout << std::get<0>(*it) << " " << std::get<1>(*it) << endl;
	}
	*/
}

/* Prim Algorithm */
void Graph::prim(int vertex){
	std::priority_queue <std::pair<int,int>, std::vector< std::pair<int,int> >, std::greater<std::pair<int,int>>> queue;
	std::vector<int> key(nbVertex, INT_MAX);
	std::vector<int> parent(nbVertex, -1);
	std::vector<bool> inMST(nbVertex, false);
	int src = vertex;

	queue.push(make_pair(0,src));
	key[src] = 0;
	parent[src] = src;

	while(!queue.empty()){
		int u = queue.top().second;
		queue.pop();
		inMST[u] = true;

		for(list<std::pair<int,int>>::iterator it = adj[u].begin() ; it != adj[u].end(); ++it){
			int v = (*it).first;
			int weight = (*it).second;

			if(inMST[v] == false && weight < key[v]){
				key[v] = weight;
				queue.push(make_pair(key[v], v));
				parent[v] = u;
			}
		}
	}

	for(int i = 0; i < nbVertex ; ++i){
		cout << parent[i] << " " << i << endl;
	}
}



