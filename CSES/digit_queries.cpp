
#include <bits/stdc++.h>
using namespace std;

int main()
{
	int N; cin >> N;
	vector<int> ans;
	vector<long long> prefix = {9};
	int num_len = 2;
	long long pow10 = 10;
	while(true){
		prefix.push_back(prefix.back() + pow10 * num_len * 9);
		if(prefix.back() > 1000000000000000000L) break;
		pow10 *= 10;
		num_len++;
	}
	for(int i = 0; i < N; ++i){
		long long q; cin >> q;
		if(q <= 9){
			ans.push_back(q);
			continue;
		}
		int idx = -1;
		for(int j = 0; j < (int)prefix.size() - 1; ++j){
			if(q > prefix[j] and q <= prefix[j + 1]){
				idx = j;
				break;
			}
		}
		long long diff = q - prefix[idx];
		num_len = idx + 2;
		long long quo = diff / num_len;
		int rem = diff % num_len;
		long long num = (long long)pow(10, num_len - 1) + quo;
		int d = -1;
		if(rem == 0){
			num--;
			d = num % 10;
		}else{
			string s = to_string(num);
			d = s[rem - 1] - '0';	
		}
		ans.push_back(d);
	}
	
	for(int val : ans) cout << val << endl;

	return 0;
}