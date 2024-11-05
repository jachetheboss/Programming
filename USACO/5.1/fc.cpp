/*
ID: jamessh3
LANG: C++20
TASK: fc
*/

#include <bits/stdc++.h>
using namespace std;

double getSlope(vector<double>& a, vector<double>& b){
	return 1.0 * (a[1] - b[1]) / (a[0] - b[0]);
}

double getDis(vector<double>& a, vector<double>& b){
    double dx = a[0] - b[0];
    double dy = a[1] - b[1];
    return sqrt(dx * dx + dy * dy);
}

int main()
{
	ifstream fin ("fc.in");
	ofstream fout ("fc.out");
	// input validation edge cases:
	// could there be duplicate points?
	
	int N; fin >> N;
	
	fout << fixed << setprecision(2);
	
	map<double, vector<double>> hm; // key:x-val, value:list of y-vals
	for(int i = 0; i < N; i++){
		double x, y; fin >> x >> y;
		if(not hm.count(x))hm.insert({x, {y, y} });
		hm[x][0] = min(hm[x][0], y);
		hm[x][1] = max(hm[x][1], y);
	}
	if(hm.size() == 0){
		fout << "0.00" << endl;
		fin.close();
		fout.close();
		return 0;
	}
	double ans = 0.0;
	ans += (hm.begin()->second)[1] - (hm.begin()->second)[0];
	ans += (hm.rbegin()->second)[1] - (hm.rbegin()->second)[0];
	// convex hull algo for the top and bottom
	
	vector<vector<double>> points;
	for(auto it = hm.begin(); it != hm.end(); it++){
		double x = it->first;
		double y = (it->second)[1];
		vector<double> point = {x, y};
		if(points.size() <= 1){
			points.push_back(point);
			continue;
		}
		while(points.size() >= 2){
			double prev_slope = getSlope(points[(int)points.size() - 2], points.back());
			double slope = getSlope(points.back(), point);
			if(slope > prev_slope) points.pop_back();
			else break;
		}
		points.push_back(point);
	}
// 	cout << "points" << endl;
// 	for(vector<double>& point : points){
// 		cout << '{' << point[0] << ',' << point[1] << "} ";
// 	}
	for(int i = 1; i < points.size(); i++){
	    ans += getDis(points[i - 1], points[i]);
	}
	
	points.clear();
	for(auto it = hm.begin(); it != hm.end(); it++){
		double x = it->first;
		double y = (it->second)[0];
		vector<double> point = {x, y};
		if(points.size() <= 1){
			points.push_back(point);
			continue;
		}
		while(points.size() >= 2){
			double prev_slope = getSlope(points[(int)points.size() - 2], points.back());
			double slope = getSlope(points.back(), point);
			if(slope < prev_slope) points.pop_back();
			else break;
		}
		points.push_back(point);
	}
	for(int i = 1; i < points.size(); i++){
	    ans += getDis(points[i - 1], points[i]);
	}
	
	fout << ans << endl;
	
	
	fin.close();
	fout.close();
	
	return 0;
}