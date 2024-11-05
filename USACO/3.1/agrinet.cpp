/*
ID: jamessh3
LANG: C++20
TASK: agrinet
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
	ifstream fin ("agrinet.in");
	int N; fin >> N;
	//vector<vector<int>> (N); // adj list
	vector<vector<int>> graph (N, vector<int> (N, -1)); // adj matrix
	for(int i = 0; i < N; ++i){
		for(int j = 0; j < N; ++j){
			int d; fin >> d;
			graph[i][j] = d;
		}
	}
	// Prim's algo
	// hardcode first node in as node 0
	vector<int> reached (N, 0);
	reached[0] = 1;
	vector<int> dis (N, INT_MAX);
	for(int j = 0; j < graph[0].size(); ++j) dis[j] = graph[0][j];
	int sz = 1; // treesize
	int ans = 0;
	while(sz < N){
		int min_d = INT_MAX;
		int node = -1;
		for(int i = 0; i < dis.size(); ++i){
			if(reached[i] == 0 and dis[i] < min_d){
				min_d = dis[i];
				node = i;
			}
		}
		reached[node] = 1;
		ans += min_d;
		for(int j = 0; j < graph[node].size(); ++j){
			if(reached[j] == 0) dis[j] = min(dis[j], graph[node][j]);
		}
		sz++;
	}
	
	ofstream fout ("agrinet.out");
	fout << ans << endl;
	
	fin.close();
	fout.close();
	return 0;
}