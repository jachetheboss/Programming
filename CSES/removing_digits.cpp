#include <bits/stdc++.h>
using namespace std;

int main()
{
	int N; cin >> N;
	vector<int> DP (N + 1, INT_MAX);
	DP[0] = 0;
	for(int i = 1; i < DP.size(); ++i){
		int num = i;
		int best = INT_MAX;
		while(num > 0){
			int d = num % 10;
			int idx = i - d;
			best = min(best, DP[idx]);
			num /= 10;
		}
		DP[i] = best + 1;
	}
	cout << DP.back() << endl;
	
	return 0;
}