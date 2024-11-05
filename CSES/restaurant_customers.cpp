#include <bits/stdc++.h>
using namespace std;

int main()
{
	int N; cin >> N;
	vector<vector<int>> events;
	for(int i = 0; i < N; ++i){
		int arrive; cin >> arrive;
		int leave; cin >> leave;
		events.push_back({arrive, 0});
		events.push_back({leave, 1});
	}
	sort(events.begin(), events.end());
	int count = 0;
	int ans = 0;
	for(vector<int>& event : events){
		if(event[1] == 0){
			count++;
			ans = max(ans, count);
		}else{
			count--;
		}
	}
	cout << ans << endl;




	return 0;
}