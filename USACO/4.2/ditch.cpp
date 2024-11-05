/*
ID: jamessh3
LANG: C++20
TASK: ditch
*/

#include <bits/stdc++.h>
using namespace std;

// from source = 1 (pond) to sink = M (stream)
vector<int> getBestPath(vector<vector<int>>& weights){
	int M = (int)weights.size() - 1;
	// union find or modified Dijkstra's
	int source = 1;
	int sink = (int)weights.size() - 1;
	priority_queue<vector<int>, vector<vector<int>>> pq; // max heap 
	for(int i = 2; i < weights.size(); ++i){
		int w = weights[source][i];
		if(w > 0) pq.push( {w, i, source} );
	}
	vector<int> path_cap (M + 1, INT_MAX);
	vector<int> searched (M + 1, 0);
	vector<int> prev (M + 1, -1);
	while(pq.size() > 0){ // max
		int w = pq.top()[0];
		int node = pq.top()[1];
		int p = pq.top()[2]; // previous node
		pq.pop();
		if(searched[node] == 1) continue;
		searched[node] = 1;
		prev[node] = p;
		path_cap[node] = min(path_cap[node], w);
		if(node == sink) break;
		for(int j = 1; j < weights[node].size(); ++j){
			if(searched[j] == 1 or weights[node][j] == 0 or j == node) continue;
			int adj_w = weights[node][j];
			pq.push( {min(adj_w, path_cap[node]), j, node} );
		}
	}
	
	if(prev[M] == -1) return {};
	
	vector<int> path;
	int node = sink;
	while(true){
		path.push_back(node);
		if(node == source) break;
		int p = prev[node];
		node = p;
	}
	// reverse path
	int bound = path.size() / 2;
	for(int i = 0; i < bound; ++i){
		int tmp = path[i];
		path[i] = path[(int)path.size() - 1 - i];
		path[(int)path.size() - 1 - i] = tmp;
	}
	return path;
}

int main()
{
	ifstream fin ("ditch.in");
	ofstream fout ("ditch.out");
	
	int N, M; fin >> N >> M;
	vector<vector<int>> weights (M + 1, vector<int> (M + 1, 0));
	for(int i = 0; i < N; ++i){
		int s, e, c; fin >> s >> e >> c;
		weights[s][e] += c;
	}
	int ans = 0;
	bool path_exists = true;
	while(path_exists){
		path_exists = false;
		vector<int> path = getBestPath(weights);
		
		if(path.size() == 0) break;
		
		path_exists = true;
		
		int min_w = INT_MAX;
		for(int i = 0; i < (int)path.size() - 1; ++i){
			int a = path[i];
			int b = path[i + 1];
			min_w = min(min_w, weights[a][b]);
		}
		ans += min_w;
		for(int i = 0; i < (int)path.size() - 1; ++i){
			int a = path[i];
			int b = path[i + 1];
			weights[a][b] -= min_w;
			weights[b][a] += min_w;
		}
	}
	fout << ans << endl;
	
	fin.close();
	fout.close();
	
	return 0;
}