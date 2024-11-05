#include <bits/stdc++.h>
using namespace std;

bool comparator(vector<int>& v1, vector<int>& v2){
	return v1[1] < v2[1];
}

int main()
{
	int N; cin >> N;
	vector<vector<int>> movies;
	for(int i = 0; i < N; ++i){
		int start; cin >> start;
		int end; cin >> end;
		movies.push_back({start, end});
	}
	// end earliest, greedy, so you can find the next one that starts!
	sort(movies.begin(), movies.end(), comparator);
	int end = 0;
	int ans = 0;
	for(vector<int>& movie : movies){
		int start = movie[0];
		if(start >= end){
			ans++;
			end = movie[1];
		}
	}
	cout << ans << endl;
	
	return 0;
}