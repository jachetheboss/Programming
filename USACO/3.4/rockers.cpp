/*
ID: jamessh3
LANG: C++20
TASK: rockers
*/

#include <bits/stdc++.h>
using namespace std;

bool canFit(vector<int>& v, int M, int T){ // M disks, T minutes

	// misinterpreted the problem, thought that each disk had to be in sorted order,
	// not the entire set of disks!
	
	int disks = 0;
	int rem_space = T;
	bool ok = true;
	for(int dur : v){
		if(dur > T){
			ok = false;
			break;
		}
		
		if(dur > rem_space){
			disks++;
			rem_space = T - dur;
		}else{
			rem_space -= dur;
		}
	}
	if(rem_space < T) disks++;
	
	if(disks > M) ok = false;
	if(not ok) return false;
	
// 	cout << "disks " << disks << endl;
	
	return true;


/*
	if(v.size() == 0) return true;
	if(M == 0 and v.size() > 0) return false;

	// meet in the middle?
	// fill in one disk at a time
	int num_songs = -1;
	int rem = T; // try to fill up one disk at a time
	int ways = (int)pow(2, (int)v.size());
	vector<int> next_v;
	vector<int> chosen;
	for(int way = 0; way < ways; ++way){
		int dur = 0; // duration 
		int pow2 = 1;
		int i = 0;
		int songs = 0;
		bool ok = true;
		while(pow2 < ways){
			if((pow2 & way) == pow2){
				songs++;
				dur += v[i];
			}
			if(dur > T){
				ok = false;
				break;
			}			
			pow2 *= 2;
			i++;
		}
		if(not ok) continue;
		
		if(T - dur < rem or (T - dur == rem and songs < num_songs)){
			rem = T - dur;
			num_songs = songs;
			pow2 = 1;
			i = 0;
			next_v.clear();
			chosen.clear();
			while(pow2 < ways){
				if((pow2 & way) == 0) next_v.push_back(v[i]);
				else chosen.push_back(v[i]);
				pow2 *= 2;
				i++;
			}
		}
	}
	if(num_songs == -1) return false;
	
    // cout << "chosen:" << endl;
    // for(int dur : chosen) cout << dur << ' ';
    // cout << endl;
    // cout << "next_v:" << endl;
    // for(int dur : next_v) cout << dur << ' ';
    // cout << endl << endl;
	
	return canFit(next_v, M - 1, T);
*/
}

int main()
{
	// Akuna bin packing problem! Redeem yourself!
	
	ifstream fin ("rockers.in");
	ofstream fout ("rockers.out");
	
	int N, T, M; fin >> N >> T >> M;
	vector<int> lengths;
	for(int i = 0; i < N; ++i){
		int L; fin >> L;
		lengths.push_back(L);
	}
	// knapsack DP? multiple knapsack? bitmask DP?
	// meet in the middle?
	
	// greedily choose k shortest duration songs?
	vector<vector<int>> sorted;
	for(int i = 0; i < lengths.size(); ++i) sorted.push_back({lengths[i], i});
	sort(sorted.begin(), sorted.end());
	
	int total_capacity = M * T;
	
// 	cout << "sorted.size() " << sorted.size() << endl;
	
	
	int ways = (int)pow(2, (int)lengths.size());
	int ans = 0;
	for(int way = 0; way < ways; ++way){
	    vector<int> subseq;
	    int pow2 = 1;
	    int i = 0;
	    while(pow2 < ways){
	        if((pow2 & way) == pow2){
	            subseq.push_back(lengths[i]);
	        }
	        if(pow2 > way) break;
	        pow2 *= 2;
	        i++;
	    }
	    
	   // cout << "subseq" << endl;
	   // for(int dur : subseq) cout << dur << ' ';
	   // cout << endl;
	    
	    bool ret = canFit(subseq, M, T);
	    if(ret == true){
	        ans = max(ans, (int)subseq.size());
	        // do pruning to see if the shortest (int)subseq.size() + 1 songs is longer than limit!
	    }
    }
    fout << ans << endl;
    
	
	
// 	for(int songs = sorted.size(); songs >= 1; --songs){
// 		int total_length = 0;
// 		for(int i = 0; i < songs; ++i) total_length += sorted[i][0];
// 		if(total_length > total_capacity) continue; // impossible
// 		// all tracks (bins) have the same capacity! 
// 		vector<int> ind;
// 		for(int i = 0; i < songs; ++i) ind.push_back(sorted[i][1]);
// 		sort(ind.begin(), ind.end());
// 		vector<int> v;
// 		for(int idx : ind) v.push_back(lengths[idx]);
	    
// 	   // cout << "v: " << endl;
// 	   // for(int dur : v) cout << dur << ' ';
// 	   // cout << endl;
	    
// 		bool ret = canFit(v, M, T);
// 		if(ret == true){
// 			fout << songs << endl;
// 			fin.close();
// 			fout.close();
// 			return 0;
// 		}
// 	}
// 	fout << 0 << endl; // no songs can be put on!	

	// prioritize completely filling up bin,
	// then leaving 1 space left
	// then leaving 2 spaces left, 3, 4, ....
	// pruning?
	// recursive descent?
	
	
	fin.close();
	fout.close();
	
	return 0;
}