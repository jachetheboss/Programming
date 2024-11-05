#include <bits/stdc++.h>
using namespace std;

int main()
{
	int N; cin >> N;
	vector<long long> v;
	for(int i = 0; i < N; ++i){
		int val; cin >> val;
		v.push_back(val);
	}
	// divide and conquer, Kadane slight
	long long ans = v[0];
	vector<long long> best_prefix;
	vector<long long> best_suffix;
	vector<long long> subsums;
	for(long long val : v){
		ans = max(ans, val);
		best_prefix.push_back(val);
		best_suffix.push_back(val);
		subsums.push_back(val);
	}
	int sz = 1;
	while(sz < N){
		vector<long long> next_best_prefix;
		vector<long long> next_best_suffix;
		vector<long long> next_subsums;
		for(int i = 0; i < best_prefix.size(); i += 2){
			if(i != (int)best_prefix.size() - 1){
				long long subsum = best_suffix[i] + best_prefix[i + 1];
				ans = max(ans, subsum);
				ans = max(ans, best_prefix[i + 1]);
				ans = max(ans, best_suffix[i + 1]);
				next_subsums.push_back(subsums[i] + subsums[i + 1]);
				next_best_prefix.push_back(max(best_prefix[i], subsums[i] + best_prefix[i + 1]));
				next_best_suffix.push_back(max(best_suffix[i + 1], subsums[i + 1] + best_suffix[i]));
			}else{
				next_subsums.push_back(subsums[i]);
				next_best_prefix.push_back(best_prefix[i]);
				next_best_suffix.push_back(best_suffix[i]);
			}
			ans = max(ans, best_prefix[i]);
			ans = max(ans, best_suffix[i]);
		}
		subsums = next_subsums;
		best_prefix = next_best_prefix;
		best_suffix = next_best_suffix;
		
		sz *= 2;
	}
	cout << ans << endl;
	
	return 0;
}