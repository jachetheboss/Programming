#include <bits/stdc++.h>
using namespace std;

int main()
{
	int N; cin >> N;
	vector<int> towers;
	for(int i = 0; i < N; ++i){
		int x; cin >> x;
		towers.push_back(x);
	}
	// set?
	// this a USACO silver problem?
	
	// greedy, put tower on previously existing tower that is immediately bigger
	
	multiset<int> ms;
	for(int tower : towers){
		if(ms.size() == 0){
			ms.insert(tower);
			continue;
		}
		if(tower >= *(ms.rbegin())){
			ms.insert(tower);
			continue;
		}
		int next = *(ms.upper_bound(tower));
		ms.erase(ms.find(next));
		ms.insert(tower);
	}
	cout << ms.size() << endl;
	
	
	
	return 0;
}