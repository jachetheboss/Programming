/*
ID: jamessh3
LANG: C++20
TASK: snail
*/

#include <bits/stdc++.h>
using namespace std;

bool canMove(int i, int j, char dir, vector<string>& grid){
	if(dir == 'N') i--;
	else if(dir == 'E') j++;
	else if(dir == 'S') i++;
	else j--; // west
	if(i < 0 or i == grid.size() or j < 0 or j == grid.size()) return false;
	if(grid[i][j] == '0') return true;
	return false;
}

void move(int& i, int& j, char dir, vector<string>& grid){
	if(dir == 'N') i--;
	else if(dir == 'E') j++;
	else if(dir == 'S') i++;
	else j--; // west
	grid[i][j] = '2';
}

void DFS(vector<string>& grid, stack<vector<int>>& stk, char dir, stack<vector<char>>& turnstk, int& ans){
	int cells = 1;
	grid[0][0] = '2'; // 2 means searched (the path)
	stack<vector<int>> stk;
	stk.push( {0, 0} );
	stack<char> turnstk; // stores the left turns that we need to do (we try turning right first)
	int i = 0;
	int j = 0;
	while(stk.size() > 0){
		while(canMove(i, j, dir, grid)){
			move(i, j, dir, grid);
			cells++;
			ans = max(ans, cells);
		}
		// can't move in direction dir anymore, have to make a turn junction at [i][j],
		turnstk.push('L'); // left, right
		char turnway = turnstk.back().back();
		turnstk[(int)turnstk.size() - 1].pop_
	}
}

int main()
{
	ifstream fin ("snail.in");
	ofstream fout ("snail.out");
	// A B C D
	//1
	//2
	//3
	//4
	// continue spiraling, like Archimedes spiral, but can change spiral direction in the middle 
	// to prolong the number of turns
	// maximum possible number of turns on a 26x26 grid is ~ 23 ?
	// can we use bitwise ops to increase runtime by ~32x? since to the right of the first 26 columns,
	// still 174 cols, only need ~6 loop iterations to set from 1111.....1111 to 0000...0000 via bitwise,
	// while need 174 loop iterations if mark one cell at a time (rather than 32 cells at a time)
	// some backtracking jaunt?
	// can only make one lap around the big 200x200 part
	// but multiple laps can be done within the 200x26 part
	int N, B; fin >> N >> B;
	vector<string> grid (N, string(N, '0')); // '0' are traversable, '1' are obstacles
	for(int i = 0; i < B; i++){
		string coor; fin >> coor; // barrier location
		int col = coor[0] - 'A';
		int row = stoi(coor.substr(1)) - 1;
		grid[row][col] = '1';
	}
	if(grid[0][0] == '1'){ // the start cell has an obstacle on it
		cout << 0 << endl;
		fin.close();
		fout.close();
		return 0
	}
	
	int ans = 0;
	char dir = 'S'; // North East South West
	DFS(grid, dir, ans);
	
	dir = 'E';
	DFS(grid, dir, ans);
	
	fout << ans << endl;
	
	fin.close();
	fout.close();
	
	return 0;
}