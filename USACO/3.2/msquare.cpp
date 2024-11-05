/*
ID: jamess3
LANG: C++20
TASK: msquare
*/

#include <bits/stdc++.h>
using namespace std;

string A(string& s){ // reverse
	string t = "";
	for(int i = (int)s.length() - 1; i >= 0; --i) t += s[i];
	return t;
}
string B(string& s){
	string t = "";
	t += s[3];
	for(int i = 0; i <= 2; ++i) t += s[i];
	for(int i = 5; i <= 7; ++i) t += s[i];
	t += s[4];
	return t;
}
string C(string& s){
	string t = "";
	t += s[0];
	t += s[6];
	t += s[1];
	t += s[3];
	t += s[4];
	t += s[2];
	t += s[5];
	t += s[7];
	return t;
}
int main()
{
	// instead of string operations, can we just do int operations?
	
	ifstream fin ("msquare.in");
	ofstream fout ("msquare.out");
	// string optimization, instead of making a bunch of small 2D or 1D vectors, just store
	// as string for the BFS, much faster
	string start = "12345678";
	string target = "";
	for(int i = 0; i < 8; ++i){
		int val; fin >> val;
		target += val + '0';
	}
	if(target == start){
		fout << '0' << endl << endl;
		fin.close();
		fout.close();
		return 0;
	}
	
	int ops = 1;
	unordered_set<string> searched;
	searched.insert(start);
	vector<string> bfs = {start};
	vector<string> paths = {""};
	string op_path = "";
	while(bfs.size() > 0){
		vector<string> next_bfs;
		vector<string> next_paths;
		bool done = false;
		for(int i = 0; i < bfs.size(); ++i){
			string& s = bfs[i];
			string t = A(s);
			if(t == target){
				op_path = paths[i];
				op_path += 'A';
				done = true;
				break;
			}
			if(searched.count(t) == false){
				searched.insert(t);
				string path = paths[i];
				path += 'A';
				next_paths.push_back(path);
				next_bfs.push_back(t);
			}
			
			t = B(s);
			if(t == target){
				op_path = paths[i];
				op_path += 'B';
				done = true;
				break;
			}
			if(searched.count(t) == false){
				searched.insert(t);
				string path = paths[i];
				path += 'B';
				next_paths.push_back(path);
				next_bfs.push_back(t);
			}
			
			t = C(s);
			if(t == target){
				op_path = paths[i];
				op_path += 'C';
				done = true;
				break;
			}
			if(searched.count(t) == false){
				searched.insert(t);
				string path = paths[i];
				path += 'C';
				next_paths.push_back(path);
				next_bfs.push_back(t);
			}
		}
		if(done) break;
		
		bfs = next_bfs;
		paths = next_paths;
		ops++;
	}
	
	fout << ops << endl;
	fout << op_path << endl;
	
	fin.close();
	fout.close();
	
	return 0;
}