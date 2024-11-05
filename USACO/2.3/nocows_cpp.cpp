/*
ID: jamessh3
LANG: C++20
TASK: nocows
*/



#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

int main()
{
    // can stop algorithm early when N, K input is reached,
    // don't have to calculate to max constraint N, K reached
	
	ifstream fin ("nocows.in");
	ofstream fout ("nocows.out");
	
    int N;
    int K;
    // cout << "Enter N: ";
    // cin >> N;
    // cout << "Enter K: ";
    // cin >> K;
	
	fin >> N >> K;
	
	int min_possible_depth = (int)(floor(log2(N)));
	int max_possible_depth = (N - 1) / 2 + 1;
	
	if(K > max_possible_depth || K < min_possible_depth || N % 2 != 1){
		fout << 0 << '\n';
		return 0;
	}
    
    int MOD = 9901;
    int ans;
    
    vector<vector<int>> prefix (100, vector<int>(100, 0));
    vector<vector<int>> DP (100, vector<int>(100, 0));
    
   //  [nodes / 2][height]
    
    DP[0][0] = 1; // 1 way for 0 nodes, height 0
    DP[1][1] = 1; // 1 way for 2 nodes, height 1 
    prefix[0][0] = 1;
    prefix[1][1] = 1;
    for(int i = 0; i <= 1; ++i){
        for(int j = i + 1; j < prefix[0].size(); ++j){
            prefix[i][j] = prefix[i][j - 1];
        }
    }
    
    for(int i = 1; i < DP.size() - 1; ++i){ // i is additional nodes (nodes excluding 3 default top nodes) / 2
        // nodes is 2 * i
        int bound = i / 2;

        for(int left = 0; left <= bound; ++left){
            // multiply by two, mirrored trees
            int right = i - left;
            int min_left_h = (int)(floor(log2(2 * left + 1))); // h for height
            int max_left_h = left;
            int min_right_h = (int)(floor(log2(2 * right + 1)));
            int max_right_h = right;
            
            int inc;
            
            for(int h = min_left_h; h <= max_left_h; ++h){ // left subtree determines height
                if(h > 0){
                    inc = DP[left][h] * prefix[right][h - 1];
                    if(left != right)
                        inc *= 2;
                    DP[i + 1][h + 1] += inc;
                    DP[i + 1][h + 1] %= MOD;
                }
            }for(int h = min_right_h; h <= max_right_h; ++h){ // right subtree determines height
                if(h > 0){
                    inc = DP[right][h] * prefix[left][h - 1];
                    if(left != right)
                        inc *= 2;
                    DP[i + 1][h + 1] += inc;
                    DP[i + 1][h + 1] %= MOD;
                }
            }
            int min_h = min(min_left_h, min_right_h); // when left and right have same height
                                                    // not necessarily same # nodes though
            int max_h = max(max_left_h, max_right_h);
            for(int h = min_h; h <= max_h; ++h){
                inc = DP[right][h] * DP[left][h];
                if(left != right)
                    inc *= 2;
                DP[i + 1][h + 1] += inc;
                DP[i + 1][h + 1] %= MOD;
            }
            
            // I think logic error is here
            // if(left != right){ // we multiply by two unless left and right, since mirrored
            //     for(int h = 0; h < DP[0].size(); ++h){
            //         DP[i + 1][h] *= 2; // mirrored;
            //         DP[i + 1][h] %= MOD;
            //     }
            // }
        }
        
        if(2 * i + 3 == N){
            ans = DP[i + 1][K - 1];
            cout << "ans: " << DP[i + 1][K] << endl;
			
			fout << ans << '\n';
			
			return 0;
			
            // break;
        }
        
        // build prefix for this i
        prefix[i + 1][0] = DP[i + 1][0];
        for(int j = 1; j < prefix[0].size(); ++j){
            prefix[i + 1][j] = prefix[i + 1][j - 1] + DP[i + 1][j];
            prefix[i + 1][j] %= MOD;
        }
    }
    
    // cout << endl << "nodes     depth" << endl;
    // cout << "     ";
    // for(int depth = 0; depth <= 14; ++depth){
    //     cout << to_string(depth) << string(8 - (int)(to_string(depth)).length(), ' ');
    // } cout << endl;
    
    // for(int i = 0; i <= 14; ++i){
    //     string num_nodes = to_string(2 * i + 1);
    //     cout << num_nodes << ':' << string(4 - (int)num_nodes.length(), ' ');
    //     for(int j = 0; j <= 14; ++j){
    //         string s = to_string(DP[i][j]);
    //         string spaces = string(8 - (int)s.length(), ' ');
    //         cout << s << spaces;
    //     }
    //     cout << endl;
    // }
    
    // cout << "ans: " << ans << endl;
    
    return 0;
}
