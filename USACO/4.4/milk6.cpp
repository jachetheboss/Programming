/*
ID: jamessh3
LANG: C++20
TASK: milk6
*/

#include <bits/stdc++.h>

#include <ctime>

using namespace std;


const int max_w = 2000000; // based on problem constraints
const int max_trucks = 1000;
const int start = 1;
int grocer = -1;

class Comparator {
public:
	bool operator()(vector<int>& a, vector<int>& b){
		if(a[0] < b[0]) return true;
		if(a[0] > b[0]) return false;
		if(a[1] > b[1]) return true;
		if(a[1] < b[1]) return false;
		return a[2] > b[2];
	}
};

// void calcAns(int max_flow, vector<vector<int>>& graph, set<int>& truck_set, unordered_map<int, vector<int>>& groups, ofstream& fout){
// 	// try every combo of edges, get rid of it, see if there is no path from start to grocer 
// 	// convert to adjacency graph
	
// }

int compare(vector<int>& a, vector<int>& b){
    long long left = a[0];
    left *= b[1];
    long long right = b[0];
    right *= a[1];
    if(left < right) return 0;
    else if(left > right) return 2;
    return 1; // equal
}

bool sorter(vector<int>& a, vector<int>& b){
    // {w, # trucks, min truck idx}
    int res = compare(a, b);
    if(res == 0) return false;
    else if(res == 2) return true;
    else return a[2] < b[2];
}

int MaxFlow(vector<vector<vector<int>>> weights, unordered_map<int, vector<int>>& groups){
    
    time_t start_t = clock();
    
	bool path_exists = true;
	int max_flow = 0;
	//int total_trucks = 0;
	//vector<int> truck_list;
	set<int> truck_set;
	while(path_exists){
	    
	   // cout << "max_flow: " << max_flow << endl;
	    
		path_exists = false;
		priority_queue<vector<int>, vector<vector<int>>, Comparator> pq;
		pq.push({max_w, max_trucks, max_trucks + 1, start, -1});
		// {bottleneck cost, bottleneck # trucks, bottleneck truck min idx, node, prev_node}
		vector<vector<int>> best (grocer + 1);
		vector<int> prev (grocer + 1, -1); // trace the path
		while(pq.size() > 0){
		    
		  //  cout << "pq.size() " << pq.size() << endl;
		    
			int bottleneck = pq.top()[0];
			int node = pq.top()[3];
			int prev_node = pq.top()[4];
			vector<int> vtop = pq.top();
			pq.pop();
			if(best[node].size() != 0) continue;
			
			best[node] = {bottleneck, vtop[1], vtop[2]};
			prev[node] = prev_node;
			
			if(node == grocer){ // reached the grocer
				path_exists = true;
				break;
			}
			for(int adj = 1; adj < weights[node].size(); ++adj){
			    
			    if(weights[node][adj].size() == 0) continue;
			    
			 //   cout << "adj " << adj << endl;
			    
				int w = weights[node][adj][0];
				int trucks = weights[node][adj][1];
				int min_idx = weights[node][adj][2];
				if(w < bottleneck){
				    
				    // cout << "if" << endl;
				    
				    pq.push( {w, trucks, min_idx, adj, node} );
				}
				else if(w > bottleneck){
				    
				    // cout << "else if" << endl;
				    
					vtop[3] = adj;
					vtop[4] = node;
					pq.push(vtop);
				}
				else{ // compare # trucks for tiebreaker
				
				    // cout << "else" << endl;
				
					if(trucks < vtop[1]){
						pq.push( {bottleneck, trucks, min_idx, adj, node} );
					}
					else if(trucks > vtop[1]){
						vtop[3] = adj;
						vtop[4] = node;
						pq.push(vtop);
					}
					else{ // compare truck idx for tiebreaker
						if(min_idx < vtop[2]) pq.push( {bottleneck, trucks, min_idx, adj, node} );
						else pq.push( {bottleneck, trucks, vtop[2], adj, node} );
					}
				}
			}
		}
		if(not path_exists) break;
		if(best[grocer][0] == 0) break; // no positive flow exists anymore
		
		int bottleneck = best[grocer][0];
		max_flow += bottleneck;
		//total_trucks += best[grocer][1];
		
		for(int idx : groups[best[grocer][2]]) truck_set.insert(idx);
		
		// decrement all edges on the path
		int prev_node = prev[grocer];
		int node = grocer;
		while(prev_node != -1){
			weights[prev_node][node][0] -= bottleneck;
			if(weights[node][prev_node].size() == 0) weights[node][prev_node] = {0, weights[prev_node][node][1], weights[prev_node][node][2]};
			weights[node][prev_node][0] += bottleneck;
			
			node = prev_node;
			prev_node = prev[node];
		}
	}
	
	time_t finish_t = clock();
	
// 	cout << "MaxFlow() func secs elapsed: " << 1.0 * (finish_t - start_t) / CLOCKS_PER_SEC << endl;
	
	return max_flow;
}

int main()
{
	
	// try a sort of DP, find all nodes exactly 1 edge away from the grocer (outwards edge leads
	// to the grocer), then cut off those edges, that's the 
	
	// can we do something greedy? Group all the multiedges (different trucks having the same path)
	// together to make the graph standard, then sort by decreasing weight, then try to 
	
	// is this max flow?
	
	// network flow. answer should be the max flow, but getting the unique solution of minimum
	// number of truck routes removed is difficult
	
	
	time_t start_t = clock();
	
	
	ifstream fin ("milk6.in");
	ofstream fout ("milk6.out");
	
	int N, M; fin >> N >> M;
	grocer = N;
	/*
	if(N == 4 and M == 5){
		fout << "60 1\n3\n";
		
		fin.close();
		fout.close();
		
		return 0;
	}
	*/
	
	
	// directed edges
	
	// handles multiedges
	vector<vector<vector<int>>> ind (N + 1, vector<vector<int>> (N + 1));
	vector<vector<vector<int>>> weights (N + 1, vector<vector<int>> (N + 1, vector<int> () ));
	vector<vector<int>> graph (weights.size());
	for(int i = 1; i <= M; i++){ // 1-indexed edges
		int S, E, C; fin >> S >> E >> C;
		if(weights[S][E].size() == 0){
			weights[S][E].push_back(0);
			weights[S][E].push_back(0);
			weights[S][E].push_back(i); // smallest index edge of the multiedge between 2 nodes
		}
		weights[S][E][0] += C; // total cost between the two nodes
		weights[S][E][1]++; // edge counter (multiedge) between the same two nodes
		
		ind[S][E].push_back(i);
	}
	
	unordered_map<int, vector<int>> groups;
	for(vector<vector<int>>& a : ind){
		for(vector<int>& b : a){
			for(int x : b){
				groups.insert({x, {} });
				for(int y : b) groups[x].push_back(y);
			}
		}
	}
	// assuming that the backedge can't be the bottleneck if the edge was the 
	// bottleneck previously
	
	// network flow algo
	
	
	// some sort of heisenbug with maxflow function, weights, groups
	
// 	cout << "max_flow " << MaxFlow(weights, groups) << endl;
	int ans = MaxFlow(weights, groups);
	cout << "max_flow " << MaxFlow(weights, groups) << endl;
	cout << "ans: " << ans << endl;
	
	vector<vector<int>> sorted;
    for(int i = 1; i < weights.size(); i++){
        for(int adj = 1; adj < weights[i].size(); adj++){
            if(weights[i][adj].size() == 0) continue;
            
            vector<int> v = weights[i][adj];
            v.push_back(i);
            v.push_back(adj);
            sorted.push_back(v);
        }
    }
    sort(sorted.begin(), sorted.end(), sorter);
    
    vector<int> searched (sorted.size(), 0);
	
// 	cout << "max_flow: " << ans << endl;
	
	set<int> truck_set;
	
	int rem = ans;
	cout << "rem: " << rem << endl;
	cout << "max_flow " << MaxFlow(weights, groups) << endl;
	cout << "sorted.size() " << sorted.size() << endl;
	int count = 0;
	while(rem > 0){
	    
	    if(count % 1000 == 0){
	        cout << "count: " << count << endl;
	        cout << "rem: " << rem << endl;
	        cout << "max_flow " << MaxFlow(weights, groups) << endl;
	        cout << "truck_set.size() " << truck_set.size() << endl;
	    }
	    
	    bool found = false;
	    for(int j = 0; j < sorted.size(); ++j){ // in heuristic descending order of weight/#trucks ratio
	        
	        if(searched[j] == 1) continue;
	        
	        
	        count++;
	        
	        vector<int>& v = sorted[j];
	        
	        int i = v[3];
	        int adj = v[4];
	        vector<int> temp = weights[i][adj];
	        weights[i][adj].clear();
	        int max_flow = MaxFlow(weights, groups);
	        
	       
	        
	        if(rem - max_flow == temp[0]){
	            // a part of the "min cut"
	            
	            cout << "max_flow " << max_flow << endl;
    	        cout << "rem " << rem << endl;
    	        cout<< "w " << temp[0] << endl;
    	        cout << endl;
    	            
	            for(int truck : groups[temp[2]]) truck_set.insert(truck);
	            rem = max_flow;
	            searched[j] = 1;
	            found = true;
	            break;
	        }else{
	            weights[i][adj] = temp;
	        }
	    }
	    if(found) cout << "found!" << endl;
	}
	
	fout << ans << ' ' << truck_set.size() << endl;
	for(auto it = truck_set.begin(); it != truck_set.end(); it++) fout << *it << endl;
	

// 	fout << max_flow << ' ' << truck_set.size() << endl;
// 	for(auto it = truck_set.begin(); it != truck_set.end(); ++it) fout << *it << endl;
	
	// now do some brute force checks to see what combos of edges weights add up to the max_flow

// 	calcAns(max_flow, weights, truck_set, groups, fout);
	
	fin.close();
	fout.close();
	
	
	time_t finish_t = clock();
	cout << "elapsed secs: " << 1.0 * (finish_t - start_t) / CLOCKS_PER_SEC << endl;
	
	return 0;
}