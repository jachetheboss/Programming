/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

// *******************************************************************************/

// #include <iostream>
#include <bits/stdc++.h>
#include "functions.h"
using namespace std;
void printVector(vector<vector<int>>& v){
    cout << "{";
    for(vector<int>& a : v){
        cout << "{";
        for(int i = 0; i < (int)a.size() - 1; i++){
            cout << a[i] << ',';
        }
        cout << a.back() << "} ";
    }
    cout << "}" << endl;
}

bool comparator(vector<int>& a, vector<int>& b){
    return max(a[0], a[1]) < max(b[0], b[1]);
}

bool ltet(vector<long long>& a, vector<long long>& b){
    long long na = a[0];
    na *= b[1];
    long long nb = b[0];
    nb *= a[1];
    return na <= nb;
}

int main()
{
    // int max_peri = 1500000;
    int max_base1 = 100;
    int max_base2 = 200;
    vector<vector<int>> triples = generatePythagoreanTriples(max_base1, max_base2);
    // for(int i = (int)triples.size() - 1; i >= 0; --i){
    //     if(triples[i][0] <= 100 and triples[i][1] <= 100 and triples[i][2] <= 100){
    //         continue;
    //     }
    //     triples.erase(triples.begin() + i);
    // }
    cout << "triples.size() " << triples.size() << endl;
    printVector(triples);
    sort(triples.begin(), triples.end(), comparator);
    vector<vector<int>> solutions;
    unordered_set<string> unique;
    vector<vector<int>> inds = {{0, 1}, {1, 0}};
    for(vector<int>& triple : triples){
        for(vector<int>& ind : inds){
            int A = triple[ind[0]];
            int B = triple[ind[1]];
            for(int x = 1; x < B; x++){
                int b = x;
                int c = B - b;
                int a = A;
                vector<int> v = {a, b, c};
                sort(v.begin(), v.end());
                if(v[0] > max_base1 or v[1] > max_base1 or v[2] > max_base1) continue;

                string s = to_string(v[0]) + " " + to_string(v[1]) + " " + to_string(v[2]);
                if(unique.count(s)) continue;
                unique.insert(s);
                
                vector<vector<int>> arr = {{a, b, c}, {a, c, b}, {b, a, c}, {b, c, a}, {c, a, b}, {c, b, a}};
                bool ok = false;
                for(vector<int>& way : arr){
                    long long numer = way[0];
                    numer *= way[1];
                    int denom = way[1] + way[2];
                    vector<long long> frac = {numer, denom};
                    vector<long long> width = {way[0], 1};
                    if(ltet(frac, width)){
                        ok = true;
                        break;
                    }
                }
                if(ok) solutions.push_back(v);
            }
        }
    }
    cout << "solutions.size() " << solutions.size() << endl;
    cout << "solutions" << endl;
    printVector(solutions);
    // cout << "unique.size() " << unique.size() << endl;
    // cout << "unique" << endl;
    // int count = 0;
    // for(auto it = unique.begin(); it != unique.end(); it++){
    //     if(count % 10 == 0)
    //         cout << *it << endl;
    //     count++;
    // }
    // unordered_map<int, vector<vector<int>>> sums;
    // for(vector<int>& triple : triples){
    //     int sum = triple[0] + triple[1];
    //     if(not sums.count(sum)) sums.insert({sum, {}});
    //     sums[sum].push_back(triple);
    // }
    // cout << "sums:" << endl;
    // for(auto it = sums.begin(); it != sums.end(); it++){
    //     cout << "sum: " << it->first << endl;
    //     cout << "sz: " << (it->second).size() << endl;
    //     printVector(it->second);
    //     cout << endl;
    // }
    return 0;
}