/*util.h*/

#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <fstream>
#include <stack>
#include <map>

#include "graph.h"
#include "minqueue.h"
#include "util.h"

const int Infinity = numeric_limits<int>::max();

using namespace std;

void buildGraph(string filename, graph& g);
vector<char> BFS(graph& g, char startV);
vector<char> DFS(graph& g, char startV);
bool StronglyConnected(graph& g, vector<char>& disconnected);
vector<char> Dijkstra (graph &g, char startV, map<char, int> & distances, map<char,char>&predecessor);
void recursiveP(char temp, char startPoint, map<char,char> &predec);
