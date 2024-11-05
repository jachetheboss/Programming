/*
ID: jamessh3
LANG: C++20
TASK: range
*/

#include <bits/stdc++.h>
using namespace std;

int countOnes(int i, int j, int side, vector<vector<int>>& prefix){
	// [i][j] topleft cell of square with side length of side 
	int ones = prefix[i + side - 1][j + side - 1];
	if(i > 0) ones -= prefix[i - 1][j + side - 1];
	if(j > 0) ones -= prefix[i + side - 1][j - 1];
	if(i > 0 and j > 0) ones += prefix[i - 1][j - 1];
	return ones;
}

int main()
{
	// prefix matrix
	ifstream fin ("range.in");
	ofstream fout ("range.out");
	int N; fin >> N;
	vector<vector<int>> prefix (N, vector<int> (N, 0)); // build with inclusion exclusion principle?
	// prefix counts how many 1's so far
	string line; fin >> line;
	if(line[0] == '1') prefix[0][0] = 1;
	for(int j = 1; j < N; ++j){
		prefix[0][j] = prefix[0][j - 1];
		if(line[j] == '1') prefix[0][j]++;
	}
	for(int i = 1; i < N; ++i){
		fin >> line;
		int ones_in_line = 0;
		if(line[0] == '1') ones_in_line++;
		prefix[i][0] = ones_in_line + prefix[i - 1][0];
		for(int j = 1; j < line.length(); ++j){
		    if(line[j] == '1') ones_in_line++;
			prefix[i][j] = prefix[i - 1][j] + ones_in_line;
		}
	}
	vector<int> freq (N + 1, 0);
	for(int side = 2; side <= N; ++side){
		int i_bound = N - side;
		int j_bound = N - side;
		int area = side * side;
		for(int i = 0; i <= i_bound; ++i){
			for(int j = 0; j <= j_bound; ++j){
				// [i][j] is the top left cell of the square
				int ones = countOnes(i, j, side, prefix);
				// if(side == 3) cout << "i: " << " j: " << j << " ones: " << ones << endl;
				if(ones == area) freq[side]++;
			}
		}
	}
	
	for(int side = 2; side < freq.size(); ++side){
		int count = freq[side];
		if(count > 0) fout << side << ' ' << count << endl;
	}
	
	fin.close();
	fout.close();
	
	return 0;
}