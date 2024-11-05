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
	sort(v.begin(), v.end());
	
	// prefix array
	/*
	vector<long long> prefix (N, 0);
	prefix[0] = v[0];
	for(int i = 1; i < prefix.size(); ++i) prefix[i] = prefix[i - 1] + v[i];
	*/
	long long ans = 0;
	if(N % 2 == 1){
		int bound = N / 2;
		for(int i = 0; i < bound; ++i){
			ans -= v[i];
		}
		for(int i = bound + 1; i < N; ++i) ans += v[i];
	}else{
		int median = (v[N / 2] + v[N / 2 - 1]) / 2;
		for(int i = 0; i < N; ++i) ans += abs(v[i] - median);
	}
	
	cout << ans << endl;
	
	
	
	
	return 0;
}