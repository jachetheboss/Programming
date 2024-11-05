/*
ID: jamessh3
LANG: C++20
TASK: milk6
*/
#include <bits/stdc++.h>
using namespace std;

// finding a non-avoidable edge and deleting it doesn't work,
// there could be a case where deleting a combination of avoidable edges
// is cheaper than deleting a single non-avoidable edge 
// some recursive search, cheapest cutting off start from dest is
// cost of cheapest way to cut off adjacent nodes that can reach dest 

// how about "merging" nodes, like in DFA, NFA (Deterministic/nondete. finite state
// automata), to help simplify the graph, combining edges, etc?


void update(vector<int>& a, int& total_a, int& trucks_a, vector<int>& ind_a, vector<int>& weights){
	for(int i = 0; i < a.size(); ++i){
		if(a[i] == 1){
			total_a += weights[i];
			trucks_a++;
			ind_a.push_back(i);
		}
	}
}

bool comparator(vector<int>& a, vector<int>& b){
	if(a[0] < b[0]) return true;
	if(a[0] > b[0]) return false;
	if(a[0] == b[0]){
		if(a[1] < b[1]) return true;
		if(a[1] > b[1]) return false;
		if(a[1] == b[1]){
			return a[2] < b[2];
		}
	}
	return true;
}

bool pathExists(int start, int end, vector<vector<int>>& graph){
	if(start == end) return true;
	vector<int> q = {start};
	vector<int> searched (graph.size(), 0);
	searched[start] = 1;
	while(q.size() > 0){
		vector<int> next_q;
		for(int node : q){
			for(int adj : graph[node]){
				if(searched[adj] == 0){
					if(adj == end) return true;
					searched[adj] = 1;
					next_q.push_back(adj);
				}
			}
		}
		q = next_q;
	}
	return false;
}

int main()
{
	// directed graph
	// is it a multigraph? If so, simply combine the edge weights into
	// a single weight
	// should also store count of how many edges are between a pair
	// of nodes, store the edge indices as well
	ifstream fin ("milk6.in");
	ofstream fout ("milk6.out");
	int N, M; fin >> N >> M;
	vector<vector<vector<int>>> cost (N + 1, vector<vector<int>> (N + 1));
	vector<int> weights;
	// {cumul_cost, # routes, min edge idx}
	for(int i = 0; i < M; ++i){
		int S, E, C; fin >> S >> E >> C;
		if(cost[S][E].size() == 0) cost[S][E] = {0, 0};
		cost[S][E][0] += C;
		cost[S][E][1]++;
		cost[S][E].push_back(i);
		
		weights.push_back(C);
	}
	// check for loops, self edges!
	vector<vector<int>> graph (N + 1); // adjacency list repr
	for(int i = 1; i < cost.size(); ++i){
		for(int j = 1; j < cost[i].size(); ++j){
			if(cost[i][j].size() > 0) graph[i].push_back(j);
		}
	}
	int start = 1;
	int dest = N;
	if(not pathExists(start, dest, graph)){
		fout << 0 << ' ' << 0 << endl;
		fin.close();
		fout.close();
		return 0;
	}
	/*
	// at this point, a path exists from start to dest, so contaminated
	// milk can reach the grocer
	// find cheapest way to cut off a path from start to dest 
	// example case: graph is complete, every pair of nodes is connected,
	// then have to disconnect every single truck route!
	// is this a minimum spanning tree problem?
	// topo sort union find Kruskal's algo
	
	// INSTEAD OF MINIMUM SPANNING TREE, FIND THE "MAXIMUM DISCONNECTED GRAPH"
	
	vector<vector<int>> edges;
	for(int i = 1; i < cost.size(); ++i){
		for(int j = 1; j < cost[i].size(); ++j){
			if(cost[i][j].size() > 0){
				edges.push_back({cost[i][j][0], cost[i][j][1], cost[i][j][2], i, j});
				// {cumul_cost, # routes, min_route_idx, from, to}
			}
		}
	}
	sort(edges.begin(), edges.end(), comparator);
	
	int best_del_cost = INT_MAX;
	int best_del_routes = INT_MAX;
	int best_min_del_idx = INT_MAX;
	// greedily include the most expensive edges, by building the
	// "graph that remains."
	vector<vector<int>> curr_graph (N + 1);
	vector<int> del_ind;
	int del_ind_prefix = (int)edges.size() - 1;
	for(int i = (int)edges.size() - 1; i >= 0; --i){
		int w = edges[i][0];
		int trucks = edges[i][1];
		int min_idx = edges[i][2];
		int from = edges[i][3];
		int to = edges[i][4];
		curr_graph[from].push_back(to);
		if(pathExists(start, dest, curr_graph)){
			del_ind.push_back(i);
			curr_graph[from].pop_back();
			continue;
		}
		int del_cost = 0;
		int del_routes = 0;
		int min_del_idx = INT_MAX;
		for(int j = 0; j < i; ++j){
			del_cost += edges[j][0];
			del_routes += edges[j][1];
			min_del_idx = min(min_del_idx, edges[j][2]);
		}
		for(int x : del_ind){
			del_cost += edges[x][0];
			del_routes += edges[x][1];
			min_del_idx = min(min_del_idx, edges[x][2]);
		}
		
		if(del_cost < best_del_cost){
			best_del_cost = del_cost;
			best_del_routes = del_routes;
			best_min_del_idx = min_del_idx;
			del_ind_prefix = i - 1;

		}else if(del_cost == best_del_cost and del_routes < best_del_routes){
			best_del_routes = del_routes;
			best_min_del_idx = min_del_idx;
			del_ind_prefix = i - 1;
		}else if(del_cost == best_del_cost and del_routes == best_del_routes and min_del_idx < best_min_del_idx){
			best_min_del_idx = min_del_idx;
			del_ind_prefix = i - 1;
		}
	}
	cout << best_del_cost << ' ' << best_del_routes << endl;
	
	sort(del_ind.begin(), del_ind.end());
	
	for(int i = 0; i <= del_ind_prefix; ++i){
		cout << edges[i][2] + 1 << endl;
	}
	for(int i : del_ind) cout << edges[i][2] + 1 << endl;
	
	// backtracking? at most have to delete 31 edges, since if 
	// all of dest's incoming edges are gone, then there is guaranteed
	// to not exist any paths!
	// DP?
	*/
	
	
	// build a reverse directed graph, BFS, keep adding 
	// actually, don't even have to build the reverse directed graph
	
	// some bellman ford type jaunt?
	
	/// I'm suspecting that a Bellman-Ford-esque algo will work here,
	// continue "relaxing", find minimum cost to disconnect so far
	// for each successive iteration for each node
	vector<vector<int>> disconnect (N + 1, vector<int> (M, 0));
	vector<int> q = {start};
	vector<int> searched (N + 1, 0);
	searched[start] = 1;
	while(q.size() > 0){
	    
	    cout << "disconnect:" << endl;
	    for(int node = 1; node < disconnect.size(); ++node){
	        cout << "\tnode: " << node << endl;
	        for(int x : disconnect[node]) cout << x << ' ';
	        cout << endl;
	    }
	    
		vector<int> next_q;
		for(int iter = 0; iter < 2; ++iter){
    		for(int node : q){
    			for(int adj : graph[node]){
    			    
    			    if(searched[adj] == 0 and iter == 0) continue;
    			    if(searched[adj] == 1 and iter == 1) continue;
    			    
    				int w = cost[node][adj][0];
    				
    				// if(adj == dest){
    				    cout << "curr_node " << node << endl;
    				    cout << "adj " << adj << endl;
    				    cout << "w: " << w << endl;
    				    cout << endl;
    				// }
    				
    				int trucks = cost[node][adj][1];
    				// cost[node][adj][2] to the last element are all truck indices
    				if(node == start){
    					for(int idx = 2; idx < cost[node][adj].size(); ++idx){
    						int truck = cost[node][adj][idx];
    						disconnect[adj][truck] = 1;
    					}
    				}else{
    					// try deleting this new edge,
    					vector<int> a = disconnect[adj];
    					for(int idx = 2; idx < cost[node][adj].size(); ++idx){
    						int truck = cost[node][adj][idx];
    						a[truck] = 1;
    					}
    					int total_a = 0;
    					int trucks_a = 0;
    					vector<int> ind_a;
    					update(a, total_a, trucks_a, ind_a, weights);
    					// or just using the best way of cutting off node from start
    					
    					vector<int> b = disconnect[adj];
    					int total_b = 0;
    					int trucks_b = 0;
    					vector<int> ind_b;
    					for(int i = 0; i < disconnect[node].size(); ++i){
    						if(disconnect[node][i] == 1) b[i] = 1;
    					}
    					update(b, total_b, trucks_b, ind_b, weights);
    					if(total_a < total_b
    						or (total_a == total_b and trucks_a < trucks_b)
    						or (total_a == total_b and trucks_a == trucks_b and ind_a < ind_b)){
    							disconnect[adj] = a;
    					}
    					else{
    						disconnect[adj] = b;
    					}
    				}
    				if(searched[adj] == 0){
    					searched[adj] = 1;
    					next_q.push_back(adj);
    				}
    			}
    		}
		}
		q = next_q;
	}
	
	int total_ans = 0;
	int trucks_ans = 0;
	vector<int> ind_ans;
	update(disconnect[dest], total_ans, trucks_ans, ind_ans, weights);
	
	fout << total_ans << ' ' << trucks_ans << endl;
	for(int i : ind_ans) fout << i + 1 << endl; // convert to 1-indexed
	
	fin.close();
	fout.close();
	
	return 0;
}