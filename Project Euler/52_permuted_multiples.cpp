/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

int main()
{
    clock_t start_time = clock();
    
    int limit = 167; // intend on multiplying by 10 each while loop iteration
    int start = 100; // intend on multiplying by 10 each while loop iteration
    bool ans_found = false;
    int ans = 0;
    while(true){
        for(int k = start; k < limit; ++k){
            vector<int> digits (10, 0);
            int num = k;
            while(num != 0){
                digits[num % 10] += 1;
                num /= 10;
            }
            vector<int> temp_digits (10, 0);
            bool status = true;
            for(int c = 2; c <= 6; ++c){
                int temp = c * k;
                while(temp != 0){
                    temp_digits[temp % 10] += 1;
                    temp /= 10;
                }
                if(digits != temp_digits){ // does C++ allow == != comparison of two vectors? Yes.
                    status = false;
                    break;
                }
                for(int i = 0; i < 10; ++i){
                    temp_digits[i] = 0;
                }
            }
            if(status == true){
                ans_found = true;
                ans = k;
                break;
            }
        }
        if(ans_found == true){
            break;
        }
        //else
        limit *= 10;
        start *= 10;
    }
    clock_t finish_time = clock();
    
    cout << "ans: " << ans << '\n';
    cout << "elapsed: " << static_cast<float>(finish_time - start_time) / CLOCKS_PER_SEC << " seconds" << '\n';
    return 0;
}
