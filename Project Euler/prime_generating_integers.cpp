
#include <bits/stdc++.h> 
#include <ctime>
using namespace std;

void incrementBuilder(vector<int>& builder, vector<int>& capacity){
	for(int i = 0; i < builder.size(); i++){
		builder[i]++;
		if(builder[i] > capacity[i]) builder[i] = 0;
		else return;
	}
}

// bool isGood(int x, vector<int>& sieve){ // sieve stores if number is prime or not
bool isGood(int x, set<int>& hs){ // sieve stores if number is prime or not
	if(x == 1) return true;
	if(x == 2) return true;
	if(x == 4) return false;
	if(x == 6) return true;
	
	int ori_x = x;
	int bound = (int)floor(sqrt(ori_x));
	
	vector<int> small_primes = {2, 3, 5};
	vector<int> pfactors;
	for(int p : small_primes){
		if(x % p == 0){
			pfactors.push_back(p);
			pfactors.push_back(0);
			while(x % p == 0){
				pfactors[(int)pfactors.size() - 1]++;
				x /= p;
			}
		}
	}
	
	// factorize x
	int f = 7; // 6t + 1, 6t + 5
	
	while(f <= bound){
		if(x % f == 0){
			pfactors.push_back(f);
			pfactors.push_back(0);
			while(x % f == 0){
				pfactors[(int)pfactors.size() - 1]++;
				x /= f;
			}
		}
		f += 4;
		if(f <= bound and x % f == 0){
			pfactors.push_back(f);
			pfactors.push_back(0);
			while(x % f == 0){
				pfactors[(int)pfactors.size() - 1]++;
				x /= f;
			}
		}
		f += 2;
	}
	
	// generate all factors from the prime factors 
	
	vector<int> builder (pfactors.size() / 2, 0);
	vector<int> ps;
	vector<int> capacity;
	int ways = 1;
	for(int i = 1; i < pfactors.size(); i += 2){
		ways *= (pfactors[i] + 1);
		capacity.push_back(pfactors[i]);
		ps.push_back(pfactors[i - 1]);
	}
	for(int way = 0; way < ways; ++way){
		int f = 1;
		for(int i = 0; i < builder.size(); i++){
			for(int j = 0; j < builder[i]; j++) f *= ps[i];
		}
		int g = ori_x / f;
		int sum = f + g;
// 		if(sieve[sum] != 1) return false;
        if(!hs.count(sum)) return false;
		
		incrementBuilder(builder, capacity);
	}
	return true;
}

void fillSieve(vector<int>& sieve){
    int limit = sieve.size();
    sieve[0] = 0;
    sieve[1] = 0;
    int bound = (int)floor(sqrt(limit));
    for(int i = 2; i <= bound; i++){
        if(sieve[i] == 1){
            for(int j = i * i; j < sieve.size(); j += i){
                sieve[j] = 0;
            }
        }
    }
}

int main()
{
    time_t start_t = clock();
    
    const int limit = (int)1e8 + 1; // uses way too much memory
    // vector<int> sieve (limit + 1, 1);
    // fillSieve(sieve);
   // /*
    

    vector<int> primes;
    set<int> hs;
    // implement segmented sieve
    
    int segment_sz = (int)floor(sqrt(limit)) + 1;
    vector<int> segment (segment_sz, 1);
    fillSieve(segment);
    vector<vector<int>> ind;
    for(int i = 2; i < segment.size(); i++){
        if(segment[i] == 1){
            hs.insert(i);
            primes.push_back(i);
            // calculate the next index
            int rem = ((int)segment.size() - i - 1) % i;
            int idx = i - 1 - rem;
            ind.push_back({i, idx});
        }
    }
    cout << "starting segment" << endl;
    for(int x : segment) cout << x << ' ';
    cout << endl;
    
    cout << "hs.size() " << hs.size() << endl;
    cout << "primes.size() " << primes.size() << endl;
    cout << "segment.size() " << segment.size() << endl;
    
    int start = segment.size();
    segment.pop_back(); // further segments do not need the leading 0-indexing
    
    cout << "segment.size() " << segment.size() << endl;
    while(start <= limit){
        // reset segment to ones (assume all prime, mark the composites as 0)
        vector<vector<int>> next_ind;
        for(int i = 0; i < segment.size(); i++) segment[i] = 1;
        for(vector<int>& pair : ind){
            int p = pair[0];
            int idx = pair[1];
            for(int j = idx; j < segment.size(); j += p){
                segment[j] = 0;
                if(j + p >= segment.size()){
                    next_ind.push_back({p, j + p - (int)segment.size()});
                }
            }
        }
        ind = next_ind;
        for(int i = 0; i < segment.size(); i++){
            int p = start + i;
            if(segment[i] == 1 and p <= limit){
                int p = start + i;
                hs.insert(p); // insert newly found primes
                primes.push_back(p);
            }
        }
        start += segment.size();
    }
    
    cout << "hs.size() " << hs.size() << endl;
    
    /*
    for(int i = 2; i < sieve.size(); i++){
        if(sieve[i] == 1){
            primes.push_back(i);
            hs.insert(i);
        }
    }
    */
    long long ans = 0;
    for(int p : primes){
        int x = p - 1;
        // if(isGood(x, sieve)) ans += x;
        if(isGood(x, hs)) ans += x;
    }
    
    time_t finish_t = clock();
    
    cout << "fancy secs elapsed: " << 1.0 * (finish_t - start_t) / CLOCKS_PER_SEC << endl;
    cout << "ans: " << ans << endl;
    
    start_t = clock();
    
    long long brute_ans = 0;
    for(int x = 1; x < limit; x++){
        if(x <= 2){
            brute_ans += x;
            continue;
        }
        int sqrtbound = (int)floor(sqrt(x));
        bool ok = true;
        for(int y = 1; y <= sqrtbound; ++y){
            if(x % y == 0){
                int z = x / y;
                // if(sieve[y + z] == 0){
                if(!hs.count(y + z)){
                    ok = false;
                    break;
                }
            }
        }
        if(ok) brute_ans += x;
    }
    finish_t = clock();
    
    cout << "brute secs elapsed: " << 1.0 * (finish_t - start_t) / CLOCKS_PER_SEC << endl;
    cout << "brute_ans: " << brute_ans << endl;
    
    //*/
    return 0;
}