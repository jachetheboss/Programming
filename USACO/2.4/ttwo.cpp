/*
ID: jamessh3
LANG: C++20
TASK: ttwo
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    // 2 approaches: First approach, more brute force-like, store in memory
    // 4D vector of all possible pairs of locations of farmer and cow, 
    // traverse simultaneously. Boolean if memory is tight, but int should be fine
    // Second approach: Traverse farmer first, figure out the path and then the
    // cycle, then traverse cow, figure out the cycle. See if the paths
    // ever intersect, maybe by using mod? if both are in different cycles without
    // touching same cells, then obviously never intersect. If both cycles share cells,
    // then might intersect, or might not (farmer could be chasing cow, SAME EXACT cycle,
    // but farmer always a step behind, never catches.). Or they reach the same 
    // cell at different times, in the path they take before reaching the cycle.
    // Seems tricky, a lot of scenarios!
	
	// as an alternative to 6D vector, could store location as a single int, a 6-digit int would
	// suffice. Be creative with data compression! 0 0 00 00 
	// mod 100 is farmer location, div 100, then next mod 100 cow location, div 100, then mod 10 farmer
	// direction, div 10, then mod 10 cow direction! Much less memory overhead, but slower due to division.
	
	// instead of division, which is very slow, could instead use 12 bits, which is every less memory!
	// Bitpacking data! Could then use bitwise AND to extract the stored data.
	
	// 11 11 11111111 11111111 bottom 8 bits farmer location, next 8 bits cow location, next 2 bits farmer direction,
	// next 2 bits cow direction. Should use much less memory, can fit into int, and should be faster than division!
    
    ifstream fin ("ttwo.in");
    ofstream fout ("ttwo.out");
    vector<vector<int>> grid (10, vector<int>(10, 0));
    char c;
    int i = 0;
    int j = 0;
    int fx;
    int fy;
    int cx;
    int cy;
    while(fin >> c){
        if(c == '*'){ // obstacle
            grid[i][j] = 1;
        }else if(c == '.'){ // empty
            grid[i][j] = 0;
        }else if(c == 'F'){ // farmer
            grid[i][j] = 2;
            fx = i;
            fy = j;
        }else if(c == 'C'){ // cow
            grid[i][j] = 3;
            cx = i;
            cy = j;
        }
        // c could also be '\n' char
        j += 1;
        if(j == 10){
            j = 0;
            i += 1;
        }
    }
    // for(int i = 0; i < grid.size(); ++i){
    //     for(int j = 0; j < grid[0].size(); ++j){
    //         cout << grid[i][j] << ' ';
    //     }
    //     cout << endl;
    // }
    
    vector<vector<vector<vector<vector<vector<int>>>>>> search (10, vector<vector<vector<vector<vector<int>>>>> (10, vector<vector<vector<vector<int>>>> (4, vector<vector<vector<int>>>())));
    // 6D vector tracking both farmer and cow location
    for(int i = 0; i < 10; ++i){
        for(int j = 0; j < 10; ++j){
            for(int d = 0; d < 4; ++d){ // direction
                vector<vector<vector<int>>> cow_pos (10, vector<vector<int>> (10, vector<int> (4, 0)));
                search[i][j][d] = cow_pos;
            }
        }
    }

    int fd = 0; // direction 0 north 1 east 2 south 3 west
    int cd = 0;
    int t = 0;
    bool found = false;
    vector<int> coor = {fx, fy, fd, cx, cy, cd};
    while(true){
        search[coor[0]][coor[1]][coor[2]][coor[3]][coor[4]][coor[5]] = 1;
        for(int i = 0; i <= 3; i += 3){
            int x = coor[i];
            int y = coor[i + 1];
            int d = coor[i + 2];
            if((d == 0 && x == 0) || (d == 1 && y == 9) || (d == 2 && x == 9) || (d == 3 && y == 0)){
                // out of bounds
                d += 1; // rotate direction
                d %= 4;
            }else{
                if((d == 0 && grid[x - 1][y] == 1) || (d == 1 && grid[x][y + 1] == 1) || (d == 2 && grid[x + 1][y] == 1) || (d == 3 && grid[x][y - 1] == 1)){
                    d += 1;
                    d %= 4;
                }else{
                    if(d == 0){
                        x -= 1;
                    }else if(d == 1){
                        y += 1;
                    }else if(d == 2){
                        x += 1;
                    }else if(d == 3){
                        y -= 1;
                    }
                }
            }
            coor[i] = x;
            coor[i + 1] = y;
            coor[i + 2] = d;
        }
        
        t += 1; // increment time;
        
        if(coor[0] == coor[3] && coor[1] == coor[4]){ // farmer and cow in same cell
            found = true;
            break;
        }
        else if(search[coor[0]][coor[1]][coor[2]][coor[3]][coor[4]][coor[5]] == 1){
            break;
        }
    }
    
    if(not found){
        fout << 0;
    }else{
        fout << t;
    }
    fout << endl;
    
    fin.close();
    fout.close();
    
    return 0;
}
