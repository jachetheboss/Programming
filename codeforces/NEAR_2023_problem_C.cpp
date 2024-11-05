    /******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

// 1 36 2617890805530 1179559901520 931489251000 126671324010 6074597799270 2651568397170 20771120370 4705764486390 5266240787535 1099307729520 5497329427590 5710853958810 3209671442670 6469693230 5688442719960 1845355576680 2123104174620 5449999493400 5179975334820 5717165754300 2089937126340 5564228043660 3772946617440 3098779363680 1886351621700 2798540702100 4456657308012 2135948860710 2254774583880 6240083423574 5676735365070 2515857093750 5847264122700 3672653864880 5791737481530 4050806582550

// could memoize some results

#include <iostream>
#include <vector>
#include <unordered_set> // unordered_set .count() takes in size_t as parameter. size_t depends on the
                        // machine, could be 32 bit unsigned int size or 64 bit unsigned long long
#include <unordered_map>
#include <algorithm>
#include <limits>
using namespace std;

// REMEMBER, WHEN YOU USE AN EARLY BREAK/CONTINUE IN YOUR CODE TO CHECK FOR SOME EDGE
// CASE OR SPECIAL CASE, REMEMBER TO CIN >> IN ALL OF THE INPUTS, OR ELSE THE INPUTS
// WILL BE OUT OF WACK! GET ALL THE INPUTS FOR THE PARTICULAR TEST CASE !!!!!!!
// THIS CONTRIBUTED TO YOU GETTING PROBLEM C OF GOODBYE 2022 CodeForces WRONG!

// ALSO FOR THIS PROBLEM, TAKING ALL OF THE DIFFERENCES BETWEEN ALL DISTINCT PAIRS
// OF TWO NUMBERS IS SLOW AND UNNECESSARY. INCREASES THE TOTAL NUMBER OF OPERATIONS!
// SINCE THE NUMBERS HAVE ALREADY BEEN CHECKED IF THEY ARE ALL DISTINCT
// (CLEAN WAY IS TO JUST SORT THEM AND THEN CHECK FOR EQUALITY OF ADJACENT NUMBERS,
// OR USE A HASHMAP, BUT REMEMBER IF YOU BREAK/CONTINUE EARLY, GET IN ALL THE cin 
// THAT YOU HAVE TO GET FOR THE TEST CASE)

// IF MOD OF PRIME FACTOR APPEARS TWICE, THEN THAT IS A DIFFERENCE. FROM O(N^2) to O(N),
// as in tourist's solution

vector<int> factorize(long long diff, vector<int>& primes){ // only distinct prime factors are returned,
                                      // also only prime factors below 10,000 are returned.
    vector<int> factors;
    for(int i = 0; i < primes.size(); ++i){ // get all prime factors under 10,000, don't care about the 
                                   // larger ones
        if(diff % primes[i] == 0){
            factors.push_back(primes[i]);
        }
    }
    return factors;
}

int main()
{
    
    clock_t start_t = clock();
    
    vector<bool> sieve (4951, true);
    sieve[0] = false;
    sieve[1] = false;
    for(int k = 2; k < (sieve.size() - 1) / 2 + 1; ++k){
        if(sieve[k] == false){
            continue;
        }
        for(int j = 2 * k; j < sieve.size(); j += k){ // REMEMBER, j += k for sieve, not ++j
            sieve[j] = false;
        }
    }
    vector<int> primes;
    for(int k = 2; k < sieve.size(); ++k){
        if(sieve[k] == true){
            primes.push_back(k);
        }
    }
    // cout << "primes" << '\n';
    // for(int i = 0; i < primes.size(); ++i){
    //     cout << primes[i] << ' ';
    // } cout << "\n\n";
    

    
    int cases = 0;
    int n = 0;
    cin >> cases;
    for(int cnt = 0; cnt < cases; ++cnt){
        cin >> n; // length of arr
        vector<long long> nums; // BE CAREFUL OF THE TYPES!
        // unordered_set<long long> unique;
        long long num = 0;
        bool status = true;
        
        // cout << "test case " << cnt + 1 << '\n';
        for(int i = 0; i < n; ++i){
            cin >> num;
            // cout << num << ' ';
            // if(unique.count(num) == true){ // if there is a duplicate value in nums, automatically "NO"
            //     status = false;
            //     for(int j = 0; j < n - 1 - i; ++j){
            //         cin >> num;
            //     }
            //     break;
            // }
            // unique.insert(num);
            nums.push_back(num);
        }
        // cout << '\n';
        
        // if(status == false){
        //     cout << "NO" << "\n\n";
        //     continue;
        // }
        
        // cout << '\n' << "nums" << '\n';
        // cout << "nums.size() " << nums.size() << '\n';
        // for(int i = 0; i < nums.size(); ++i){
        //     cout << nums[i] << ' ';
        // } cout << "\n\n";
        
        unordered_map<long long, vector<bool>> hm; // prime factor key, mod (shift) boolean field,
                                                  // only primes under 10,000 are considered, since
                                                 // prime greater than that there is no way to cover
                                                // all possible mods of it with possible combinations
                                              // of just 100 digits.
        sort(nums.begin(), nums.end());
        for(int i = 0; i < nums.size() - 1; ++i){
            if(nums[i] == nums[i + 1]){
                status = false;
                break;
            }
        }
        if(status == false){
            cout << "NO" << '\n';
            continue;
        }
        
        vector<vector<int>> PRIME_MODS (primes.size(), vector<int>());
        for(int i = 0; i < PRIME_MODS.size(); ++i){
            for(int j = 0; j < primes[i]; ++j){
                PRIME_MODS[i].push_back(0);
            }
        }
        // for(int i = 0; i < nums.size() - 1; ++i){
        //     for(int j = 0; j < primes.size(); ++j){
        //         hm[prim]
        //     }
            // for(int j = i + 1; j < nums.size(); ++j){
            //     long long diff = nums[j] - nums[i];
            //     // if(nums[j] - nums[i] == 1){
            //     //     continue; // all adjacent integers (differ by only 1) are coprime! So for any X 
            //     //              // a + X, b + X, where b = a + 1, is coprime!
            //     // }
            //     vector<int> factors = factorize(diff, primes);
            //     // cout << "diff " << diff << '\n';
            //     // for(int m = 0; m < factors.size(); ++m){
            //     //     cout << factors[m] << ' ';
            //     // } cout << "\n\n";
            //     for(int m = 0; m < factors.size(); ++m){
            //         if(hm.count(factors[m]) == false){
            //             hm.insert({factors[m], vector<bool> (factors[m], false)});
            //             // int rem = nums[i] % factors[m];
            //             hm[factors[m]][nums[i] % factors[m]] = true;
            //         }else{
            //             // int rem = nums[i] % factors[m];
            //             hm[factors[m]][nums[i] % factors[m]] = true;
            //         }
            //     }
            // }
        // }
        for(int i = 0; i < nums.size(); ++i){
            for(int j = 0; j < primes.size(); ++j){
                PRIME_MODS[j][nums[i] % primes[j]] += 1;
            }
        }
        
        // the count(vec.begin(), vec.end(), <my_value>);
        // is a good function
        
        for(int i = 0; i < PRIME_MODS.size(); ++i){
            bool less_than_2 = false;
            for(int j = 0; j < PRIME_MODS[i].size(); ++j){
                if(PRIME_MODS[i][j] < 2){
                    less_than_2 = true;
                    break;
                }
            }
            if(less_than_2 == false){
                status = false;
                break;
            }
        }
        if(status == true){
            cout << "YES" << '\n';
        }else{
            cout << "NO" << '\n';
        }
        
        // status = true;
        // unordered_map<long long, vector<bool>>::iterator it;
        // for(it = hm.begin(); it != hm.end(); ++it){
        //     int num_false = count((it->second).begin(), (it->second).end(), false);
        //     if(num_false == 0){
        //         status = false;
        //         break;
        //     }
        // }
        // if(status == true){
        //     cout << "YES" << "\n\n";
        // }else{
        //     cout << "NO" << "\n\n";
        // }
    }
    
    clock_t finish_t = clock();
    // cout << "elapsed: " << static_cast<float>(finish_t - start_t) / CLOCKS_PER_SEC << " seconds" << '\n';
    
    return 0;
    
//     unordered_set<long long> hs;
//     hs.insert(2);
//     if(hs.count(2) == true){
//         cout << "hello" << '\n';
//     }
    
//     size_t num1 = std::numeric_limits<size_t>::max();
//     long long num2 = std::numeric_limits<long long>::max();
//     cout << num1 << '\n';
//     cout << num2 << '\n';
//     return 0;
// }

//     return 0;
}


//1
//36
//2617890805530 1179559901520 931489251000 126671324010 6074597799270 2651568397170 20771120370 4705764486390 //5266240787535 1099307729520 5497329427590 5710853958810 3209671442670 6469693230 5688442719960 1845355576680 //2123104174620 5449999493400 5179975334820 5717165754300 2089937126340 5564228043660 3772946617440 //3098779363680 1886351621700 2798540702100 4456657308012 2135948860710 2254774583880 6240083423574 //5676735365070 2515857093750 5847264122700 3672653864880 5791737481530 4050806582550
