
// REMEMBER TO USE FIXED POINT, EXACT INTEGRAL VALUES WHENEVER POSSIBLE,
// AS EVEN LONG DOUBLE FLOATING POINT REPRESENTATION LOSES PRECISION!

// This Project Euler almost equilateral triangles and Kattis Olympus Mans
// questions are great examples. Start to lose precision with large number test cases


#pragma GCC("optimize")
#pragma target("avx,avx2,ofast")

#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int main()
{
    // unique side length MUST BE EVEN
    long long output = 0;
    for(int b = 3; b <= 170000000; ++b){
        int base = b + b;
        int c = base + 1; // c^2 - b^2 = (c - b)(c + b), which must be a perfect square since
                            // triangle altitude must be integer as well!
        long long val = c - b;
        val *= (c + b);
        
        long double height = static_cast<int>(sqrt(val));
        long long square = height;
        square *= height;
        
        if(square == val){
            int perimeter = base + c + c;
            if(perimeter <= 1000000000){
                cout << base << ' ' << c << ' ' << c << ' ' << "perimeter: " << perimeter << endl;
                cout << "height: " << height << endl << endl;
                output += perimeter;
            }
        }
        
        c = base - 1;
        val = c - b;
        val *= (c + b);
        
        height = static_cast<int>(sqrt(val));
        square = height;
        square *= height;
        
        if(square == val){
            int perimeter = base + c + c;
            if(perimeter <= 1000000000){
                cout << base << ' ' << c << ' ' << c << ' ' << "perimeter: " << perimeter << endl;
                cout << "height: " << height << endl << endl;
                output += perimeter;
            }
        }
    }
    cout << "output: " << output << endl;

    return 0;
}
