/*
ID: jamessh3
LANG: C++20
TASK: game1
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
	ifstream fin ("game1.in");
	ofstream fout ("game1.out");
	
	int N; fin >> N;
	vector<int> nums;
	for(int i = 0; i < N; ++i){
		int val; fin >> val; nums.push_back(val);
	}
	
	// O(n^2) DP
	vector<vector<vector<int>>> alice_DP (N, vector<vector<int>> (N, vector<int> (2, 0)));
	// {alice score, bob score}
	vector<vector<vector<int>>> bob_DP (N, vector<vector<int>> (N, vector<int> (2, 0)));
	bool alice_move = true;
	if(N % 2 == 0) alice_move = false; // working backwards (alice always moves first)
	if(alice_move){
		for(int i = 0; i < nums.size(); ++i) alice_DP[i][i] = {nums[i], 0};
	}else{
		for(int i = 0; i < nums.size(); ++i) bob_DP[i][i] = {0, nums[i]};
	}
	alice_move = not alice_move;
	for(int subarr_len = 2; subarr_len <= N; ++subarr_len){
		int bound = N - subarr_len;
		for(int L = 0; L <= bound; ++L){ // L left bound
			// try both left and right endpoints of the subarray
			int R = L + subarr_len - 1;
			if(alice_move){
				// choose the one that benefits alice the most,
				// messes up bob the most
				int alice_score1 = nums[L] + bob_DP[L + 1][R][0];
				int bob_score1 = bob_DP[L + 1][R][1];
				int alice_score2 = nums[R] + bob_DP[L][R - 1][0];
				int bob_score2 = bob_DP[L][R - 1][1];
				if(alice_score1 >= alice_score2){
					alice_DP[L][R][0] = alice_score1;
					alice_DP[L][R][1] = bob_score1;
				}else{
					alice_DP[L][R][0] = alice_score2;
					alice_DP[L][R][1] = bob_score2;
				}
			}else{
				int alice_score1 = alice_DP[L + 1][R][0];
				int bob_score1 = nums[L] + alice_DP[L + 1][R][1];
				int alice_score2 = alice_DP[L][R - 1][0];
				int bob_score2 = nums[R] + alice_DP[L][R - 1][1];
				if(bob_score1 >= bob_score2){
					bob_DP[L][R][0] = alice_score1;
					bob_DP[L][R][1] = bob_score1;
				}else{
					bob_DP[L][R][0] = alice_score2;
					bob_DP[L][R][1] = bob_score2;
				}
			}
		}
		alice_move = not alice_move;
	}
	
	int alice_score = alice_DP[0].back()[0];
	int bob_score = alice_DP[0].back()[1];
	fout << alice_score << ' ' << bob_score << endl;
	
// 	for(int i = 0; i < alice_DP.size(); ++i){
// 	    for(int j = i; j < alice_DP[i].size(); ++j){
// 	        cout << "i: " << i << " j: " << j << endl;
// 	        cout << "{" << alice_DP[i][j][0] << ',' << alice_DP[i][j][1] << '}' << endl;
// 	    }
// 	}
	
	fin.close();
	fout.close();
	return 0;
}