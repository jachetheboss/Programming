#include <bits/stdc++.h>
using namespace std;

int main()
{
	int N, M, K; cin >> N >> M >> K;
	vector<int> desire;
	for(int i = 0; i < N; ++i){
		int val; cin >> val;
		desire.push_back(val);
	}
	vector<int> apt;
	for(int i = 0; i < M; ++i){
		int val; cin >> val;
		apt.push_back(val);
	}
	sort(desire.begin(), desire.end());
	sort(apt.begin(), apt.end());
	
	// two pointers greedy
	int i = 0;
	int j = 0;
	int ans = 0;
	while(i < desire.size() and j < apt.size()){
		int mn = desire[i] - K;
		int mx = desire[i] + K;
		if(mn <= apt[j] and apt[j] <= mx){
			ans++;
			i++;
			j++;
		}else if(mn > apt[j]) j++;
		else if(mx < apt[j]) i++;
	}
	cout << ans << endl;
	
	
	return 0;
}