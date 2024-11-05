/*
ID: jamessh3
LANG: C++20
TASK: fact4
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
	ifstream fin ("fact4.in");
	ofstream fout ("fact4.out");
	
	int N; fin >> N;
	
	// edge case
	if(N == 1){
		fout << 1 << endl;
		fin.close();
		fout.close();
		return 0;
	}
	
	// divide out all the multiples of 5
	vector<int> v;
	for(int i = 1; i <= N; ++i) v.push_back(i);
	int fives = 0;
	int twos = 0;
	for(int i = 0; i < v.size(); ++i){
		while(v[i] % 5 == 0){
			v[i] /= 5;
			fives++;
		}while(v[i] % 2 == 0){
			v[i] /= 2;
			twos++;
		}
	}
	twos -= fives;
	int unit_d = 1; // units digit
	for(int x : v){
		int d = x % 10;
		unit_d *= d;
		unit_d %= 10;
	}
	// 2, 4, 8, 6
	int rem = twos % 4;
	if(rem == 1) unit_d *= 2;
	else if(rem == 2) unit_d *= 4;
	else if(rem == 3) unit_d *= 8;
	else if(rem == 0) unit_d *= 6;
	unit_d %= 10;
	
	fout << unit_d << endl;
	fin.close();
	fout.close();
	
	return 0;
}