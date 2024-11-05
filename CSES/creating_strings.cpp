#include <bits/stdc++.h>
using namespace std;

void generatePermutations(string& perm, string& bank, vector<string>& permutations){
	if(bank.length() == 0) permutations.push_back(perm);
	else{
		for(int i = 0; i < bank.length(); ++i){
			string next_perm = perm;
			next_perm += bank[i];
			string next_bank = bank;
			next_bank.erase(next_bank.begin() + i);		
			generatePermutations(next_perm, next_bank, permutations);
		}
	}
}

int main()
{
	string inp; cin >> inp;
	vector<string> permutations;
	string bank = inp;
	string perm = "";
	generatePermutations(perm, bank, permutations);
	set<string> hs;
	for(string& perm : permutations) hs.insert(perm);
	set<string>::iterator it;
	cout << hs.size() << endl;
	for(it = hs.begin(); it != hs.end(); ++it) cout << *it << endl;
	
	return 0;
}