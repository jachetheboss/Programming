#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <set>
#include <tuple>
#include <algorithm>

using namespace std;

// change to long long, should make it faster. Can write all Pythagorean triples up to a certain 
// size to file, then read in file

// Function to increment the builder
void incrementBuilder(vector<int>& builder, const vector<int>& capacity) {
    for (int i = builder.size() - 1; i >= 0; --i) {
        builder[i] += 1;
        if (builder[i] > capacity[i]) {
            builder[i] = 0;
        } else {
            return;
        }
    }
}

// Function to factorize a number
vector<int> factorize(int num) {
    vector<int> factorization;
    int bound = static_cast<int>(floor(sqrt(num)));
    for (int k = 2; k <= bound; ++k) {
        if (num % k == 0) {
            factorization.push_back(k);
            factorization.push_back(0);
            while (num % k == 0) {
                factorization.back() += 1;
                num /= k;
            }
            if (num == 1) break;
        }
    }
    if (num > 1) {
        factorization.push_back(num);
        factorization.push_back(1);
    }
    return factorization;
}

// Retrieve factorization from precomputed data
vector<int>& getFactorization(int num, vector<vector<int>>& factorizations) {
    return factorizations[num];
}

vector<vector<int>> generatePythagoreanTriples(int max_base1, int max_base2){
	if(max_base2 < max_base1){
		cout << "max_base2 must be >= max_base1" << endl;
		return {};
	}
	// note: hypotenuse can be bigger than max_base (duh)
	// generates all triples, not just primitive triples 
    // Precompute factorizations up to max_peri
	int max_peri = (int)(ceil(max_base1 + 2.5 * max_base2));
    vector<vector<int>> factorizations(max_peri + 1);
    for (int k = 2; k < factorizations.size(); ++k) {
        if (factorizations[k].empty()) {
            int j = k;
            while (j < factorizations.size()) {
                int num = j;
                int count = 0;
                while (num % k == 0) {
                    num /= k;
                    ++count;
                }
                factorizations[j].push_back(k);
                factorizations[j].push_back(count);
                j += k;
            }
        }
    }

    //unordered_map<int, set<tuple<int, int, int>>> di;
	set<tuple<int, int, int>> unique_triples;
    for (int b = 3; b <= max_base1; ++b) {
        cout << "b: " << b << endl;
        vector<int> factorization = getFactorization(b, factorizations);
        vector<int> pfactors;
        vector<int> capacity;
        
        for (size_t i = 0; i < factorization.size(); i += 2) {
            pfactors.push_back(factorization[i]);
            capacity.push_back(2 * factorization[i + 1]);
        }
        
        int ways = 1;
        for (int c : capacity) {
            ways *= (c + 1);
        }

        vector<int> builder(pfactors.size(), 0);
        vector<long long> factors;
        for (int i = 0; i < ways; ++i) {
            long long f = 1;
            for (size_t j = 0; j < builder.size(); ++j) {
                f *= (long long)pow(pfactors[j], builder[j]);
            }
            factors.push_back(f);
            incrementBuilder(builder, capacity);
        }

        long long bsq = b;
        bsq *= b;
        for (long long f : factors) {
            long long quo = bsq / f;
            if (quo <= f) continue;
            if ((quo - f) % 2 != 0) continue;
            
            long long d = f;
            long long a = (quo - f) / 2;
            long long c = d + a;

            if (a * a + bsq == c * c) {
                //long long peri = a + b + c;
                //if (peri <= (long long)max_peri) {
				if(b <= (long long)max_base1 and a <= (long long)max_base2){
					tuple<int, int, int> tup;
                    if(a < b) tup = tuple<int, int, int>(a, b, c);
					else tup = tuple<int, int, int>(b, a, c);
                    unique_triples.insert(tup);
                }
            }
        }
    }
	vector<vector<int>> triples;
	set<tuple<int, int, int>>::iterator it;
	for(auto it = unique_triples.begin(); it != unique_triples.end(); it++){
		tuple<int, int, int> tup = *it;
		vector<int> triple = {get<0>(tup), get<1>(tup), get<2>(tup)};
		triples.push_back(triple);
	}
	return triples;
}
