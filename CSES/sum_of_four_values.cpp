#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n, x; cin >> n >> x;
	vector<int> v;
	for(int i = 0; i < n; ++i){
		int val; cin >> val;
		v.push_back(val);
	}
	unordered_map<int, vector<int>> hm;
	for(int i = 0; i < v.size(); ++i){
		for(int j = i + 1; j < v.size(); ++j){
			int sum = v[i] + v[j];
			if(hm.count(sum) == false) hm.insert({sum, {}});
			hm[sum].push_back(i);
			hm[sum].push_back(j);
		}
	}
	bool found = false;
	vector<int> ans;
	unordered_map<int, vector<int>>::iterator it;
	for(it = hm.begin(); it != hm.end(); ++it){
		int sum = it->first;
		if(sum >= x) continue;
		int target = x - sum;
		if(hm.count(target) == false) continue;
		vector<int>& a = it->second;
		vector<int>& b = hm[target];
		for(int i = 0; i < a.size(); i += 2){
			for(int j = 0; j < b.size(); j += 2){
				if(a[i] != b[j] and a[i] != b[j + 1] and a[i + 1] != b[j] and a[i + 1] != b[j + 1]){
					found = true;
					ans = {a[i] + 1, a[i + 1] + 1, b[j] + 1, b[j + 1] + 1};
					break;
				}
			}
			if(found) break;
		}
	}
	if(not found) cout << "IMPOSSIBLE" << endl;
	else cout << ans[0] << ' ' << ans[1] << ' ' << ans[2] << ' ' << ans[3] << endl;
	
	return 0;
}