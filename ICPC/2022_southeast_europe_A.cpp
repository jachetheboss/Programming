// A. AppendAppendAppend

// Momo has a string s which he plays with. After each day, he takes the initial string and appends it to the one that he currently has, that is, if the string is "abc", on the first day the string will remain "abc", on the second day the string will become "abcabc", on the third day the string becomes "abcabcabc", and so on.

// Bobo has another string t. Bobo is curious whether his string t can be found as a subsequence in Momo's string. He is curious what is the first day when this property will hold.

// A string a is a subsequence of a string b if a can be obtained from b by deletion of several (possibly, zero or all) elements.

// Input
// The first line of the input contains Momo's string s.

// The second line of the input contains Bobo's string t.

// Both strings have lengths at least 1 and at most 5⋅105 and contain only lowercase letters of the English alphabet.

// Output
// Output a single integer  — the number of the day when Bobo's string will be a subsequence of Momo's string for the first time.

// It is guaranteed that for all test cases in this problem such a day exists.

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;
int main(){
    string S = "";
    string T = "";
    cin >> S >> T;
    vector<vector<int>> next (S.length(), vector<int> (26, -1)); // next index for each letter in alphabet
    vector<int> first (26, -1); // indices of first appearance of each letter
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    for(int i = 0; i < alphabet.length(); ++i){
        for(int j = 0; j < S.length(); ++j){
            if(S[j] == alphabet[i]){
                first[i] = j;
                break;
            }
        }
    }
    for(int i = 0; i < alphabet.length(); ++i){
        int index = -1; // if -1, go to index in first vector, meaning no more of that letter to the right in S
        for(int j = S.length() - 1; j >= 0; --j){
            next[j][i] = index;
            if(S[j] == alphabet[i]){
                index = j;
            }
        }
    }
    int day = 1;
    int j = 0; // index in S
    for(int i = 0; i < T.length(); ++i){
        j = next[j][T[i] - 'a'];
        if(j == -1){
            day += 1;
            j = first[T[i] - 'a'];
        }
    }
    
    cout << day << '\n';
    
    return 0;
}