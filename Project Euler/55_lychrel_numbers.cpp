/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <vector>
#include <ctime> // do some experiments with different implementations of incrementing.
                 // for each increment call, check if all nines, or increment without consideration
                 // for every x iterations, x *= 10 between each increase in number of digits
using namespace std;

void increment(vector<int>& digits){ // this method mutates digits
    bool non_nine = false;
    for(int i = digits.size() - 1; i >= 0; --i){
        if(digits[i] == 9){
            digits[i] = 0;
        }else{
            digits[i] += 1;
            non_nine = true;
            break;
        }
    }
    if(non_nine == false){
        digits.insert(digits.begin(), 1);
    }
    // void return, since digits
}
vector<int> reverse_add(vector<int>& digits){
    int carry = 0;
    vector<int> result (digits.size(), 0);
    for(int i = digits.size() - 1; i >= 0; --i){
        result[i] = (carry + digits[i] + digits[digits.size() - 1 - i]) % 10; // using if-else block for carring
        carry = (carry + digits[i] + digits[digits.size() - 1 - i]) / 10;    // is probably faster!
    }
    if(carry == 1){
        result.insert(result.begin(), 1);
    }
    return result;
}
bool is_palindrome(vector<int>& digits){ // reused the digits variable name a bunch of times, but in different
                                        // functions and scopes, so should be ok
    for(int i = 0; i < digits.size() / 2; ++i){
        if(digits[i] != digits[digits.size() - 1 - i]){
            return false;
        }
    }
    return true;
}

int main()
{
    clock_t start_t = clock();
    
    vector<int> digits = {1};
    int lychrel_nums = 0;
    for(int count = 0; count < 9999; ++count){
        vector<int> result = reverse_add(digits);
        int iterations = 1;
        bool is_lychrel = true;
        while(iterations < 49){
            if(is_palindrome(result) == true){
                is_lychrel = false;
                break;
            }
            result = reverse_add(result);
            iterations += 1;
        }
        if(is_lychrel == true){
            lychrel_nums += 1;
        }
        increment(digits); // void function, mutates digits without reassignment since pass by reference
    }
    clock_t finish_t = clock();
    
    cout << "lychrel_nums: " << lychrel_nums << '\n';
    cout << "elapsed: " << static_cast<float>(finish_t - start_t) / CLOCKS_PER_SEC << " seconds" << '\n';
    return 0;
}
