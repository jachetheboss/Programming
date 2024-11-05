/*
ID: jamessh3
LANG: C++20
TASK: stamps
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
	ifstream fin ("stamps.in");
	ofstream fout ("stamps.out");
	
	int K, N; fin >> K >> N;
	vector<int> stamps;
	for(int i = 0; i < N; ++i){
		int val; fin >> val;
		stamps.push_back(val);
	}
	bool contains_1 = false;
	int max_stamp = 0;
	for(int stamp : stamps){
		if(stamp == 1) contains_1 = true;
		max_stamp = max(max_stamp, stamp);
	}
	if(not contains_1){
		fout << 0 << endl;
		fin.close();
		fout.close();
		return 0;
	}
	
	int max_possible = K * max_stamp;
	/*
	if(max_possible == 1){
		fout << 1 << endl;
		fin.close();
		fout.close();
		return 0;
	}
	*/
	
	vector<int> DP (max_possible + 1, INT_MAX);
	DP[1] = 1;
	int ans = max_possible;
	for(int i = 2; i < DP.size(); ++i){
		bool early_continue = false;
		for(int stamp : stamps){
			if(i == stamp){
				DP[i] = 1;
				early_continue = true;
				break;
			}
		}
		if(early_continue) continue;
		
		int prev_best = INT_MAX - 1;
		for(int stamp : stamps){
			if(i - stamp > 0){
				prev_best = min(prev_best, DP[i - stamp]);
			}
		}
		int ops = prev_best + 1;
		if(ops > K){
			ans = i - 1;
			break;
		}
		DP[i] = ops;
	}
	
	fout << ans << endl;	
	fin.close();
	fout.close();
	return 0;
}