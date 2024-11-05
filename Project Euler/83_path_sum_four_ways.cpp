// 83 pathsum four ways

#include <bits/stdc++.h>
using namespace std;

vector<int> parseLine(string& line){
	vector<int> row;
	string num = "";
	for(char c : line){
		if(c == ','){
			row.push_back(stoi(num));
			num = "";
		}else num += c;
	}
	row.push_back(stoi(num));
	return row;
}

int main()
{
	ifstream fin ("matrix.txt");
	vector<vector<int>> grid;
	string line;
	while(getline(fin, line)){
		vector<int> row = parseLine(line);
		grid.push_back(row);
	}
	int m = grid.size();
	int n = grid[0].size();
	// Dijkstra's
	vector<vector<int>> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
	vector<vector<int>> min_cost (m, vector<int> (n, INT_MAX));
	priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
	pq.push( {grid[0][0], 0, 0} ); // {dis, i, j}
	while(min_cost.back().back() == INT_MAX){
		vector<int> tp = pq.top();
		int d = tp[0];
		int i = tp[1];
		int j = tp[2];
		pq.pop();
		if(min_cost[i][j] != INT_MAX) continue;
		min_cost[i][j] = d;
		for(vector<int>& dir : dirs){
			int a = i + dir[0];
			int b = j + dir[1];
			if(a >= 0 and a < m and b >= 0 and b < n and min_cost[a][b] == INT_MAX){
				pq.push( {d + grid[a][b], a, b} );
			}
		}
	}
	cout << "ans: " << min_cost.back().back() << endl;
	fin.close();

	return 0;
}