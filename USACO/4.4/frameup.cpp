/*
ID: jamessh3
LANG: C++20
TASK: frameup
*/

#include <bits/stdc++.h>
using namespace std;

void reverse(string& s){
    int bound = s.length() / 2;
    for(int i = 0; i < bound; ++i){
        char c = s[i];
        s[i] = s[(int)s.length() - 1 - i];
        s[(int)s.length() - 1 - i] = c;
    }
}

// void DFS(vector<char>& stk, vector<int>& searched, vector<vector<char>>& next, vector<string>& ans, int len){
	
// // 	cout << "stk.size() " << stk.size() << endl;
	
// 	if(stk.size() == 0) return;
// 	if(stk.size() == len){
// 		string s = "";
// 		for(char c : stk) s += c;
// 		ans.push_back(s);
// 	}
// 	char letter = stk.back();
// 	bool deadend = true;
// 	for(char nletter : next[letter]){
// 		if(searched[nletter] == false){
// 			stk.push_back(nletter);
// 			searched[nletter] = 1;
// 			DFS(stk, searched, next, ans, len);
// 		}
// 	}
// 	if(deadend){
// 		searched[letter] = 0;
// 		stk.pop_back();
// 	}
// }

bool usable(vector<int>& frame, vector<string>& wall, vector<vector<int>>& searched){
    char letter = frame[0];
    for(int idx = 1; idx < frame.size(); idx += 2){
        int i = frame[idx];
        int j = frame[idx + 1];
        if(wall[i][j] != letter and searched[i][j] != 1) return false;
    }
    return true;
}

void DFS(vector<string>& wall, vector<vector<int>>& frames, string& stk, vector<vector<int>>& searched, vector<int>& used, vector<string>& ans){
    
    // may utilize layers or above/under as pruning in case TLE
    
    // cout << "stk.size() " << stk.size() << endl;
    
    // if(stk.size() == 0) return;
    if(stk.size() == frames.size()) ans.push_back(stk);
    // bool deadend = true;
    for(vector<int>& frame : frames){
        char letter = frame[0];
        if(used[letter] == 1) continue;
        
        // check if it is able to be used based on current searched state
        if(usable(frame, wall, searched)){
            used[letter] = 1;
            stk += letter;
            vector<int> newly_searched_ind;
            for(int idx = 1; idx < frame.size(); idx += 2){
                int i = frame[idx];
                int j = frame[idx + 1];
                if(searched[i][j] == 0){
                    searched[i][j] = 1;
                    newly_searched_ind.push_back(i);
                    newly_searched_ind.push_back(j);
                }
            }
            DFS(wall, frames, stk, searched, used, ans);
            
            // un-update
            stk.pop_back();
            used[letter] = 0;
            for(int idx = 0; idx < newly_searched_ind.size(); idx += 2){
                int i = newly_searched_ind[idx];
                int j = newly_searched_ind[idx + 1];
                searched[i][j] = 0;
            }
        }
    }
    
    // if(deadend){
    //     // update searched, used, pop from stk
    // }
}

void helper(string& perm, vector<char>& bank, vector<string>& perms){
    if(bank.size() == 0){
        perms.push_back(perm);
    }else{
        for(int i = 0; i < bank.size(); ++i){
            string next_perm = perm;
            next_perm += bank[i];
            vector<char> next_bank = bank;
            next_bank.erase(next_bank.begin() + i);
            helper(next_perm, next_bank, perms);
        }
    }
}

vector<string> getPermutations(vector<char>& layer){
    vector<char> bank = layer;
    string perm;
    vector<string> perms;
    helper(perm, bank, perms);
    return perms;
}

// void helper(vector<int>& perm, vector<int>& bank, vector<vector<int>>& perms){
//     if(bank.size() == 0){
//         perms.push_back(perm);
//     }else{
//         for(int i = 0; i < bank.size(); ++i){
//             vector<int> next_perm = perm;
//             next_perm.push_back(bank[i]);
//             vector<int> next_bank = bank;
//             next_bank.erase(next_bank.begin() + i);
//             helper(next_perm, next_bank, perms);
//         }
//     }
// }

// vector<vector<int>> getPermutations(vector<int>& layer){
//     vector<int> bank = layer;
//     vector<int> perm;
//     vector<vector<int>> perms;
//     helper(perm, bank, perms);
//     return perms;
// }

void incrementBuilder(vector<int>& builder, vector<int>& capacity){
// 	for(int i = (int)builder.size() - 1; i >= 0; --i){
// 		builder[i]++;
// 		if(builder[i] == capacity[i]){
// 			builder[i] = 0;
// 		}else{
// 			return;
// 		}
// 	}
    for(int i = 0; i < builder.size(); ++i){
		builder[i]++;
		if(builder[i] == capacity[i]){
			builder[i] = 0;
		}else{
			return;
		}
	}
}

int main()
{
	ifstream fin ("frameup.in");
	ofstream fout ("frameup.out");
	
	int H, W; fin >> H >> W;
	vector<string> wall;
	for(int i = 0; i < H; ++i){
		string line; fin >> line;
		wall.push_back(line);
	}
	// find the topleft cell and dimensions of each frame!
	// question constraints imply that there are up to 26 possible picture bounds,
	// not just 5 as in the picture. If it was just 5, then we could do a brute
	// force all permutations search.
	vector<vector<int>> bounds (91, vector<int> (4, -1)); // {N, E, S, W}
	for(int i = 0; i < wall.size(); ++i){
		for(int j = 0; j < wall[0].size(); ++j){
			char c = wall[i][j];
			
			if(c == '.') continue;
			
			if(bounds[c][0] == -1) bounds[c][0] = i;
			else bounds[c][0] = min(bounds[c][0], i);
			bounds[c][1] = max(bounds[c][1], j);
			bounds[c][2] = max(bounds[c][2], i);
			if(bounds[c][3] == -1) bounds[c][3] = j;
			else bounds[c][3] = min(bounds[c][3], j);
		}
	}
	vector<vector<int>> frames; // {LETTER, i, j, i, j, i, .......}
	for(int idx = 0; idx < bounds.size(); ++idx){
		vector<int>& v = bounds[idx];
		vector<int> uninit = {-1, -1, -1, -1};
		if(v == uninit) continue;
		vector<int> coors;
		int ti = v[0]; // top i, right j, bottom i, left j
		int rj = v[1];
		int bi = v[2];
		int lj = v[3]; 
		
		coors.push_back(idx); // the upper case letter!
		
		for(int j = lj; j <= rj; ++j){
			coors.push_back(ti);
			coors.push_back(j);
			coors.push_back(bi);
			coors.push_back(j);
		}for(int i = ti + 1; i < bi; ++i){
			coors.push_back(i);
			coors.push_back(lj);
			coors.push_back(i);
			coors.push_back(rj);
		}
		frames.push_back(coors);
	}
	// frames contains the coordinates of every cell of each frame!
	
	cout << "frames.size() " << frames.size() << endl;
	
/*
	vector<int> ind;
	for(int i = 0; i < frames.size(); ++i) ind.push_back(i);
	
	vector<vector<int>> orders = getPermutations(ind);
	vector<string> ans;
	for(vector<int>& order : orders){
	    vector<string> newwall (H, string(W, '.'));
	    string s = "";
	    for(int idx : order){
	        char letter = frames[idx][0];
	        s += letter;
	        for(int a = 1; a < frames[idx].size(); a += 2){
	            int i = frames[idx][a];
	            int j = frames[idx][a + 1];
	            newwall[i][j] = letter;
	        }
	    }
	    if(newwall == wall){
	        ans.push_back(s);
	    }
	}
	sort(ans.begin(), ans.end());
	for(string& s : ans) fout << s << endl;
*/	

///*
	int rem = frames.size();
	vector<vector<int>> searched (H, vector<int> (W, 0));
	vector<vector<char>> layers;
	vector<int> frame_searched (frames.size(), 0);
	while(rem > 0){
		vector<char> layer;
		vector<int> mark_as_searched; // mark as searched after all frames 
			// in current layer iteration are all checked for!
		for(int a = 0; a < frames.size(); ++a){
		    
		    if(frame_searched[a] == 1) continue;
		    
		    vector<int> coors = frames[a];
		    
			bool is_next_layer = true;
			char letter = coors[0];
			for(int idx = 1; idx < coors.size(); idx += 2){
				int i = coors[idx];
				int j = coors[idx + 1];
				if(wall[i][j] != letter and searched[i][j] == 0){
					is_next_layer = false;
					break;
				}
			}
			if(is_next_layer){
				layer.push_back(letter);
				for(int idx = 1; idx < coors.size(); idx += 2){
					int i = coors[idx];
					int j = coors[idx + 1];
					mark_as_searched.push_back(i);
					mark_as_searched.push_back(j);
				}
				frame_searched[a] = 1;
				rem--;
			}
		}
		layers.push_back(layer);
		for(int idx = 0; idx < mark_as_searched.size(); idx += 2){
			int i = mark_as_searched[idx];
			int j = mark_as_searched[idx + 1];
			searched[i][j] = 1;
		}
	}
	
	// layers is from top to bottom
	vector<int> belong_layer (91, -1);
	for(int layer = 0; layer < layers.size(); ++layer){
	    for(char letter : layers[layer]) belong_layer[letter] = layer;
	}
	
	
	cout << "check1" << endl;
/*	
	vector<vector<string>> layer_combos;
	for(vector<char>& layer : layers){
	    sort(layer.begin(), layer.end());
	    vector<string> perms = getPermutations(layer);
	    // permutations in alphabetical order
	    layer_combos.push_back(perms);
	}
	
	cout << "layer_combos" << endl;
	for(vector<string>& combos : layer_combos){
	    for(string& combo : combos) cout << combo << ' ';
	    cout << endl;
	}
	
	int ways = 1;
	vector<int> capacity;
	for(vector<string>& combos : layer_combos){
		
		ways *= combos.size();
		capacity.push_back(combos.size());
	}
	vector<int> builder (layers.size(), 0);
	
	//vector<string> ans;
	for(int way = 0; way < ways; ++way){
		string ans = "";
		for(int i = (int)builder.size() - 1; i >= 0; --i){
			ans += layer_combos[i][builder[i]];
		}
		
		fout << ans << endl;
		
		incrementBuilder(builder, capacity);
	}
	
	cout << "layers.size() " << layers.size() << endl;
//	*/


	// find the relation between each pair of distinct frames,
	// check if they overlap. Can base it on the layers as well
	
	// utilize backtracking
	
// 	vector<vector<char>> next (91); // which letters can be above curr letter?
// 	for(int i = 0; i < layers.size(); ++i){
// 	    for(int j = i + 1; j < layers.size(); ++j){
	        
// 	    }
// 	}
	/*
	for(int i = 0; i < frames.size(); ++i){
	    char letter1 = frames[i][0];
	    for(int j = i + 1; j < frames.size(); ++j){
	        char letter2 = frames[j][0];
	        vector<vector<int>> count (H, vector<int> (W, 0));
	        for(int idx = 1; idx < frames[i].size(); idx += 2){
	            int a = frames[i][idx];
	            int b = frames[i][idx + 1];
	            count[a][b]++;
	        }
	        for(int idx = 1; idx < frames[j].size(); idx += 2){
	            int a = frames[j][idx];
	            int b = frames[j][idx + 1];
	            count[a][b]++;
	        }
	        bool overlap = false;
	        for(int a = 0; a < count.size(); ++a){
	            for(int b = 0; b < count[a].size(); ++b){
	                if(count[a][b] == 2){
	                    overlap = true;
	                    break;
	                }
	            }
	            if(overlap) break;
	        }
	        if(not overlap){
	            if(belong_layer[letter1] > belong_layer[letter2])
	                next[letter1].push_back(letter2);
	            else if(belong_layer[letter1] < belong_layer[letter2])
				    next[letter2].push_back(letter1);
	            else{
    	            next[letter1].push_back(letter2);
    	            next[letter2].push_back(letter1);
	            }
	           // next[letter1].push_back(letter2);
    	       // next[letter2].push_back(letter1);
	        }else{
	            int letter1_count = 0;
	            int letter2_count = 0;
	            for(int a = 0; a < count.size(); ++a){
    	            for(int b = 0; b < count[a].size(); ++b){
    	                if(count[a][b] == 2){
    	                    if(wall[a][b] == letter1) letter1_count++;
    	                    else if(wall[a][b] == letter2) letter2_count++;
    	                }
    	            }
    	        }
    	        if(letter1_count == 0 and letter2_count == 0){ // cannot tell which covers which
    	        
    	            // for this case, their order matters!
    	            // use what layer they belong to as the tiebreak.
    	   //         if(belong_layer[letter1] > belong_layer[letter2])
    	   //             next[letter1].push_back(letter2);
    	   //         else
					   // next[letter2].push_back(letter1);
					    
					next[letter1].push_back(letter2);    
					next[letter2].push_back(letter1);
					
    	        }else if(letter1_count == 0){ // letter1 was covered
    	            next[letter1].push_back(letter2);
    	        }else if(letter2_count == 0){ // letter2 was covered
    	            next[letter2].push_back(letter1);
    	        }
	        }
	    }
	}
	*/
	
// 	cout << "next:" << endl;
// 	for(int i = 0; i < next.size(); ++i){
// 	    if(next[i].size() > 0){
// 	        cout << "i: " << i << " adj:{";
// 	        for(int adj : next[i]) cout << adj << ' ';
// 	        cout << "}" << endl;
// 	    }
// 	}
	
// 	//for(int i = 0; i < layers.size(); ++i){	
// 	//}
	
// 	vector<string> ans;
// 	for(vector<int>& frame : frames){
// 		char start_letter = frame[0];
// 		vector<int> searched (91, 0);
// 		searched[start_letter] = 1;
// 		vector<char> stk = {start_letter};
// 		DFS(stk, searched, next, ans, frames.size());
// 	}

    vector<string> ans;
    // vector<vector<int>> searched (H, vector<int> (W, 0));
    searched = vector<vector<int>> (H, vector<int> (W, 0));
    string stk = "";
    vector<int> used (91, 0);
    DFS(wall, frames, stk, searched, used, ans);

    // reverse all of ans, from top-to-bottom to bottom-to-top
    for(string& s : ans){
        reverse(s);
    }

	sort(ans.begin(), ans.end());
	
	cout << "ans.size() " << ans.size() << endl;
	
	for(string& line : ans){
		cout << line << endl;
		fout << line << endl;
	}
	
	
	fin.close();
	fout.close();
	
	return 0;
}