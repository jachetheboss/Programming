#include <bits/stdc++.h>
using namespace std;

int main()
{
	int X, N; cin >> X >> N;
	vector<int> positions;
	for(int i = 0; i < N; ++i){
		int pos; cin >> pos;
		positions.push_back(pos);
	}
	set<int> lights;
	lights.insert(0);
	lights.insert(X);
	multiset<int> sizes;
	sizes.insert(X);
	vector<int> ans;
	for(int pos : positions){
		int L = *(prev(lights.upper_bound(pos)));
		int R = *(lights.upper_bound(pos));
		int sz = R - L;
		int L_sz = pos - L;
		int R_sz = R - pos;
		sizes.erase(sizes.find(sz));
		sizes.insert(L_sz);
		sizes.insert(R_sz);
		lights.insert(pos);
		ans.push_back(*(sizes.rbegin()));
	}
	for(int i = 0; i < (int)ans.size() - 1; ++i) cout << ans[i] << ' ';
	cout << ans.back() << endl;
	
	
	
	
	
	return 0;
}