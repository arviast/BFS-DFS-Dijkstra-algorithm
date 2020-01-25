/*util.cpp*/

#include "graph.h"
#include "util.h"
#include "minqueue.h"

using namespace std;


//
// buildGraph:
//
// Inputs the graph vertices and edges from the given file, building
// the graph g.  File format:
//   vertex vertex vertex ... #
//   src dest weight ... #
//
void buildGraph(string filename, graph& g)
{
  //
  // replace this function with the function you wrote in previous exercise:
  //
  //
    ifstream file(filename);

    if (!file.good())
    {
        cout << endl;
        cout << "**Error: unable to open input file '" << filename << "'." << endl;
        cout << endl;
        return;
    }

    char a;
    while (!file.eof() && a != '#') {
        file >> a;
        g.addvertex(a);
    }

    char b,c;
    int weight;
    while(!file.eof() && b != '#') {
        file >> b;
        file >> c;
        file >> weight;
        g.addedge(b,c,weight);
    }
}


//
// BFS:
//
// Performs a breadth-first search from the given starting vertex.  
// Returns the vertices in the order they were visited; startV will
// be first.
//
vector<char> BFS(graph& g, char startV)
{
  vector<char>  visited;
  queue<char>   frontierQueue;
  set<char>     discoveredSet;
  char current;

  frontierQueue.push(startV);
  discoveredSet.insert(startV);
  
  while (!frontierQueue.empty()) {
     current = frontierQueue.front();
     visited.push_back(current);
     frontierQueue.pop();
     
     for (unsigned int i = 0; i < g.neighbors(current).size(); i++) {
        
         if(discoveredSet.find(g.neighbors(current).at(i)) == discoveredSet.end()) {
            frontierQueue.push(g.neighbors(current).at(i));
            discoveredSet.insert(g.neighbors(current).at(i));
         }
        
     }
  }
  return visited;
}

// DFS searching
// ...
vector<char> DFS(graph& g, char startV)
{
  vector<char>  visited;
  stack<char>   frontierStack;
  set<char>     visitedSet;
  char current;

  frontierStack.push(startV); 
  visitedSet.insert(startV);
  
  while (!frontierStack.empty()) {
     current = frontierStack.top();
     visited.push_back(current);
     frontierStack.pop();
     
     for (unsigned int i = 0; i < g.neighbors(current).size(); i++) {
         if(visitedSet.find(g.neighbors(current).at(i)) == visitedSet.end()) {
            frontierStack.push(g.neighbors(current).at(i));
            visitedSet.insert(g.neighbors(current).at(i));
         }
     }
  }
  return visited;
}

// Dijkstra algorith to find shortest weight path
// ...
vector<char> Dijkstra (graph &g, char startV, map<char,int> &distances, map<char,char> &predecessors)
{
    minqueue<char, int> unvisitedQueue;
    vector<char> visited;
    
    for(char i: g.vertices()) {
        distances[i] = Infinity;
        predecessors[i] = ' ';
        unvisitedQueue.pushinorder(i, Infinity);
    }
    
    distances[startV] = 0;
    unvisitedQueue.pushinorder(startV, 0);
    
    while(!unvisitedQueue.empty()) {
        int edgeWeight = -1;
        int alternativePathDistance = -1;
        char currentV = unvisitedQueue.minfront();
        unvisitedQueue.minpop();
        
        if(distances[currentV] == Infinity) {
            break;
        }
        
        visited.push_back(currentV);
        
        for(char i: g.neighbors(currentV)){
            edgeWeight = g.getweight(currentV, i);
            alternativePathDistance = distances[currentV] + edgeWeight;
            
            if(alternativePathDistance < distances[i]) {
                distances[i] = alternativePathDistance;
                predecessors[i] = currentV;
                unvisitedQueue.pushinorder(i, alternativePathDistance);
            }
        }
    }
    return visited;
}

// recursive print for predecessors
// ...
void recursiveP(char temp, char startPoint, map<char,char> &predec)
{
    char temp1 = ' ';
    for (auto i: predec) {
        if(i.first == temp) {
            temp1 = i.second;
            break;
        }
    }
    
    if(temp == startPoint || temp1 == ' ') {
        cout << temp << " ";
        return;
    }
    else {
        recursiveP(temp1, startPoint, predec);
    }
    cout << temp << " ";
}
