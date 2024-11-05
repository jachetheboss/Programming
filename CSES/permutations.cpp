#include <bits/stdc++.h>
using namespace std;

int main()
{
	int N; cin >> N;
	if(N == 1){
		cout << 1 << endl;
		return 0;
	}
	else if(N == 2 or N == 3){
		cout << "NO SOLUTION" << endl;
		return 0;
	}
	vector<int> ans;
	for(int i = 2; i <= N; i += 2) ans.push_back(i);
	for(int i = 1; i <= N; i += 2) ans.push_back(i);
	for(int i = 1; i < ans.size(); ++i) cout << ans[i - 1] << ' ';
	cout << ans.back();

	return 0;
}