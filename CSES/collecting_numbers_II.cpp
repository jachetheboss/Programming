#include <bits/stdc++.h>
using namespace std;

int main()
{
	int N, M; cin >> N >> M;
	vector<int> ans;
	// sqrt decomp? If too slow, code up a segment tree
	// completely misinterpreted the question!
	int block_sz = (int)floor(sqrt(N));
	int num_blocks = N / block_sz;
	int rem = N % block_sz;
	if(rem != 0) num_blocks++;
	vector<int> v (N);
	for(int i = 0; i < N; ++i){
	    int val; cin >> val;
	    v[i] = val;
	}
	vector<int> blocks (num_blocks);
	for(int block = 0; block < blocks.size(); ++block){
	    int L = block * block_sz;
	    int R = min(L + block_sz - 1, N - 1);
	    int ops = 1;
	    for(int i = L + 1; i <= R; ++i){
	        if(v[i] < v[i - 1]) ops++;
	    }
	    blocks[block] = ops;
	}
	
// 	cout << "blocks" << endl;
// 	for(int val : blocks) cout << val << ' ';
// 	cout << endl;
	
	for(int i = 0; i < M; ++i){
		int idx1, idx2; cin >> idx1 >> idx2; // 1-indexed
		idx1--;
		idx2--; // convert to 0-indexed
		int tmp = v[idx1];
		v[idx1] = v[idx2];
		v[idx2] = tmp;
		int block1 = idx1 / block_sz;
		int block2 = idx2 / block_sz;
		
		int L = block1 * block_sz;
		int R = min(L + block_sz - 1, N - 1);
		int ops = 1;
		for(int j = L + 1; j <= R; ++j){
			if(v[j] < v[j - 1]) ops++;
		}
		blocks[block1] = ops;
		
		L = block2 * block_sz;
		R = min(L + block_sz - 1, N - 1);
		ops = 1;
		for(int j = L + 1; j <= R; ++j){
			if(v[j] < v[j - 1]) ops++;
		}
		blocks[block2] = ops;
		
		
// 		cout << "blocks:" << endl;
// 		for(int x : blocks) cout << ' ' << x << ' ';
// 		cout << endl;
// 		cout << "v" << endl;
// 		for(int x : v) cout << ' ' << x << ' ';
// 		cout << endl;
// 		cout << endl;
		
		
		// complete the query
	    ops = 1;
		int prev = -1;
		for(int block = 0; block < blocks.size(); ++block){
		    ops += blocks[block];
		    int idx = block * block_sz;
		    int first = v[idx];
		    if(first > prev) ops--;
			if(block != num_blocks - 1) prev = v[idx + block_sz - 1];
		}
		ans.push_back(ops);		
	}
	for(int val : ans) cout << val << endl;


	return 0;
}