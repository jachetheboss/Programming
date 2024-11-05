#include <bits/stdc++.h>
using namespace std;

int main()
{
	int N; cin >> N;
	long long sum = 0;
	for(int i = 0; i < N - 1; ++i){
		int val; cin >> val;
		sum += val;
	}
	long long full = N;
	full *= (N + 1);
	full /= 2;
	
	long long ans = full - sum;
	cout << ans << endl;
	
	return 0;
}