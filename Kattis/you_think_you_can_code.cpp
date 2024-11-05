#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
	
	int N;
	int t;
	cin >> N >> t;
	
	// Kind of like an ALU operation,
	// t would be the opcode
	
	int val;
	vector<int> v;
	for(int i = 0; i < N; ++i){
		cin >> val;
		v.push_back(val);
	}

	if(t == 1){
		cout << 7 << endl;
		return 0;
	}
	if(t == 2){
		
		if(v[0] < v[1]){
			cout << "Smaller" << endl;
		}else if(v[0] == v[1]){
			cout << "Equal" << endl;
		}else{
			cout << "Bigger" << endl;
		}
		return 0;
	}
	if(t == 3){
		
		sort(v.begin(), v.begin() + 3);
		cout << v[1] << endl;
		return 0;
	}
	
	if(t == 4){
		
		long long sum = 0;
		for(int i = 0; i < v.size(); ++i){
			sum += v[i];
		}
		cout << sum << endl;
		return 0;
	}
	if(t == 5){
		long long sum = 0;
		for(int i = 0; i < v.size(); ++i){
			if(v[i] % 2 == 0){
				sum += v[i];
			}
		}
		cout << sum << endl;
		return 0;
	}
	if(t == 6){
		string S = "";
		char c;
		for(int i = 0; i < v.size(); ++i){
			v[i] %= 26;
			c = 'a' + v[i];
			S += c;
		}
		cout << S << endl;
		return 0;
	}
	if(t == 7){
		
		// TRICKY EDGE CASE:
		if(N == 1){
			if(v[0] == 0){
				cout << "Done" << endl;
			}
			else{
				cout << "Out" << endl;
			}
			return 0;
		}
		
		// at this point we know
		// N >= 2
		
		int i = 0;
		vector<bool> reached (N, false); // track if index has been reached or not, faster than hashing value at index
		
		while(true){
			reached[i] = true;
			if(v[i] < 0 || v[i] >= N){
				cout << "Out" << endl;
				return 0;
			}
			else if(v[i] == N - 1){
				cout << "Done" << endl;
				return 0;
			}
			else if(reached[v[i]] == true){
				cout << "Cyclic" << endl;
				return 0;
			}
			
			i = v[i];
		}
	}
	return 0;
}