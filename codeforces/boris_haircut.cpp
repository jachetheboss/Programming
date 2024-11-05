
// Hello 2023 D.
// I think I can solve this with monotonic stack,
// also sorting by height and then solving is doable

#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <stack>

using namespace std;

int main()
{
    int cases = 0;
    cin >> cases;
    int n = 0;
    for(int cnt = 0; cnt < cases; ++cnt){
        cin >> n;
        vector<int> before (n, 0);
        int val = 0;
        for(int i = 0; i < n; ++i){
            cin >> val;
            before[i] = val;
        }
        vector<int> after (n, 0);
        for(int i = 0; i < n; ++i){
            cin >> val;
            after[i] = val;
        }
        int m = 0;
        cin >> m;
        unordered_map<int, int> clips; // the clips Boris has at his disposal
        unordered_map<int, int> needed;
        for(int i = 0; i < m; ++i){
            cin >> val;
            if(clips.count(val) == false){
                clips.insert({val, 1});
                needed.insert({val, 0});
            }else{
                clips[val] += 1;
            }
        }
        bool ok = true;
        vector<int> req; // required clip sizes
        for(int i = 0; i < before.size(); ++i){
            if(after[i] > before[i]){
                ok = false;
                break;
            }else if(after[i] < before[i]){
                req.push_back(after[i]);
            }
        }
        
        if(not ok){ // accelerator, BUT REMEMBER TO cin ALL INPUTS BEFORE THE EARLY BREAK/CONTINUE!
            cout << "NO" << '\n';
            continue;
        }
        
        for(int i = 0; i < req.size(); ++i){
            if(clips.count(req[i]) == false){
                ok = false;
                break;
            }
        }
       
        if(not ok){ // accelerator, BUT REMEMBER TO cin ALL INPUTS BEFORE THE EARLY BREAK/CONTINUE!
            cout << "NO" << '\n';
            continue;
        }
        
        stack<int> mono; // monotonic stack
        unordered_set<int> heights;
        for(int i = after.size() - 1; i >= 0; --i){
            while(mono.size() != 0){
                if(after[i] > mono.top()){
                    if(heights.count(mono.top()) == true){ // .erase(key) if key is not in the hashset, then
                                                          // return 0. Not sure if there is undefined behavior,
                                                         // so check if mono.top() is in heights before trying to
                                                        // erase key just to be safe!
                        heights.erase(mono.top());
                    }
                    // heights.erase(mono.top());
                    mono.pop();
                }else if(after[i] <= mono.top()){
                    break;
                }
            }
            if(heights.count(after[i]) == false){
                mono.push(after[i]);
                if(after[i] != before[i]){
                    needed[after[i]] += 1;
                    // ok = false;
                    if(needed[after[i]] > clips[after[i]]){
                        ok = false;
                        break;
                    }
                    heights.insert(after[i]);
                }
            }
            if(not ok){
                break;
            }
        }
        
        if(not ok){
            cout << "NO" << '\n';
            continue;
        }
        cout << "YES" << '\n';
        
        // unordered_map<int, int>::iterator it;
        // for(it = needed.begin(); it != needed.end(); ++it){
        //     if(it->second > clips[it->first]){ // my initial sample runs gave incorrect answers since
        //                                       // used less than < instead of the correct greater than > !!!!!!!
        //                                      // BE VERY CAREFUL WITH SIGNS! DIFFICULT TO FIND TINY BUGS!
        //                                     // BE METICULOUS AND DO EXACTLY WHAT YOU INTEND ON DOING !!!!!!!
        //                                   // logic is if need MORE clips of that size than there are available,
        //                                   // then not ok. Use tourist's ok boolean variable,
        //                                  // VERY CLEAR AND HELPFUL !!!!!!!
        //         ok = false;
        //         break;
        //     }
        // }
        // if(ok){
        //     cout << "YES" << '\n';
        // }else{
        //     cout << "NO" << '\n';
        // }
    }

    return 0;
}
