/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <limits>

using namespace std;

int DP_method(int target){ // target total rectangles
    
    vector<int> DP = {1};
    int incr = 2;
    int min_distance = std::numeric_limits<int>::max();
    int top_row_size = -1;
    int ans = -1; // ans is area of closest rectangle
    
    // top row is triangular numbers
    while(true){
        int val = DP.back() + incr;
        DP.push_back(val);
        if(val > target){
            top_row_size = DP.size();
            if(DP.back() - target < min_distance){
                min_distance = DP.back() - target;
                ans = DP.size();
                cout << "min_distance: " << min_distance << endl;
                    cout << "ans: " << ans << endl;
                    cout << endl;
            }if(target - DP[top_row_size - 2] < min_distance){
                min_distance = target - DP[top_row_size - 2];
                ans = DP.size() - 1;
                cout << "min_distance: " << min_distance << endl;
                    cout << "ans: " << ans << endl;
                    cout << endl;
            }
            break;
        }
        incr += 1;
    }
    
    incr = 2; // set incr back to 2
    
    int rows = top_row_size - 1; // want to keep checking until rectangle is only 2 columns wide
    for(int row = 2; row <= rows; ++row){
        vector<int> next_DP = {DP[0] + incr};
        int i = 1;
        while(true){
            int val = next_DP.back();
            val -= DP[i - 1];
            val += DP[i];
            val += row * (i + 1);
            next_DP.push_back(val);
            if(val > target){
                if(next_DP.back() - target < min_distance){
                    min_distance = next_DP.back() - target;
                    ans = row * next_DP.size();
                    cout << "min_distance: " << min_distance << endl;
                    cout << "ans: " << ans << endl;
                    cout << endl;
                }if(target - next_DP[next_DP.size() - 2] < min_distance){
                    min_distance = target - next_DP[next_DP.size() - 2];
                    ans = row * (next_DP.size() - 1);
                    cout << "min_distance: " << min_distance << endl;
                    cout << "ans: " << ans << endl;
                    cout << endl;
                }
                break;
            }
            i += 1;
        }
        DP = next_DP;
        incr += 1;
    }
    
    return ans;
}

// int formula_method(int target){
//     // formula is (m(m + 1) / 2) * (n(n + 1) / 2)
//     // for every m, calculate n
    
//     int ans = -1;
//     int min_distance = std::numeric_limits<int>::max();
//     int m = 1;
//     int temp = m * (m + 1) / 2;
//     double c = 1.0 * target * 2 / temp; // solve using quadratic formula
//     // n^2 + n - c = 0, solve for n, but at large values of target, should instead use fixed point numbers,
//     // by first calculating list of squares
// }

int main()
{
    
    // Also a combinatorial question, with number of paths between points
    // in Cartesian plane, number of total steps! / (x_steps!)(y_steps!),
    // number of paths could also be solved using dynamic programming
    // Likewise, this number of rectangles problem can also be solved using
    // combination, from width, can choose 2 x-bounds, from height, can choose 2 y-bounds
    // to form the subrectangle
    
    int target;
    cout << "Enter target area: "; // algorithm may not be entirely correct for small input sizes
    cin >> target;
    
    // Dynamic Programming approach, should be O(target)
    clock_t begin = clock();
    int ans1 = DP_method(target);
    clock_t finish = clock();
    double elapsed1 = 1.0 * (finish - begin) / CLOCKS_PER_SEC;
    
    // Formula approach, should be O(sqrt(target))
    // begin = clock();
    // int ans2 = formula_method(target);
    // finish = clock();
    // double elapsed2 = 1.0 * (finish - begin) / CLOCKS_PER_SEC;
    
    // if(ans1 == ans2){
    //     cout << "Methods return same ans." << endl;
    // }else{
    //     cout << "Check your algorithms." << endl;
    // }
    
    cout << "DP_method elapsed: " << elapsed1 << " seconds" << endl;
    cout << "ans1: " << ans1 << endl;
    // cout << "formula_method elapsed: " << elapsed2 << " seconds" << endl;
    
    return 0;
}