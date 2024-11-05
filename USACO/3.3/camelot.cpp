/*
ID: jamessh3
LANG: C++20
TASK: camelot
*/

#include <bits/stdc++.h>
using namespace std;

int getIdx(int si, int sj, int di, int dj, int R, int C){
    return si * C*R*C + sj * R*C + di * C + dj;
}

// vector<vector<vector<vector<int>>>> generatePrecompute(vector<vector<int>>& board){
vector<int> generatePrecompute(vector<vector<int>>& board){
	int R = board.size();
	int C = board[0].size();
	// precompute of -1 means impossible to reach that location
// 	vector<vector<vector<vector<int>>>> precompute (R, vector<vector<vector<int>>> (C, vector<vector<int>> (R, vector<int> (C, -1))));
	int sz = R * R * C * C;
	vector<int> precompute (sz, -1);
	vector<vector<int>> knight_moves = {{-2, -1}, {-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}};
	for(int si = 0; si < R; ++si){
		for(int sj = 0; sj < C; ++sj){
			// knight starts at [si][sj];
			vector<vector<int>> searched (R, vector<int> (C, 0));
			searched[si][sj] = 1;
// 			precompute[si][sj][si][sj] = 0; // 0 moves for starting cell
            int idx = getIdx(si, sj, si, sj, R, C);
            precompute[idx] = 0;
			vector<int> bfs {si, sj};
			int num_moves = 1;
			while(bfs.size() > 0){
				vector<int> next_bfs;
				for(int ind = 0; ind < bfs.size(); ind += 2){
					int i = bfs[ind];
					int j = bfs[ind + 1];
					for(vector<int>& move : knight_moves){
						int a = i + move[0];
						int b = j + move[1];
						if(a < 0 or a >= R or b < 0 or b >= C) continue;
						if(searched[a][b] == 1) continue;
						searched[a][b] = 1;
						//precompute[si][sj][a][b] = num_moves;
						idx = getIdx(si, sj, a, b, R, C);
						precompute[idx] = num_moves;
						next_bfs.push_back(a);
						next_bfs.push_back(b);
					}
				}
				bfs = next_bfs;
				num_moves++;
			}
		}
	}
	return precompute;
}

int kingDis(int si, int sj, int di, int dj){ // start i, j destination i, j 
	return max(abs(si - di), abs(sj - dj));
}
// int knightDis(int si, int sj, int di, int dj, vector<vector<vector<vector<int>>>>& precompute){
// 	return precompute[si][sj][di][dj];
// }
int knightDis(int si, int sj, int di, int dj, int R, int C, vector<int>& precompute){
    int idx = getIdx(si, sj, di, dj, R, C);
	return precompute[idx];
}


#include <bits/stdc++.h>
using namespace std;

int main()
{
    time_t curr = clock();
    
	ifstream fin ("camelot.in");
	ofstream fout ("camelot.out");
	
	int R, C; fin >> R >> C; // rows, cols
	
	vector<int> king;
	char col; int row; fin >> col >> row;
// 	cout << "king: col " << col << " row " << row << endl;
	king = {R - row, col - 'A'};
	int inp;
	bool col_mode = true;
	vector<vector<int>> knights;
	vector<int> knight;
	
// 	cout << "hello " << endl;
	
	while(true){
	    
	    if(col_mode){
	        if(!(fin >> col)) break;;
	        col -= 'A';
	        knight.push_back(col);
	    }else{
	        if(!(fin >> row)) break;;
	        row = R - row;
	        knight.insert(knight.begin(), row);
	        knights.push_back(knight);
	        knight.clear();
	    }
	    col_mode = not col_mode;
	}
	
// 	cout << "world" << endl;
	
// 	cout << "knights.size() " << knights.size() << endl;
	
// 	for(vector<int>& knight : knights){
// 	    cout << "{" << knight[0] << ',' << knight[1] << "} ";
// 	}
// 	cout << endl;
	
	
	
	vector<vector<int>> board (R, vector<int> (C, 0));
// 	vector<vector<vector<vector<int>>>> precompute = generatePrecompute(board);
	vector<int> precompute = generatePrecompute(board);
// 	cout << "precompute generation elapsed secs: " << 1.0 * (clock() - curr) / CLOCKS_PER_SEC << endl;
	
	// try every destination cell
	// for every destination cell, try every possible king + knight mount combo,
	// or just lone king walking to destination himself
	// utilize pruning
	int best = INT_MAX;
	for(int di = 0; di < R; ++di){
		for(int dj = 0; dj < C; ++dj){
			// try lone king
			bool ok = true; // possible for all knights to maneuver to that square
			int moves = kingDis(king[0], king[1], di, dj);
			int total_knight_dis = 0;
			for(vector<int>& knight : knights){
				// int ret = knightDis(knight[0], knight[1], di, dj, precompute);
				int ret = knightDis(knight[0], knight[1], di, dj, R, C, precompute);
				if(ret == -1){
					ok = false;
					break;
				}
				moves += ret;
				total_knight_dis += ret;
			}
			if(ok) best = min(best, moves);
			
			if(total_knight_dis > best) continue; // pruning condition, impossible to find
			// a better solution at this destination cell since king is not even put into consideration
			// yet, king can only add moves (either by walking himself, or forcing a knight 
			// to make a detour)
			
			// try all knight/king mounts
			for(int k = 0; k < knights.size(); ++k){
				// choose knight k as the mount for the king
				// choose a "pitstop" cell
				// for knight + king to both meet at
				// knight might have to detour, but overall conserves moves!
				
				// int other_knight_dis = total_knight_dis - knightDis(knights[k][0], knights[k][1], di, dj, precompute);
				int other_knight_dis = total_knight_dis - knightDis(knights[k][0], knights[k][1], di, dj, R, C, precompute);				
				moves = 0;
				ok = true;
				int best_pitstop = INT_MAX;
				vector<int> pitstop_loc;
				for(int pi = 0; pi < R; ++pi){ // pitstop i, j
					for(int pj = 0; pj < C; ++pj){
						bool pitstop_ok = true;
						int pitstop = 0; // pitstop moves
				// 		int ret = knightDis(knights[k][0], knights[k][1], pi, pj, precompute);
				        int ret = knightDis(knights[k][0], knights[k][1], pi, pj, R, C, precompute);
						if(ret == -1){
							pitstop_ok = false;
							break;
						}
						pitstop += ret;
						pitstop += kingDis(king[0], king[1], pi, pj);
				// 		ret = knightDis(pi, pj, di, dj, precompute);
				        ret = knightDis(pi, pj, di, dj, R, C, precompute);
						if(ret == -1){
							pitstop_ok = false;
							break;
						}
						pitstop += ret;
						// 		best_pitstop = min(best_pitstop, pitstop);
						if(pitstop < best_pitstop){
						    best_pitstop = pitstop;
						    pitstop_loc = {pi, pj};
						}
					}
				}
				if(best_pitstop == INT_MAX) ok = false;
				
				// have to improve time complexity of this stuff! wayyyyy too slow
				// if find way to prune the search (guaranteed that no better pit stop exists for
				// that knight, then continue)
				// if still too slow, then replace 4D vector with 1D vector, should improve runtime
				// by a significant constant
				/*
				for(int h = 0; h < knights.size(); ++h){ // other knights
					if(h == k) continue;
					int ret = knightDis(knights[h][0], knights[h][1], di, dj, precompute);
					if(ret == -1){
						ok = false;
						break;
					}
					moves += ret;
				}
				*/
				moves += other_knight_dis;
				moves += best_pitstop;
				if(ok) best = min(best, moves);
				
				// if(pitstop_loc[0] == 4 and pitstop_loc[1] == 3){
				//     int pi = pitstop_loc[0];
				//     int pj = pitstop_loc[1];
				//     cout << "HELLO WORLD!" << endl;
				//     cout << "moves " << moves << endl;
				//     cout << "kingDis " << kingDis(king[0], king[1], pi, pj) << endl;
				// }
				
				// if(di == 3 and dj == 1){
				//     cout << "di: " << di << " dj: " << dj << endl;
				//     cout << "k: " << k << endl;
    //                 cout << "pitstop: " << "{" << pitstop_loc[0] << ',' << pitstop_loc[1] << "}" << endl;
				//     cout << "moves: " << moves << endl;
				//     cout << "king: " << "{" << king[0] << ',' << king[1] << "}" << endl;
				//     cout << endl;
				// }
			}
		}
	}
	
	fout << best << endl;	
	
	fin.close();
	fout.close();
	
	cout << "elapsed secs: " << 1.0 * (clock() - curr) / CLOCKS_PER_SEC << endl;
	
// 	vector<int> freq (100, 0);
// 	for(int x : precompute) freq[x]++;
// 	cout << "precompute freq" << endl;
// 	for(int i = 0; i < freq.size(); ++i){
// 	    cout << "i: " << i << " " << freq[i] << endl;
// 	}
// 	int mx = -1;
// 	for(int x : precompute) mx = max(mx, x);
// 	cout << "max: " << mx << endl;

	return 0;
}