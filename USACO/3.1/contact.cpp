/*
ID: jamessh3
LANG: C++20
TASK: contact
*/

#include <bits/stdc++.h>
using namespace std;

vector<string> splitIntoLines(vector<string>& v, int bound){ // each line max 6 elements
	vector<string> lines;
	for(int i = 0; i <= bound; i += 6){
		string line = "";
		for(int j = i; j < min(bound, i + 5); ++j){
			line += v[j];
			line += ' ';
		}
		line += v[min(bound, i + 5)];
		lines.push_back(line);
	}
	return lines;	
}

int binToInt(string& s){
	int val = 0;
	int pow2 = 1;
	for(int i = (int)s.length() - 1; i >= 0; --i){
		if(s[i] == '1') val += pow2;
		pow2 *= 2;
	}
	return val;
}
bool comparator(string& s, string& t){
	if(s.length() < t.length()) return true;
	if(s.length() > t.length()) return false;
	int val_s = binToInt(s);
	int val_t = binToInt(t);
	return val_s < val_t;
}

int main()
{
	ifstream fin ("contact.in");
	int A, B, N; fin >> A >> B >> N;
	
	string s = ""; 
    string ln = "";
    while(fin >> ln) s += ln;
	
	unordered_map<string, int> hm; // substring frequency count
	for(int L = A; L <= B; ++L){
		for(int i = L - 1; i < s.length(); ++i){
			string sub = s.substr(i - L + 1, L);
			if(hm.count(sub) == false) hm.insert({sub, 0});
			hm[sub]++;
		}
	}
	vector<int> unique_freq;
	unordered_map<int, vector<string>> freq;
	unordered_map<string, int>::iterator it;
	for(it = hm.begin(); it != hm.end(); ++it){
		string t = it->first;
		int cnt = it->second;
		if(freq.count(cnt) == false){
			freq.insert({cnt, {}});
			unique_freq.push_back(cnt);
		}
		freq[cnt].push_back(t);
	}
	sort(unique_freq.begin(), unique_freq.end());
// 	int rem = N;
	vector<string> lines;
	for(int i = (int)unique_freq.size() - 1; i >= max(0, (int)unique_freq.size() - N); --i){
		int cnt = unique_freq[i];
// 		cout << "cnt: " << cnt << endl;
		vector<string>& v = freq[cnt];
		sort(v.begin(), v.end(), comparator);
		lines.push_back(to_string(cnt));
		//vector<string> append = splitIntoLines(v, min((int)v.size() - 1, rem - 1));
		vector<string> append = splitIntoLines(v, (int)v.size() - 1);
		for(string& line : append) lines.push_back(line);
// 		rem -= min(rem, (int)v.size());
// 		if(rem == 0) break;
	}
	
	ofstream fout ("contact.out");
	for(string& line : lines){
		fout << line << endl;
	}
	
	fin.close();
	fout.close();
	
	return 0;
}