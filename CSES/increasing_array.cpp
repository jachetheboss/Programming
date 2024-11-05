#include <bits/stdc++.h>
using namespace std;

int main()
{
	int N; cin >> N;
	int prev;
	long long ans = 0;
	for(int i = 0; i < N; ++i){
		int val; cin >> val;
		if(i == 0) prev = val;
		else{
			if(val < prev) ans += prev - val;
			prev = max(prev, val);
		}
	}
	cout << ans << endl;

	return 0;
}