/*
ID: jamessh3
LANG: C++20
TASK: fence6
*/

#include <bits/stdc++.h>
using namespace std;


// make this recursive?
//int findCycleLen(unordered_set<int>& MST, vector<vector<int>>& graph, int new_edge, vector<int>& len){
int findCycleLen(unordered_set<int>& MST, vector<vector<vector<int>>>& graph, int new_edge, vector<int>& len, vector<vector<unordered_set<int>>>& hs_graph){


    // strategy of building a MST and then adding edges may not create pastures, since there could
    // be graphs like, so have to check if it is a simple cycle, no other cycles exist in the selected
    // fences
    // ---
    // | |
    // ---
    // | |
    // ---
    
    // once the cycle is detected, must check if the cycle is a simple cycle (no edges between
    // edges in the cycle candidate that are not immediate adjacent )

	int cycle_len = 0;
	
	vector<int> stk = {new_edge};
	unordered_set<int> searched;
	searched.insert(new_edge);
	int edge = new_edge;
	
	cout << "new_edge: " << new_edge << endl;
	
	if(new_edge == 7){
	    cout << "graph[new_edge][0].size() " << graph[new_edge][0].size() << endl;
	    cout << "graph[new_edge][0] adj: " << graph[new_edge][0][0] << ", " << graph[new_edge][0][1] << endl;
	}
	
	// ALL NEW EDGES MUST BE A PART OF THE MST!
	
	while(stk.size() > 0){
	    
	    //cout << "stk.size() " << stk.size() << endl;
	    
	    if(stk.size() == 1){
	        // should never be a deadend here, since a cycle exists!
	        for(int adj : graph[new_edge][0]){
	            if(searched.count(adj) == false and MST.count(adj) == true){
	                edge = adj;
	                searched.insert(edge);
	                stk.push_back(edge);
	                break;
	            }
	        }
	    }else{
	        
	       // cout << "curr stk:" << endl;
        // 	for(int id : stk) cout << id << ' ';
        // 	cout << endl;
	        
	        // maybe use unordered_map for faster lookup!
	        int prev_edge = stk[(int)stk.size() - 2];
	        int idx = -1;
	        for(int adj : graph[edge][0]){
	            if(adj == prev_edge){
	                idx = 1;
	                break;
	            }
	        }
	        if(idx == -1) idx = 0;
	        
	        cout << "idx: " << idx << endl;
	        
	        bool deadend = true;
    	    bool cycle_found = false;
    	    for(int adj : graph[edge][idx]){
    	        if(searched.count(adj) == true and MST.count(adj) == true){
    	            if(stk.size() >= 3 and adj == new_edge){
    	                bool ok = false;
    	                for(int e : graph[new_edge][1]){
    	                    if(e == edge){
    	                        ok = true;
    	                        break;
    	                    }
    	                }
    	                if(ok){
        	                cycle_found = true;
        	                break;
    	                }
    	            }
    	            continue;
    	        }
    	        
    	        if(MST.count(adj) == false) continue;
    	        
    	        // at this point, not searched!
    	        deadend = false;
    	        searched.insert(adj);
                stk.push_back(adj);
                edge = adj;
                break;
    	    }
    	    if(cycle_found) break;
    	    
    	    if(deadend){
        	    stk.pop_back();
        	    if(stk.size() > 0) edge = stk.back();
    	    }
	    }
	}
	
	cout << "new_edge: " << new_edge << endl;
	cout << "stk:" << endl;
	for(int id : stk) cout << id << ' ';
	cout << endl;
	
	
	// check if it is a face of planar graph (simple cycle, no other connecting edges in between)
	bool is_face = true;
	for(int i = 0; i < stk.size(); ++i){
	    for(int j = i + 1; j < stk.size(); ++j){ // check hashset graph
	        int e1 = stk[i]; // edge 1 
	        int e2 = stk[j];
	        if((hs_graph[e1][0].count(e2) == true or hs_graph[e1][1].count(e2) == true)){
	            if(not ((i == 0 and j == (int)stk.size() - 1) or j - i == 1)){
	                is_face = false;
	                break;
	            }
	        }
	    }
	    if(not is_face) break;
	}
	
	if(not is_face) return -1;
	
	for(int x : stk) cycle_len += len[x];
	
	return cycle_len;
}

bool detectCycle(int new_edge, unordered_set<int>& MST, vector<vector<unordered_set<int>>>& graph, vector<int>& belong, int& unique_set_ID){
	
	// endpoint 1 and endpoint 2 matters
	
	// return true means cycle detected
	// return false means no cycle 
	
	//unordered_map<int, int> groups; // if 1, just left  if 2, just right, if 3, both (cycle)
	//unordered_set<int> groups;
	unordered_set<int>::iterator it;

	int group0 = -1;
	int group1 = -1;
	for(it = graph[new_edge][0].begin(); it != graph[new_edge][0].end(); ++it){
		int adj = *it;
		if(MST.count(adj) == true) group0 = belong[adj];
	}
	for(it = graph[new_edge][1].begin(); it != graph[new_edge][1].end(); ++it){
		int adj = *it;
		if(MST.count(adj) == true) group1 = belong[adj];
	}
	
	if(group0 == -1 and group1 == -1){
		belong[new_edge] = unique_set_ID;
		unique_set_ID++;
		return false;
	}
	if(group0 == -1){
		belong[new_edge] = group1;
		return false;
	}
	if(group1 == -1){
		belong[new_edge] = group0;
		return false;
	}
	if(group0 == group1) return true; // cycle 
	
	// convert all group0 to group1
	for(int i = 1; i < belong.size(); ++i){
		if(belong[i] == group0) belong[i] = group1;
	}
	belong[new_edge] = group1;
	return false;
}

int main()
{
	ifstream fin ("fence6.in");
	ofstream fout ("fence6.out");
	
	// some pastures may not be convex
	// computational geometry? or just a graph problem of connected components
	// and stuff? cycle detection? shortest weighted cycle
	// can we modify Dijkstra's?
	// union find? DP?
	
	// Dijkstra's shortest path from vertex back to itself (without traveling
	// twice on same edge?)
	
	// successive BFS with deleting edges?
	
	// planar graph faces
	
	// assume it is not a multigraph
	
	// assume all pastures are already enclosed (there are no "leaf" nodes)
	
	// Minimum Spanning Tree, then try all edges, do a DFS to find the cycle
	
	/*
	int N; fin >> N;
	vector<vector<int>> graph (N + 1);
	vector<vector<int>> weights (201, vector<int> (201, -1)); // weight of edge from
	// node u to v [u][v]
	int node_ID = 0;
	// create adjacency vertex list repr of graph from the edges
	vector<int> seen (N + 1, 0); // if edges have already been seen
	for(int i = 0; i < N; ++i){
		int edge_ID, L, cnt1, cnt2; fin >> edge_ID >> L >> cnt1 >> cnt2;
		bool edge_seen = false;
		if(seen[edge_ID] == 1) edge_seen = true;
		bool adj_seen = false;
		for(int i = 0; i < cnt1; ++i){
			int adj; fin >> adj;
			graph[ID].push_back(adj);
		}for(int i = 0; i < cnt2; ++i){
			int adj; fin >> adj;
			graph[ID].push_back(adj);
		}
	}
	*/
	
	
	// solve with Kruskal's MST, also solve with Prim's
	int N; fin >> N;
	vector<vector<unordered_set<int>>> graph (N + 1, vector<unordered_set<int>> (2, unordered_set<int>() ));
	vector<vector<int>> edges;
	vector<int> len (N + 1); // store the len of edges
	for(int i = 0; i < N; ++i){
		int edge_ID, L, cnt1, cnt2; fin >> edge_ID >> L >> cnt1 >> cnt2;	
		for(int i = 0; i < cnt1; ++i){
			int adj; fin >> adj;
			graph[edge_ID][0].insert(adj); // left
		}for(int i = 0; i < cnt2; ++i){
			int adj; fin >> adj;
			graph[edge_ID][1].insert(adj); // right
		}
		edges.push_back({L, edge_ID});
		len[edge_ID] = L;
	}
	sort(edges.begin(), edges.end());
	unordered_set<int> MST; // edge IDs in MST, before it is fully built it may consist of
	// multiple disconnected components
	vector<int> belong (N + 1, -1);
	int unique_set_ID = 0;
	for(vector<int>& edge : edges){
		int ID = edge[1];
		MST.insert(ID);
		bool cycle_exists = detectCycle(ID, MST, graph, belong, unique_set_ID);
		if(cycle_exists) MST.erase(ID); // don't want a cycle
	}
	
	cout << "MST.size() " << MST.size() << endl;
	cout << "edges.size() " << edges.size() << endl;
	cout << "graph.size() " << graph.size() << endl;
	cout << "belong: " << endl;
	for(int i = 0; i < belong.size(); ++i) cout << belong[i] << ' ';
	cout << endl;
	cout << "edges: " << endl;
	for(vector<int>& edge : edges){
	    cout << '{' << edge[0] << ',' << edge[1] << "} ";
	}
	cout << endl;
	
	// MST built at this point, now try all edges and find cycle length
	
	//vector<vector<int>> vec_graph = { {} };
	vector<vector<vector<int>>> vec_graph = { {{}, {}} };
	unordered_set<int>::iterator it;
	for(int i = 1; i < graph.size(); ++i){
	    //vector<int> adjs;
	    vector<vector<int>> adjs = { {}, {} };
	    for(it = graph[i][0].begin(); it != graph[i][0].end(); ++it) {
	        int adj = *it;
	       // adjs.push_back(adj);
	       adjs[0].push_back(adj);
	    }
	    for(it = graph[i][1].begin(); it != graph[i][1].end(); ++it) {
	        int adj = *it;
	        //adjs.push_back(adj);
	        adjs[1].push_back(adj);
	    }
	    vec_graph.push_back(adjs);
	}
	
	int ans = INT_MAX;
	for(vector<int>& edge : edges){
	    
	    cout << "MST.size() " << MST.size() << endl;
	    
		int ID = edge[1];
		if(MST.count(ID) == true) continue;
		
		MST.insert(ID);
		int cycle_len = findCycleLen(MST, vec_graph, ID, len, graph);
		if(cycle_len != -1){ // -1 means not a face of planar graph
		    ans = min(ans, cycle_len);
		}
		MST.erase(ID);
	}
	fout << ans << endl;
	
	
	
	fin.close();
	fout.close();
	
	return 0;
}