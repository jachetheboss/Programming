/*
ID: jamessh3
LANG: C++20
TASK: fence
*/

#include <bits/stdc++.h>
using namespace std;

void findCircuit(vector<map<int, int>>* graph, vector<int>* eulerian, int* eulerian_pos, int node){
	if((*graph)[node].size() == 0){ // if no neighbors
		(*eulerian)[*eulerian_pos] = node;
		*eulerian_pos += 1;
	}else{
		while((*graph)[node].size() > 0){
// 			int adj = *((*graph)[node].rbegin());
//          int adj = *((*graph)[node].begin());
			int adj = ((*graph)[node].begin())->first;
			(*graph)[adj][node]--;
			(*graph)[node][adj]--;
			if((*graph)[adj][node] == 0) (*graph)[adj].erase(node);
			if((*graph)[node][adj] == 0) (*graph)[node].erase(adj);
//			(*graph)[adj].erase(node);
//			(*graph)[node].erase(adj);
			findCircuit(graph, eulerian, eulerian_pos, adj);
		}
		(*eulerian)[*eulerian_pos] = node;
		*eulerian_pos += 1;
	}
}

int main()
{
	// Eulerian tour (either path or circuit)
	
	ifstream fin ("fence.in");
	ofstream fout ("fence.out");
	
	int F; fin >> F;
	vector<map<int, int>> graph (501); // set permits fast lookup of biggest, and fast deletion
	for(int i = 0; i < F; ++i){
		int u, v; fin >> u >> v;
		if(graph[u].count(v) == false) graph[u].insert({v, 0});
		graph[u][v]++;
		if(graph[v].count(u) == false) graph[v].insert({u, 0});
		graph[v][u]++;
	}
	int idx = -1;
	for(int i = (int)graph.size() - 1; i >= 0; --i){
		if(graph[i].size() != 0){
			idx = i;
			break;
		}
	}
	graph.erase(graph.begin() + idx + 1, graph.end());
	
	// find the odd-degree nodes, if any (from problem constraints, guaranteed
	// either 0 or 2 of them 
	
	vector<int> odds;
	for(int node = 1; node < graph.size(); ++node){
		int deg = 0;
		map<int, int>::iterator it;
		for(it = graph[node].begin(); it != graph[node].end(); ++it) deg += it->second;
		if(deg % 2 == 1) odds.push_back(node);
	}
	
	// for smallest order, always start at the biggest node,
	// since algo returns path in reverse order
	vector<int> eulerian (F + 1, -1);
	int eulerian_pos = 0;
	int node;
	if(odds.size() == 2){ // path
// 		if(odds[0] > odds[1]) node = odds[0];
// 		else node = odds[1];
        if(odds[0] > odds[1]) node = odds[1];
		else node = odds[0];
	}else{ // circuit
		// find smallest node, node 1
		node = 1;
	}
	
	//vector<set<int>>* ptr1 = &graph;
	vector<map<int, int>>* ptr1 = &graph;
	vector<int>* ptr2 = &eulerian;
	int* ptr3 = &eulerian_pos;
	findCircuit(ptr1, ptr2, ptr3, node);
	
	for(int i = (int)eulerian.size() - 1; i >= 0; --i){
		fout << eulerian[i] << endl;
	}
    // for(int val : eulerian) fout << val << endl;
	
	fin.close();
	fout.close();

	return 0;
}