/*
ID: jamessh3
LANG: C++20
TASK: job
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
	// is this problem supposed to be some sort of network flow?
	
	ifstream fin ("job.in");
	ofstream fout ("job.out");
	
	int N, M1, M2; fin >> N >> M1 >> M2;
	vector<int> machines1;
	vector<int> machines2;
	for(int i = 0; i < M1; ++i){
		int t; fin >> t;
		machines1.push_back(t);
	}for(int i = 0; i < M2; ++i){
		int t; fin >> t;
		machines2.push_back(t);
	}
	
	// DP? greedy?
	
	// try all pairs of mac1, mac2 for each task?
	// shortest path in disguise?
	
	// greedy, probably doesn't have to be network flow algo
	// the earliest a machine is available, put task through the 
	// fastest-finishing machine that is available 
	// sort by "events", event is when a machine becomes available (when all machines 
	// are filled), mark the event as "A available" or "B available", decrementing the
	// remaining tasks that are to be completed for stage A/B
	
	/*
	int jobs1_ready = N;
	int jobs1_done = 0;
	int jobs2_ready = 0;
	int jobs2_done = 0;
	//priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> ready1;
	priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> ready1;
	for(int mac = 0; mac < M1; ++mac){
		int t = machines1[mac];
		ready1.push( {0, t} );
	}
	priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> ready2;
	for(int mac = 0; mac < M2; ++mac){
		int t = machines2[mac];
		ready2.push( {0, t} );
	}
	int done_time1 = 0;
	int done_time2 = 0;
	//priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> ready2;
	// should put time t = 0 all machines1 ready and all machines2 ready at the beginning?
	// keep two separate queues: machines1 ready and machines2 ready 
	/*
	int t = 0;
	while(jobs1_done < N or jobs2_done < N){
		if(jobs1_done < N){
			int rt = ready1.top()[0]; // ready time
			if(t < rt){ // wait for a machine1 to open up
				int dur = ready1.top()[1];
				jobs1_done++;
				jobs2_ready++;
				ready1.pop();
				ready1.push( {rt + dur, dur} );
				
				// check if finished job1 can be immediately transfered to a machine2
				// if a machine2 is available
			}
		}else{
			// only waiting for machines2
			int rt2 = ready2.top()[0];
			int dur = ready2.top()[1];
			done_time2 = max(done_time2, rt2 + dur);
			ready2.pop();
			ready2.push( {rt2 + dur, dur} );
			jobs2_done++;
		}
	}
	for(int i = 0; i < N; ++i){
		int rt1 = ready1.top()[0];
		int dur = ready1.top()[1];
		done_time1 = max(done_time1, rt1 + dur);
		ready1.pop();
		ready1.push( {rt1 + dur, dur} );
		int rt2 = ready2.top()[0];
		dur = ready2.top()[1];
		int rt = max(rt1, rt2);
		done_time2 = max(done_time2, rt + dur);
		ready2.pop();
		ready2.push( {rt + dur, dur} );
	}
	fout << done_time1 << ' ' << done_time2 << endl;
	*/
	
	//map<int, int> ready1;
	priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> ready1;
	//vector<vector<int>> next_ready1 (machines1.size(), 0);
	for(int t : machines1) ready1.push({t, t}); // {when next available, dur}
	vector<int> done1; // times of job completion
	for(int i = 0; i < N; ++i){
		int earliest = ready1.top()[0];
		int dur = ready1.top()[1];
		done1.push_back(earliest);
		ready1.pop();
		ready1.push( {earliest + dur, dur} );
		//int done_time = earliest + dur;
		//int earliest_finish = INT_MAX;
		//for(int j = 0; j < next_ready1.size(); ++j){
		//	if(
		//}
	}
	// DP
	//vector<vector<vector<int>>> DP (N, vector<vector<int>> (machines2.size(), v
	/*
	vector<vector<vector<int>>> DP (N + 1, vector<vector<int>> (machines2.size(), vector<int> (machines2.size(), INT_MAX)));
	for(int j = 0; j < DP[0].size(); ++j) DP[0][j] = vector<int> (machines2.size(), 0);
	for(int i = 1; i < DP.size(); ++i){ // for each task
	    int t = done1[i - 1];
		for(int j = 0; j < machines2.size(); ++j){ // for each mac2
			int dur = machines2[j];
			vector<int> sorted = DP[i][j];
			sort(sorted.begin(), sorted.end(), greater<int>() );
			for(int k = 0; k < machines2.size(); ++k){ // machine used for previous task
				vector<int> v = DP[i - 1][k];
				v[j] = max(v[j], t);
				v[j] += dur;
				sort(v.begin(), v.end(), greater<int>() );
				
				if(v < sorted){
					DP[i][j] = DP[i - 1][k];
					DP[i][j][j] = max(DP[i][j][j], t);
					DP[i][j][j] += dur;
					sorted = DP[i][j];
					sort(sorted.begin(), sorted.end(), greater<int>() );
				}
			}
		}
	}
	*/
	/*
	// prioritize minimizing each task ready time, for each machine used for each task?
	vector<vector<vector<int>>> DP (N + 1, vector<vector<int>> (machines2.size(), vector<int> (machines2.size(), INT_MAX)));
	for(int j = 0; j < DP[0].size(); ++j) DP[0][j] = vector<int> (machines2.size(), 0);
	for(int i = 1; i < DP.size(); ++i){ // for each task
	    int t = done1[i - 1];
		for(int j = 0; j < machines2.size(); ++j){ // for each mac2
			int dur = machines2[j];
			vector<int> sorted = DP[i][j];
			sort(sorted.begin(), sorted.end(), greater<int>() );
			for(int k = 0; k < machines2.size(); ++k){ // machine used for previous task
				vector<int> v = DP[i - 1][k];
				v[j] = max(v[j], t);
				v[j] += dur;
				sort(v.begin(), v.end(), greater<int>() );
				
				if(v < sorted){
					DP[i][j] = DP[i - 1][k];
					DP[i][j][j] = max(DP[i][j][j], t);
					DP[i][j][j] += dur;
					sorted = DP[i][j];
					sort(sorted.begin(), sorted.end(), greater<int>() );
				}
			}
		}
	}
	
	int done2_time = INT_MAX;
	for(int j = 0; j < DP.back().size(); ++j){
		int mx = 0;
		for(int k = 0; k < DP.back()[j].size(); ++k) mx = max(mx, DP.back()[j][k]);
		done2_time = min(done2_time, mx);
	}
	*/
	
	// how about backwards DP, in the reverse direction? rather than front to back, we 
	// go back to front!
	// modify this DP so that it goes in the reverse dir 
	/*
	vector<vector<vector<int>>> DP (N + 1, vector<vector<int>> (machines2.size(), vector<int> (machines2.size(), INT_MAX)));
	for(int j = 0; j < DP[0].size(); ++j) DP[0][j] = vector<int> (machines2.size(), 0);
	for(int i = 1; i < DP.size(); ++i){ // for each task
	    int t = done1[i - 1];
		for(int j = 0; j < machines2.size(); ++j){ // for each mac2
			int dur = machines2[j];
			vector<int> sorted = DP[i][j];
			sort(sorted.begin(), sorted.end(), greater<int>() );
			for(int k = 0; k < machines2.size(); ++k){ // machine used for previous task
				vector<int> v = DP[i - 1][k];
				v[j] = max(v[j], t);
				v[j] += dur;
				sort(v.begin(), v.end(), greater<int>() );
				
				if(v < sorted){
					DP[i][j] = DP[i - 1][k];
					DP[i][j][j] = max(DP[i][j][j], t);
					DP[i][j][j] += dur;
					sorted = DP[i][j];
					sort(sorted.begin(), sorted.end(), greater<int>() );
				}
			}
		}
	}
	*/
	
	// or backwards greedy, prioritize using the quickest machines for the
	// last-finishing stage A task 
	// (try using all machines for the latest finishing stage A task, at all 
	// time gaps (try starting immediately after finishing, 1 quanta after finishing,
	// 2 quanta, 2*10^4 quanta, etc.) Try this for all machines
	
	// use whatever extends the latest mac2 finish time the least
	
    cout << "check1" << endl;
	
	sort(machines2.begin(), machines2.end());
	vector<vector<int>> starts (machines2.size());
	//vector<int> machine_max_t (machines2.size(), 0);
	int done2_time = done1.back();
	for(int i = (int)done1.size() - 1; i >= 0; --i){
		int t = done1[i]; // the time the task exists stage A 
		//bool ok = false;
		int choose = -1; // chosen machine
		bool must_push_back = true; // do we have to push done2_time back?
		for(int j = 0; j < starts.size(); ++j){
			int dur = machines2[j];
			if(starts[j].size() == 0){ // haven't used this particular type B machine yet
				int finish = t + dur;
				if(finish <= done2_time){ // is this sound?
					choose = j;
					must_push_back = false;
				}
			}
			else{
				int finish = t + dur;
				int k = (int)starts[j].size() - 1;
				while(k >= 0 and finish > starts[j][k]){
					finish += dur;
					k--;
				}
				if(k != -1){
					must_push_back = false;
					choose = j;
				}
			}
			if(not must_push_back) break;
		}
		if(must_push_back){ // choose the mac2 such that done2_time is pushed back
							// the minimum amount
			int min_finish = INT_MAX;
			for(int j = 0; j < starts.size(); ++j){
				int dur = machines2[j];
				if(starts[j].size() == 0){
					int finish = t + dur;
					if(finish < min_finish){
						min_finish = finish;
						choose = j;
					}
				}else{
					int finish = t + dur;
					int k = (int)starts[j].size() - 1;
					while(k >= 0 and finish > starts[j][k]){
						finish += dur;
						k--;
					}
					if(finish < min_finish){
						min_finish = finish;
						choose = j;
					}
				}
			}
		}
		
		int dur = machines2[choose];
		if(starts[choose].size() == 0){
			starts[choose].push_back(t);
		}else{
			int finish = t + dur;
			while(starts[choose].size() > 0 and finish > starts[choose].back()){
				finish += dur;
				starts[choose].pop_back();
			}
			int start = finish - dur;
			while(start >= t){
				starts[choose].push_back(start);
				start -= dur;
			}
		}
		done2_time = max(done2_time, starts[choose][0] + dur);
		
		//if(not ok){
		//}
	}
	
	cout << done1.back() << ' ' << done2_time << endl;
	
	fout << done1.back() << ' ' << done2_time << endl;
	
	return 0;
}