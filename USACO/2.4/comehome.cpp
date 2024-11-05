/*
ID: jamessh3
LANG: C++20
TASK: comehome
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
	ifstream fin ("comehome.in");
	int P; fin >> P;
	vector<vector<char>> graph (123); // adj list
	vector<vector<int>> dis (123, vector<int> (123, INT_MAX)); // find a way to reduce storage requirement
	for(int i = 0; i < P; ++i){
		char c1, c2; fin >> c1 >> c2;
		int d; fin >> d;
		if(c1 == c2) continue; // no loops (self edges)
		dis[c1][c2] = min(dis[c1][c2], d);
		dis[c2][c1] = min(dis[c2][c1], d);
	}
	for(int i = 0; i < dis.size(); ++i){
		for(int j = 0; j < dis[i].size(); ++j){
			if(dis[i][j] != INT_MAX) graph[i].push_back(j);
		}
	}
	// from each capital letter (except Z), do Dijkstra's to Z
	vector<int> z_arrive (90, INT_MAX);
	for(char start = 'A'; start <= 'Y'; ++start){
		if(graph[start].size() == 0) continue; // capital letter not in input 
		vector<int> searched (123, 0);
		priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
		pq.push({0, start});
		vector<int> min_dis (123, INT_MAX);
		while(pq.size() > 0){
			int d = pq.top()[0];
			int node = pq.top()[1];
			if(searched[node] == 1){
				pq.pop();
				continue;
			}
			searched[node] = 1;
			min_dis[node] = d;
			for(int adj : graph[node]){
				int nd = min_dis[node] + dis[node][adj];
				if(nd < min_dis[adj]){
					min_dis[adj] = nd;
					pq.push({nd, adj});
				}
			}
		}
		z_arrive[start] = min_dis['Z'];
	}
	int shortest = INT_MAX;
	char pasture = '\0';
	for(char c = 'A'; c <= 'Y'; ++c){
		if(z_arrive[c] != INT_MAX){
			if(z_arrive[c] < shortest){
				shortest = z_arrive[c];
				pasture = c;
			}
		}
	}
	
	ofstream fout ("comehome.out");
	fout << pasture << ' ' << shortest << endl;
	
	fin.close();
	fout.close();
	
	return 0;
}