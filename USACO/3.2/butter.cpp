/*
ID: jamessh3
LANG: C++20
TASK: butter
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
	ifstream fin ("butter.in");
	ofstream fout ("butter.out");
	
	int N, P, C; fin >> N >> P >> C;
	vector<int> freq (P + 1, 0); // how many cows are in each pasture
	for(int i = 0; i < N; ++i){
		int pasture; fin >> pasture; // pasture location of a cow
		freq[pasture]++;
	}
	vector<vector<int>> graph (P + 1); // adj list representation of graph
	for(int i = 0; i < C; ++i){
		int from, to, w; fin >> from >> to >> w; // weight
		graph[from].push_back(to);
		graph[from].push_back(w);
		graph[to].push_back(from);
		graph[to].push_back(w);
	}
	
	// do Dijkstra's a bunch of times, Floyd-Warshall prolly slow with 800 nodes
	// 800^3 is 6.4 * 10^7, Dijkstra's suitable since relatively small number of edges,
	// very sparse graph, do Dijkstra's on all pastures, VElogE should be smaller than V^3
	
	// then try to place sugar at every pasture, find the best!
	vector<vector<int>> mindis (P + 1, vector<int> (P + 1, INT_MAX));
	for(int source = 1; source <= P; ++source){
		mindis[source][source] = 0;
		priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
		pq.push({0, source});
		vector<int> searched (P + 1, 0);
		while(pq.size() > 0){
			int d = pq.top()[0];
			int pasture = pq.top()[1];
			
			pq.pop();
			
			if(searched[pasture] == 1) continue;
			searched[pasture] = 1;
			
			for(int i = 0; i < graph[pasture].size(); i += 2){
				int adj = graph[pasture][i];
				int w = graph[pasture][i + 1];
				if(searched[adj] == 1) continue;
				int nd = d + w; // new dis
				if(nd < mindis[source][adj]){
					mindis[source][adj] = nd;
					pq.push({nd, adj});
				}
			}
		}
	}
	
	int ans = INT_MAX;
	for(int sugar = 1; sugar <= P; ++sugar){
		int total_dis = 0;
		for(int i = 1; i < freq.size(); ++i){
			if(freq[i] > 0){ // # of cows at that pasture
				int incr = freq[i] * mindis[sugar][i];
				total_dis += incr;
			}
		}
		cout << "total_dis: " << total_dis << endl;
		ans = min(ans, total_dis);
	}
	
	fout << ans << endl;
	
	fin.close();
	fout.close();
	
	return 0;
}