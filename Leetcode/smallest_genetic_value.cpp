#include <bits/stdc++.h>
#include <ctime>

using namespace std;


class Solution {
public:
    
    void printSubtrees(vector<vector<vector<int>>>& subtrees){
        cout << "subtrees" << endl;
        for(int node = 0; node < subtrees.size(); ++node){
            cout << "node: " << node << endl;
            vector<vector<int>>& subtree = subtrees[node];
            cout << "{";
            for(vector<int>& decomp : subtree){
                cout << "{" << endl;
                for(int value : decomp) cout << value << ' ';
                cout << "} ";
            }
            cout << "}" << endl;
        }
        cout << endl;
    }
    void findMissing(bool& missing_found, int& missing, vector<vector<int>>& subtree, int block_sz, int last_block_sz, int n){
        for(int block = 0; block < subtree.size(); ++block){
            int sz = subtree[block].size();
            int full_sz = block_sz;
            if(block == (int)subtree.size() - 1){
                full_sz = last_block_sz;
            }
            if(sz < full_sz){
                int L = block * block_sz + 1;
                int R = min(n, L + block_sz - 1);

                if(subtree[block].size() == 0){
                    missing_found = true;
                    missing = L;
                    return;
                }
                else{
                    if(subtree[block][0] != L){
                        missing_found = true;
                        missing = L;
                        return;
                    }
                    else{
                        for(int i = 0; i < (int)subtree[block].size() - 1; ++i){
                            if(subtree[block][i + 1] - subtree[block][i] > 1){
                                missing_found = true;
                                missing = subtree[block][i] + 1;
                                return;
                            }
                        }if(not missing_found){
                            missing_found = true;
                            missing = subtree[block].back() + 1;
                            return;
                        }
                    }
                }
            } 
        }
    }
    void mergeSubtrees(int node, int value, int block_num, vector<vector<int>>& tree, vector<vector<int>>& subtree, vector<vector<vector<int>>>& subtrees){
        
        // cout << "enter mergeSubtrees" << endl;
        
        for(int block = 0; block < subtree.size(); ++block){
            vector<int> decomp;
            priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
            
            // cout << "mergeSubtrees node: " << node << endl;
            // cout << "tree.size() " << tree.size() << endl;
            
            for(int child : tree[node]){
                
                // cout << "child: " << child << endl;
                // cout << "subtrees.size() " << subtrees.size() << endl;
                // cout << "block: " << block << endl;
                // cout << "subtrees[" << child << "].size() " << subtrees[child].size() << endl;
                
                if(subtrees[child][block].size() > 0)
                    pq.push( {subtrees[child][block][0], child, 0} );
            }
            
            // cout << "mergeSubtrees check1" << endl;
            
            while(pq.size() > 0){
                int smallest = pq.top()[0]; // smallest genetic value
                int child = pq.top()[1];
                int j = pq.top()[2];
                
                pq.pop();
                
                decomp.push_back(smallest);
                
                if(j < (int)subtrees[child][block].size() - 1){
                    pq.push( {subtrees[child][block][j + 1], child, j + 1} );
                }
            }
            
            // cout << "mergeSubtrees check2" << endl;
            
            if(block == block_num){ // insert node's genetic value into the decomp
                if(decomp.size() == 0) decomp.push_back(value);
                else if(value > decomp.back()) decomp.push_back(value);
                else if(value < decomp[0]) decomp.insert(decomp.begin(), value);
                else{
                    for(int i = 0; i < (int)decomp.size() - 1; ++i){
                        if(decomp[i] < value and value < decomp[i + 1]){
                            decomp.insert(decomp.begin() + i + 1, value);
                            break;
                        }
                    }
                }
            }
            subtree[block] = decomp;
        }
        subtrees[node] = subtree;
        
        // cout << "exit mergeSubtrees" << endl;
    }
    
    // made it recursive code
    void DFS(int node, vector<vector<int>>& tree, vector<vector<vector<int>>>& subtrees, vector<int>& nums, vector<int>& parents, vector<int>& ans, int num_blocks, int block_sz, int last_block_sz){
        // while(searched[root] == 0){ // dis shit up to O(n^2), but easy to code, try writing it recursive as well
            
            // cout << "DFS node: " << node << endl;
            
            // printSubtrees(subtrees);
            
            int n = parents.size();
        
            for(int child : tree[node]){
                DFS(child, tree, subtrees, nums, parents, ans, num_blocks, block_sz, last_block_sz);
            }
        
            // bool deadend = true;
            // for(int child : tree[node]){
            //     if(searched[child] == 0){
            //         node = child;
            //         deadend = false;
            //         break;
            //     }
            // }
            // if(deadend){
                // searched[node] = 1;
                // build the sqrt decomp of the descendants
                vector<vector<int>> subtree (num_blocks);
                int block_num = (nums[node] - 1) / block_sz; // my scheme is 0-indexed
                mergeSubtrees(node, nums[node], block_num, tree, subtree, subtrees);
                
                // finally find the smallest missing!
                bool missing_found = false;
                int missing = -1;
                findMissing(missing_found, missing, subtree, block_sz, last_block_sz, n);
                
                if(missing_found) ans[node] = missing;
                else ans[node] = n + 1;
                
                for(int child : tree[node]){ // free up memory!
                    subtrees[child].clear();
                }
                
                // node = parents[node];
            // }
        // }
    }
    
    
    vector<int> smallestMissingValueSubtree(vector<int>& parents, vector<int>& nums) {
        // some type of sqrt decomp, dfs leaf-up DP
        // remember to delete descendant lists of nodes that are fully searched, to avoid
        // MLE/TLE
        
        int n = parents.size();
        
        vector<int> ans (n, -1);
        
        vector<vector<int>> tree (n); // adj list of parent to child edges, does not contain child to parent edges
        for(int i = 0; i < n; ++i){
            int parent = parents[i];
            if(parent != -1){
                tree[parent].push_back(i);
            }
        }
        int root = 0;
        vector<vector<vector<int>>> subtrees (n);
        int node = root;
        vector<int> searched (n, 0);
        
        int max_val = 0;
        for(int val : nums) max_val = max(max_val, val);
        
        int block_sz = (int)floor(sqrt(max_val));
        int num_blocks = max_val / block_sz;
        int last_block_sz = block_sz;
        if(n % block_sz != 0){
            num_blocks++;
            last_block_sz = max_val % block_sz;   
        }
        
        // cout << "check1" << endl;
        DFS(root, tree, subtrees, nums, parents, ans, num_blocks, block_sz, last_block_sz);
        
        return ans;
    }
};


void parseInput(vector<int>& parents, vector<int>& nums, ifstream& fin){
	string s = "";
	getline(fin, s);
	string num = "";
	for(char c : s){
		if(c != ',' and c != '[' and c != ']') num += c;
		else if(num != ""){
			//cout << "num: " << num << endl;
			parents.push_back(stoi(num));
			num = "";
		}
	}
	s = "";
	getline(fin, s);
	num = "";
	for(char c : s){
		if(c != ',' and c != '[' and c != ']') num += c;
		else if(num != ""){
			//cout << "num: " << num << endl;
			nums.push_back(stoi(num));
			num = "";
		}
	}
}


int main()
{
	ifstream fin ("smallest_genetic_value_input.txt");

	vector<int> parents;
	vector<int> nums;
	parseInput(parents, nums, fin);
	
	Solution* sol = new Solution();
	
	time_t curr = clock();
	
	vector<int> ans = sol->smallestMissingValueSubtree(parents, nums);
	
	cout << "elapsed secs: " << 1.0 * (clock() - curr) / CLOCKS_PER_SEC << endl;
	
	cout << "ans:" << endl;
	for(int x : ans) cout << x << ' ';
	cout << endl;
	

	fin.close();
	return 0;
}
