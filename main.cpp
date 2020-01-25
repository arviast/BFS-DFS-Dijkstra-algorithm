/*main.cpp*/

//
// Program to input a graph from an input file, output to console, and then
// input starting vertex from user and run BFS algorithm.
//
// Prof. Joe Hummel
// U. of Illinois, Chicago
// CS 251: Fall 2019
//
// Arvinbayar Jamsranjav

#include "graph.h"
#include "util.h"
#include "minqueue.h"

using namespace std;

// checks if the vertice exists
bool validVertice(graph& g, char temp) {
    vector<char> myVertices = g.vertices();
    int countVertices = 0;
    
    for(unsigned int i = 0; i < myVertices.size(); i++){
        if(myVertices[i] == temp) {
            countVertices++;
        }
    }
    
    if(countVertices == 0) {
        return false;
    }
    return true;
}


int main()
{
  graph  g;
  string filename;
  char inputVertice;
  
  cout << "Enter filename containing graph data> ";
  cin >> filename;
  
  // for filename check ...
  ifstream ifile(filename);
  if(!ifile) {
      cout << "Error: File doesn't exist\n";
      exit(0);
  }
    
  //
  // Let's input the graph, and then output to see what we have:
  //
  buildGraph(filename, g);
  g.output();
  
  // vector that stores all vertices
  vector<char> myVertices = g.vertices();
    
  cout << "\nEnter a starting vertex or #> ";
  cin >> inputVertice;
    
  while (inputVertice != '#'){
      // checks if the vertix exists or not
      if(!validVertice(g, inputVertice)) {
          cout << "Not a vertex in graph, ignored...\n";
          cout << "\nEnter a starting vertex or #> ";
          cin >> inputVertice;
          continue;
      }
      
      // declarations for util functions
      map<char,int> dist;
      map<char,char> predec;
      vector<char> Neighbors = g.neighbors(inputVertice);
      vector<char> buildBFS = BFS(g, inputVertice);
      vector<char> buildDFS = DFS(g, inputVertice);
      vector<char> buildDjikastra = Dijkstra(g, inputVertice, dist, predec);
      
      // printing
      cout << "Neighbors: ";
      for(unsigned int i = 0; i < Neighbors.size(); i++) {
          cout << Neighbors[i] << " ";
      }
      
      cout << "\nBFS: ";
      for(unsigned int i = 0; i < buildBFS.size(); i++) {
          cout << buildBFS[i] << " ";
      }
      
      
      cout << "\nDFS: ";
      for(unsigned int i = 0; i < buildDFS.size(); i++) {
          cout << buildDFS[i] << " ";
      }      
      
      cout << "\nDijkstra: ";
      for(unsigned int i = 0; i < buildDjikastra.size();i++) {
          cout << buildDjikastra[i] << " ";
      }
      
      for(unsigned int i = 0; i < buildDjikastra.size();i++) {
          cout << endl <<" "<< buildDjikastra[i] << ": " << dist[buildDjikastra[i]] << " via ";
          recursiveP(buildDjikastra[i], inputVertice, predec);
      }
            
      cout << "\n\nEnter a starting vertex or #> ";
      cin >> inputVertice;
  }
  return 0;
}
