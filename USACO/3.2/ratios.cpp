/*
ID: jamessh3
LANG: C++20
TASK: ratios
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
	ifstream fin ("ratios.in");
	ofstream fout ("ratios.out");
	
	vector<int> target;
	int a, b, c; fin >> a >> b >> c;
	target = {a, b, c};
	
	// edge case
	if(target[0] == 0 and target[1] == 0 and target[2] == 0){
	    fout << "0 0 0 0" << endl;
	    fin.close();
	    fout.close();
	    return 0;
	}
	
	vector<vector<int>> feeds;
	for(int i = 0; i < 3; ++i){
		fin >> a >> b >> c;
		feeds.push_back({a, b, c});
		cout << "feeds[i].size() " << feeds[i].size() << endl;
	}
	
	cout << "hello world" << endl;
	cout << "feeds.size() " << feeds.size() << endl;
	cout << "target.size() " << target.size() << endl;
	
	int best = INT_MAX;
	vector<int> ans;
	for(int i = 0; i < 100; ++i){ // # feed 1
		for(int j = 0; j < 100; ++j){ // # feed 2
			for(int k = 0; k < 100; ++k){ // # feed 3
			
			    if(i == 0 and j == 0 and k == 0) continue;
			
			    // division by zero error
			
				int a = i * feeds[0][0] + j * feeds[1][0] + k * feeds[2][0];
				int b = i * feeds[0][1] + j * feeds[1][1] + k * feeds[2][1];
				int c = i * feeds[0][2] + j * feeds[1][2] + k * feeds[2][2];
				
				if(a < target[0] or b < target[1] or c < target[2]) continue;
				if((a > 0 and target[0] == 0) or (b > 0 and target[1] == 0) or (c > 0 and target[2] == 0)) continue;
				
				// cout << "hello" << endl;
				
				if((target[0] != 0 and a % target[0] != 0) or (target[1] != 0 and b % target[1] != 0) or (target[2] != 0 and c % target[2] != 0)) continue;
				int coeff;
				if(target[0] != 0) coeff = a / target[0];
				else if(target[1] != 0) coeff = b / target[1];
				else coeff = c / target[2];
				if((target[0] != 0 and a / target[0] != coeff) or (target[1] != 0 and b / target[1] != coeff) or (target[2] != 0 and c / target[2] != coeff)) continue;
				int sum = i + j + k;
				if(sum < best){
					best = sum;
					ans = {i, j, k, coeff};
				}
				// cout << "world" << endl;
			}
		}
	}
	
	cout << "best: " << best << endl;
	
	if(best == INT_MAX) fout << "NONE" << endl;
	else{
		for(int i = 1; i < ans.size(); ++i) fout << ans[i - 1] << ' ';
		cout << "ans.size() " << ans.size() << endl;
		fout << ans.back() << endl;
	}
		
	fin.close();
	fout.close();

	return 0;
}