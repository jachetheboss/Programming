#include <bits/stdc++.h>
using namespace std;

int getBitcount(int x){
	int pow2 = 1;
	int count = 0;
	while(pow2 <= x){
		if((pow2 & x) == pow2) count++;
		pow2 *= 2;
	}
	return count;
}
int main()
{
	int N, X; cin >> N >> X;
	vector<int> weights;
	for(int i = 0; i < X; ++i){
		int w; cin >> w;
		weights.push_back(w);
	}
	// bitmask DP type jaunt
	vector<vector<int>> bitcounts;
	int pow_set_sz = (int)pow(2, N);
	for(int i = 0; i < pow_set_sz; ++i){
		int bitcount = getBitcount(i);
		bitcounts.push_back({bitcount, i});
	}
	
	
	
	return 0;
}