/*
ID: jamessh3
LANG: C++20
TASK: starry
*/

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> normalize(vector<vector<int>>& component){
// returns normalized component without mutating the original component
	int leftmost = INT_MAX;
	int top = INT_MAX;
	for(vector<int>& cell : component){
		int i = cell[0];
		int j = cell[1];
		leftmost = min(leftmost, j);
		top = min(top, i);
	}
	int i_shift = top;
	int j_shift = leftmost;
	vector<vector<int>> normalized = component;
	for(int idx = 0; idx < normalized.size(); idx++){
		vector<int>& cell = normalized[idx];
		cell[0] -= i_shift;
		cell[1] -= j_shift;
	}
	return normalized;
}

vector<vector<int>> rotateClockwise90(vector<vector<int>> component){
	// must be a square matrix to rotate clockwise in-place 
	component = normalize(component);
	int m = 0; // m and n are the maximum indices (not the dimensions!)
	int n = 0;
	for(vector<int>& cell : component){
		int i = cell[0];
		int j = cell[1];
		int m = max(m, i);
		int n = max(n, j);
	}
	int p = max(m, n);
	for(int idx = 0; idx < component.size(); idx++){
		vector<int>& cell = component[idx];
		int i = cell[0];
		int j = cell[1];
		cell[0] = j;
		cell[1] = p - i;
	}
	component = normalize(component);
	return component;
}
vector<vector<int>> reflectAcrossY(vector<vector<int>> component){ // pass by value since modifying in place
	int leftmost = 0;
	int rightmost = INT_MAX;
	for(vector<int>& cell : component){
		int j = cell[1];
		leftmost = min(leftmost, j);
		rightmost = max(rightmost, j);
	}
	for(int idx = 0; idx < component.size(); idx++){
		vector<int>& cell = component[idx];
		int diff = cell[1] - leftmost;
		cell[1] = rightmost - diff;
	}
	return component;
}

string serialize(vector<vector<int>> component){ // pass by value since sort mutates
	sort(component.begin(), component.end());
	string key = "";
	for(vector<int>& cell : component){
		int i = cell[0];
		int j = cell[1];
		key += to_string(i);
		key += ' ';
		key += to_string(j);
		key += ' ';
	}
	return key;
}

void BFS(vector<string>& grid, vector<vector<int>>& searched, vector<vector<vector<int>>>& components, int start_i, int start_j){
	
	if(searched[start_i][start_j] == 1 or grid[start_i][start_j] == '0') return;
	
	int H = grid.size();
	int W = grid[0].size();
	searched[start_i][start_j] = 1;
	
	vector<vector<int>> q = { {start_i, start_j} };
	vector<vector<int>> dirs = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
	vector<vector<int>> component = { {start_i, start_j} };
	while(q.size() > 0){
		vector<vector<int>> next_q;
		for(vector<int>& cell : q){
			int i = cell[0];
			int j = cell[1];
			for(vector<int>& dir : dirs){
				int a = i + dir[0];
				int b = j + dir[1];
				if(a < 0 or a == H or b < 0 or b == W) continue; // out of bounds
				if(searched[a][b] == 1){
				    // cout << "hello" << endl;
				    continue;
				}
				if(grid[a][b] == '0'){
				    // cout << "world" << endl;
				    continue;
				}
				searched[a][b] = 1;
				next_q.push_back( {a, b} );
				component.push_back( {a, b} );
			}
		}
		q = next_q;
	}
	components.push_back(component);
}

int main()
{
	ifstream fin ("starry.in");
	ofstream fout ("starry.out");
	
	// bfs minesweeper style (8 adj cells), then find a way to identify rotations/reflections)
	// "normalize" each connected component by putting it as left and up as possible without
	// exiting the matrix boundaries
	// for each of the 8 rotation/reflection configs, normalize it, then serialize into string 
	// from top left to bottom right, going left to right, then down. Store in hashmap, each unique 
	// serialization will have a group of connected component IDs, then populate the matrix replacing 
	// each connected component cell with the ID it belongs to 
	string line; getline(fin, line);
	int W = stoi(line);
	getline(fin, line);
	int H = stoi(line);

	vector<string> grid (H);
	for(int i = 0; i < H; i++){
		string s = "";
		getline(fin, s);
		grid[i] = s;
	}
	
	cout << "grid.size() " << grid.size() << endl;
	cout << "grid[0].size() " << grid[0].size() << endl;
	
	cout << "grid" << endl;
	for(string& row : grid) cout << row << endl;
	cout << endl;
	
	vector<vector<vector<int>>> components;
	vector<vector<int>> searched (H, vector<int> (W, 0));
	for(int i = 0; i < H; i++){
		for(int j = 0; j < W; j++){
			BFS(grid, searched, components, i, j);
		}
	}
// 	cout << "components.size() " << components.size() << endl;
//     cout << "components" << endl;
// 	for(vector<vector<int>>& component : components){
// 	    cout << "{";
// 	    for(vector<int>& cell : component){
// 	        cout << "{" << cell[0] << ',' << cell[1] << "} ";
// 	    }
// 	    cout << "}" << endl;
// 	}
	
	cout << "here" << endl;
	
	vector<string> ans (H, string(W, '0'));
	char letter = 'a';
	
	unordered_map<string, vector<int>> keys;
	for(int i = 0; i < components.size(); i++){
		vector<vector<int>> component = components[i];
		component = normalize(component);
		string key = serialize(component);
		if(not keys.count(key)) keys.insert({key, { } });
		keys[key].push_back(i);
	}
	
	vector<int> components_searched (components.size(), 0);
	for(int idx = 0; idx < components.size(); idx++){
		if(components_searched[idx] == 1) continue;
		vector<vector<int>> component = components[idx];
		unordered_set<int> ind;
		for(int iter = 0; iter < 4; iter++){
		    component = normalize(component);
			string key = serialize(component);
			if(keys.count(key)){
			    for(int i : keys[key]) ind.insert(i);
			}
			component = rotateClockwise90(component);
		}
		component = reflectAcrossY(component);
		for(int iter = 0; iter < 4; iter++){
		    component = normalize(component);
			string key = serialize(component);
			if(keys.count(key)){
			    for(int i : keys[key]) ind.insert(i);
			}
			component = rotateClockwise90(component);
		}
		unordered_set<int>::iterator it;
		for(it = ind.begin(); it != ind.end(); it++){
			int i = *it;
			components_searched[i] = 1;
			for(vector<int>& cell : components[i]){
				int a = cell[0];
				int b = cell[1];
				ans[a][b] = letter;
			}
		}
		letter++;
	}
	for(string& row : ans) fout << row << endl;
	
	cout << "keys" << endl;
	for(auto it = keys.begin(); it != keys.end(); it++){
	    cout << "group: ";
	    for(int i : it->second) cout << i << ' ';
	    cout << endl;
	}
	
	cout << "components" << endl;
	for(vector<vector<int>>& component : components){
	    cout << "{";
	    for(vector<int>& cell : component){
	        cout << "{" << cell[0] << ',' << cell[1] << "} ";
	    }
	    cout << "}" << endl;
	}
	
	fin.close();
	fout.close();
	
	return 0;
}