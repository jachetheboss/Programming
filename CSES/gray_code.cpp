#include <bits/stdc++.h>
using namespace std;

int main(){
	int N; cin >> N;
	// gray code builder
	vector<int> ops = {1};
	int pow_set_sz = (int)pow(2, N);
	while(ops.size() < pow_set_sz - 1){
		int sz = ops.size();
		for(int i = 0; i < sz; ++i) ops.push_back(ops[i]);
		ops[2 * sz - 1]++;
	}
	
// 	cout << "ops" << endl;
// 	for(int op : ops) cout << op << ' ';
// 	cout << endl;
	
	string s = string(N, '0');
	cout << s << endl;
	for(int i = 0; i < pow_set_sz - 1; ++i){
		int idx = N - ops[i];
		if(s[idx] == '1') s[idx] = '0';
		else s[idx] = '1';
		cout << s << endl;
	}
	
	
	
	
	return 0;
}