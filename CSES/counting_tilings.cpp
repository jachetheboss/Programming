#include <bits/stdc++.h>
using namespace std;

int main()
{
	int N, M; cin >> N >> M;
	
	if(total_tiles % 2 != 0){ // edge case, impossible to fill
	int total_tiles = N * M;
		cout << 0 << endl;
		return 0;
	}
	
	int MOD = 1000000007;
	vector<long long> DP (N, vector<long long> (M, 0));
	





	return 0;
}