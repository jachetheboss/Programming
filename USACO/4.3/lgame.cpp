/*
ID: jamessh3
LANG: C++20
TASK: lgame
*/

#include <bits/stdc++.h>
using namespace std;

void incrementBuilder(vector<int>& builder){
	for(int i = (int)builder.size() - 1; i >= 0; --i){
		if(builder[i] <= 1){
			builder[i]++;
			return;
		}else builder[i] = 0;
	}
}

bool canMake(vector<int>& word_freq, vector<int>& avail){
	for(int i = 0; i < avail.size(); ++i){
		if(word_freq[i] > avail[i]) return false;
	}
	return true;
}

vector<int> getFreq(string& s){
	vector<int> freq (26, 0);
	for(char c : s) freq[c - 'a']++;
	return freq;
}

string getKey(vector<int>& freq){
	string key = "";
	for(int count : freq){
		key += to_string(count);
		key += ' ';
	}
	return key;
}

int getScore(string& word, vector<int>& score_lookup){
	int score = 0;
	for(char c : word) score += score_lookup[c - 'a'];
	return score;
}

int main()
{
	
	// solve using permutations and subset builder counting enumeration method?
	// anagrams
	
	vector<int> score_lookup (26, 0);
	string qwerty = "qwertyuiopasdfghjklzxcvbnm";
	string vals =   "76122541352146557637746525";
	for(int i = 0; i < qwerty.length(); ++i){
		char c = qwerty[i];
		int val = vals[i] - '0';
		score_lookup[c - 'a'] = val;
	}
	
	ifstream fin ("lgame.in");
	ifstream fin1 ("lgame.dict");
	ofstream fout ("lgame.out");
	
	string word;
	unordered_map<string, int> hm;
	unordered_map<string, unordered_set<string>> anagrams;
	while(fin1 >> word){
	    
	    if(word == ".") continue;
	    
		if(hm.count(word) == false) hm.insert({word, 0});
		
		vector<int> freq = getFreq(word);
		string key = getKey(freq);
		if(anagrams.count(key) == false) anagrams.insert({key, unordered_set<string>() });
		anagrams[key].insert(word);
		
		hm[word]++;
	}
	string inp; fin >> inp;
	unordered_map<string, int>::iterator it;
	
	vector<int> inp_freq = getFreq(inp);
	
	vector<vector<string>> ans;
	int max_score = 0;
	for(it = hm.begin(); it != hm.end(); ++it){
		word = it->first;
		
		string huh = "huh";
		if(word == huh) cout << "word: huh" << endl;
		
		int count = it->second;
		
		vector<int> word_freq = getFreq(word);
		
		// try single word
		if(canMake(word_freq, inp_freq)){
			int score = getScore(word, score_lookup);
			if(word == huh) cout << "huh score: " << score << endl;
			if(score > max_score){
				max_score = score;
				ans = { {word} };
			}
			else if(score == max_score) ans.push_back( {word} );
		}
	}
	// pairs of words case
	unordered_set<string> searched;
	vector<int> builder (inp.length(), 0);
	int ways = (int)pow(3, (int)inp.length());
	for(int way = 0; way < ways; ++way){

		string chars1 = "";
		string chars2 = "";
		for(int i = 0; i < builder.size(); ++i){
			if(builder[i] == 0) continue;
			if(builder[i] == 1) chars1 += inp[i];
			else chars2 += inp[i];
		}
		
		incrementBuilder(builder);
		
		if(chars1 == "" or chars2 == "") continue;
		// need both strings to be non-empty in order to have a valid pair
		
		int len1 = chars1.length();
		int len2 = chars2.length();
		if(len1 <= 2 or len1 >= 5 or len2 <= 2 or len2 >= 5) continue;
		
		sort(chars1.begin(), chars1.end());
		sort(chars2.begin(), chars2.end()); // must be sorted to be unique
		
		if(chars1 <= chars2){
			string s = chars1 + " " + chars2;
			if(searched.count(s) == true) continue;
			searched.insert(s);
		}else{
			string s = chars2 + " " + chars1;
			if(searched.count(s) == true) continue;
			searched.insert(s);
		}
		
		if(getScore(chars1, score_lookup) + getScore(chars2, score_lookup) == 24){
		    cout << "chars1: " << chars1 << " chars2: " << chars2 << endl;
		}
		
		vector<int> freq1 = getFreq(chars1);
		vector<int> freq2 = getFreq(chars2);
		
		if(freq1 == freq2){
			string key = getKey(freq1);
			if(anagrams.count(key) == false) continue;
			unordered_set<string>::iterator iter;
			for(iter = anagrams[key].begin(); iter != anagrams[key].end(); ++iter){
				word = *iter;
				if(hm[word] >= 2){
					int score = getScore(word, score_lookup);
					if(score == max_score) ans.push_back({word, word});
					else if(score > max_score) ans = { {word, word} };
				}
			}
			continue;
		}
		
		string key1 = getKey(freq1);
		string key2 = getKey(freq2);
		if(anagrams.count(key1) == false or anagrams.count(key2) == false) continue;
		
		unordered_set<string>::iterator it1;
		unordered_set<string>::iterator it2;
		for(it1 = anagrams[key1].begin(); it1 != anagrams[key1].end(); ++it1){
			string word1 = *it1;
			for(it2 = anagrams[key2].begin(); it2 != anagrams[key2].end(); ++it2){
				string word2 = *it2;
				int score = getScore(word1, score_lookup) + getScore(word2, score_lookup);
				if(score > max_score){
					max_score = score;
					ans.clear();
				}
				if(score == max_score) ans.push_back( {word1, word2} );
			}
		}
	}
	
	for(vector<string>& a : ans){
		if(a.size() == 2) sort(a.begin(), a.end());
	}
	sort(ans.begin(), ans.end());
	
	fout << max_score << endl;
	for(vector<string>& a : ans){
	    if(a.size() == 1){
	        fout << a[0] << endl;
	    }else{
	        fout << a[0] << ' ' << a[1] << endl;
	    }
	}
	
	fin.close();
	fin1.close();
	fout.close();
	
	return 0;
}