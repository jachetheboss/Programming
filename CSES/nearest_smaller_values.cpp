#include <bits/stdc++.h>
using namespace std;

int main()
{
	int N; cin >> N;
	vector<int> v;
	for(int i = 0; i < N; ++i){
		int val; cin >> val;
		v.push_back(val);
	}
	if(N == 1){
		cout << 0 << endl;
		return 0;
	}
	// 1-indexed!!!!!!!
	// solve using monotonic stack, topological sort, sqrt decomp
	/*
	int block_sz = (int)floor(sqrt(N));
	vector<int> blocks;
	for(int L = 0; L < N; L += block_sz){
		int R = min(L + block_sz - 1, N - 1);
		int mn = INT_MAX;
		for(int i = L; i <= R; ++i) mn = min(mn, v[i]);
		blocks.push_back(mn);
	}
	int rolling_block_min = v[0];
	vector<int> ans = {0};
	for(int i = 1; i < N; ++i){
		int block = i / block_sz;
		int L = block * block_sz;
		bool smaller_found = false;
		int idx = 0;
		if(i == L) rolling_block_min = v[i];
		else if(rolling_block_min < v[i]){
			for(int j = i - 1; j >= L; --j){
				if(v[j] < v[i]){
					idx = j + 1;
					smaller_found = true;
					break;
				}
			}
		}
		if(not smaller_found){
			for(int bl = block - 1; bl >= 0; --bl){
				if(blocks[bl] < v[i]){
					int Lbl = bl * block_sz;
					int Rbl = Lbl + block_sz - 1;
					for(int j = Rbl; j >= Lbl; --j){
						if(v[j] < v[i]){
							idx = j + 1;
							smaller_found = true;
							break;
						}
					}
				}
				if(smaller_found) break;
			}
		}
		ans.push_back(idx);
		
		rolling_block_min = min(rolling_block_min, v[i]);
	}
	for(int i = 0; i < (int)ans.size() - 1; ++i) cout << ans[i] << ' ';
	cout << ans.back() << endl;
	*/
	
	/*
	map<int, vector<int>> hm;
	for(int i = 0; i < v.size(); ++i){
		if(hm.count(v[i]) == false) hm.insert({v[i], {}});
		hm[v[i]].push_back(i);
	}
	set<int> ind;
	vector<int> ans (N, 0);
	map<int, vector<int>>::iterator it;
	for(it = hm.begin(); it != hm.end(); ++it){
		if(it == hm.begin()){
			for(int idx : it->second) ind.insert(idx);
			continue;
		}
		for(int idx : it->second){
			if(idx < *(ind.begin())) continue; // do nothing, already ans[idx] = 0
			else if(idx > *(ind.rbegin())) ans[idx] = *(ind.rbegin()) + 1; // make it 1-indexed
			else{
				int idx1 = *(prev(ind.upper_bound(idx)));
				ans[idx] = idx1 + 1; // make it 1-indexed
			}
		}
		for(int idx : it->second) ind.insert(idx);
	}
	for(int i = 0; i < (int)ans.size() - 1; ++i) cout << ans[i] << ' ';
	cout << ans.back() << endl;
	*/
	
	// monotonic stack
	vector<int> ans = {-1};
	vector<int> mono = {0};
	for(int i = 1; i < v.size(); ++i){
		while(mono.size() > 0 and v[mono.back()] >= v[i]) mono.pop_back();
		if(mono.size() == 0) ans.push_back(-1);
		else ans.push_back(mono.back());
		mono.push_back(i);
	}
	
	for(int i = 0; i < (int)ans.size() - 1; ++i) cout << ans[i] + 1 << ' ';
	cout << ans.back() + 1 << endl;
	
	return 0;
}