/*
ID: jamessh3
LANG: C++20
TASK: maze1
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

// JUST REALIZED THAT CIN, FIN DO NOT READ IN IMPLICIT ENTERS,
// DOES NOT READ IN SPACES EITHER! CIN DOES NOT READ IN ANY WHITESPACE!
// ONLY READ IN EXPLICIT \n

// USE getline(fin, s) TO GET ALL THE WHITESPACE IN THE MIDDLE OF THE LINE!
// getline() also preserves the '\r' carriage return
// the >> operator IGNORES WHITESPACE!

// USE GETLINE!
// s would contain the LITERAL chars, if \n is explicitly in file,
// \ and n would be separated, could as 2 chars, +2 length of string

using namespace std;

int main(){
	
	int W, H;
	
	ifstream fin ("maze1.in");
	ofstream fout ("maze1.out");
	
	fin >> W >> H;
	
	vector<vector<vector<int>>> grid (H, vector<vector<int>> (W, vector<int> (4, 1))); // north, east, south, west
	// 1 means clear path, 0 means wall
	// initially all directions are clear, but delete
	// edges based on where walls are in maze input
	
	vector<int> entrances; // .push_back() to size 4, 2 entrances, x, y each
	
	vector<string> lines;
	string s;
	
	
	
	
	
	
	getline(fin, s); // WITHOUT THIS LINE, THE "CURSOR" IS STILL RIGHT AFTER THE DIGIT 3 
	                // IN THE FIRST LINE OF maze1.in
	           // SO MUST GETLINE TO GET TO THE NEXT LINE!
	
	
	
	
	
	
	while(getline(fin, s)){
	    lines.push_back(s);
	}

	// when reading top border, bottom border, and the first and last chars of inbetween cell rows,
	// remember to check for entrances
	
	
	// read in top border
	s = lines[0];
    
    cout << s << endl;
    
	for(int j = 0; j < W; ++j){
		if(s[2 * j + 1] == ' '){ // opening in wall
			entrances.push_back(0); // x index
			entrances.push_back(j); // y index
		}
		grid[0][j][0] = 0; // north is blocked, even if entrance (we don't want to go outside the grid
	}

	// seems like implicit enter characters are not read!
	
	// read in middle rows (and bottom border)
	for(int i = 0; i < H; ++i){
		// left border
		s = lines[2 * i + 1];
		cout << s << endl;
		if(s[0] == ' '){
			entrances.push_back(i);
			entrances.push_back(0);
		}
		grid[i][0][3] = 0;
		
		// vert walls
		for(int j = 1; j < W; ++j){
			if(s[2 * j] == '|'){
				grid[i][j][3] = 0; // west blocked
				grid[i][j - 1][1] = 0; // east blocked
			}
		}
		
		if(s[2 * W] == ' '){ // not s.back(), which is a '\r' char
			entrances.push_back(i);
			entrances.push_back(W - 1);
		}
		grid[i][W - 1][1] = 0;
		
		// horizontal walls
		
		s = lines[2 * i + 2];
		cout << s << endl;
	    
		
		for(int j = 0; j < W; ++j){
			if(s[2 * j + 1] == '-'){
				grid[i][j][2] = 0; // south blocked
				if(i != H - 1){ // check if not last row in grid
					grid[i + 1][j][0] = 0; // north blocked
				}
			}
			if(i == H - 1){ // read in bottom border
				if(s[2 * j + 1] == ' '){
					entrances.push_back(i);
					entrances.push_back(j);
				}
				grid[i][j][2] = 0; // bottom border, south blocked
			}
		}
	}	
	
	
	for(int i = 0; i < grid.size(); ++i){
		for(int j = 0; j < grid[0].size(); ++j){
			for(int idx = 0; idx < grid[i][j].size(); ++idx){
				cout << grid[i][j][idx];
			}
			cout << "  ";
		}
		cout << endl;
		cout << endl;
	}
    
    cout << "entrances:" << endl;
    for(int i = 0; i < entrances.size(); ++i){
        cout << entrances[i] << ' ';
    }
    cout << endl;
    
    
    vector<vector<int>> dis_from_entrance (H, vector<int> (W, 1000000000));
    for(int i = 0; i < entrances.size(); i += 2){
        
        int dis = 1;
        vector<int> BFS;
        BFS.push_back(entrances[i]);
        BFS.push_back(entrances[i + 1]);
        vector<vector<int>> search (H, vector<int> (W, 0));
        search[entrances[i]][entrances[i + 1]] = 1;
		dis_from_entrance[entrances[i]][entrances[i + 1]] = 1;
		dis += 1;
        while(BFS.size() != 0){
            vector<int> temp;
            for(int i = 0; i < BFS.size(); i += 2){
                int x = BFS[i];
                int y = BFS[i + 1];
                if(grid[x][y][0] == 1 and search[x - 1][y] == 0){
                    search[x - 1][y] = 1;
                    temp.push_back(x - 1);
                    temp.push_back(y);
					if(dis < dis_from_entrance[x - 1][y]){
						dis_from_entrance[x - 1][y] = dis;
					}
                }if(grid[x][y][1] == 1 and search[x][y + 1] == 0){
                    search[x][y + 1] = 1;
                    temp.push_back(x);
                    temp.push_back(y + 1);
					if(dis < dis_from_entrance[x][y + 1]){
						dis_from_entrance[x][y + 1] = dis;
					}
                }if(grid[x][y][2] == 1 and search[x + 1][y] == 0){
                    search[x + 1][y] = 1;
                    temp.push_back(x + 1);
                    temp.push_back(y);
					if(dis < dis_from_entrance[x + 1][y]){
						dis_from_entrance[x + 1][y] = dis;
					}
                }if(grid[x][y][3] == 1 and search[x][y - 1] == 0){
                    search[x][y - 1] = 1;
                    temp.push_back(x);
                    temp.push_back(y - 1);
					if(dis < dis_from_entrance[x][y - 1]){
						dis_from_entrance[x][y - 1] = dis;
					}
                }
            }
            dis += 1;
            BFS = temp;
        }
    }
	
	int longest = 0;
	for(int i = 0; i < H; ++i){
		for(int j = 0; j < W; ++j){
			if(dis_from_entrance[i][j] > longest){
				longest = dis_from_entrance[i][j];
			}
		}
	}
    
    cout << "longest: " << longest << endl;
    
	fout << longest << endl;
	
	fin.close();
	fout.close();

	return 0;
}