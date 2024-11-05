/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

void add_vector(vector<int>& N, vector<int>& D){ // pass by reference
    // numbers in reverse order (lowest index is least significant digit)
    // since a carry at the end would mean insertion of a new 1 digit,
    // .push_back(1) is faster than .insert(vec.begin(), 1);
    
    // int max_size = max(N.size(), D.size());
    // int N_size = N.size();
    // int D_size = D.size();
    // for(int i = 0; i < max_size - N_size; ++i){
    //     N.push_back(0);
    // }for(int i = 0; i < max_size - D_size; ++i){
    //     D.push_back(0);
    // }
    
    while(N.size() < D.size()){ // superfluous, since numerator should
                               // always be larger than the denominator, at least
                              // Denominator's number of digits
        N.push_back(0); // add leading zero to hold place value for adding
    }while(D.size() < N.size()){
        D.push_back(0);
    }
    int carry = 0;
    for(int i = 0; i < N.size(); ++i){
        N[i] = N[i] + D[i] + carry;
        if(N[i] >= 10){
            carry = 1;
            N[i] -= 10;
        }else{
            carry = 0;
        }
    }
    if(carry == 1){
        N.push_back(1);
    }
    return; // void return
}

void subtract_vector(vector<int> N, vector<int>& D){ // D pass by reference, but N pass by value,
                                                    // so N is a copy, will not modify N in larger function
                                                   // scope
    while(N.size() < D.size()){ // superfluous, N >= D always, so at least the number of digits
        N.push_back(0); // add leading zero to hold place value for adding
    }while(D.size() < N.size()){
        D.push_back(0);
    }
    for(int i = 0; i < N.size(); ++i){
        if(N[i] >= D[i]){
            D[i] = N[i] - D[i];
        }else{
            D[i] = 10 + N[i] - D[i];
            int j = i + 1;
            while(N[j] == 0){
                N[j] = 9;
                j += 1;
            }
            N[j] -= 1;
        }
    }
}

int main()
{
    // use vector arithmetic for large number
    vector<int> N = {1};
    vector<int> D = {1}; // Numerator and Denominator
    int output = 0;
    for(int cnt = 0; cnt < 1000; ++cnt){
        add_vector(N, D); // should pass both by reference
        add_vector(N, D);
        subtract_vector(N, D); // should only pass D by reference
        // to see size of numerator and denominator, take out all leading zeros.
        // N does not have leading zeros, but D might.
        int N_size = N.size();
        int D_size = D.size();
        int lead_zeros = 0;
        for(int i = D.size() - 1; i >= 0; --i){
            if(D[i] == 0){
                lead_zeros += 1;
            }else{
                break;
            }
        }
        if(cnt < 10){
            cout << 'N' << '\n';
            for(int i = 0; i < N.size(); ++i){
                cout << N[i];
            } cout << '\n';
            cout << 'D' << '\n';
            for(int i = 0; i < D.size(); ++i){
                cout << D[i];
            } cout << "\n\n";
        }
        D_size -= lead_zeros;
        if(N_size > D_size){
            output += 1;
        }
    }
    cout << "output: " << output << '\n';
    

    return 0;
}
