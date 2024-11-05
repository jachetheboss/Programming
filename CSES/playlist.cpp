#include <bits/stdc++.h>
#include <ctime>
using namespace std;

int main()
{
    time_t curr = clock();
    
	int N; cin >> N;
	vector<int> v;
	//unordered_set<int> hs;
	set<int> hs;
	for(int i = 0; i < N; ++i){
		int val; cin >> val;
		v.push_back(val);
	}
	int ans = 0;
	int j = 0;
	int i = 0;
	bool searching = true;
	while(j < v.size()){
		if(searching){
			if(hs.count(v[j]) == false){
				hs.insert(v[j]);
				ans = max(ans, (int)hs.size());
				j++;
			}else{
				searching = false;
			}
		}else{
			if(v[i] == v[j]){
				searching = true;
				j++;
				i++;
			}else{
				hs.erase(v[i]);
				i++;
			}
		}
	}
	cout << ans << endl;
	
	//cout << "secs elapsed: " << 1.0 * (clock() - curr) / CLOCKS_PER_SEC << endl;
	
	return 0;
}