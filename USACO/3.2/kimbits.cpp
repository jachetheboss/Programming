/*
ID: jamessh3
LANG: C++20
TASK: kimbits
*/

#include <bits/stdc++.h>
using namespace std;

string binaryString(long long num){
    long long pow2 = 1;
    string s = "";
    while(pow2 <= num){
        if((pow2 & num) == pow2) s += '1';
        else s += '0';
        pow2 *= 2;
    }
    // reverse
    int bound = s.length() / 2;
    for(int i = 0; i < bound; ++i){
        char c = s[i];
        s[i] = s[(int)s.length() - 1 - i];
        s[(int)s.length() - 1 - i] = c;
    }
    return s;
}

bool isInteresting(long long num, int N, int L){
    long long pow2 = 1;
    int bitcount = 0;
    while(pow2 <= num){
        if((pow2 & num) == pow2) bitcount++;
        pow2 *= 2;
    }
    return bitcount <= L;
}

long long countHelper(vector<long long>& freq, int N, int L){
    long long count = 0;
    for(int i = 1; i <= L + 1; ++i){
        count += freq[i];
    }
    return count;
}

long long countInteresting(long long num, int N, int L){
	
	long long nums = 1;
	vector<long long> freq (32, 0);
	freq[0] = 1;
	vector<vector<long long>> freqs;
	freqs.push_back(freq);
	freqs[0].insert(freqs[0].begin(), 1);
	//while(nums < num){
	long long bound = INT_MAX;
	bound *= 2;
	while(nums <= bound){
		nums *= 2;
		vector<long long> next_freq (32, 0);
		for(int i = 1; i < next_freq.size(); ++i){
			next_freq[i] += freq[i - 1];
		}
		for(int i = 0; i < next_freq.size(); ++i) next_freq[i] += freq[i];
		freqs.push_back(next_freq);
		freqs[(int)freqs.size() - 1].insert(freqs[(int)freqs.size() - 1].begin(), nums);
		freq = next_freq;
	}
// 	cout << "freqs" << endl;
// 	for(vector<long long>& v : freqs){
// 		for(long long val : v) cout << val << ' ';
// 		cout << endl;
// 	}
// 	cout << endl;
	
	long long rem = num;
	long long interesting = 0;
	int decr = 0;
	while(rem > 0){
	    int idx = -1;
    	for(int i = 0; i < (int)freqs.size() - 1; ++i){
    	    long long count1 = freqs[i][0];
    	    long long count2 = freqs[i + 1][0];
    	    if(rem >= count1 and rem < count2){
    	        idx = i;
    	        break;
    	    }
    	}
    	interesting += countHelper(freqs[idx], N, L - decr);
    	rem -= freqs[idx][0];
    	decr++;
	}
	
	return interesting;
}


int main()
{
	ifstream fin ("kimbits.in");
	ofstream fout ("kimbits.out");
	
	long long N, L, I; fin >> N >> L >> I;
	// 00000 1
	// 00001 2
	// 00010 3
	// 00011 4
	// 00100 5
	// 00101 6
	// 00110 7
	// 00111 8
	// 01000 9
	// 01001 10
	// 01010 11
	// 01011 12
	// 01100 13
	// 01101 14
	// 01110 15
	// 10000 16
	// 10001 17
	// 10010 18
	// 10011 19
	
	// binary search?
	// {0, 1, 1, 2, 1, 2, 2, 3}
	//  0  1  2  3  4  5  6  7
	// store bitcount freq
	
	
	long long lo = 0;
	long long hi = 2147483648L;
	long long mid = (lo + hi) / 2;
	long long ans = -1;
	while(true){
		long long count = countInteresting(mid, N, L);
		if(isInteresting(mid, N, L)) count++;
		if(count == I and isInteresting(mid, N, L)){
			ans = mid;
			break;
		}else if(count >= I) hi = mid;
		else if(count < I) lo = mid;
		mid = (lo + hi) / 2;
	}

	string s = binaryString(ans);
	s = string(N - (int)s.length(), '0') + s;
	fout << s << endl;
	
	fin.close();
	fout.close();
	
	return 0;
}