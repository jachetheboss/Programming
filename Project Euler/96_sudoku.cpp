#include <bits/stdc++.h>
using namespace std;

void solve(vector<vector<char>>& board, vector<vector<int>>& row_freq, vector<vector<int>>& col_freq, vector<vector<int>>& square_freq, int empty_cells, vector<vector<char>>& solution){
        
	// printBoard(board);
	
	if(empty_cells == 0){
		solution = board;
		return;
	}
	
	int x, y;
	bool found = false;
	for(int i = 0; i < 9; ++i){
		for(int j = 0; j < 9; ++j){
			if(board[i][j] == '0'){
				x = i;
				y = j;
				found = true;
				break;
			}
		}
		if(found) break;
	}
	
	int square_idx = 3 * (x / 3) + y / 3;
	for(int val = 1; val <= 9; ++val){
		if(row_freq[x][val] == 0 and col_freq[y][val] == 0 and square_freq[square_idx][val] == 0){ 
			row_freq[x][val] = 1;
			col_freq[y][val] = 1;
			square_freq[square_idx][val] = 1;
			board[x][y] = val + '0';
			solve(board, row_freq, col_freq, square_freq, empty_cells - 1, solution);
			
			if(solution.size() != 0) return;
			
			row_freq[x][val] = 0;
			col_freq[y][val] = 0;
			square_freq[square_idx][val] = 0;
			board[x][y] = '0';
		}
	}
}
void solveSudoku(vector<vector<char>>& board) {
	int empty_cells = 0;
	vector<vector<int>> row_freq (9, vector<int> (10, 0));
	vector<vector<int>> col_freq = row_freq;
	vector<vector<int>> square_freq = row_freq;
	// squares numbered 0, 1, 2, 3... from top left to bottom right
	for(int i = 0; i < 9; ++i){
		for(int j = 0; j < 9; ++j){
			if(board[i][j] == '0'){
				empty_cells++;
			}else{
				int val = board[i][j] - '0';
				row_freq[i][val] = 1;
				col_freq[j][val] = 1;
				int square_idx = 3 * (i / 3) + j / 3;
				square_freq[square_idx][val] = 1;
			}
		}
	}
	
	vector<vector<char>> solution;
	solve(board, row_freq, col_freq, square_freq, empty_cells, solution);
	
	board = solution;
}

int main()
{
	ifstream fin ("sudoku.txt");
	vector<vector<vector<char>>> grids;
	for(int i = 0; i < 50; i++){
		string line; getline(fin, line);
		vector<vector<char>> grid;
		for(int j = 0; j < 9; j++){
			getline(fin, line);
			vector<char> row;
			for(char c : line) row.push_back(c);
			grid.push_back(row);
		}
		grids.push_back(grid);
	}
	
	int ans = 0;
	for(vector<vector<char>>& grid : grids){
	   // cout << "before:" << endl;
	   // for(vector<char>& row : grid){
	   //     for(char c : row) cout << c;
	   //     cout << endl;
	   // }
	   // cout << endl;
	    
		solveSudoku(grid);
		
// 		cout << "after:" << endl;
// 	    for(vector<char>& row : grid){
// 	        for(char c : row) cout << c;
// 	        cout << endl;
// 	    }
// 	    cout << endl;
	    
		ans += 100 * (grid[0][0] - '0') + 10 * (grid[0][1] - '0') + grid[0][2] - '0';
	}
	cout << "ans: " << ans << endl;
	
	fin.close();
	
	return 0;
}