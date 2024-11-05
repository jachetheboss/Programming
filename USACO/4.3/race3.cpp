/*
ID: jamessh3
LANG: C++20
TASK: race3
*/

#include <bits/stdc++.h>
using namespace std;



bool checkOutgoing(int avoid, vector<int>& searched, vector<vector<int>>& graph){
    for(int adj : graph[avoid]){
        if(searched[adj] == 1) return true;
        //if(adj == avoid) return true; // avoid has self-loop
        // don't consider the self-loop as a part of the left portion,
        // greedily consider it to be a part of the right portion!
    }
    return false;
}

bool canReach(int start, int target, vector<vector<int>>& subgraph){
    // remember, target may be finish of the whole graph (the final end node)
    
    if(start == target) return true;
    
    vector<int> q = {start};
    vector<int> searched (subgraph.size(), 0);
    searched[start] = 1;
    while(q.size() > 0){
        vector<int> next_q;
        for(int node : q){
            for(int adj : subgraph[node]){
                if(adj == target) return true;
                if(searched[adj] == 0){
                    searched[adj] = 1;
                    next_q.push_back(adj);
                }
            }
        }
        q = next_q;
    }
    return false;
}

bool allCanReachAvoid(int target, vector<int>& curr_section, vector<vector<int>>& subgraph){
    for(int i = 0; i < curr_section.size(); ++i){
	    if(curr_section[i] == 1){
	        if(not canReach(i, target, subgraph)){
	            return false;
	        }
	    }
	}
	return true;
}

bool restCanReachFinish(vector<int>& searched, vector<vector<int>>& graph, int avoid, bool& back_edge){
    
    int N = graph.size();
    int finish = N;
    
    // build subgraph
    vector<vector<int>> subgraph (graph.size());
    for(int i = 0; i < searched.size(); ++i){
	    if(searched[i] == 1) continue;
        for(int adj : graph[i]){
            if(searched[adj] == 0) subgraph[i].push_back(adj);
        }
	}

    for(int i = 0; i < searched.size(); ++i){
        if(searched[i] == 1) continue; // seen before
        
        for(int adj : graph[i]){ // check for back edges
            if(i != avoid and searched[adj] == 1) back_edge = true;
        }
        // check to see if it can reach finish
        if(not canReach(i, finish, subgraph)) return false;
    }
    return true;
}

vector<vector<int>> buildSubgraph(int avoid, vector<int>& curr_section, vector<vector<int>>& graph){
    vector<vector<int>> subgraph (graph.size());
    for(int i = 0; i < curr_section.size(); ++i){
	    if(curr_section[i] == 1){
	        for(int adj : graph[i]){
	            if(curr_section[adj] == 1 or adj == avoid) subgraph[i].push_back(adj);
	        }
	    }
	}
	return subgraph;
}



vector<int> bfs(int start, int avoid, vector<vector<int>>& graph, vector<int>& searched, bool& back_edge){
    //vector<int> section;
    int N = graph.size();
    vector<int> curr_section (N, 0);
    vector<int> q = {start};
    searched[start] = 1;
    curr_section[start] = 1;
    while(q.size() > 0){
        vector<int> next_q;
        for(int node : q){
            for(int adj : graph[node]){
                if(searched[adj] == 1){
                    if(curr_section[adj] == 0) back_edge = true;
                    continue;
                }
                if(searched[adj] == 0 and adj != avoid){
                    next_q.push_back(adj);
                    curr_section[adj] = 1;
                    searched[adj] = 1;
                }
            }
        }
        q = next_q;
    }
    return curr_section;
}

int main()
{
	ifstream fin ("race3.in");
	ofstream fout ("race3.out");
	
	int val = -3;
	vector<vector<int>> graph = { {} };
	while(true){
		fin >> val;
		if(val == -1){
		    graph.pop_back();
		    graph.pop_back();
		    break;
		}
		if(val == -2) graph.push_back( {} );
		else{
			graph[(int)graph.size() - 1].push_back(val);
		}
	}
	// be wary of self loops!
	
	// to find unavoidable points, try deleting each point and seeing if 
	// the finish is reachable from the start 
	
// 	cout << "graph" << endl;
// 	for(int i = 0; i < graph.size(); ++i){
// 	    cout << "i: " << i << endl;
// 	    for(int x : graph[i]) cout << x << ' ';
// 	    cout << endl;
// 	}
	
	int N = (int)graph.size();
	vector<vector<int>> unavoidable; // {sz of conn_comp, avoid}
	for(int avoid = 1; avoid < N; ++avoid){ // avoid this node
		vector<int> q = {0};
		vector<int> searched (N + 1, 0);
		searched[0] = 1;
		int comp_sz = 1; // component size
		while(q.size() > 0){
			vector<int> next_q;
			for(int node : q){
				for(int adj : graph[node]){
					if(adj == avoid or searched[adj] == 1) continue;
					comp_sz++;
					searched[adj] = 1;
					next_q.push_back(adj);
				}
			}
			q = next_q;
		}
		
// 		cout << "searched[N] " << searched[N] << endl;
		
		if(searched[N] == 0) unavoidable.push_back({comp_sz, avoid});
	}
	// split nodes MUST BE unavoidable!
	
	sort(unavoidable.begin(), unavoidable.end());
	// will go in order from earliest unavoidable node to latest
	vector<int> searched = vector<int> (N + 1, 0);
	vector<int> q = {0};
	searched[0] = 1;
	// check for "back edges" to determine if a valid split
	// going from left to right, if an unavoidable node is not a valid split
	// due to failing condition of avoid being reachable from every node so far,
	// then all unavoidable nodes to the right are also not valid splits,
	// think of it as a sequence of bottlenecks
	int prev_avoid = 0;
	vector<int> splitting_nodes;
	for(vector<int>& v : unavoidable){
		int avoid = v[1];
// 		cout << "avoid: " << avoid << endl;
		// must check to see if avoid is reachable from all nodes so far,
		// and if avoid has no outgoing edges to the nodes reached so far
		// (avoid may have outgoing edges to nodes not yet reached)
		// also check if avoid can reach every node that is not reached so far 
		// (the nodes and edges that are on the "right" side of the split,
		// what is reached is considered the "left", check if completely
		// reachable)
		// also check that there are no backwards edges from the unreached
		// nodes to the reached nodes)
		// ***Are avoid_node's own self loops considered back edges?
		
		bool back_edge = false;
		// avoid_node is NOT considered a part of the curr_section,
		// but the prev avoid is considered a part
		vector<int> curr_section = bfs(prev_avoid, avoid, graph, searched, back_edge);
		// for index i in curr_section, if curr_section[i] == 1 then
		// node i is a part of the current section 
		vector<vector<int>> subgraph = buildSubgraph(avoid, curr_section, graph); // graph of current section only
		
// 		cout << "subgraph" << endl;
// 		for(int i = 0; i < subgraph.size(); ++i){
// 		    cout << "i: " << i << endl;
// 		    for(int adj : subgraph[i]) cout << adj << ' ';
// 		    cout << endl;
// 		}
// 		cout << endl;
		
// 		cout << "curr_section" << endl;
// 		for(int x : curr_section) cout << x << ' ';
// 		cout << endl;
		
		bool all_reach_avoid = allCanReachAvoid(avoid, curr_section, subgraph);
		
// 		cout << "all_reach_avoid " << all_reach_avoid << endl;
		
		if(not all_reach_avoid) break;
		bool avoid_has_outgoing_in_reached = checkOutgoing(avoid, searched, graph);
		
		// the above backedge checking logic is wrong, backedges should be
		// between the two splits, above logic checks for backedge within the split
		back_edge = false;
		bool rest_can_reach_finish = restCanReachFinish(searched, graph, avoid, back_edge);
		
		if(back_edge == false and rest_can_reach_finish and not avoid_has_outgoing_in_reached){
		    splitting_nodes.push_back(avoid);
		}
		
		// udpate prev_avoid !!!!!!!
		prev_avoid = avoid;
	}
	
	if(unavoidable.size() == 0){
	    fout << 0 << endl;
	}else{
	    fout << unavoidable.size() << ' ';
    	for(int i = 0; i < (int)unavoidable.size() - 1; ++i){
    		int node = unavoidable[i][1];
    		fout << node << ' ';
    	}
    	fout << unavoidable.back()[1] << endl;
	}
	
	if(splitting_nodes.size() == 0){
	    fout << 0 << endl;
	}else{
	    fout << splitting_nodes.size() << ' ';
	    for(int i = 0; i < (int)splitting_nodes.size() - 1; ++i){
	        fout << splitting_nodes[i] << ' ';
	    }
	    fout << splitting_nodes.back() << endl;
	}
	
	fin.close();
	fout.close();
	
	return 0;
}