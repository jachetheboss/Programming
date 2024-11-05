#include <bits/stdc++.h>
using namespace std;

int main()
{
	string inp; cin >> inp;
	// RLE
	int ans = 0;
	int streak = 0;
	char prev = inp[0];
	for(char c : inp){
		if(c == prev) streak++;
		else{
			ans = max(ans, streak);
			streak = 1;
			prev = c;
		}
	}
	ans = max(ans, streak);
		
	cout << ans << endl;
	
	return 0;
}