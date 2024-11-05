#include <bits/stdc++.h>
using namespace std;

int main()
{
	int N; cin >> N;
	vector<int> next (N + 1, -1);
	for(int i = 1; i <= N; ++i){
		int j; cin >> j;
		next[i] = j;
	}
	




	return 0;
}