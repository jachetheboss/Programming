/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <limits>

using namespace std;




/////////
/////////
///////// REMEMBER, POSSIBLE OVERFLOWS WHEN CONCATENATING TWO INTS !!!!!!!
///////// AND POSSIBLE INDEX OVERFLOWS WHEN CHECKING IF LARGE NUMBER IS PRIME IN SIEVE!


int main()
{//664579
    vector<bool> sieve (100000000, true);
    sieve[0] = false;
    sieve[1] = false;
    for(int k = 2; k < (sieve.size() - 1) / 2 + 1; ++k){
        if(sieve[k] == false){
            continue;
        }
        for(int j = 2 * k; j < sieve.size(); j += k){
            sieve[j] = false;
        }
    }
    int num_primes = 0;
    vector<int> primes;
    for(int i = 0; i < sieve.size(); ++i){
        if(sieve[i] == true){
            num_primes += 1;
            primes.push_back(i);
        }
    }
    cout << "primes less than 10 million: " << num_primes << '\n';
    
    unordered_map<string, vector<int>> hm; // stores frequency of a combination of digits
    unordered_map<string, vector<int>>::iterator it;
    vector<int> digits (10, 0); // digits[j] is how many times digit j is in a particular prime number
    for(int i = 0; i < primes.size(); ++i){
        int num = primes[i];
        while(num != 0){
            digits[num % 10] += 1;
            num /= 10;
        }
        string key = "";
        for(int j = 0; j < digits.size(); ++j){
            key += to_string(j) + ":" + to_string(digits[j]) + " ";
            digits[j] = 0; // reset digits back to all zeros. Since digits vector scope is outside
                          // of for loop, save some runtime/memory, instead of redeclaring for each
                         // new for loop, but MUST REMEMBER TO ALL FREQUENCIES BACK TO ZERO!
        }
        if(hm.count(key) == false){
            hm.insert({key, {primes[i]}});
        }else{
            hm[key].push_back(primes[i]);
        }
    }
    
    vector<int> viable;
    unordered_map<int, int> build; // building block substring
    int iteration = 0;
    for(it = hm.begin(); it != hm.end(); ++it){
        if((it->second).size() == 1){
            continue;
        }
        for(int j = 0; j < (it->second).size(); ++j){
            string s = to_string((it->second)[j]);
            string a = "";
            string b = "";
            for(int k = 1; k <= s.length() - 1; ++k){ // if s is split into two substrings a and b,
                                                     // k is the length of substring a
                a = s.substr(0, k);
                b = s.substr(k, s.length() - k);
                if(a.back() == '0' || a.back() == '2' || a.back() == '4' || a.back() == '6' || a.back() == '8' || a.back() == '5'){
                    continue; // can't be an ending even digit after splitting the number
                }
                if(b.front() == '0'){ // can't be a leading 0 after splitting the number
                    continue;
                }
                int num_a = atoi(a.c_str());
                int num_b = atoi(b.c_str());
                // if((it->second)[j] == 73 || (it->second)[j] == 7109 || (it->second)[j] == 1097){
                //     cout << "num_a: " << num_a << '\n';
                //     cout << "num_b: " << num_b << '\n';
                // }
                long concat = num_b * pow(10, static_cast<int>(a.length())) + num_a;
                if(concat > sieve.size()){
                    continue;
                }
                if(sieve[num_a] == true && sieve[num_b] == true && sieve[concat] == true){
                    // if(iteration < 50){
                    //     cout << "num_a: " << num_a << '\n';
                    //     cout << "num_b: " << num_b << '\n';
                    // }
                    viable.push_back((it->second)[j]); // viable will have duplicate values since there
                                                      // could be numbers will multiple viable splitting
                                                     // points, a side effect of commenting out the break
                    if(build.count(num_a) == false){
                        build.insert({num_a, 1});
                    }else{
                        build[num_a] += 1;
                    }if(build.count(num_b) == false){
                        build.insert({num_b, 1});
                    }else{
                        build[num_b] += 1;
                    }
                    // break; // commenting out this break since
                    // there could be multiple viable splitting points in a number, so we want to get
                    // all of them, not just one of them.
                }
            }
        }
        iteration += 1;
    }
    unordered_map<int, int>::iterator it1;
    vector<int> gr8r_than_8; ///////////////// The prime building num has to appear in at least
                             ///////////////// 8 concatenated larger primes in order to be able 
                             ///////////////// to be a part of a group of 5 primes by the problem description
    for(it1 = build.begin(); it1 != build.end(); ++it1){
        if(it1->second >= 8){
            gr8r_than_8.push_back(it1->first);
        }
    }
    cout << "viable.size() " << viable.size() << '\n'; // originally 34969, now 35918 after break commented
                                                      // out above, introducing some duplicate primes
                                                     // that have more than one viable splitting point
    cout << "gr8r_than_8.size() " << gr8r_than_8.size() << '\n';
    
    sort(gr8r_than_8.begin(), gr8r_than_8.end());
    // cout << "gr8r_than_8" << '\n';
    // for(int i = 0; i < gr8r_than_8.size(); ++i){
    //     cout << gr8r_than_8[i] << ' ';
    // } cout << "\n\n";
    
    vector<int> rem1;
    vector<int> rem2;
    for(int i = 0; i < gr8r_than_8.size(); ++i){
        if(gr8r_than_8[i] % 3 == 1){
            rem1.push_back(gr8r_than_8[i]);
        }else{
            rem2.push_back(gr8r_than_8[i]);
        }
    }
    
    
    rem1.insert(rem1.begin(), 3); // only prime that has digits sum to multiple of 3
    
    cout << "rem1" << '\n';
    for(int i = 0; i < rem1.size(); ++i){
        cout << rem1[i] << ' ';
    } cout << "\n\n";
    cout << "rem2" << '\n';
    for(int i = 0; i < rem2.size(); ++i){
        cout << rem2[i] << ' ';
    } cout << "\n\n";
    
    cout << "hello" << '\n';
    
    vector<vector<int>> options1 (rem1.size(), vector<int>());
    
    cout << "rem1.size() " << rem1.size() << '\n';
    
    for(int i = 0; i < rem1.size(); ++i){
        for(int j = 0; j < rem1.size(); ++j){
            if(i == j){
                continue;
            }
            int len_i = static_cast<int>(floor(log10(rem1[i]))) + 1;
            long num1 = pow(10, len_i) * rem1[j] + rem1[i];
            int len_j = static_cast<int>(floor(log10(rem1[j]))) + 1;
            long num2 = pow(10, len_j) * rem1[i] + rem1[j];
            // cout << "num1: " << num1 << '\n';
            // cout << "num2: " << num2 << '\n';
            // cout << '\n';
            if(num1 > 100000000 || num2 > 100000000){ // have to check if index out of bounds,
                                                   // sieve only has up to 10 million, while concatenating
                                                  // two large primes can easily surpass sieve max index.
                                                 // WATCH OUT FOR OVERFLOW TYPES AS WELL! concatenating
                                                // two large primes bounded by 10 million can overflow int
                                               // type. BE VERY CAREFUL WITH TYPES IN C++
                continue;
            }
            if(sieve[num1] == true && sieve[num2] == true){
                options1[i].push_back(rem1[j]);
            }
        }
    }
    int max_options = 0;
    int max = 0;
    for(int i = 0; i < options1.size(); ++i){
        if(options1[i].size() > max_options){
            max_options = options1[i].size();
            max = rem1[i];
        }
    }
    
    cout << "options for 3:" << '\n';
    for(int i = 0; i < options1[0].size(); ++i){
        cout << options1[0][i] << ' ';
    } cout << "\n\n";
    
    cout << "max_options: " << max_options << '\n';
    cout << "max: " << max << '\n';
    
    unordered_map<int, unordered_set<int>> di;
    
    for(int i = 0; i < options1.size(); ++i){
        di.insert({rem1[i], unordered_set<int>()});
        for(int j = 0; j < options1[i].size(); ++j){
            di[rem1[i]].insert(options1[i][j]);
        }
    }
    
    
    
    // CHECK IF THE LOGIC BELOW IS CORRECT, brute force N^4 for loop
    
    int min_sum = std::numeric_limits<int>::max();
    for(int i = 0; i < options1.size(); ++i){
        if(options1.size() < 4){ // must be size 4 or greater to be able to make a group of 5 (rem1[i] host
                                 // itself considered as well)
            continue;
        }
        for(int a = 0; a < options1[i].size() - 3; ++a){
            for(int b = a + 1; b < options1[i].size() - 2; ++b){
                for(int c = b + 1; c < options1[i].size() - 1; ++c){
                    for(int d = c + 1; d < options1[i].size(); ++d){
                        if(di[options1[i][a]].count(options1[i][b]) == true && 
                           di[options1[i][a]].count(options1[i][c]) == true &&
                           di[options1[i][a]].count(options1[i][d]) == true &&
                          di[options1[i][b]].count(options1[i][c]) == true &&
                           di[options1[i][b]].count(options1[i][d]) == true &&
                           di[options1[i][c]].count(options1[i][d]) == true){
                            // ){
                              if(rem1[i] + options1[i][a] + options1[i][b] + options1[i][c] + 
                              options1[i][d] < min_sum){
                                    min_sum = rem1[i] + options1[i][a] + options1[i][b] + options1[i][c] + 
                                    options1[i][d];
                            //     if(rem1[i] + options1[i][a] + options1[i][b] + options1[i][c] < min_sum){
                            //         min_sum = rem1[i] + options1[i][a] + options1[i][b] + options1[i][c];
                              }
                        }
                    }
                }
            }
        }
    }
    cout << "min_sum: " << min_sum << '\n'; // but have to do the same for rem2
    
    
    
    
    
    // options2
    
    vector<vector<int>> options2 (rem2.size(), vector<int>());
    
    cout << "rem2.size() " << rem2.size() << '\n';
    
    for(int i = 0; i < rem2.size(); ++i){
        for(int j = 0; j < rem2.size(); ++j){
            if(i == j){
                continue;
            }
            int len_i = static_cast<int>(floor(log10(rem2[i]))) + 1;
            long num1 = pow(10, len_i) * rem2[j] + rem2[i];
            int len_j = static_cast<int>(floor(log10(rem2[j]))) + 1;
            long num2 = pow(10, len_j) * rem2[i] + rem2[j];
            // cout << "num1: " << num1 << '\n';
            // cout << "num2: " << num2 << '\n';
            // cout << '\n';
            if(num1 > 100000000 || num2 > 100000000){ // have to check if index out of bounds,
                                                   // sieve only has up to 10 million, while concatenating
                                                  // two large primes can easily surpass sieve max index.
                                                 // WATCH OUT FOR OVERFLOW TYPES AS WELL! concatenating
                                                // two large primes bounded by 10 million can overflow int
                                               // type. BE VERY CAREFUL WITH TYPES IN C++
                continue;
            }
            if(sieve[num1] == true && sieve[num2] == true){
                options2[i].push_back(rem2[j]);
            }
        }
    }
    // int max_options = 0;
    // // int max = 0;
    // for(int i = 0; i < options2.size(); ++i){
    //     if(options2[i].size() > max_options){
    //         max_options = options2[i].size();
    //         max = rem2[i];
    //     }
    // }
    
    cout << "options for 3:" << '\n';
    for(int i = 0; i < options2[0].size(); ++i){
        cout << options2[0][i] << ' ';
    } cout << "\n\n";
    
    cout << "max_options: " << max_options << '\n';
    cout << "max: " << max << '\n';
    
    // unordered_map<int, unordered_set<int>> di;
    di.clear();
    
    for(int i = 0; i < options2.size(); ++i){
        di.insert({rem2[i], unordered_set<int>()});
        for(int j = 0; j < options2[i].size(); ++j){
            di[rem2[i]].insert(options2[i][j]);
        }
    }
    
    // int min_sum = std::numeric_limits<int>::max();
    for(int i = 0; i < options2.size(); ++i){
        if(options2.size() < 4){ // must be size 4 or greater to be able to make a group of 5 (rem2[i] host
                                 // itself considered as well)
            continue;
        }
        for(int a = 0; a < options2[i].size() - 3; ++a){
            for(int b = a + 1; b < options2[i].size() - 2; ++b){
                for(int c = b + 1; c < options2[i].size() - 1; ++c){
                    for(int d = c + 1; d < options2[i].size(); ++d){
                        if(di[options2[i][a]].count(options2[i][b]) == true && 
                           di[options2[i][a]].count(options2[i][c]) == true &&
                           di[options2[i][a]].count(options2[i][d]) == true &&
                          di[options2[i][b]].count(options2[i][c]) == true &&
                           di[options2[i][b]].count(options2[i][d]) == true &&
                           di[options2[i][c]].count(options2[i][d]) == true){
                            // ){
                              if(rem2[i] + options2[i][a] + options2[i][b] + options2[i][c] + 
                              options2[i][d] < min_sum){
                                    min_sum = rem2[i] + options2[i][a] + options2[i][b] + options2[i][c] + 
                                    options2[i][d];
                            //     if(rem2[i] + options2[i][a] + options2[i][b] + options2[i][c] < min_sum){
                            //         min_sum = rem2[i] + options2[i][a] + options2[i][b] + options2[i][c];
                              }
                        }
                    }
                }
            }
        }
    }
    cout << "min_sum: " << min_sum << '\n'; // but have to do the same for rem2
    
    return 0;
    
    // now the bank of possible primes has been winnowed down. winnow down to minnow. reduce in size. good
    // way to remember it.
}
