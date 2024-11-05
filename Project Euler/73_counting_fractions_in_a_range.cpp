/*Project Euler
Counting fractions in range:

Explore a graphical approach, I think that most fractions cluster around 1/2, there are most ways to make ~ 1/2, and very few ways to make tiny fractions close to 0, and very few ways to make large fractions close to 1. Normal distribution?
*/
/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <sstream>
#include <cmath>
#include <limits>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> distinct_prime_factors(int num){ // we do not expect 0 or 1 to be input for num
    int limit = static_cast<int>(floor(sqrt(num)));
    vector<int> factors;
    for(int k = 2; k <= limit; ++k){
        if(num % k == 0){
            factors.push_back(k);
            while(num % k == 0){
                num /= k;
            }
        }if(num == 1){
            break;
        }
    }if(num != 1){
        factors.push_back(num);
    }
    return factors;
}

int main(){
    
    long long output = 0; // # of proper fractions with denominator <= 12000
                         // that are greater than 1/3 and less than 1/2
    // CODE BELOW WAS MY FIRST ATTEMPT, BUT INCORRECT, SINCE IT CONSIDERED
    // ALL POSSIBLE FRACTIONS, NOT PROPER REDUCED FRACTIONS.
    // for(int d = 2; d <= 12000; ++d){
    //     int start = d / 3 + 1;
    //     int limit = d / 2; // limit is inclusive, just like what I do in my 
    //                       // prime factorization algorithms
    //     if(d % 2 == 0){
    //         limit -= 1;
    //     }
    //     output += limit - start + 1;
    // }
    // cout << "ans: " << output << '\n';
    
    // One idea is to generate all fractions for all denominator, d, with
    // start <= nu <= limit, and then simplify the fractions, and put them
    // in a hashset to not count duplicates. Only 12,000 * 12,000, or
    // 1.44 * 10^8 fractions TOTAL, including improper fractions (1 or greater) 
    // and unsimplified fractions. So the memory used by hashset will likely
    // not be unrealistic.
    // The issue is the runtime. Simplyfing a fraction requires finding GCD,
    // so either finding prime factorizations of nu and de, and dividing
    // away GCD based on minimum # appearances of each prime factor, or
    // simply taking the smaller number (nu in this case), and checking
    // factors up to sqrt(nu), and dividing if nu and de both divisible
    // by the factor, this should be faster than taking full prime factorization
    // of both numbers. For each 2 <= d <= 12,000, have to take GCD
    // (1/2 - 1/3) * d number of times. Total number of GCD is thus
    // SigmaSummation(d = 2 to d = 12,000, 1/6 * d), so order of N^2 calculations.
    // Worst case taking GCD is O(sqrt(n)) time for a number n, so
    // O(N^(5/2)) calculations, which is quite slow for this method.
    
    // Another idea is using the totient function from the previous few problems.
    // Just find totient of de, but slightly modified, so that
    // not ALL coprimes to de less than d are found, but only those between
    // 1/3 de and 1/2 de. This would be quite tricky to implement, I think,
    // but should be blazing compared to the O(N^(5/2)) more naive approach
    // above.
    // Yet another approach, and easier to implement in practice than
    // the fully-fledged combinatorial method of finding totient (actually
    // try to implement a better one than using my good old trusty
    // builder arr technique), would be to
    // use a MODIFIED SIEVE similar to the marking method I talked about
    // with baba. I will implement it here.
    
    for(int de = 2; de <= 12000; ++de){
        int start = de / 3 + 1;
        int limit = de / 2; // limit is inclusive, just like what I do in my 
                          // prime factorization algorithms
        if(de % 2 == 0){
            limit -= 1;
        }
        // nu and de must be coprime with each other to be proper!
        // can use sieve, and cross out the nu in range start, limit (end inclusive)
        // that are multiples of prime factors of de,
        // but could just check every nu if it is divisible by prime factors of
        // de, so sieve is not necessary. Sieve is good for GENERATING, not CHECKING.
        // SIEVE WOULD STILL BE FASTER THAN THE FOLLOWING METHOD THOUGH,
        // SINCE SIEVE JUMPS WITH GAP SIZE, WHILE I AM CHECKING FOR DIVISIBILITY
        // FOR EACH OF THEM. AKA the below code does not utilize one important
        // fact: The next multiple of a number k will only occur at k + k,
        // and k + k + k, etc., so checking every number in the range for 
        // divisibility by k would be slow and redundant.
        vector<int> distinct = distinct_prime_factors(de);
        for(int nu = start; nu <= limit; ++nu){
            bool is_coprime = true;
            for(int i = 0; i < distinct.size(); ++i){
                if(nu % distinct[i] == 0){
                    is_coprime = false;
                    break;
                }
            }if(is_coprime){
                output += 1;
            }
        }
    }
    cout << "ans: " << output << '\n';
    

    return 0;
}
