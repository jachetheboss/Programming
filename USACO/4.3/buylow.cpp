/*
ID: jamessh3
LANG: C++20
TASK: buylow
*/

/*
#include <bits/stdc++.h>
using namespace std;

// MUST USE BIGNUMS! Write your own bignum class, using long longs?

vector<long long> add(vector<long long>& a, vector<long long>& b){
	vector<long long> sum;
	long long base = 1000000000000000000L;
	long long carry = 0;
	int i = 0;
	while(i < a.size() or i < b.size()){
		if(i == a.size()){
			
		}else if(i == b.size()){
			
		}
	}
}

int main()
{
    // REMEMBER, EACH SEQUENCE MUST BE UNIQUE!
	
	// include some introspective logic, if about to overflow, switch 
	// from native int type to bignum type
    
	// sqrt decomp on sorted sqrt blocks + O(n^2) DP? will in run in time?
	// ^^^ time complexity would be O(n^2 sqrt n) I think
	// how about segtree, would be O(n^2 log n)
	
	ifstream fin ("buylow.in");
	ofstream fout ("buylow.out");
	int N; fin >> N;
	vector<int> prices;
	for(int i = 0; i < N; ++i){
		int p; fin >> p; prices.push_back(p);
	}
	vector<vector<int>> DP (prices.size(), vector<int> (prices.size() + 1, -1));
	DP[0][0] = 1;
	DP[0][1] = 1; // DP[i][j] == 1 means subseq with len j, ending at i exists
	for(int i = 1; i < DP.size(); ++i){
		DP[i][0] = 1;
		DP[i][1] = 1;
		for(int j = 0; j < i; ++j){
			if(prices[j] > prices[i]){
				for(int k = 0; k < DP[j].size(); ++k){
					if(DP[j][k] == -1) break;
					// subseq length of k
					DP[i][k + 1] = 1;
				}
			}
		}
	}
	
// 	cout << "DP" << endl;
// 	for(int i = 0; i < DP.size(); ++i){
// 	    for(int x : DP[i]) cout << x << ' ';
// 	    cout << endl;
// 	}
	
	int longest = 0;
	for(int i = 0; i < DP.size(); ++i){
	    int i_best = -1;
	    for(int len = (int)DP[i].size() - 1; len >= 0; --len){
    		if(DP[i][len] == 1){
    			i_best = len;
    			break;
    		}
    	}
    	longest = max(longest, i_best);
	}
	
	cout << "longest: " << longest << endl;
	
	DP = vector<vector<int>> (prices.size(), vector<int> (prices.size() + 1, 0));
	DP[0][0] = 1;
	DP[0][1] = 1;
	for(int i = 1; i < DP.size(); ++i){
	    DP[i][0] = 1;
	    DP[i][1] = 1;
	    set<int> seen;
	    for(int j = i - 1; j >= 0; --j){
	        if(prices[j] <= prices[i] or seen.count(prices[j])) continue;
	        seen.insert(prices[j]);
	        for(int k = 1; k < DP[j].size(); ++k){
	            if(DP[j][k] == 0) break;
	            DP[i][k + 1] += DP[j][k];
	        }
	    }
	}
	
// 	cout << "DP" << endl;
// 	for(int i = 0; i < DP.size(); ++i){
// 	    for(int x : DP[i]) cout << x << ' ';
// 	    cout << endl;
// 	}
	set<int> seen;
	int count = 0;
	for(int i = (int)DP.size() - 1; i >= 0; --i){
	    if(seen.count(prices[i])) continue;
	    seen.insert(prices[i]);
	    count += DP[i][longest];
	}
	cout << "count: " << count << endl;
	
	fout << longest << ' ' << count << endl;
	
	fin.close();
	fout.close();
	
	return 0;
}
*/




///*

#include <bits/stdc++.h>

//#pragma GCC optimize("Ofast")
//#pragma GCC target("avx,avx2,fma")

// #define ll long long

using namespace std;

void printBignum(vector<int> num){
    for(int i = (int)num.size() - 1; i >= 0; --i){
        int d = num[i];
        cout << d;
    }
    cout << endl;
}

vector<int> add(vector<int>& a, vector<int>& b, vector<int>& zero){
    
    // if(a.size() == 0 or b.size() == 0){
    //     cout << "a or b empty" << endl;
    // }
    
    if(a == zero and b == zero) return {0};
    if(a == zero) return b;
    if(b == zero) return a;
    
	vector<int> sum;
	int base = 100000000;
	int carry = 0;
	int i = 0;
	while(i < a.size() or i < b.size()){
	    int digit = carry;
		if(i != a.size()) digit += a[i];
		if(i != b.size()) digit += b[i];
		if(digit >= base){
		    digit -= base;
		    carry = 1;
		}else carry = 0;
		
		sum.push_back(digit);
		
		i++;
	}
	if(carry == 1) sum.push_back(1);
	
// 	if(sum.size() == 0){
// 	    cout << "empty sum" << endl;
// 	}
	
	return sum;
}

int main()
{
    // REMEMBER, EACH SEQUENCE MUST BE UNIQUE!
    
	// sqrt decomp on sorted sqrt blocks + O(n^2) DP? will in run in time?
	// ^^^ time complexity would be O(n^2 sqrt n) I think
	// how about segtree, would be O(n^2 log n)
	
	ifstream fin ("buylow.in");
	ofstream fout ("buylow.out");
	int N; fin >> N;
	vector<int> prices;
	for(int i = 0; i < N; ++i){
		int p; fin >> p; prices.push_back(p);
	}
// 	vector<vector<int>> DPa (prices.size(), vector<int> (prices.size() + 1, -1));
// 	DPa[0][0] = 1;
// 	DPa[0][1] = 1; // DP[i][j] == 1 means subseq with len j, ending at i exists
// 	for(int i = 1; i < DPa.size(); ++i){
// 		DPa[i][0] = 1;
// 		DPa[i][1] = 1;
// 		for(int j = 0; j < i; ++j){
// 			if(prices[j] > prices[i]){
// 				for(int k = 0; k < DPa[j].size(); ++k){
// 					if(DPa[j][k] == -1) break;
// 					// subseq length of k
// 					DPa[i][k + 1] = 1;
// 				}
// 			}
// 		}
// 	}
	
// 	cout << "DP" << endl;
// 	for(int i = 0; i < DP.size(); ++i){
// 	    for(int x : DP[i]) cout << x << ' ';
// 	    cout << endl;
// 	}
	
// 	int longest = 0;
// 	for(int i = 0; i < DPa.size(); ++i){
// 	    int i_best = -1;
// 	    for(int len = (int)DPa[i].size() - 1; len >= 0; --len){
//     		if(DPa[i][len] == 1){
//     			i_best = len;
//     			break;
//     		}
//     	}
//     	longest = max(longest, i_best);
// 	}
	
// 	cout << "longest: " << longest << endl;

    vector<int> DPa (prices.size(), 1);
    for(int i = 1; i < prices.size(); ++i){
        for(int j = 0; j < i; ++j){
            if(prices[j] > prices[i]){
                DPa[i] = max(DPa[i], DPa[j] + 1);
            }
        }
    }
    int longest = 0;
    for(int x : DPa) longest = max(longest, x);
    cout << "longest: " << longest << endl;
	
// 	vector<vector<vector<int>>> DP (prices.size(), vector<vector<int>> (prices.size() + 1, vector<int> (1, 0)));
// 	DP[0][0] = {1};
// 	DP[0][1] = {1};
	
	vector<int> zero = {0};
	
// 	for(int i = 1; i < DP.size(); ++i){
// 	    DP[i][0] = {1};
// 	    DP[i][1] = {1};
// 	    set<int> seen;
// 	    for(int j = i - 1; j >= 0; --j){
// 	        if(prices[j] <= prices[i] or seen.count(prices[j])) continue;
// 	        seen.insert(prices[j]);
// 	        for(int k = 1; k < DP[j].size(); ++k){
// 	            if(DP[j][k] == zero) break;
// 	            DP[i][k + 1] = add(DP[i][k + 1], DP[j][k]);
// 	        }
// 	    }
// 	}
	
// 	cout << "DP" << endl;
// 	for(int i = 0; i < DP.size(); ++i){
// 	    for(int x : DP[i]) cout << x << ' ';
// 	    cout << endl;
// 	}


    map<int, pair<int, vector<int>>> hs;
    map<int, pair<int, vector<int>>>::iterator it;
   
   // utilize some pruning! Should save memory.
   
    // vector<vector<int>> v;
    //for(int j = 0; j < prices.size(); ++j){
    for(int p : prices){
// 		int p = prices[j];
		
// 		vector<vector<int>> next_v;
		
//         for(int i = 0; i < v.size(); ++i){
//             if(p == v[i][0] or v[i][1] + (int)prices.size() - j < longest){
// 				continue;
//             }else{
// 				next_v.push_back(v[i]);
// 			}
//         }
// 		v = next_v;
    //     for(int i = 0; i < v.size(); ++i){
    //         if(p == v[i][0]){
				// v.erase(v.begin() + i);
				// break;
    //         }
    //     }
        
        // vector<int> ele = {p, 1, 1};
        // vector<int> prev_count = {1};
        
        pair<int, vector<int>> pr;
        pr.first = 1;
        pr.second = {1};
        
        hs[p] = pr;
        for(it = hs.begin(); it != hs.end(); ++it){
        // for(vector<int>& ab : v){
            int x = it->first;
            // int x = ab[0];
            if(x <= p) continue;
            int L = (it->second).first;
            // int L = ab[1];
            vector<int>& count = (it->second).second;
            // vector<int> count;
            //for(int i = 2; i < ab.size(); ++i) count.push_back(ab[i]);
            // count.assign(ab.begin() + 2, ab.end());
            
            // if(L + 1 > ele[1]){
            //     ele = ab;
            //     ele[0] = p;
            //     ele[1] = L + 1;
            //     prev_count.clear();
            //     // for(int i = 2; i < ele.size(); ++i) prev_count.push_back(ele[i]);
            //     prev_count.assign(ele.begin() + 2, ele.end());
                
            // }else if(L + 1 == ele[1]){
            //     prev_count = add(prev_count, count, zero);
            // }
            if(L + 1 > pr.first){
                pr.first = L + 1;
                pr.second = count;
            }else if(L + 1 == pr.first){
                pr.second = add(pr.second, count, zero);
            }
        }
        hs[p] = pr;
        // ele = {ele[0], ele[1]};
        // for(int y : prev_count) ele.push_back(y);
        // copy(prev_count.begin(), prev_count.end(), back_inserter(ele));
        // for(int i = 0; i < prev_count.size(); ++i){
        //     if(i + 2 == ele.size()) ele.push_back(prev_count[i]);
        //     else ele[i + 2] = prev_count[i];
        // }
        // int L = ele[1];
        // ele = prev_count;
        // ele.insert(ele.begin(), L);
        // ele.insert(ele.begin(), p);
        // v.push_back(ele);
    }
    
    vector<int> ans = {0};
    for(it = hs.begin(); it != hs.end(); ++it){
        int L = (it->second).first;
        if(L == longest){
            ans = add(ans, (it->second).second, zero);
        }
    }
    vector<int> count = ans;
    
    // for(vector<int>& a : v){
    //     int L = a[1];
    //     if(L == longest){
    //         vector<int> count;
    //         for(int i = 2; i < a.size(); ++i) count.push_back(a[i]);
    //         ans = add(ans, count, zero);
    //     }
    // }
    
    // cout << "hs.size() " << hs.size() << endl;


	/*set<int> seen;
	vector<int> count = {0};
	for(int i = (int)DP.size() - 1; i >= 0; --i){
	    if(seen.count(prices[i])) continue;
	    seen.insert(prices[i]);
	    count = add(count, DP[i][longest]);
	}
	
	//cout << "count: " << count << endl;
	cout << "count: ";
	printBignum(count);
	*/
	//fout << longest << ' ' << count << endl;
// 	fout << longest << ' ';
// 	for(int i = (int)count.size() - 1; i >= 0; --i){
//         fout << count[i];
//     }
//     fout << endl;
    fout << longest << ' ';
	for(int i = (int)ans.size() - 1; i >= 0; --i){
        fout << ans[i];
    }
    fout << endl;
	
	
	fin.close();
	fout.close();
	
	return 0;
}
//*/