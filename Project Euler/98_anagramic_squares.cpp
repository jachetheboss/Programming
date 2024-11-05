// Below: notes from 2023, implementation is from 2024, ~18 months later, so implementation might
// not be in line with my thought/ideas from 18 months ago

// One requirement for Project Euler #98 anagramic squares is that the mappings of the letters
// to digits must be injective (no two different letters can map to the same digit value)

    // are all words unique? Are there duplicate words in the file input?
    
    // Algorithm:
    // 1. Find all anagrams, by checking character frequency
    // 2. Frequency hash, only consider the character frequencies with multiple word members.
    // 3. Check to see if pattern of word fits pattern of a perfect square. For the perfect squares that
    //    fit the character change pattern, get the letter to digit mapping. Then use this mapping
    //    on the other words in the anagram group, to see if they result in perfect squares as well.

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

vector<string> parseInput(string filename){
    ifstream fin (filename);
    
    vector<string> words;
    string line = "";
    while(getline(fin, line)){
        string word = "";
        bool in_quote = false;
        for(char c : line){
            if(in_quote){
                if(c == '\"'){
                    words.push_back(word);
                    word = "";
                    in_quote = false;
                }
                else word += c;
            }else{
                if(c == '\"') in_quote = true;
            }
        }
    }
    fin.close();
    
    return words;
}

bool group_sorter(vector<string>& a, vector<string>& b){
    return a[1] < b[1];
}

int factorial(int x){
    int prod = 1;
    while(x > 0){
        prod *= x;
        x--;
    }
    return prod;
}

vector<string> getCombos(string& unique, string& digits){
    vector<string> combos;
    string combo = digits.substr(0, (int)unique.length());
    combos.push_back(combo);
    while(combo.length() > 0){
        while(combo.length() > 0 and combo.back() + (int)unique.length() - (int)combo.length() == '9'){
            combo.pop_back();
        }
        if(combo.length() == 0) break;
        combo[(int)combo.length() - 1]++;
        while(combo.length() < unique.length()) combo.push_back(combo.back() + 1);
        
        combos.push_back(combo);
    }
    return combos;
}

vector<vector<string>> getGroups(vector<string>& words){
    
    vector<vector<string>> v;
    for(string& word : words){
        v.push_back({word, word});
    }
    for(vector<string>& x : v){
        sort(x[1].begin(), x[1].end()); // {original_word, sorted_word to allow grouping anagrams
    }
    sort(v.begin(), v.end(), group_sorter);
    
    vector<vector<string>> groups;
    string prev = v[0][1];
    vector<string> group;
    for(vector<string>& w : v){
        if(w[1] != prev){
            groups.push_back(group);
            group = {w[0]};
            prev = w[1];
        }else{
            group.push_back(w[0]);
        }
    }
    groups.push_back(group);
    
    return groups;
}

bool isPerfectSquare(long long val){
    int root = (int)floor(sqrt(val));
    long long square = root;
    square *= root;
    return val == square;
}

int main()
{
    string filename = "words.txt";
    vector<string> words = parseInput(filename);
    
    // max word length is 14, so we should use long long as our data type 
    
    int max_len = 0;
    cout << "max_len: " << max_len << endl;
    
    vector<vector<string>> groups = getGroups(words);
    
    long long ans = 0;
    string digits = "0123456789";
    
    int max_unique_len = 0;
    
    for(vector<string>& group : groups){
        
        if(group.size() < 2) continue; // we want PAIRS
        
        string s = group[0];
        sort(s.begin(), s.end());
        string unique = string(1, s[0]);
        
        char prev_c = s[0];
        for(char c : s){
            if(c != prev_c){
                unique += c;
                prev_c = c;
            }
        }
        
        if(unique.length() > 10) continue; // can't be mapped to 10 digits
        max_unique_len = max(max_unique_len, (int)unique.length());
        
        vector<string> combos = getCombos(unique, digits);
        for(string& combo : combos){
            string perm = combo;
            int num_perms = factorial((int)combo.length());
            for(int perm_num = 0; perm_num < num_perms; ++perm_num){
                // perm[i] is the digit that maps to the letter, unique[i]
                
                vector<char> mapping (26, '\0');
                for(int i = 0; i < unique.length(); ++i){
                    mapping[unique[i] - 'A'] = perm[i];
                }
                vector<long long> squares;
                for(string& cand : group){
                    // check for leading zeros
                    if(mapping[cand[0] - 'A'] == '0') continue;
                    
                    string num = "";
                    for(char c : cand) num += mapping[c - 'A'];
                    long long val = stol(num);
                    if(isPerfectSquare(val)) squares.push_back(val);
                }
                if(squares.size() >= 2){
                    long long max_square = 0;
                    for(long long square : squares) max_square = max(max_square, square);
                    ans = max(ans, max_square);
                }
                
                next_permutation(perm.begin(), perm.end());
            }
        }
    }
    cout << "max_unique_len: " << max_unique_len << endl;
    cout << "groups.size() " << groups.size() << endl;
    int max_group_sz = 0;
    vector<int> freq (51, 0);
    for(vector<string>& group : groups){
        max_group_sz = max(max_group_sz, (int)group.size());
        freq[(int)group.size()]++;
    }
    cout << "max_group_sz: " << max_group_sz << endl;
    
    cout << "group size freqs:" << endl;
    cout << freq[0] << ' ' << freq[1] << ' ' << freq[2] << ' ' << freq[3] << endl;
    
    cout << "ans: " << ans << endl;
    
    return 0;
}