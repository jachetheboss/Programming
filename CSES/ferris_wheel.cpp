#include <bits/stdc++.h>
using namespace std;

int binarySearch(vector<int>& v, int i, int target){
	if(target < v[0]) return -1;
	if(target < v[i]) return -1;
	if(i == (int)v.size() - 1) return -1;
	if(v[i + 1] > target) return -1;
	
	if(v.back() <= target) return (int)v.size() - 1;
	
	int lo = i + 1;
	int hi = (int)v.size() - 1;
	int mid = (lo + hi);
	while(true){
		if(v[mid] <= target and v[mid + 1] > target) return mid;
		else if(v[mid] > target) hi = mid;
		else if(v[mid + 1] <= target) lo = mid + 1;
		mid = (lo + hi) / 2;		
	}
	return -1;
}

int main()
{
	// incorrect greedy algorithm, should get the biggest one possible, not the 
	// smallest!
	
	int N, X; cin >> N >> X;
	vector<int> weights;
	for(int i = 0; i < N; ++i){
		int w; cin >> w;
		weights.push_back(w);
	}
	sort(weights.begin(), weights.end());
	int ans = 0;
	int put = 0;
	map<int, vector<int>> hm;
	for(int i = 0; i < weights.size(); ++i){
		int w = weights[i];
		if(hm.count(w) == false) hm.insert({w, {}});
		hm[w].push_back(i);
	}
	vector<int> searched (N, 0);
	for(int i = 0; i < weights.size(); ++i){
		if(searched[i] == 1) continue;
		int diff = X - weights[i];
		if(diff < weights[i]){
			ans += N - put;
			break;
		}
		if(weights[i] == hm.rbegin()->first){ // biggest remaining
			int count = hm[weights[i]].size();
			int pairs = count / 2;
			ans += pairs;
			int rem = count % 2;
			if(rem == 1) ans++;
			break;
		}
		int key;
		if(hm.rbegin()->first <= diff){
			key = hm.rbegin()->first;
		}
		else key = (prev(hm.upper_bound(diff)))->first;
		
		if(key == weights[i]){
		    int count = hm[weights[i]].size();
			int pairs = count / 2;
			ans += pairs;
			put += 2 * pairs;
			int rem = count % 2;
			ans += N - put;
			break;
// 			if(rem == 0){
// 			    hm.erase(weights[i]);
// 			    continue;
// 			}else{
//     			vector<int>& ind = hm[weights[i]];
//     			ind.erase(ind.begin() + 1, ind.end());
// 			}
		}
		
		
		int del = min((int)hm[key].size(), (int)hm[weights[i]].size());
		vector<int>& ind1 = hm[weights[i]];
		vector<int>& ind2 = hm[key];
		for(int j = 0; j < del; ++j) searched[ind1[j]] = 1;
		for(int j = (int)ind2.size() - del; j < ind2.size(); ++j) searched[ind2[j]] = 1;
		ind1.erase(ind1.begin(), ind1.begin() + del);
		ind2.erase(ind2.end() - del, ind2.end());
		ans += del;
		put += 2 * del;
		if(ind1.size() == 0) hm.erase(weights[i]);
		if(ind2.size() == 0) hm.erase(key);

	}
	
	cout << ans << endl;


	return 0;
}