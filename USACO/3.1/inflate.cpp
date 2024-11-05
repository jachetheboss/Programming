/*
ID: jamessh3
LANG: C++20
TASK: inflate
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
	ifstream fin ("inflate.in");
	int M, N; fin >> M >> N;
	// O(n^2) DP?
	//vector<vector<int>> categories;
	unordered_map<int, int> hm;
	for(int i = 0; i < N; ++i){
		int p, m; fin >> p >> m; // points, minutes
		//categories.push_back({p, m});
		if(hm.count(m) == false) hm.insert({m, 0});
		hm[m] = max(hm[m], p);
	}
	vector<vector<int>> categories;
	unordered_map<int, int>::iterator it;
	for(it = hm.begin(); it != hm.end(); ++it){
		int minutes = it->first;
		int points = it->second;
		categories.push_back({minutes, points});
	}
	
	// DP on dis bitch
	vector<int> DP (M + 1, -1);
	for(vector<int>& pair : categories){
		int m = pair[0];
		int points = pair[1];
		
// 		cout << "m: " << m << " points: " << points << endl;
		
		// do a DP on this, should be O(n log n) complexity? harmonic series
		// no, is O(n^2) since it is done on all sum amounts reached!
		if(m > M) continue;
		DP[m] = max(DP[m], points);
		int i = m;
		while(i + m < DP.size()){
			DP[i + m] = max(DP[i + m], DP[i] + points);
			i += m;
		}
		for(int start = 0; start < m; ++start){
			bool ok = false;
			int i = start;
			while(i + m < DP.size()){
				if(not ok){
					if(DP[i] == -1){
						
					}else{
						ok = true;
						DP[i + m] = max(DP[i + m], DP[i] + points);
					}
				}else{
					DP[i + m] = max(DP[i + m], DP[i] + points);
				}
				i += m;
			}
		}
	}
	int ans = 0;
	for(int total : DP) ans = max(ans, total);
	
	ofstream fout ("inflate.out");
	fout << ans << endl;
	
	fin.close();
	fout.close();
	
	return 0;
}