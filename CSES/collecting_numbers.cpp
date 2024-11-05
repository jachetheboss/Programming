#include <bits/stdc++.h>
using namespace std;

int main()
{
	int N; cin >> N;
	//vector<int> v;
	vector<int> ind (N + 1, -1);
	for(int i = 0; i < N; ++i){
		int val; cin >> val;
		//v.push_back(val);
		ind[val] = i;
	}
	int ops = 1;
	int prev_idx = -1;
	for(int num = 1; num <= N; ++num){
		int idx = ind[num];
		if(idx < prev_idx){
			ops++;
		}
		prev_idx = idx;
	}
	cout << ops << endl;
	
	
	
	return 0;
}