
// REMEMBER TO USE FIXED POINT, EXACT INTEGRAL VALUES WHENEVER POSSIBLE,
// AS EVEN LONG DOUBLE FLOATING POINT REPRESENTATION LOSES PRECISION!

// This Project Euler almost equilateral triangles and Kattis Olympus Mans
// questions are great examples. Start to lose precision with large number test cases


#pragma GCC("optimize")
#pragma target("avx,avx2,ofast")

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <ctime>
#include <numeric>

using namespace std;

void increment_digits(vector<int>& digits){
    int last_i = digits.size() - 1;
    for(int i = last_i; i >= 0; --i){
        if(digits[i] == 9 - (last_i - i)){
            continue;
        }else{
            digits[i] += 1;
            for(int j = i + 1; j <= last_i; ++j){
                digits[j] = digits[j - 1] + 1;
            }
            break;
        }
    }
    return;
}

void increment_perm_builder(vector<int>& perm_builder, vector<int>& perm_builder_incrementer, int i){
    
    // 000
    // 110
    // 200
    // 310
    // 400
    // 510
    // 000
    // 121213 121213 121213 121214 this sort of hierarchical self vector copy-and-pasting
    // is similar to the leetcode list binary representation of strings.
    // copy, add 1 to all, copy everything again, etc. etc. iterative process gone wild
    
    int index = perm_builder.size() - 1 - perm_builder_incrementer[i];
    if(index == -1){
        return;
    }
    perm_builder[index] += 1;
    for(int j = index + 1; j < perm_builder.size(); ++j){
        perm_builder[j] = 0;
    }
}

vector<int> calc(vector<int> a, vector<int> b, int op){
    vector<int> output; // numer, denom fraction
    int numer;
    int denom;
    if(op == 0 or op == 1){
        int LCM = lcm(a[1], b[1]); // lcm?
        if(op == 0) // add
            numer = a[0] * (LCM / a[1]) + b[0] * (LCM / b[1]);
        else       // subtract
            numer = a[0] * (LCM / a[1]) - b[0] * (LCM / b[1]);
            
        int GCD = gcd(LCM, numer);
        numer /= GCD;
        denom = LCM / GCD;

    }else if(op == 2){ // mult
        numer = a[0] * b[0];
        denom = a[1] * b[1];
        int GCD = gcd(numer, denom);
        numer /= GCD;
        denom /= GCD;

    }else if(op == 3){ // divide
        if(b[0] == 0){
            return {-1, -1}; // indicate invalid
        }
        numer = a[0] * b[1];
        denom = a[1] * b[0];
        int GCD = gcd(numer, denom);
        numer /= GCD;
        denom /= GCD;
    }
    if(numer > 0 and denom < 0){ // only numer should be negative
        numer = 0 - numer;
        denom = 0 - denom;
    }else if(numer < 0 and denom < 0){ // neg / neg is pos
        numer = 0 - numer;
        denom = 0 - denom;
    }
    output.push_back(numer);
    output.push_back(denom);
    
    // cout << '{' << a[0] << ',' << a[1] << "} {" << b[0] << ',' << b[1] << "} " << op << " = " << '{' << numer << ',' << denom << '}' << endl;
    
    return output;
}

void evaluate_expression(vector<int>& expression, vector<int>& operators, unordered_set<int>& unique_values){
    
    vector<int> one = {expression[0], 1}; // fraction form
    vector<int> two = {expression[1], 1};
    vector<int> three = {expression[2], 1};
    vector<int> four = {expression[3], 1};
    
    // must be positive integer values
    
    vector<int> left = calc(one, two, operators[0]);
    vector<int> middle = calc(two, three, operators[1]);
    vector<int> right = calc(three, four, operators[2]);
    
    vector<int> ans;
    vector<int> temp;
    // (--) (--)c
    if(left[1] != -1 && right[1] != -1){
        ans = calc(left, right, operators[1]);
        if(ans[0] > 0 and ans[1] > 0 and ans[0] % ans[1] == 0){
            unique_values.insert(ans[0] / ans[1]);
        }
    }
    
    // ((--)-)-
    if(left[1] != -1){
        temp = calc(left, three, operators[1]);
        if(temp[1] != -1){
            ans = calc(temp, four, operators[2]);
            if(ans[0] > 0 and ans[1] > 0 and ans[0] % ans[1] == 0){
                unique_values.insert(ans[0] / ans[1]);
            }
        }
    }
    
    // (-(--))-
    if(middle[1] != -1){
        temp = calc(one, middle, operators[0]);
        if(temp[1] != -1){
            ans = calc(temp, four, operators[2]);
            if(ans[0] > 0 and ans[1] > 0 and ans[0] % ans[1] == 0){
                unique_values.insert(ans[0] / ans[1]);
            }
        }
    }
    
    // -((--)-)
    if(middle[1] != -1){
        temp = calc(middle, four, operators[2]);
        if(temp[1] != -1){
            ans = calc(one, temp, operators[0]);
            if(ans[0] > 0 and ans[1] > 0 and ans[0] % ans[1] == 0){
                unique_values.insert(ans[0] / ans[1]);
            }
        }
    }
    
    // -(-(--))
    if(right[1] != -1){
        temp = calc(two, right, operators[1]);
        if(right[1] != -1){
            ans = calc(one, temp, operators[0]);
            if(ans[0] > 0 and ans[1] > 0 and ans[0] % ans[1] == 0){
                unique_values.insert(ans[0] / ans[1]);
            }
        }
    }
    
    return;
}

int main()
{
    // 0000
    // 0010
    // 0100
    // 0110
    // 0200
    // 0210
    // 1000
    
    clock_t begin = clock();

    vector<int> perm_builder_incrementer = {1, 2};
    int count = 2;
    while(count < 4){
        int times = perm_builder_incrementer.back();
        int size = perm_builder_incrementer.size();
        for(int k = 0; k < times; ++k){
            for(int i = 0; i < size; ++i){
                perm_builder_incrementer.push_back(perm_builder_incrementer[i]);
            }
        }
        size = perm_builder_incrementer.size();
        perm_builder_incrementer[size - 1] += 1;
        count += 1;
    }
    for(int i = 0; i < perm_builder_incrementer.size(); ++i){
        cout << perm_builder_incrementer[i] << ' ';
    }
    cout << endl;
    
    
    
    
    string ans = "";
    int longest_streak = 0;
    
    // are unary subtraction signs allowed?
    vector<int> digits = {0, 1, 2, 3}; // use backtracking + counting method
    int total_combos = 10 * 9 * 8 * 7 / 24;
    for(int cnt1 = 0; cnt1 < total_combos; ++cnt1){
        
        vector<int> temp_digits = digits; // deep copy
        
        vector<int> perm_builder = {0, 0, 0, 0};
        
        unordered_set<int> unique_values; // expression evaluation
        
        for(int i = 0; i < perm_builder_incrementer.size(); ++i){
            
            vector<int> expression;
            for(int j = 0; j < perm_builder.size(); ++j){
                expression.push_back(temp_digits[perm_builder[j]]);
                temp_digits.erase(temp_digits.begin() + perm_builder[j]);
            }
            // for(int j = 0; j < expression.size(); ++j){
            //     cout << expression[j] << ' ';
            // }
            // cout << endl;
            
            // for(int j = 0; j < perm_builder.size(); ++j){
            //     cout << perm_builder[j] << ' ';
            // }
            // cout << endl;
            
            
            // consider parenthesis grouping and operators
            vector<int> operators (3, 0);
            for(int opcombo = 0; opcombo < 64; ++opcombo){ // 0 add, 1 subtract, 2 multiply, 3 divide
                
                // test all groupings
                evaluate_expression(expression, operators, unique_values);
                
                for(int j = operators.size() - 1; j >= 0; --j){
                    if(operators[j] == 3){
                        operators[j] = 0;
                    }else{
                        operators[j] += 1;
                        break;
                    }
                }
                // cout << "opcombo: " << opcombo << endl;
            }

            temp_digits = digits;
            
            increment_perm_builder(perm_builder, perm_builder_incrementer, i);
        }
        unordered_set<int>::iterator it;
        vector<int> values;
        for(it = unique_values.begin(); it != unique_values.end(); ++it){
            values.push_back(*it);
        }
        sort(values.begin(), values.end());
        
        // cout << "values:" << endl;
        // for(int i = 0; i < values.size(); ++i){
        //     cout << values[i] << ' ';
        // }
        // cout << endl;
        
        // find longest consecutive streak of val
        int streak = 1;
        int prev = values[0];
        
        bool changed = false;
        
        for(int i = 1; i < values.size(); ++i){
            if(values[i] == prev + 1){
                streak += 1;
                prev = values[i];
            }else{
                if(streak > longest_streak){
                    
                    changed = true;
                    
                    longest_streak = streak;
                    ans = to_string(digits[0]) + to_string(digits[1]) + to_string(digits[2]) + to_string(digits[3]);
                    cout << "ans: " << ans << endl;
                }
                prev = values[i];
                streak = 1;
            }
        }
        if(streak > longest_streak){
            
            changed = true;
            
            longest_streak = streak;
            ans = to_string(digits[0]) + to_string(digits[1]) + to_string(digits[2]) + to_string(digits[3]);
            cout << "ans: " << ans << endl;
        }
        if(changed){
            for(int i = 0; i < values.size(); ++i){
                cout << values[i] << ' ';
            }
            cout << endl << endl;
        }
        
        
        increment_digits(digits);
    }
    
    clock_t finish = clock();
    
    cout << 1.0 * (finish - begin) / CLOCKS_PER_SEC << " seconds";
    

    return 0;
}
