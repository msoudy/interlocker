#include "parts_graph.h"

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
    this->index = 0;
}


void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
    adj[w].push_back(v); // Add v to w’s list.
}

Graph::~Graph()
{
    delete []adj;
}

void Graph::setLIGs(std::vector<int> cycle)
{
    cycles.push_back(cycle);
}

void Graph::printLIGs()
{
    for (int i = 0; i < cycles.size(); i++)
    {
        for (int j = 0; j < cycles[i].size(); j++)
        {
            printf("%d ", cycles[i][j]);
        }
        printf("\n");
    }
}

//void Graph::isCycle()
//{
//    bool* visited = new bool[V];
//    
//    for(int i = 0; i < V; i++)
//        visited[i]=false;
//    
//    
//    isCyclicUtil(0, visited, -1);
//    
//}
//
//void Graph::isCyclicUtil(int v, bool visited[], int parent)
//{
//    visited[v] = true;
//    circle[k++] = v;
//    
//    list<int>::iterator it;
//    
//    for(it = adj[v].begin(); it != adj[v].end(); ++it)
//    {
//        if(!visited[*it])
//        {
//            isCyclicUtil(*it,visited,v);
//        }
//        else
//            if(*it!=parent)
//            {
//                for(int i=0;i<k;i++)
//                    cout<<circle[i]<<" ";
//                cout<<endl; 
//            }
//    }
//    visited[v]=false;
//    k--;
//}
