/*
ID: jamessh3
LANG: C++20
TASK: cowtour
*/

// #include <iostream>
// #include <fstream>
// #include <vector>
// #include <string>
#include <bits/stdc++.h>

using namespace std;

// a couple ideas about this problem. There is O(n^3) algorithm to find shortest
// path between ALL PAIRS of nodes. Can try all possible combinations ~n^2 of making new
// edge, then run all-pairs shortest path algo, but program would run in O(n^5) time, but
// n = 150, TLE.

// Instead, just find the 2 connected components (no more than 2 connected components, pretty sure),
// run O(n^3) algo on each component, then try all ways to make new edge, then shortest path between
// nodes in previously separated components would be sum of shortest path to the "bridge" nodes, plus
// the length of bridge itself. This would be O(n^3) complexity, doable.

double getDis(vector<vector<int>>& coor, int node1, int node2){
	long long dx = coor[node1][0];
	dx -= coor[node2][0];
	long long dy = coor[node1][1];
	dy -= coor[node2][1];
	dx *= dx;
	dy *= dy;
	dx += dy;
	double d = sqrt((double)dx);
	return d;
}

int main(){

    // vector<vector<int>> coor = {{0, 2}, {2, 0}};
    // cout << getDis(coor, 0, 1);

///*
    ifstream fin ("cowtour.in");
	int N;
	// cin >> N;
    fin >> N;
	vector<vector<int>> coor;
	for(int i = 0; i < N; ++i){
		int x, y;
		//cin >> x >> y;
		fin >> x >> y;
		coor.push_back({x, y});
	}
	vector<vector<int>> graph (N);
	for(int i = 0; i < N; ++i){
		string s;
		//cin >> s;
		fin >> s;
// 		cout << "s: " << s << endl;
		for(int j = 0; j < N; ++j){
		  //  if(s[j] == '1') cout << "hello world" << endl;
		    if(s[j] == '1') graph[i].push_back(j);
		}
	}
	
// 	cout << "graph" << endl;
// 	for(vector<int>& adj_list : graph){
// 	    for(int adj : adj_list) cout << adj << ' ';
// 	    cout << endl;
// 	}
// 	cout << endl;
	
	vector<vector<double>> dis (N, vector<double> (N, DBL_MAX));
	vector<int> belong (N, -1);
	int component_ID = 0;
	for(int source = 0; source < N; ++source){
		priority_queue<vector<double>, vector<vector<double>>, greater<vector<double>>> pq; // minheap
		pq.push({0, (double)source});
		vector<int> searched (N, 0);
		while(pq.size() > 0){
			double d = pq.top()[0];
			int node = (int)pq.top()[1];
			
			if(searched[node] == 1){
			    pq.pop();
			    continue;
			}
			
			searched[node] = 1;
			if(belong[node] == -1) belong[node] = component_ID;
			
			dis[source][node] = d;
			pq.pop();
			for(int adj : graph[node]){
				double nd = d + getDis(coor, node, adj); // new distance
				
				// cout << "nd: " << nd << endl;
				
				if(nd < dis[source][adj]){					
					dis[source][adj] = nd;
					pq.push({nd, (double)adj});
				}
			}
		}
		component_ID++;
	}
	
// 	cout << "dis" << endl;
// 	for(vector<double>& row : dis){
// 	    for(double d : row) cout << d << ' ';
// 	    cout << endl;
// 	}
// 	cout << endl;
	
	// furthest is either the path along bridge connecting two furthest pairs, or the diameter of the original separated
	// fields (connected bridge path is still smaller than old diameter)
	
	vector<double> furthest (N, 0);
	for(int source = 0; source < N; ++source){
		double max_d = 0;
		for(int adj = 0; adj < N; ++adj){
			//if(dis[source][adj] != DBL_MAX) furthest[source] = max(furthest[source], dis[source][adj]);
	        if(dis[source][adj] < INT_MAX) furthest[source] = max(furthest[source], dis[source][adj]);
		}
	}
	
	//vector<int> components;
	unordered_map<int, vector<int>> hm;
	for(int node = 0; node < belong.size(); ++node){
		int ID = belong[node];
		if(hm.count(ID) == false) hm.insert({ID, {}});
		hm[ID].push_back(node);
	}
	unordered_map<int, vector<int>>::iterator it;
	unordered_map<int, double> diameter;
	for(it = hm.begin(); it != hm.end(); ++it){
		int ID = it->first;
		diameter.insert({ID, 0});
		vector<int>& component = it->second;
		for(int node : component) diameter[ID] = max(diameter[ID], furthest[node]);
	}
	
	double ans = DBL_MAX;
	for(int node1 = 0; node1 < N; ++node1){
		for(int node2 = node1 + 1; node2 < N; ++node2){
			if(belong[node1] == belong[node2]) continue;
			double dia1 = diameter[belong[node1]];
			double dia2 = diameter[belong[node2]];
			double dia_cand = furthest[node1] + furthest[node2] + getDis(coor, node1, node2);
			double d = max(dia1, dia2);
			d = max(d, dia_cand);
			ans = min(ans, d);
		}
	}
	
	ofstream fout ("cowtour.out");
	fout << setprecision(6) << fixed << ans << endl;
	fin.close();
	fout.close();
	
//*/

	return 0;
}
