#include <bits/stdc++.h>
using namespace std;

int main()
{
	int N; cin >> N;
	vector<int> ans;
	vector<int> people (N);
	for(int i = 0; i < N; ++i) people[i] = i + 1;
	
	int start_idx = 1;
	while(people.size() > 0){
		vector<int> next_people;
		if(start_idx == 1) next_people.push_back(people[0]);
		for(int i = start_idx; i < people.size(); i += 2){
			ans.push_back(people[i]);
			if(i != (int)people.size() - 1) next_people.push_back(people[i + 1]);
			if(i == (int)people.size() - 1) start_idx = 1;
			else if(i == (int)people.size() - 2) start_idx = 0;
		}
		people = next_people;
		if(people.size() == 1){
			ans.push_back(people[0]);
			break;
		}
	}
	string s = "";
	for(int person : ans){
		s += to_string(person);
		s += ' ';
	}
	s.pop_back();
	cout << s << endl;
	
	
	
	
	return 0;
}