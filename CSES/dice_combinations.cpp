#include <bits/stdc++.h>
using namespace std;

int main()
{
	int N; cin >> N;
	vector<long long> DP (N + 1, 0);
	int MOD = 1000000007;
	DP[0] = 1;
	for(int i = 1; i < DP.size(); ++i){
		for(int j = 1; j <= 6; ++j){
			if(i - j >= 0) DP[i] += DP[i - j];
		}
		DP[i] %= MOD;
	}
	cout << DP.back() << endl;
	
	
	return 0;
}