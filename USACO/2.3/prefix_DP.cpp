
/*
ID: jamessh3
TASK: prefix
LANG: C++20
*/


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <ctime>

using namespace std;

int main(){
	
	clock_t begin = clock();
	
	ifstream fin ("prefix.in"); // in file stream
	ofstream fout ("prefix.out"); // out file stream
	// ifstream fin ("sample.txt");
	// ofstream fout ("output.txt");
	string substring = "";
    vector<string> substrings;
    while(true){
        fin >> substring;
        if(substring == "."){
            break;
        }
        substrings.push_back(substring);
    }
	string S = "";
    string temp = "";
    
    while(fin >> temp){ // standard way to keep reading file input
        S += temp; // temp is no more than 76 characters in length (no '\n' included)
    }
	
	unordered_set<string> substring_set;
    for(int i = 0; i < substrings.size(); ++i){ // word bank words now put into a set
        substring_set.insert(substrings[i]);
    }
	
	// what if S is shorter than the shortest prefix?
	
	vector<int> DP (S.length() + 1, 0); // is it S.length() or S.length() + 1
	
	int min_prefix_length = 1000000000;
	for(int i = 0; i < substrings.size(); ++i){
		if(substrings[i].length() < min_prefix_length){
			min_prefix_length = substrings[i].length();
		}	
	}
	if(min_prefix_length > S.length()){
		fout << 0 << '\n';
		return 0;
	}
	
	
	// DP vector base case initializer
	// version 1:
	// for(int i = 0; i < substrings.size(); ++i){
		// string sub = substrings[i];
		// if(sub.length() > S.length()){ // prefix cannot be longer than S itself!
			// continue;
		// }
		// bool is_prefix = true;
		// for(int j = 0; j < sub.length(); ++j){
			// if(sub[j] != S[j]){
				// is_prefix = false;
				// break;
			// }	
		// }
		// if(is_prefix){
			// DP[i + 1] = 1; // DP[i] == 1 means prefix covers entirety of (0 to i - 1 inclusive), so ans >= i
		// }
	// }
	
	// DP vector base case initializer
	// version 2:
	string sub = "";
	for(int i = 0; i < 10; ++i){
		sub += S[i];
		if(substring_set.count(sub) == true){
			DP[i + 1] = 1;
		}	
	}
	
	
	// iterate through DP
	// for(int i = 1; i < S.length(); ++i){
		// int bound = min(10, i);
		// for(int j = 0; j < bound; ++j){
			// if(DP[i - j] == 1){
				// if(substring_set.count(S.substr(i - j, j + 1)) == true){
					// DP[i + 1] = 1;
				// }
			// }
		// }
	// }	
	
	// iterate through DP
	// optimization: instead of looking at previous 10 chars, discarding substring, then looking at prev 9, discarding,
	// looking at prev 8, discarding, in standard left-to-right order, make a set of reverse-order prefixes, then
	// build substrings of length 1 - 10 by concatenating backwards. uses 10 operations per index, rather than 55.
	
	
	unordered_set<string> reverse_substring_set; // build set of REVERSED SUBSTRINGS
	for(int i = 0; i < substrings.size(); ++i){
		string temp = "";
		for(int j = substrings[i].length() - 1; j >= 0; --j){
			temp += substrings[i][j];
		}
		reverse_substring_set.insert(temp);
	}
	for(int i = 1; i < S.length(); ++i){
		string reverse_sub = "";
		int bound = min(10, i);
		for(int j = 0; j < bound; ++j){
			reverse_sub += S[i - j];
			if(DP[i - j] == 1 and reverse_substring_set.count(reverse_sub) == true){
				DP[i + 1] = 1;
			}
		}
	}
	
	
	int ans = 0;
	for(int i = 0; i < DP.size(); ++i){
		if(DP[i] == 1){
			ans = i;
		}
	}
	fout << ans << '\n';
	
	clock_t end = clock();
	
	cout << "ans: " << ans << endl;	
	cout << "elapsed: " << 1.0 * (end - begin) / CLOCKS_PER_SEC << " sec" << endl;
	
	return 0;
}