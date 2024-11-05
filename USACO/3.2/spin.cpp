/*
ID: jamessh3
LANG: C++20
TASK: spin
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
	// think about the edge case: when can the wheel wedges never align 
	
	// factors of 360
	// 1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 15, 18, 20, 24, 30, 36, 40, 45, 60, 72, 90
	// 120, 180, 360
	
	ifstream fin ("spin.in");
	ofstream fout ("spin.out");
	vector<vector<int>> wheels;
	for(int i = 0; i < 5; ++i){
		int speed; fin >> speed;
		int wedges; fin >> wedges;
		vector<int> v = {speed};
		for(int w = 0; w < wedges; ++w){
			int start, sz; fin >> start >> sz;
			v.push_back(start);
			v.push_back(sz);
		}
		wheels.push_back(v);
	}
	int ans = -1;
	for(int sec = 0; sec <= 359; ++sec){
		// calculate positions of all wedges
		// do brute force search, one degree at a time, then do
		// binary search (merge intervals type stuff)
		vector<vector<int>> positions;
		for(vector<int>& wheel : wheels){
			int speed = wheel[0];
			vector<int> position;
			for(int i = 1; i < wheel.size(); i += 2){
				int start = wheel[i];
				int sz = wheel[i + 1];
				int new_start = (start + speed * sec) % 360;
				position.push_back(new_start);
				position.push_back(sz);
			}
			positions.push_back(position);
		}
		vector<int> degrees; // degrees at which there is wedge opening
		// for the top wheel
		for(int i = 0; i < positions[0].size(); i += 2){
			int start = positions[0][i];
			int sz = positions[0][i + 1];
			for(int deg = start; deg <= start + sz; ++deg){
				if(deg >= 360) degrees.push_back(deg - 360);
				else degrees.push_back(deg);
			}
		}
		bool all_align = false;;
		for(int deg : degrees){
			bool ok = true;
			for(int i = 1; i < positions.size(); ++i){
				bool align = false;
				for(int j = 0; j < positions[i].size(); j += 2){
					int start = positions[i][j];
					int sz = positions[i][j + 1];
					int end = start + sz;
					if(end >= 360){
						if((start <= deg and deg <= 359) or deg <= end - 360){
							align = true;
							break;
						}
					}else{
						if(start <= deg and deg <= end){
							align = true;
							break;
						}
					}
				}
				if(not align){
					ok = false;
					break;
				}
			}
			if(ok){
				all_align = true;
				break;
			}
		}
		if(all_align){
			ans = sec;
			break;
		}
	}
	if(ans == -1) fout << "none" << endl;
	else fout << ans << endl;
	
	return 0;
}