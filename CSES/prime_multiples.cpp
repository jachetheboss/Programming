#include <bits/stdc++.h>
using namespace std;

void print(__int128 x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

// string add(string a, string b){ // assume always positive
//     int L = max((int)a.length(), (int)b.length());
//     if(a.length() < L) a = string(L - (int)a.length(), '0') + a;
//     if(b.length() < L) b = string(L - (int)b.length(), '0') + b;
//     // add a and b
//     int carry = 0;
//     string s = "";
//     for(int j = L - 1; j >= 0; --j){
//         int sum = a[j] - '0' + b[j] - '0' + carry;
//         carry = sum / 10;
//         int d = sum % 10;
//         char c = '0' + d;
//         s += c;
//     }
//     if(carry != 0) s += '1';
//     // reverse s 
//     int bound = s.length() / 2;
//     for(int i = 0; i < bound; ++i){
//         char c = s[i];
//         s[i] = s[(int)s.length() - 1 - i];
//         s[(int)s.length() - 1 - i] = c;
//     }
//     return s;
// }

// string subtract(string a, string b){ // assume always a > b
//     b = string((int)a.length() - (int)b.length(), '0') + b;
//     bool borrow = 
// }

int main()
{
	long long N, K; cin >> N >> K;
	vector<long long> primes;
	for(int i = 0; i < K; ++i){
		long long p; cin >> p;
		primes.push_back(p);
	}
	sort(primes.begin(), primes.end(), greater<int>());
	int ways = (int)pow(2, K);
	//long long ans = 0;
// 	string ans = "0";
    __int128 ans = 0;
	for(int way = 1; way < ways; ++way){
	// bitwise faster than my vector/string builder
	// technique
		int pow2 = 1;
		int idx = 0;
		long long prod = 1;
		int bitcount = 0;
		bool ok = true;
		while(pow2 < ways){
			if((pow2 & way) == pow2){
				double prod_log = log(prod) / log(10);
				long long p = primes[idx];
				double prime_log = log(p) / log(10);
				if(prod_log + prime_log > 18.01){
					ok = false;
					break;
				}
				bitcount++;
				prod *= p;
			}
			pow2 *= 2;
			idx++;
		}
		if(ok){
			long long quo = N / prod;
// 			string t = to_string(quo);
            __int128 x = quo;
// 			if(bitcount % 2 == 0) ans -= quo;
// 			else ans += quo;
	        if(bitcount % 2 == 0) ans -= x;
			else ans += x;	
            // if(bitcount % 2 == 0){
            //     ans = subtract(ans, t);
            // }else{
            //     ans = add(ans, t);
            // }
		}
	}
// 	long long ret = ans;
//     cout << ret << endl;

    print(ans);
    cout << endl;


	return 0;
}