/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx,avx2,fma")

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <ctime>
using namespace std;

// Probably some overflow error going on. The correct answer
// was outputted for small inputs.

void increment_builder(vector<int>& builder, vector<int>& capacity){
    for(int i = 0; i < builder.size(); ++i){ // "LSB" on left
        if(builder[i] == capacity[i]){
            builder[i] = 0;
        }else{
            builder[i] += 1;
            break;
        }
    }
    return;
}
void get_perimeters(int b, int max_perimeter, vector<vector<int>>& p_factors, vector<int>& perimeter_freq){
    vector<int> builder (p_factors[b].size() / 2, 0);
    vector<int> capacity;
    int combos = 1;
    vector<int> distinct; // distinct prime factors of b
    for(int i = 0; i < p_factors[b].size(); i += 2){
        distinct.push_back(p_factors[b][i]);
        capacity.push_back(p_factors[b][i + 1]);
        combos *= (p_factors[b][i + 1] + 1); // if freq of distinct prime factor is 2, then option to
                                            // include it 0 times, 1 time, 2 times, so 3 choices.
    }
    long long b_squared = b;
    b_squared *= b;
    //cout << "b_squared: " << b_squared << "\n\n";
    long long divisor = 0;
    for(int cnt = 0; cnt < combos; ++cnt){
        divisor = 1;
        for(int i = 0; i < builder.size(); ++i){
            // divisor *= pow(distinct[i], builder[i]); // pow function takes in double
            for(int j = 0; j < builder[i]; ++j){
                divisor *= distinct[i];
            }
        }
        //cout << "divisor: " << divisor << '\n';
        if(divisor >= b){
            increment_builder(builder, capacity);
            continue;
        }
        int rem = ((b_squared / divisor) - divisor) % 2;
        if(rem == 0){
            long long a = ((b_squared / divisor) - divisor) / 2;
            long long a_squared = a;
            a_squared *= a;
            long long c_squared = a_squared + b_squared;
            int c = static_cast<int>(floor(sqrt(c_squared)));
            if(a + b + c > max_perimeter){
                increment_builder(builder, capacity); // whenever early continue, update the things
                                                     // that are supposed to be updated a few lines below!
                continue;
            }
            perimeter_freq[static_cast<int>(a) + static_cast<int>(b) + static_cast<int>(c)] += 1;
            //if(a + b + c == 36){
                //cout << "a:" << a << " b:" << b << " c:" << c << '\n';
                //cout << "perimeter: " << a + b + c << "\n\n";
            //}
        }
        increment_builder(builder, capacity);
    }
    return;
}
int main()
{
    clock_t t1 = clock();
    
    int max_perimeter = 0;
    cout << "Enter max perimeter: ";
    cin >> max_perimeter;
    int max_b = max_perimeter / 2 - 1; // max_b inclusive,
                                      // max length of side b given perimeter
    vector<bool> sieve (max_b + 1, true);
    sieve[0] = false;
    sieve[1] = false;
    int limit = static_cast<int>(floor(sqrt(max_b))); // limit is inclusive
    for(int k = 2; k <= limit; ++k){
        if(sieve[k] == false){
            continue;
        }for(int j = k * k; j < sieve.size(); j += k){
            sieve[j] = false;
        }
    }
    int num_primes = count(sieve.begin(), sieve.end(), true);
    //cout << "Primes within " << max_b << ": " << num_primes << '\n';
    vector<int> primes;
    for(int k = 2; k < sieve.size(); ++k){
        if(sieve[k] == true){
            primes.push_back(k);
        }
    }
    vector<vector<int>> p_factors (max_b + 1, vector<int>()); // prime factors
    for(int i = 0; i < primes.size(); ++i){
        int p = primes[i];
        for(int j = p; j < p_factors.size(); j += p){
            p_factors[j].push_back(p); // prime val
            p_factors[j].push_back(1);// freq
        }
        long long pow_of_p = p; // USE LONG LONG, SINCE MULTIPLYING BIG ints TOGETHER !!!!!!!
                          // Make this an AUTOMATIC habit!
        pow_of_p *= p;
        while(pow_of_p < p_factors.size()){
            for(int j = pow_of_p; j < p_factors.size(); j += pow_of_p){ // make sure to make special incrementer
                                                                       // correct!
                p_factors[j][p_factors[j].size() - 1] += 1;
            }
            pow_of_p *= p;
        }
    }
    // //cout << "prime factorization of 720:" << '\n';
    // for(int i = 0; i < p_factors[720].size(); ++i){
    //     //cout << p_factors[720][i] << ' ';
    // } //cout << "\n\n";
    
    for(int k = 2; k < p_factors.size(); ++k){
        for(int i = 0; i < p_factors[k].size(); i += 2){ // double freq of all prime factors,
                                                        // effectively squaring k
            p_factors[k][i + 1] *= 2;
        }
    }
    // be on the lookout for overflows. When the C++ program terminates
    // in the middle, without outputting anything, that is a sign 
    // that there is a memory bug, potentially due to undefined behavior
    // involving numeric types.
    vector<int> perimeter_freq (max_perimeter + 1, 0); // every freq should be divided by 2,
                                                      // since there are duplicates. When b = 9, a = 40 found.
                                                     // When b = 40, a = 9 found.
    //cout << "perimeter_freq.size() " << perimeter_freq.size() << "\n\n";
    int iterations = 0;
    for(int b = 3; b <= max_b; ++b){
        get_perimeters(b, max_perimeter, p_factors, perimeter_freq);
        iterations += 1;
        if(b % 100 == 0){
            //cout << "iterations: " << iterations << '\n';
        }
    }
    int output = 0;
    for(int i = 0; i < perimeter_freq.size(); ++i){
        if(perimeter_freq[i] == 2){
            output += 1;
        }
    }
    
    clock_t t2 = clock();
    cout << "output: " << output << '\n';
    
    // for(int i = 0; i < perimeter_freq.size(); ++i){
    //     //cout << "perimeter: " << i << '\n';
    //     //cout << "freq: " << perimeter_freq[i] << "\n\n";
    // }
    cout << "elapsed: " << static_cast<double>(t2 - t1) / CLOCKS_PER_SEC << " seconds" << '\n';

    return 0;
}
