#include <bits/stdc++.h>
using namespace std;

int binarySearchStart(vector<int>& v, int target){
	if(target == v[0]) return 0;
	int lo = 0;
	int hi = (int)v.size() - 1;
	int mid = (lo + hi) / 2;
	while(true){
		if(v[mid] < target and target <= v[mid + 1]) return mid + 1;
		else if(v[mid] >= target) hi = mid;
		else if(target > v[mid + 1]) lo = mid + 1;
		mid = (lo + hi) / 2;
	}
	return -1;
}

int binarySearchEnd(vector<int>& v, int target){ // start of range must be to the LEFT of target!
	if(v.back() < target) return (int)v.size() - 1;
	int lo = 0;
	int hi = (int)v.size() - 1;
	int mid = (lo + hi) / 2;
	while(true){
		if(v[mid] < target and target <= v[mid + 1]) return mid;
		else if(v[mid] >= target) hi = mid;
		else if(target > v[mid + 1]) lo = mid + 1;
		mid = (lo + hi) / 2;
	}
	return -1;
}

int main()
{
	int N; cin >> N;
	
	if(N == 1){
		cout << 0 << endl;
		cout << 0 << endl;
		return 0;
	}
	
	vector<int> ranges;
	for(int i = 0; i < N; ++i){
		int start, end; cin >> start >> end;
		ranges.push_back({start, end, i});
	}
	sort(ranges.begin(), ranges.end());
	
	// sort, then prefix
	vector<int> enveloped (N, 0);
	vector<int> envelops (N, 0);
	vector<int> prefix; // prefix for maximum rightmost bound
	// RLE type jaunt
	int streak = 0;
	int rolling_max = ranges[0][1];
	int prev = ranges[0][0];
	for(vector<int>& range : ranges){
		if(range[0] == prev) streak++;
		else{
			for(int i = 0; i < streak; ++i) prefix.push_back(rolling_max);
			prev = range[0];
			streak = 1;
		}
		rolling_max = max(rolling_max, range[1]);
	}
	for(int i = 0; i < streak; ++i) prefix.push_back(rolling_max);
	
	for(int i = 0; i < ranges.size(); ++i){
		if(range[i][1] <= prefix[i]){
			int idx = range[i][2];
			enveloped[idx] = 1;
		}
	}
	
	// sqrt decomp
	int block_sz = (int)floor(sqrt(N));
	vector<int> blocks;
	for(int L = 0; L < N; L += block_sz){
		int R = min(L + block_sz - 1, N - 1);
		int min_r = ranges[L][1];
		for(int i = L; i <= R; ++i){
			min_r = min(min_r, ranges[i][1]);
		}
		blocks.push_back(min_r);
	}
	vector<int> starts;
	
	// MUST KEEP IN MIND THAT A RANGE CANNOT USE ITSELF AS ENVELOPED/ENVELOPS,
	// FOR EVERY RANGE, UPDATE THE SQRT DECOMP BLOCK THAT IT IS IN TO NOT INCLUDE IT!
	
	for(vector<int>& range : ranges) starts.push_back(range[0]);
	for(int i = 0; i < ranges.size(); ++i){
		int start = ranges[i][0];
		int end = ranges[i][1];
		int L = binarySearchStart(starts, start);
		int R = binarySearchEnd(starts, end);
		int L_block = L / block_sz;
		int R_block = R / block_sz;
		int min_r = INT_MAX;
		int bound = L_block
		
		if(L_block == R_block){
			for(int j = L; 
		}else{
			
		}
		
		for(int j = L; j < 
		
		
		if(min_r <= end){
			int idx = ranges[i][2];
			envelops[idx] = 1;
		}
	}
	for(int i = 0; i < (int)envelops.size() - 1; ++i) cout << envelops[i] << ' ';
	cout << envelops.back() << endl;
	for(int i = 0; i < (int)enveloped.size() - 1; ++i) cout << enveloped[i] << ' ';
	cout << enveloped.back() << endl;
	
	
	return 0;
}