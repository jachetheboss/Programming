#include <bits/stdc++.h>
using namespace std;

bool binarySearch(vector<long long>& v, long long target){
	if(target < v[0] or target > v.back()) return false;
	int lo = 0;
	int hi = (int)v.size() - 1;
	int mid = (lo + hi) / 2;
	while(true){
		if(v[mid] == target) return true;
		if(v[mid + 1] == target) return true;
		if(v[mid] < target and target < v[mid + 1]) return false;
		else if(target < v[mid]) hi = mid;
		else if(target > v[mid + 1]) lo = mid + 1;
		mid = (lo + hi) / 2;
	}
	return false;
}

int main(){
	int N, X; cin >> N >> X;
	vector<long long> prefix;
	for(int i = 0; i < N; ++i){
		int val; cin >> val;
		if(prefix.size() == 0) prefix.push_back(val);
		else prefix.push_back(prefix.back() + val);
	}
	// binary searches
	int ans = 0;
	for(int i = 0; i < N; ++i){
		long long target = X;
		if(i > 0) target += prefix[i - 1];
		if(binarySearch(prefix, target)) ans++;
	}
	cout << ans << endl;
	
	
	return 0;
}