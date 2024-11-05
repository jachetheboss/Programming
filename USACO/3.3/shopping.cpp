/*
ID: jamessh3
LANG: C++20
TASK: shopping
*/

#include <bits/stdc++.h>
using namespace std;

int getKey(vector<int>& counts, string& capacity){
	int key = 0;
	int coeff = 1;
	for(int i = 0; i < counts.size(); ++i){
		int incr = coeff * counts[i];
		key += incr;
		coeff *= (capacity[i] - '0' + 1);
	}
	return key;
}

int rightmostNonzero(string& s, int bound){
	for(int i = bound; i >= 0; --i){
		if(s[i] != '0') return i;
	}
	return -1;
}

void incrementBuilder(string& builder, string& capacity){
	for(int i = (int)builder.length() - 1; i >= 0; --i){
		if(builder[i] == capacity[i]) builder[i] = '0';
		else{
			builder[i]++;
			return;
		}
	}
}

bool comparator(string& builder1, string& builder2){
	string freq1 = string(6, '0');
	string freq2 = string(6, '0');
	for(char count : builder1) freq1[count - '0']++;
	for(char count : builder2) freq2[count - '0']++;
	int bound1 = (int)freq1.length() - 1;
	int bound2 = (int)freq2.length() - 1;
	bool resolved = false;
	while(not resolved){
		int R1 = rightmostNonzero(freq1, bound1);
		int R2 = rightmostNonzero(freq2, bound2);
		
		if(R1 == -1 and R2 == -1) return true;
		
		if(R1 < R2) return true;
		else if(R1 > R2) return false;
		else if(freq1[R1] < freq2[R2]) return true;
		else if(freq1[R1] > freq2[R2]) return false;
		// at this point, R1 == R2 and freq1[R1] == freq2[R2]
		bound1 = R1 - 1;
		bound2 = R2 - 1;
// 		cout << "hello" << endl;
// 		cout << "world" << endl;
        // cout << "R1: " << R1 << " R2: " << R2 << endl;
        // cout << "builder1: " << builder1 << " builder2: " << builder2 << endl;
	}
	return true;
}

int main()
{
	ifstream fin ("shopping.in");
	ofstream fout ("shopping.out");
	
	int S; fin >> S; // # special offers
	vector<vector<int>> specials;
	for(int i = 0; i < S; ++i){
		int n; fin >> n;
		vector<int> special;
		for(int j = 0; j < n; ++j){
			int c, k; fin >> c >> k; // product code, k count	
			special.push_back(c);
			special.push_back(k);
		}
		int p; fin >> p; // price
		special.push_back(p);
		specials.push_back(special);
	}
	int B; fin >> B;
	vector<int> reg_price (1000);
	vector<vector<int>> items;
	for(int i = 0; i < B; ++i){
		int c, k, p; fin >> c >> k >> p; // code, count, regular price
		reg_price[c] = p;
		items.push_back({c, k, p});
	}
	// edge case: no special offers, have to use all regular prices
	int ans = 0;
	for(vector<int>& item : items){
		int k = item[1];
		int p = item[2];
		int incr = k * p;
		ans += incr;
	}
	if(S == 0){
		
		fout << ans << endl;
		
		fin.close();
		fout.close();
		return 0;
	}
	
	string builder = string((int)items.size(), '0');
	vector<string> builders;
	string capacity = "";
	int combos = 1;
	for(vector<int>& item : items){
		int choices = item[1] + 1;
		capacity += '0' + item[1];
		combos *= choices;
	}
	for(int combo = 0; combo < combos; ++combo){
		builders.push_back(builder);
		incrementBuilder(builder, capacity);		
	}
	
// 	cout << "builders.size() " << builders.size() << endl;
	sort(builders.begin(), builders.end(), comparator);
// 	cout << "builders" << endl;
// 	for(string& builder : builders) cout << builder << endl;
// 	cout << endl;
		
	vector<int> DP (builders.size(), INT_MAX);
	DP[0] = 0; // costs nothing to have none of the items
	
	vector<int> idx_of_code (1000, -1);
	for(int i = 0; i < items.size(); ++i){
	    int c = items[i][0];
	    idx_of_code[c] = i;
	}
	
	for(string& builder : builders){
		vector<int> codes;
		vector<int> counts;
		for(int i = 0; i < builder.length(); ++i){
			int c = items[i][0];
			int count = builder[i] - '0';
			codes.push_back(c);
			counts.push_back(count);
		}
		for(vector<int>& special : specials){
			bool ok = true;
			int p = special.back();
			vector<int> rems = counts;
// 			cout << "special.size() " << special.size() << endl;
			for(int j = 0; j < special.size(); j += 2){
				if(j == (int)special.size() - 1){
					p = special[j];
					continue;
				}
				int c = special[j];
				int k = special[j + 1];
				bool found = false; // is this necessary? special deal contains
							// a product code that we don't want?
				// for(int i = 0; i < codes.size(); ++i){
				// 	if(c == codes[i]){
				
				int idx = idx_of_code[c];
				if(idx == -1){
				    ok = false;
				    continue;
				}
				
				int i = idx;
				
						found = true;
						int count = counts[i];
						if(k > count){
							ok = false;
						}
				// 		cout << "count: " << count << " k: " << k << endl;
						//rems.push_back(count - k);
						rems[i] = count - k;
						//break;
				// 	}
				// }
				if(not found) ok = false;
				// if(not ok) break;
			}
			
			if(not ok) continue;
			
// 			cout << "-----SPECIAL-------" << endl;
// 			cout << "p: " << p << endl;
// 			cout << "builder: " << builder << endl;
// 			cout << "capacity: " << capacity << endl;
// 			cout << "rems: " << endl;
// 			for(int x : rems) cout << x << ' ';
// 			cout << endl;
			
			int key = getKey(rems, capacity);
// 			cout << "key: " << key << endl << endl;
			
			if(DP[key] == INT_MAX) ok = false; // that combo not yet created
			if(not ok) continue;
			
			int prev_best = DP[key];
			key = getKey(counts, capacity);
			DP[key] = min(DP[key], prev_best + p);
			
			int still_need = 0;
			for(int i = 0; i < codes.size(); ++i){
				int c = codes[i];
				int price = reg_price[c];
				int k = counts[i];
				still_need += (capacity[i] - '0' - k) * price;
			}
			
// 			cout << "still_need: " << still_need << endl;
			
			int total = DP[key] + still_need;
// 			cout << "total: " << total << endl;
			ans = min(ans, total);
		}
	}
	
	fout << ans << endl;
	
	fin.close();
	fout.close();
	
	// what about do a DP on the special deals, seeing which ones are linear
	// combinations of others?
	// enumerate all combos, then sort them using a custom sorter to put 
	// them in ascending DP-oriented order
	// do DP on all possible combos of items, using special	deals only,
	// then "pad out" the rest with regular prices
	return 0;
}