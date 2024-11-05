/*
ID: jamessh3
LANG: C++20
TASK: fence9
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
	ifstream fin ("fence9.in");
	ofstream fout ("fence9.out");
	int N, M, P; fin >> N >> M >> P;
	// slope m = M / N
	// do a bunch of binary searches? or how about simple y=mx+b O(1) math?
	int cows = 0;
	for(int y = 1; y < M; ++y){
		// x = y / m, where m is the slope
		// x = y / (M / N) = y * N / M
		int prod = y * N;
		int L = prod / M; // left bound
		L++;
		
		// find right bound, line formed by (N, M) and (P, 0)
		int R;
		if(P == N) R = P - 1; // vertical line
		else{
			// Y = (M / N)(X - P)
			// Y = MX / N - MP / N 
			// Y + MP/N = MX / N 
			// (Y + MP/N) * N / M = X
			// X = YN/M + P
			// X = (YN + PM) / M
			int rise = M;
			int run = N - P;
			int numer = y * run + P * rise;
			// cout << "numer: " << numer << endl;
			R = numer / rise;
			if(numer % rise == 0) R--;
		}
		cows += R - L + 1;
		// cout << "y: " << y << " L: " << L << " R: " << R << endl;
	}
	
	fout << cows << endl;
	
	fin.close();
	fout.close();
	
	return 0;
}