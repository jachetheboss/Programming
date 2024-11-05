#include <bits/stdc++.h>
using namespace std;

int main()
{
	long long N; cin >> N;
	vector<long long> ans;
	while(true){
		ans.push_back(N);
		
		if(N == 1) break;
		
		if(N % 2 == 0) N /= 2;
		else N = 3 * N + 1;
	}
	for(int i = 0; i < (int)ans.size() - 1; ++i) cout << ans[i] << ' ';
	cout << ans.back() << endl;

	return 0;
}