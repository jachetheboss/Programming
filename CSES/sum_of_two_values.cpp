#include <bits/stdc++.h>
using namespace std;

int binarySearch(vector<int>& v, int target, int bound){
	if(bound == (int)v.size() - 1) return -1;
	if(bound == (int)v.size() - 2){
		if(v[bound + 1] == target) return bound + 1;
		else return -1;
	}
	
// 	cout << "bound: " << bound << endl;
	
	if(target > v.back()) return -1;
	if(target < v[bound + 1]) return -1;
	int lo = bound + 1;
	int hi = (int)v.size() - 1;
	int mid = (lo + hi) / 2;
	while(true){
		if(v[mid] == target) return mid;
		if(v[mid + 1] == target) return mid + 1;
		if(v[mid] < target and target < v[mid + 1]) return -1;
		if(v[mid] > target) hi = mid;
		else if(target > v[mid + 1]) lo = mid + 1;
		mid = (lo + hi) / 2;
		
// 		cout << "lo: " << lo << " hi: " << hi << " mid: " << mid << endl;
		
	}
	return -1;
}

int main()
{
	int N, X; cin >> N >> X;
	
	if(N == 1){
		cout << "IMPOSSIBLE" << endl;
		return 0;
	}
	
	vector<int> original;
	vector<vector<int>> arr;
	for(int i = 0; i < N; ++i){
		int val; cin >> val;
		original.push_back(val);
		arr.push_back({val, i});
	}
	sort(arr.begin(), arr.end());
	vector<int> v;
	for(vector<int>& a : arr) v.push_back(a[0]);
	// binary searches
	vector<int> ans;
	for(int i = 0; i < v.size() - 1; ++i){
		int diff = X - v[i];
		if(diff > v.back()) continue;
		if(diff == v.back()){
		    ans = {i, (int)v.size() - 1}; 
		    break;
		}
		if(diff < v[i]) break;
		if(diff == v[i]){
			if(i != (int)v.size() - 1){
				if(v[i + 1] == v[i]){
					ans = {i, i + 1};
				}
				break;
			}
		}
		else{
			int idx = binarySearch(v, diff, i);
			if(idx == -1) continue;
			ans = {i, idx};
			//cout << "v[i]: " << v[i] << " diff: " << diff << "  i: " << i << " idx: " << idx << endl;
			break;
		}
	}
	
// 	cout << "hello world" << endl;
	
	if(ans.size() == 0) cout << "IMPOSSIBLE" << endl;
	else{
		// convert to 1-indexed
// 		ans[0]++;
// 		ans[1]++;
// 		cout << "bruh" << endl;
		
// 		cout << ans[0] << ' ' << ans[1] << endl;	
		int x = arr[ans[0]][1];
		int y = arr[ans[1]][1];
		x++;
		y++;
		cout << x << " " << y << endl;
// 		cout << original[x] << ' ' << original[y] << endl;
	}
	
	return 0;
}