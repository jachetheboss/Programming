#include <bits/stdc++.h>
using namespace std;
// DP keeping track of previous sums, even or odd len palindromes, has a 2 or doesnt have a 2
// combinatorics probably too difficult
// could it be more fast exponentiation shii? If the quadratic DP doesn't work, then 
// use prefixes for linear, if still not good, then have to find 
// the logarithmic relation?

/*
int main(){
	// shouldn't be too difficult to find the relation, since we are only looking 
	// for divisibility by 1 million, I would guess that we would have to look for 
	// around a million terms, somewhere around that neighborhood
	// {no 2 even length, no 2 odd length, 2 present even length, 2 present odd length}
	// [sum][one of the 4 describe states]
    vector<vector<int>> DP = { {-1, -1, -1, -1}, {0, 1, 0, 0} };
    vector<vector<int>> odd_prefix = DP;
    vector<vector<int>> even_prefix = DP;
    for(int i = 2; i < odd_prefix.size(); ++i){
        
    }
    for(int i = 2; i < even_prefix.size(); ++i){
        
    }
	
	const int MOD = 1000000;
	int count = 0;
	while(true){
		vector<int> v (4, 0);
		DP.push_back(v);
		int i = DP.size() - 1;
		// i is the index we are currently dealing with (append with), i is also the sum
		if(i % 2 == 0){
			for(int new_val = 1; i - 2 * new_val >= 2; new_val++){
				int j = i - 2 * new_val;
				if(new_val == 2){
					DP[i][2] += DP[j][0];
					DP[i][2] += DP[j][2];
					DP[i][3] += DP[j][3];
					DP[i][3] += DP[j][1];
				}
				else{
					DP[i][2] += DP[j][2];
					DP[i][0] += DP[j][0];
					DP[i][3] += DP[j][3];
					DP[i][1] += DP[j][1];
				}
			}
			// can create a new double center
			if(i == 4){ // can create 4 with two 2's
				DP[i][2]++;
			}else{
				DP[i][0]++;
			}
			// can also create a new single center 
			if(i == 2){
			    DP[i][3]++;
			}else{
			    DP[i][1]++;
			}
			
		}else{ // must be odd length with an odd center (since sum is odd (i is the sum))
			for(int new_val = 1; i - 2 * new_val >= 1; new_val++){
				int j = i - 2 * new_val;
				if(new_val == 2){
					DP[i][3] += DP[j][1];
					DP[i][3] += DP[j][3];
				}
				else{
					DP[i][3] += DP[j][3];
					DP[i][1] += DP[j][1];
				}
			}
			// can also just create a new center
			DP[i][1]++;
		}
		for(int i = 0; i < DP.back().size(); ++i) DP[(int)DP.size() - 1][i] %= MOD;
		int sum = (DP.back()[2] + DP.back()[3]) % MOD;
		if(sum == 0 and i > 42) break; // remainder is 0 when divided by million
		
		cout << "i: " << i << endl;
		
		if(count > 100) break; 
		count++;
	}
	cout << "ans: " << (int)DP.size() - 1;
	
	cout << "DP" << endl;
	for(int i = 0; i < DP.size(); ++i){
	    vector<int>& v = DP[i];
	    cout << "i:" << i << " ";
	    cout << '{';
	    for(int x : v) cout << x << ',';
	    cout << "} ";
	}
	return 0;
}
*/

// ^^^^^^^ O(n^2) algo, below is O(n)

#include <bits/stdc++.h>
using namespace std;

int main(){
	
	vector<vector<int>> DP = { {-1, -1, -1, 1}, {0, 1, 0, 0}, {1, 0, 0, 1}, {0, 2, 0, 0}, {1, 1, 1, 1} };
    vector<vector<int>> prefix = DP;
    prefix[1] = DP[1];
    prefix[2] = DP[2];
    for(int i = 3; i < DP.size(); ++i){
        for(int j = 0; j < DP[i].size(); j++){
            prefix[i][j] += prefix[i - 2][j];
        }
    }
	
	const int MOD = 1000000;
	int count = 0;
	while(true){
		vector<int> v (4, 0);
		DP.push_back(v);
		int i = DP.size() - 1;
	
		// i is the index we are currently dealing with (append with), i is also the sum
		if(i % 2 == 0){
			for(int j = 0; j < DP[i].size(); ++j){
			    DP[i][j] = prefix[i - 2][j];
			    DP[i][j] -= DP[i - 4][j];
			    if(DP[i][j] < 0) DP[i][j] += MOD;
			}
			DP[i][2] += DP[i - 4][0];
			DP[i][2] += DP[i - 4][2];
			DP[i][3] += DP[i - 4][3];
			DP[i][3] += DP[i - 4][1];
			
            DP[i][0]++; // create a new double center
			DP[i][1]++; // create a new single center
			
		}else{ // must be odd length with an odd center (since sum is odd (i is the sum))

			DP[i][3] = prefix[i - 2][3];
			DP[i][1] = prefix[i - 2][1];
			DP[i][3] -= DP[i - 4][3];
			if(DP[i][3] < 0) DP[i][3] += MOD;
			DP[i][1] -= DP[i - 4][1];
			if(DP[i][1] < 0) DP[i][1] += MOD;
			DP[i][3] += DP[i - 4][1];
			DP[i][3] += DP[i - 4][3];
			
			DP[i][1]++; // create a new single center
		}
		
		for(int j = 0; j < DP[i].size(); ++j) DP[i][j] %= MOD;
		
		// remember to update prefix
		prefix.push_back(DP[i]);
		for(int j = 0; j < prefix[i].size(); ++j){
		    prefix[i][j] += prefix[i - 2][j];
		    prefix[i][j] %= MOD;
		}
		
		// check if multiple of million
		int sum = (DP.back()[2] + DP.back()[3]) % MOD;
		if(sum == 0 and i > 42) break; // remainder is 0 when divided by million
		
		if(i % MOD == 0) cout << "i: " << i << endl;
		
// 		if(count > 100) break; 
// 		count++;
	}
	cout << "ans: " << (int)DP.size() - 1;
	
// 	cout << "DP" << endl;
// 	for(int i = 0; i < DP.size(); ++i){
// 	    vector<int>& v = DP[i];
// 	    cout << "i:" << i << " ";
// 	    cout << '{';
// 	    for(int x : v) cout << x << ',';
// 	    cout << "} ";
// 	}
	return 0;
}