/*
ID: jamessh3
LANG: C++20
TASK: fracdec
*/


#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

//.915254237288135593220338983
//.91525423728813559322338983584745762711864467796611694
// I messed up the zeros somewhere.

int main()
{
    int N, D;
    ifstream fin ("fracdec.in");
    ofstream fout ("fracdec.out");
	
	vector<int> fractions;
	
	// for(int i = 0; i < 8; ++i){
		
	fin >> N >> D;
		// fractions.push_back(N);
		// fractions.push_back(D);
    // cin >> N >> D;
	// }
    
	// for(int cnt = 0; cnt < fractions.size(); cnt += 2){
		// N = fractions[cnt];
		// D = fractions[cnt + 1];
		
	
    if(N % D == 0){
        // cout << N / D << ".0" << endl;

        fout << N / D << ".0" << endl;
        fin.close();
        fout.close();
        return 0;
		// continue;
    }
    
    int integer_part = N / D;
    N %= D;
    int GCD = __gcd(N, D);
    N /= GCD;
    D /= GCD;
    int rem = N;
	
	cerr << "N: " << N << endl;
	cerr << "D: " << D << endl;
    
	vector<int> digits; // decimal part digits
	int i = 0;
	
	unordered_map<int, int> hm;
	
	// newly added
	rem *= 10;
    hm.insert({rem, 0});

    int cycle_start = -1;
    while(true){
        // rem *= 10;
		bool done = false;
		while(rem < D){
			rem *= 10;
			digits.push_back(0);
			i += 1;
			if(hm.count(rem) == true){
				done = true;
				cycle_start = hm[rem];
				break;
			}
			hm.insert({rem, i});
		}
		if(done){
			break;
		}
		// if(hm.count(rem) == true){
			// cycle_start = hm[rem];
			// break;
		// }
		// hm.insert({rem, i});
		
        int digit = rem / D;
        digits.push_back(digit);
        rem %= D;
        if(rem == 0){
            break;
        }
		rem *= 10;
		i += 1;
		
		if(hm.count(rem) == true){
			cycle_start = hm[rem];
			break;
		}
		hm.insert({rem, i});
    }
    

	string ans = to_string(integer_part) + ".";
	
    if(cycle_start == -1){
        for(int i = 0; i < digits.size(); ++i){
            ans += to_string(digits[i]);
        }
    }
    else{
        for(int i = 0; i < cycle_start; ++i){
            ans += to_string(digits[i]);
        }
        ans += '(';
        for(int i = cycle_start; i < digits.size(); ++i){
            ans += to_string(digits[i]);
        }
        ans += ')';
    }
    
	int lines = ans.length() / 76 + 1;
	i = 0;
	for(int line = 0; line < lines - 1; ++line){
		fout << ans.substr(i, 76);
		fout << '\n';
		i += 76;
	}
	fout << ans.substr(i) << '\n';
	
	cout << ans;
	
    fin.close();
    fout.close();
    
    return 0;
}