/*
ID: jamessh3
TASK: prefix
LANG: C++20
*/


// ////////////////////////////
// //////////////////////////// REMEMBER, THE MIN FUNCTION TAKES IN TWO INTS AS PARAMETERS.
///////////////////////////////////////// the .length() function on strings RETURNS A SIZE_T UNSIGNED INT!
                                /////// ALSO WHEN ADDING A LONG OR SIZE_T WITH INT, WARNING FLAG IS RAISED!


// FIND THE MEMORY LEAK! ST9_BAD_ALLOC

#include <iostream> // input output stream
#include <fstream> // file stream
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <cassert>

using namespace std;

int main(){
     ifstream fin ("prefix.in"); // in file stream
     ofstream fout ("prefix.out"); // out file stream
//    ifstream fin ("sample.txt");
//    ofstream fout ("output.txt");
//    ifstream fin ("C:/Users/james/OneDrive/Desktop/UF Textbooks/Fall 2022/Programming/USACO/2.3/sample.txt");
//    ifstream fin ("2.3/sample.txt");
//    ofstream fout ("output.txt");
    string substring = "";
    vector<string> substrings;
    while(true){
        fin >> substring;
        if(substring == "."){
            break;
        }
        substrings.push_back(substring);
    }
    // while(true){
    //     cin >> substring;
    //     if(substring == "."){
    //         break;
    //     }
    //     substrings.push_back(substring);
    // }
    string S = "";
    string temp = "";
    // while(cin >> temp){
    //     S += temp;
    // }
    while(fin >> temp){ // standard way to keep reading file input
        S += temp; // temp is no more than 76 characters in length (no '\n' included)
    }

//    if(S.length() == 200000){ // hardcode to see where the error is
//        return 0;
//    }

//    cout << "S: " << S << '\n';
//    cout << "substrings: " << '\n';
//    for(int i = 0; i < substrings.size(); ++i){
//        cout << substrings[i] << ' ';
//    } cout << '\n';
   
    unordered_map<int, vector<int>> hm;
    unordered_set<string> substring_set;
    for(int i = 0; i < substrings.size(); ++i){ // word bank words now put into a set
        substring_set.insert(substrings[i]);
    }
//     for(int i = 0; i < substrings.size(); ++i){
//         // if substrings[i].length() > S.length(), the inner for loop does not run
//         for(int j = 0; j < S.length() - static_cast<int>((substrings[i]).length()) + 1; ++j){
// //            if(substrings[i].length() > S.length() - j){ // check if index out of bounds
// //                continue;
// //            }
//             if(substrings[i] == S.substr(j, static_cast<int>((substrings[i]).length()))){
//                 if(hm.count(j) == false){
//                     hm.insert({j, {j + static_cast<int>((substrings[i]).length())}});
//                 }else{
//                     hm[j].push_back(j + static_cast<int>((substrings[i]).length()));
//                 }
//             }
//         }
//     }

//    ofstream fout2 ("S.txt");
//    fout << S;

    cout << "hm.max_size() " << hm.max_size() << '\n';
    cout << "S.length() " << S.length() << '\n';
//    if(S.length() == 200000){ // hardcode to see where the error is
//        return 0;
//    }

    substrings.clear();

//    cout << "S: " << '\n';
//    cout << S << '\n';
 
    string s1 = "";
    int S_length = static_cast<int>(S.length());
    for(int i = 0; i < S_length; ++i){
//        if(i % 100 == 0){
//            cout << "i: " << i << '\n';
//        }
        //int arg2 = static_cast<int>(S.length());
        int limit = min(i + 10, S_length);
        for(int j = i; j < limit; ++j){
            assert(j < S_length);
            s1 += S[j];
            if(substring_set.count(s1) == true){
                if(hm.count(i) == false){
                    hm.insert({i, vector<int>()});
                }
                hm[i].push_back(j + 1);
            }
        }
        s1 = "";
    }
    
    cout << "Checkpoint" << '\n';

    if(S.length() == 200000){ // hardcode to check where the error is
        return 0;
    }

    if(hm.count(0) == false){ // if there is no substring from the bank that
                              // starts at index 0 in the first place
        fout << 0 << '\n';
        return 0; // return 0 early to break out of the main function and terminate the program.
    }
    int max_length = 0;
    int index = 0; // starting index (starting "node")
    vector<bool> searched (S.length() + 1, false); // only need true or false for graphs with no cycles
                                              // (with cycles, meaning backwards edges, "w" "g" "b" needed)
    // S.length() + 1, +1 is for the index right after the last position in the string, in case all of S
    // is able to be covered by the words from the bank
    vector<int> index_stack;
    index_stack.push_back(0);
    while(searched[0] == false){ // while search not complete, while the root is not all searched
        if(hm.count(index) == false){ // the prefix cannot continue from this index
            if(index > max_length){
                max_length = index;
            }
            searched[index] = true;
            index_stack.pop_back();
            index = index_stack.back(); // will never call .top() on an empty stack, since .count(index) is
                                      // false. The root (index 0) definitely is in hm, or else program
                                      // would have already ended a few LOC ago. Has to have come from 0.
            continue;
        }
        bool deadend = true;
        for(int i = 0; i < hm[index].size(); ++i){
            if(searched[hm[index][i]] == false){
                index = hm[index][i];
                index_stack.push_back(index);
                deadend = false;
                break;
            }
        }
        if(deadend == true){
            if(index > max_length){
                max_length = index;
            }
            searched[index] = true;
            index_stack.pop_back();
            if(index_stack.size() != 0){
                index = index_stack.back();
            }
        }
    }
    fout << max_length << '\n';    
    cout << max_length << '\n';
    return 0;
}