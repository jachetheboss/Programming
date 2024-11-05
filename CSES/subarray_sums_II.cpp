#include <bits/stdc++.h>
using namespace std;

int binarySearch(vector<int>& v, int x){
	if(x <= v[0]) return v.size();
	if(x == v.back()) return 1;
	if(x > v.back()) return 0;
	int lo = 0;
	int hi = (int)v.size() - 1;
	int mid = (lo + hi) / 2;
	while(true){
		if(x > v[mid] and x <= v[mid + 1]) return (int)v.size() - 1 - mid;
		if(x == v[mid] and x < v[mid + 1]) return (int)v.size() - mid;
		if(x <= v[mid]) hi = mid;
		else if(x > v[mid + 1]) lo = mid + 1;
		mid = (lo + hi) / 2;
	}
	return -1;
}

int main()
{
	int N, X; cin >> N >> X;
	//unordered_map<long long, vector<int>> prefix;
	map<long long, vector<int>> prefix;
	long long rolling_sum = 0;
	vector<int> v;
	for(int i = 0; i < N; ++i){
		int val; cin >> val;
		v.push_back(val);
		rolling_sum += val;
		if(prefix.count(rolling_sum) == false) prefix.insert({rolling_sum, {}});
		prefix[rolling_sum].push_back(i);
	}
	rolling_sum = 0;
	long long ans = 0;
	for(int i = 0; i < v.size(); ++i){
		long long target = rolling_sum + X;
		if(prefix.count(target) == true){
    		vector<int>& ind = prefix[target];
    		ans += binarySearch(ind, i);
		}
		rolling_sum += v[i];
	}
	cout << ans << endl;
	
	
	
	
	return 0;
}