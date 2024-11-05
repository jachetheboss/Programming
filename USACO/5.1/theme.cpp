/*
ID: jamessh3
LANG: C++20
TASK: theme
*/

#include <bits/stdc++.h>
using namespace std;

const long long MOD = 17000000000000071L;

bool themeExists(vector<int>& delta, vector<long long>& pows, int coeff, int L){
	map<long long, int> hm;
	long long key = 0;
	for(int i = 0; i < L; i++){
		key *= coeff;
		key += delta[i];
		key %= MOD;
	}
	hm.insert( {key, 0} );
	bool found = false;
	for(int i = L; i < delta.size(); i++){
		key *= coeff;
		key += delta[i];
		key %= MOD;
		long long decr = pows[L];
		decr *= delta[i - L];
		decr %= MOD;
		key -= decr;
		if(key < 0) key += MOD;
		if(not hm.count(key)) hm.insert( {key, i - L + 1 } );
		else{
		    int rleft = hm[key] + L - 1;
			int lright = i - L + 1;
			if(lright >= rleft + 1) return true;
		}
	}
	return false;
}

int main()
{
	ifstream fin ("theme.in");
	ofstream fout ("theme.out");
	
	int N; fin >> N;
	
	if(N < 10){
		fout << 0 << endl;
		fin.close();
		fout.close();
		
		return 0;
	}
	
	vector<int> v;
	for(int i = 0; i < N; i++){
		int val; fin >> val;
		v.push_back(val);
	}
	// Rabin-Karp
	// I thought I could use binary search on top of Rabin-Karp, but now 
	// I just think that it will be O(n^2)
	
	// if Rabin-Karp too slow due to all the hashing, try to do KMP?
	// or some other insight that doesn't involve a difficult algo?
	// can binary search be utilized?
	
	vector<int> delta;
	for(int i = 1; i < v.size(); i++) delta.push_back(v[i] - v[i - 1]);
	int lowest = INT_MAX;
	for(int d : delta) lowest = min(lowest, d);
	if(lowest < 0){
		for(int i = 0; i < delta.size(); i++) delta[i] -= lowest;
	}
	int highest = 0;
	for(int d : delta) highest = max(highest, d);
	int coeff = highest + 1;
	
	//cout << "delta" << endl;
	//for(int d : delta) cout << d << ' ';
	//cout << endl;
	// Rabin-Karp
	// use a single big prime modulo of 17000000000000071L
	// try longest to shortest
	
	int max_L = delta.size() / 2;
	if(delta.size() % 2 == 0) max_L--;
	
	vector<long long> pows = {1};
	while(pows.size() < max_L + 1) pows.push_back(pows.back() * coeff % MOD);

	int ans = 0;
	int min_L = 4;
	if(not themeExists(delta, pows, coeff, min_L)){
		fout << 0 << endl;
		fin.close();
		fout.close();
		return 0;
	}
	
	int lo = min_L;
	int hi = max_L + 1;
	int mid = (lo + hi) / 2;
	while(true){
		bool mid_exists = themeExists(delta, pows, coeff, mid);
		bool mid_exists_1 = themeExists(delta, pows, coeff, mid + 1);
		if(mid_exists and not mid_exists_1){
			ans = mid + 1; // since delta are the differences, the theme length is one greater
			break;
		} else if(not mid_exists) hi = mid;
		else lo = mid + 1;
		mid = (lo + hi) / 2;
	}
	
	fout << ans << endl;
	
	fin.close();
	fout.close();
	
	return 0;
}