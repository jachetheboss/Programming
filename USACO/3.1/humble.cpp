/*
ID: jamessh3
LANG: C++20
TASK: humble
*/

#include <bits/stdc++.h>
#include <ctime>
using namespace std;

bool isHumble(int num, vector<int>& primes){
	for(int p : primes){
		while(num % p == 0) num /= p;
		if(num == 1) return true;
	}
	return false;
}

double mylog(int base, int val){
    return log2(val) / log2(base);
}

int bruteForce(vector<int>& primes, int N){

	int count = 0;
	int num = 2;
	while(count < N){
		if(isHumble(num, primes)) count++;
		num++;
	}
	return num - 1;
}

int main()
{
    // how about algo that estimates the number of humble numbers in a range
	
	// is there algo that calculates exactly how many humble numbers there are in a range?
	
    
	// binary search? sqrt bounds? recursive backtracking?
	// invert? find non-humble numbers?
	
	// sieving?
	
	time_t ct = clock();
	
	ifstream fin ("humble.in");
	ofstream fout ("humble.out");
	int K, N; fin >> K >> N;
	// int N = 100000;
    // vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};//, 41};//, 43};// 47, 53, 59, 61, 67, 71};// 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293};
	vector<int> primes;
	for(int i = 0; i < K; ++i){
		int p; fin >> p;
		primes.push_back(p);
	}
	sort(primes.begin(), primes.end());
	// if first 20 primes found
	vector<int> first_20 = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71};
	if(primes.size() >= 20){
	    bool ok = true;
	    for(int i = 0; i < 20; ++i){
	        if(primes[i] != first_20[i]){
	            ok = false;
	            break;
	        }
	    }
	    if(ok){
	        int ans = bruteForce(primes, N);
	        fout << ans << endl;
	        fin.close();
	        fout.close();
	        return 0;
	    }
	}
	
	// singles
// 	vector<int> cand;
// 	for(int p : primes) cand.push_back(p);
// 	// pairs
// 	for(int i = 0; i < primes.size(); ++i){
// 	    for(int j = i; j < primes.size(); ++i){
// 	        int prod = primes[i] * primes[j];
// 	        cand.push_back(prod);
// 	    }
// 	}
// 	// triples
// 	for(int i = 0; i < primes.size(); ++i){
// 	    for(int j = i; j < primes.size(); ++j){
// 	        for(int k = j; k < primes.size(); ++k){
// 	            int prod = primes[i] * primes[j] * primes[k];
// 	            cand.push_back(prod);
// 	        }
// 	    }
// 	}
// 	sort(cand.begin(), cand.end());
// 	int bound = cand[N - 1];
// 	for(int )
// 	// quads

    // backtracking
    set<long long> hs;
    int L_max = (int)floor(mylog(primes[0], INT_MAX));
    // cout << "L_max: " << L_max << endl;
    // cout << "K: " << K << " N: " << N << endl;
    
    // cout << "bruteForce ans: " << bruteForce(primes, N) << endl;
    
    for(int L = 1; L <= L_max; ++L){
        //for(int start = 0; start < primes.size(); ++start){ // does logic already cover this loop?
        
            // cout << "hs.size() " << hs.size() << endl;    
        
            int start = 0;
            vector<int> ind_stk;
            vector<long long> prod_stk;
            long long prod = 1;
            bool too_big = false;
            for(int cnt = 0; cnt < L; ++cnt){
                ind_stk.push_back(start);
                prod *= primes[start];
                if(prod > INT_MAX){
                    too_big = true;
                    break;
                }
                prod_stk.push_back(prod);
            }
            
            if(too_big) break;
            //if(hs.size() == N and prod > *(hs.rbegin())) break;
            
            long long iter = 0;
            
            while(true){
                
                iter++;
                
                hs.insert(prod);
                while(hs.size() > N){
                //if(hs.size() > N){
                    // cout << "hs.size() " << hs.size() << endl;
                    long long mx = *(hs.rbegin());
                    hs.erase(mx);
                }
                
                // cout << "jache" << endl;
                
                // increment ind_stk
                while(ind_stk.back() == K - 1){
                    ind_stk.pop_back();
                    prod_stk.pop_back();
                    if(ind_stk.size() == 0) break;
                }
                if(ind_stk.size() == 0) break;
                
                // cout << "boss" << endl;
                
                int sz = ind_stk.size();
                bool next_found = false;
                bool done = false;
                
                // cout << "iter " << iter << endl;
                
                while(not next_found){
                    
                    // cout << clock() << endl;
                    // cout << "hs.size() " << hs.size() << endl;
                    // cout << "ind_stk.size() " << ind_stk.size() << endl;
                    // for(int idx : ind_stk) cout << idx << ' ';
                    // cout << endl;
                    // cout << "prod_stk.size() " << prod_stk.size() << endl;
                    // for(long long x : prod_stk) cout << x << ' ';
                    // cout << endl;
                    // cout << "sz: " << sz << endl;
                    
                    if(sz == 0){
                        done = true;
                        break;
                    }
                    
                    while(ind_stk.size() > sz){
                        ind_stk.pop_back();
                        prod_stk.pop_back();
                    }
                    
                    // cout << "check 1" << endl;
                    
                    int last_i = ind_stk.back();
                    prod_stk[(int)prod_stk.size() - 1] /= primes[last_i];
                    ind_stk.pop_back();
                    int next_i = last_i + 1;
                    ind_stk.push_back(next_i);
                    
                    // cout << "check 2" << endl;
                    
                    // prod_stk[(int)prod_stk.size() - 1] *= primes[next_i];
                    long long next_prod = prod_stk.back();
                    next_prod *= primes[next_i];
                    prod_stk.pop_back();
                    prod_stk.push_back(next_prod);
                    
                    bool ok = true;
                    while(ind_stk.size() < L){
                        ind_stk.push_back(next_i);
                        prod_stk.push_back(prod_stk.back() * primes[next_i]);
                        if(prod_stk.back() > INT_MAX){
                            ok = false;
                            break;
                        }
                    }
                    
                    // cout << "check 3" << endl;
                    
                    if(hs.size() == N and prod_stk.back() > *(hs.rbegin())) ok = false;
                    
                    if(ok){
                        prod = prod_stk.back();
                        next_found = true;
                    }
                    else sz--;
                    
                    // cout << "check 4" << endl;
                }
                if(done) break;
                
                // cout << "hello world" << endl;
            }
        // }
    }
    // cout << "bruh" << endl;
    
    while(hs.size() > N){
        long long mx = *(hs.rbegin());
        hs.erase(mx);
    }
    
    int ans = *(hs.rbegin());
   
	fout << ans << endl;
	
	fin.close();
	fout.close();
	
	cout << "secs elapsed: " << 1.0 * (clock() - ct) / CLOCKS_PER_SEC << endl;
	
	return 0;
}