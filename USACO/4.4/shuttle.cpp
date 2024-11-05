/*
ID: jamessh3
LANG: C++20
TASK: shuttle
*/

#include <bits/stdc++.h>
#include <ctime>
using namespace std;

void swap(string& s, int i, int j){
    char c = s[i];
    s[i] = s[j];
    s[j] = c;
}

string build(int count, string s){
    return string(count, s[0]) + " " + string(count, s[1]);
}

bool checkColor(char color, long long key, int idx, vector<long long>& pows_of_2){
    int a = 0;
    int b = 0;
    if((key & pows_of_2[2 * idx]) == pows_of_2[2 * idx]) a = 1;
    if((key & pows_of_2[2 * idx + 1]) == pows_of_2[2 * idx + 1]) b = 1;

    if(color == 'w'){
        // if(a == 0 and b == 1) return true;
        if(a == 1 and b == 0) return true;
        return false;
    }
    if(color == 'b'){
        // if(a == 1 and b == 0) return true;
        if(a == 0 and b == 1) return true;
        return false;
    }
    return true;
}

// long long getKey(string& s, vector<long long>& pows_of_3){
//     long long key = 0;
//     for(int i = 0; i < s.length(); ++i){
//         int coeff = -1;
//         if(s[i] == 'w') coeff = 0;
//         else if(s[i] == 'b') coeff = 1;
//         else if(s[i] == ' ') coeff = 2;
        
//         key += coeff * pows_of_3[i];
//     }
//     return key;
// }

long long getKey(string& s, vector<long long>& pows_of_4){
    long long key = 0;
    for(int i = 0; i < s.length(); ++i){
        int coeff = 0;
        if(s[i] == 'w') coeff = 1;
        else if(s[i] == 'b') coeff = 2;
        else if(s[i] == ' ') coeff = 3;
        
        key += coeff * pows_of_4[i];
    }
    return key;
}

long long tweakKey(long long& key, int i, int j, vector<long long>& pows_of_2){
    
    long long nkey = key;
    long long val = 0;
    val = pows_of_2[2 * i] & nkey;
    val ^= (pows_of_2[2 * j] & nkey);
    if(val != 0 and val != pows_of_2[2 * i] + pows_of_2[2 * j]){
        nkey ^= pows_of_2[2 * i];
        nkey ^= pows_of_2[2 * j];
    }
    val = pows_of_2[2 * i + 1] & nkey;
    val ^= (pows_of_2[2 * j + 1] & nkey);
    if(val != 0 and val != pows_of_2[2 * i + 1] + pows_of_2[2 * j + 1]){
        nkey ^= pows_of_2[2 * i + 1];
        nkey ^= pows_of_2[2 * j + 1];
    }
    
    return nkey;
}

bool same(long long& key, int i, int j, vector<long long>& pows_of_2){
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    if((key & pows_of_2[2 * i]) == pows_of_2[2 * i])         a = 1;
    if((key & pows_of_2[2 * i + 1]) == pows_of_2[2 * i + 1]) b = 1;
    if((key & pows_of_2[2 * j]) == pows_of_2[2 * j])         c = 1;
    if((key & pows_of_2[2 * j + 1]) == pows_of_2[2 * j + 1]) d = 1;
    
    return a == c and b == d;
}

int main()
{
    
    time_t curr = clock();

    ifstream fin ("shuttle.in");
    ofstream fout ("shuttle.out");
    
    int sz = 12;
    
    fin >> sz;
    
    string start = build(sz, "wb");
    string target = build(sz, "bw");
    
    // long long pow3 = 1;
    // vector<long long> pows_of_3;
    // for(int i = 0; i < 2 * sz + 1; ++i){
    //     pows_of_3.push_back(pow3);
    //     pow3 *= 3;
    // }
    long long pow4 = 1;
    vector<long long> pows_of_4;
    long long pow2 = 1;
    vector<long long> pows_of_2;
    for(int i = 0; i < 2 * sz + 1; ++i){
        pows_of_4.push_back(pow4);
        pow4 *= 4;
        
        pows_of_2.push_back(pow2);
        pow2 *= 2;
        pows_of_2.push_back(pow2);
        pow2 *= 2;
    }
    long long start_key = getKey(start, pows_of_4);
    long long target_key = getKey(target, pows_of_4);
    
    // 3 8 15 24
    
    
    // try a DLDFS?
    // Depth-Limited-Depth-First-Search may be much faster?
    // set the limit to sz^2 + 2sz # of moves, will it take
    // ages to finish the search?
    
    int moves = 1;
    vector<string> q = {start};
    vector<int> ind = {sz};
    vector<int> prev_move = {2}; // 0 means shift, 1 means jump,
                                // 2 means placeholder
    
    // pruning optimization, never shift twice in a row?
    
    vector<vector<int>> paths = {{-1}};
    vector<int> ans;
    
    vector<long long> keys = {start_key};
    // unordered_set<string> hs;
    unordered_set<long long> hs;
    // hs.insert(start);
    hs.insert(start_key);
    // while(q.size() > 0){
    while(keys.size() > 0){
        // vector<string> next_q;
        vector<int> next_ind;
        vector<int> next_prev_move;
        vector<long long> next_keys;
        vector<vector<int>> next_paths;
        // for(int i = 0; i < q.size(); ++i){
        for(int i = 0; i < keys.size(); ++i){
            // string& pos = q[i];
            int idx = ind[i];
            long long key = keys[i];

            // check for valid moves
            
            // UTILIZE PRUNING TO CHECK IF WE ARE MAKING A DUMB
            // MOVE! DON'T DO ANYTHING STUPID, DON'T DO
            // ANYTHING TWICE!
            
            if(idx >= 2 and checkColor('w', key, idx - 2, pows_of_2)){
                // if(pos[idx - 2] != pos[idx - 1]){
                //     string next_pos = pos;
                //     next_pos[idx] = next_pos[idx - 2];
                //     next_pos[idx - 2] = ' ';
                //     if(hs.count(next_pos) == false){
                //         hs.insert(next_pos);
                //         next_q.push_back(next_pos);
                //         next_ind.push_back(idx - 2);
                //         // next_prev_move.push_back(1);
                //     }
                // }
                if(not same(key, idx - 1, idx - 2, pows_of_2)){
                    long long nkey = tweakKey(key, idx - 2, idx, pows_of_2);
                    if(hs.count(nkey) == false){
                        hs.insert(nkey);
                        next_keys.push_back(nkey);
                        next_ind.push_back(idx - 2);
                        next_prev_move.push_back(1);
                        
                        vector<int> path = paths[i];
                        path.push_back(idx - 2);
                        next_paths.push_back(path);
                        if(nkey == target_key) ans = path;
                    }
                }
            }
            
            if(idx != 0 and prev_move[i] != 0 and checkColor('w', key, idx - 1, pows_of_2)){
            // if(idx != 0){
                // string next_pos = pos;
                // swap(next_pos, idx - 1, idx);
                
                // check if going to next_pos is a stupid move,
                // going to have to backtrack out and waste
                // moves!
                // if(hs.count(next_pos) == false){
                //     hs.insert(next_pos);
                //     next_q.push_back(next_pos);
                //     next_ind.push_back(idx - 1);
                //     // next_prev_move.push_back(0);
                // }
                
                long long nkey = tweakKey(key, idx - 1, idx, pows_of_2);

                if(hs.count(nkey) == false){
                    hs.insert(nkey);
                    next_ind.push_back(idx - 1);
                    next_keys.push_back(nkey);
                    next_prev_move.push_back(0);
                    
                    vector<int> path = paths[i];
                    path.push_back(idx - 1);
                    next_paths.push_back(path);
                    if(nkey == target_key) ans = path;
                }
            }
            if(idx != 2 * sz and prev_move[i] != 0 and checkColor('b', key, idx + 1, pows_of_2)){
            // if(idx != 2 * sz){
                // string next_pos = pos;
                // swap(next_pos, idx, idx + 1);
                // if(hs.count(next_pos) == false){
                //     hs.insert(next_pos);
                //     next_q.push_back(next_pos);
                //     next_ind.push_back(idx + 1);
                //     // next_prev_move.push_back(0);
                // }
                
                long long nkey = tweakKey(key, idx, idx + 1, pows_of_2);

                if(hs.count(nkey) == false){
                    hs.insert(nkey);
                    next_ind.push_back(idx + 1);
                    next_keys.push_back(nkey);
                    next_prev_move.push_back(0);
                    
                    vector<int> path = paths[i];
                    path.push_back(idx + 1);
                    next_paths.push_back(path);
                    if(nkey == target_key) ans = path;
                }
            }
            // check for leaps
            
            if(idx <= 2 * sz - 2 and checkColor('b', key, idx + 2, pows_of_2)){
                // if(pos[idx + 2] != pos[idx + 1]){
                //     string next_pos = pos;
                //     next_pos[idx] = next_pos[idx + 2];
                //     next_pos[idx + 2] = ' ';
                //     if(hs.count(next_pos) == false){
                //         hs.insert(next_pos);
                //         next_q.push_back(next_pos);
                //         next_ind.push_back(idx + 2);
                //         // next_prev_move.push_back(1);
                //     }
                // }
                if(not same(key, idx + 1, idx + 2, pows_of_2)){
                    long long nkey = tweakKey(key, idx, idx + 2, pows_of_2);
                    if(hs.count(nkey) == false){
                        hs.insert(nkey);
                        next_keys.push_back(nkey);
                        next_ind.push_back(idx + 2);
                        next_prev_move.push_back(1);
                        
                        vector<int> path = paths[i];
                        path.push_back(idx + 2);
                        next_paths.push_back(path);
                        if(nkey == target_key) ans = path;
                    }
                }
            }
        }
        // if(hs.count(target) == true){
        //     cout << "moves: " << moves << endl;
        //     break;
        // }
        if(hs.count(target_key) == true){
            cout << "moves: " << moves << endl;
            break;
        }
        // q = next_q;
        paths = next_paths;
        ind = next_ind;
        prev_move = next_prev_move;
        keys = next_keys;
        moves++;
    }
    
    
    
    cout << "hs.size() " << hs.size() << endl;
    
    ans.erase(ans.begin());
    // adjust to 1-indexed
    for(int i = 0; i < ans.size(); ++i) ans[i]++;
    cout << "ans:" << endl;
    for(int x : ans) cout << x << ' ';
    cout << endl;
    
    vector<vector<int>> rows;
    for(int i = 0; i < ans.size(); i += 20){
        int bound = min((int)ans.size(), i + 20);
        vector<int> row;
        for(int j = i; j < bound; ++j){
            row.push_back(ans[j]);
        }
        rows.push_back(row);
    }
    for(vector<int>& row : rows){
        for(int i = 0; i < (int)row.size() - 1; ++i){
            fout << row[i] << ' ';
        }
        fout << row.back() << endl;
    }
    
    cout << "elapsed secs: " << 1.0 * (clock() - curr) / CLOCKS_PER_SEC << endl;




    fin.close();
    fout.close();
    
    return 0;
}