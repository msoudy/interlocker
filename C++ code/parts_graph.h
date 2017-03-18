// TO-DO LIST:
// √Construct part-graph for different furniture: starting from the chair
// Separate overlapping cycles and create LIGs
// Find the key and local interlocking state for LIGs

// Data structure:
// undirected graph

#include <iostream>
#include <vector>
#include <list>
#include <limits.h>
using namespace std;

#define FINISHED -1
#define NOCYCLE -2

// Class for an undirected graph
class Graph
{
private:
    int V;    // No. of vertices
    int index;
    list<int> *adj;    // Pointer to an array containing adjacency lists
    std::vector<std::vector<int>> cycles;
    
public:
    Graph(int V);   // Constructor
    ~Graph();       // Destructor
    void addEdge(int v, int w);   // to add an edge to graph
    void setLIGs(std::vector<int>);
    void printLIGs();
//    void isCycle();
//    void isCyclicUtil(int v,bool visited[],int parent);
};
