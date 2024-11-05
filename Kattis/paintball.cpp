#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Paintball II
// You are playing paintball on a 1000 x 1000 square field. A number of your opponents are on the field hiding behind trees 
// at various positions. Each opponent can fire a paintball a certain distance in any direction. Can you cross the field 
// without being hit by a paintball?

// Assume that the southwest corner of the field is at (0, 0) and the northwest corner at (0, 1000).

// Input
// The input consists of a line containing 1 <= n <= 1000, the number of opponents. A line follows for each opponent, containing 
// three integers: the (x, y) location of the opponent (0 <= x, y <= 1000) and its firing range r (1 <= r <= 1000)
 // (
// ). The opponent can hit you with a paintball if you ever pass strictly within firing range (i.e., within distance strictly 
// less than r of the opponent.

// You must enter the field somewhere between the southwest and northwest corner and must leave somewhere between the southeast 
// and northeast corners.

// Output
// If you can complete the trip, output four real numbers with two digits after the decimal place, the coordinates at which you 
// may enter and leave the field, separated by spaces. If you can enter and leave at several places, give the most northerly. 
// If there is no such pair of positions, print a line containing “IMPOSSIBLE”.

// Idea: calculate intersection of circles by deriving math formula. Then use O(N^2) brute force all pairs of circles, 
// or sweep line. Then use union find or connected components of graph

// sample input:
// 3
// 500 500 499
// 0 0 999
// 1000 1000 200

// sample output:
// 0.00 1000.00 1000.00 800.00


int main(){

	int N;
	cin >> N;
	int x;
	int y;
	int r;
	vector<vector<int>> circles;
	for(int i = 0; i < N; ++i){
		cin >> x >> y >> r;
		vector<int> circle;
		circle.push_back(x);
		circle.push_back(y);
		circle.push_back(r);
		circles.push_back(circle);
	}
	for(int i = 0; i < circles.size(); ++i){
		for(int j = 0; j < 3; ++j){
			cout << circles[i][j] << ' ';
		}
		cout << endl;
	}
	// must be strictly inside circle, along circumference is safe.
	// so circles must intersect at TWO points.
	
	// impossible if entire north-south is impenetrable
	// could also be a connection from north side to west side, north side to east, south to west, south to east,
	// or east to west that could affect passing through the field.
	
	
	
	return 0;
}