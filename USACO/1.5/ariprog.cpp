/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: jamessh3
TASK: ariprog
LANG: C++                 
*/
/* LANG can be C++11 or C++14 for those more recent releases */
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    //ofstream fout ("ariprog.out");
    ofstream fout;
    ifstream fin ("ariprog.in");
    int N, M;
    fin >> N >> M;
    
    unordered_map<int, int> bisquares; // unique vals of the form p^2 + q^2

    for (int i = 0; i < M + 1; i++) {
        for (int j = i; j < M + 1; j++){
            int val = pow(i, 2) + pow(j, 2);
            bisquares[val] = 0;
        }
    }
    
    int size = bisquares.size();
    int bisquares_list[size];
    unordered_map <int, int>::iterator itr;
    itr = bisquares.begin();
    for (int i = 0; i < size; i++){
        bisquares_list[i] = (*itr).first;
        itr++;
    }
    int n = sizeof(bisquares_list) / sizeof(bisquares_list[0]);
  
    sort(bisquares_list, bisquares_list + n);
    // for (int i = 0; i < size; i++){
    //     std::cout << bisquares_list[i] << " ";
    // }
    // std::cout << "\n\n";
    vector<vector<int>> solutions;
    int index;
    for (int i = 0; i < size - 1; i++){
        for (int j = i + 1; j < size; j++){
            int A = bisquares_list[i];
            int diff = bisquares_list[j] - A;
            if ((A + diff * (N - 1)) > bisquares_list[size - 1]){
                break;
            }
            int num = A + diff * (N - 1);
            int len = 1;
            for (int n = N - 1; n > 0; n--){
                itr = bisquares.find(num);
                if (itr != bisquares.end()){
                    len = len + 1;
                }
                else{
                    break;
                }
                num = num - diff;
            }
            if (len == N){
                std::cout << A << " " << diff << "\n";
                vector<int> solution = {A, diff};
                solutions.push_back(solution);
                index = index + 1;
                std::cout << "index " << index;
                
            }
                
            }
        }

    sort(solutions.begin(), solutions.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
        return a[1] < b[1];});

    fout.open("ariprog.out");
    vector<vector<int>>::iterator it;
    it = solutions.begin();
    if (solutions.begin() == solutions.end()){
        fout << "NONE\n";
        return 0;
    }
    for (it = solutions.begin(); it != solutions.end(); it++){
        int x = (*it)[0];
        int y = (*it)[1];
        string a, b;
        a = std::to_string(x);
        b = std::to_string(y);
        std::cout << x << " " << y << "\n";
        fout << x << " " << y << endl;
    }
    fout.close();
    
    
    
    return 0;  
}