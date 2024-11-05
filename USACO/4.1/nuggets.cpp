/*
ID: jamessh3
LANG: C++20
TASK: nuggets
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
	ifstream fin ("nuggets.in");
	ofstream fout ("nuggets.out");
	
	// Frobenius numbers
	int N; fin >> N;
	vector<int> amounts;
	for(int i = 0; i < N; ++i){
		int amt; fin >> amt;
		amounts.push_back(amt);
	}
	// edge cases
	bool unit_amt = false;
	int GCD = amounts[0];
	for(int amt : amounts){
		if(amt == 1) unit_amt = true;
		GCD = __gcd(GCD, amt);
	}
	if(unit_amt == true or GCD > 1){
		fout << 0 << endl;
		return 0;
	}
	
	// find largest pairwise Frobenius #
	int max_frob = -1;
	for(int i = 0; i < amounts.size(); ++i){
		for(int j = i + 1; j < amounts.size(); ++j){
			int GCD = __gcd(amounts[i], amounts[j]);
			if(GCD > 1) continue;
			int frob = amounts[i] * amounts[j] - amounts[i] - amounts[j];
			max_frob = max(max_frob, frob);
		}
	}
	vector<int> DP (max_frob + 1, 0);
	for(int i = 1; i < DP.size(); ++i){ // check if amt i can be made
		for(int amt : amounts){
			if(amt == i){
				DP[i] = 1;
				break;
			}
			if(i - amt > 0 and DP[i - amt] == 1){
				DP[i] = 1;
				break;
			}
		}
	}
	int ans = 0;
	for(int i = (int)DP.size() - 1; i >= 0; --i){
		if(DP[i] == 0){
			ans = i;
			break;
		}
	}
	fout << ans << endl;
	
	fin.close();
	fout.close();
	
	return 0;
}