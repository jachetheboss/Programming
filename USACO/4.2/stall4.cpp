/*
ID: jamessh3
LANG: C++20
TASK: stall4
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> DFS(vector<vector<int>>& graph, vector<vector<int>>& weights){
	// must start at source, end at sink
	int source = 0;
	int sink = (int)graph.size() - 1;
	vector<int> stk = {source};
	vector<int> searched (graph.size(), 0);
	searched[source] = 1;
	int node = source;
	while(stk.size() > 0){
		bool deadend = true;
		for(int adj : graph[node]){
			if(searched[adj] == 0 and weights[node][adj] > 0){
				deadend = false;
				node = adj;
				stk.push_back(node);
				searched[adj] = 1;
				break;
			}
		}
		if(deadend){
			stk.pop_back();
			if(stk.size() > 0) node = stk.back();
		}
		//cout << "node: " << node << endl;
		if(node == sink) break;
	}
	// if stk is empty, that means that there does not exist a path with
	// all edges having non-zero weights
	return stk;
}

int main()
{
	//int N, M; cin >> N >> M;
	ifstream fin ("stall4.in");
	ofstream fout ("stall4.out");
	int N, M; fin >> N >> M;
	
	vector<vector<int>> graph (N + M + 2); // digraph directed graph
	vector<vector<int>> weights (N + M + 2, vector<int> (N + M + 2, -1));
	// cows are 1 -> N
	// stalls are N + 1 -> N + M
	// source is 0, sink is N + M + 1
	for(int i = 1; i <= N; ++i){
		int stalls; fin >> stalls;
		for(int j = 0; j < stalls; ++j){
			int stall; fin >> stall;
			int node = stall + N;

            // comment some of these out?
			graph[i].push_back(node);
			//graph[node].push_back(i);
			weights[i][node] = 1;
		//	weights[node][i] = 1;
		}
	}
	
	cout << "hello world!" << endl;
	
	int source = 0;
	for(int i = 1; i <= N; ++i){
	    graph[source].push_back(i);
	    weights[source][i] = 1;
	}
	int sink = N + M + 1;
	for(int i = N + 1; i <= N + M; ++i){
	    graph[i].push_back(sink);
	    weights[i][sink] = 1;
	}
	
	int ans = 0;
	bool path_exists = true;
	while(path_exists){
		path_exists = false;
		vector<int> stk = DFS(graph, weights);
		
		cout << "stk.size() " << stk.size() << endl;
		
		if(stk.size() == 0) break; // no valid path exists anymore!
		path_exists = true;
		int min_w = INT_MAX;
		for(int i = 0; i < (int)stk.size() - 1; ++i){
		    int a = stk[i];
		    int b = stk[i + 1];
			int w = weights[a][b];
			min_w = min(min_w, w);
		}
		ans += min_w;
		cout << "min_w: " << min_w << endl;
		// update all edges
		for(int i = 0; i < (int)stk.size() - 1; ++i){
			int a = stk[i];
			int b = stk[i + 1];
			weights[a][b] -= min_w;
			if(weights[b][a] == -1){
				weights[b][a] = min_w;
				graph[b].push_back(a);
			}
			else weights[b][a] += min_w;
		}
	}
	
	fout << ans << endl;
	
	fin.close();
	fout.close();
	
	return 0;
}
	
	