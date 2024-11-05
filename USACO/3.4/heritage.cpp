/*
ID: jamessh3
LANG: C++20
TASK: heritage
*/

#include <bits/stdc++.h>
using namespace std;

// change ints to chars? cout << intType vs cout << charType has different graphical
// output behavior!

string getPostorder(vector<vector<char>>& tree, char root){
	vector<char> stk = {root};
	char node = root;
	string postorder = "";
	unordered_map<char, int> color;
	while(color.count(root) == false or color[root] != 2){
		if(tree[node][0] != -1 and color.count(tree[node][0]) == false){
			node = tree[node][0];
			stk.push_back(node);
			continue;
		}if(tree[node][1] != -1 and color.count(tree[node][1]) == false){
			node = tree[node][1];
			stk.push_back(node);
			continue;
		}else{
			color.insert({node, 2});
			postorder += node;
			stk.pop_back();
			if(stk.size() > 0) node = stk.back();
		}
	}
	return postorder;
}

vector<char> getPath(vector<vector<char>>& tree, char root, char target_node){
	if(target_node == root) return {root};
	vector<char> stk = {root};
	unordered_set<char> searched;
	char node = root;
	while(searched.count(root) == false){
		if(tree[node][0] != -1 and searched.count(tree[node][0]) == false){
			node = tree[node][0];
			stk.push_back(node);
			if(node == target_node) return stk;
		}
		else if(tree[node][1] != -1 and searched.count(tree[node][1]) == false){
			node = tree[node][1];
			stk.push_back(node);
			if(node == target_node) return stk;
		}
		else{
			searched.insert(node);
			stk.pop_back();
			if(stk.size() > 0) node = stk.back();
		}		
	}
	return {};
}

char LCA(vector<vector<char>>& tree, char root, char node1, char node2){
	
	if(node1 == node2) return node1;
		
	vector<char> path1 = getPath(tree, root, node1);
	vector<char> path2 = getPath(tree, root, node2);
	for(int i = 0; i < min((int)path1.size(), (int)path2.size()); ++i){
		if(path1[i] == path2[i] and (i + 1 >= path1.size() or i + 1 >= path2.size() or path1[i + 1] != path2[i + 1])){
			return path1[i];
		}
	}
	return root;
}

int main()
{
	ifstream fin ("heritage.in");
	ofstream fout ("heritage.out");
	
	string inorder; fin >> inorder;
	string preorder; fin >> preorder;
	
	vector<int> order (123, -1);
	for(int i = 0; i < inorder.length(); ++i) order[inorder[i]] = i;
	
	char root = preorder[0];
	vector<vector<char>> tree (123, vector<char> (2, -1));
	//vector<int> so_far = {root};
	map<int, char> cand_parent; // key is rank of candidate parent, key is parent node
	map<int, char>::iterator it;
	cand_parent.insert({order[root], root});
	for(int i = 1; i < preorder.length(); ++i){
		char node = preorder[i];
		// find the nodes that are closest to node, bigger and smaller
		// update tree afterwards
		int rank = order[node];
		if(rank > (cand_parent.rbegin())->first){
			char parent = (cand_parent.rbegin())->second;
			tree[parent][1] = node;
			int parent_rank = (cand_parent.rbegin())->first;
			cand_parent.erase(parent_rank);
			cand_parent.insert({rank, node});
			
		}else if(rank < (cand_parent.begin())->first){
			char parent = (cand_parent.begin())->second;
			tree[parent][0] = node;
			cand_parent.insert({rank, node});
		}else{
			// two options now, based on LCA
			// rank1 < rank2
			int rank1 = (prev(cand_parent.upper_bound(rank)))->first;
			int rank2 = (cand_parent.upper_bound(rank))->first;
// 			cout << "rank1: " << rank1 << " rank2: " << rank2 << endl;
			char parent1 = cand_parent[rank1];
			char parent2 = cand_parent[rank2];
			char lca = LCA(tree, root, parent1, parent2);
			
// 			cout << "parent1: " << parent1 << " parent2: " << parent2 << " lca: " << lca << endl;
			
			int lca_rank = order[lca];
			if(rank > lca_rank){
				tree[parent2][0] = node;
				cand_parent.insert({rank, node});
				
			}else{ // rank < lca_rank
				tree[parent1][1] = node;
				cand_parent.insert({rank, node});
				cand_parent.erase(rank1);
			}
		}
	}
	
// 	cout << "tree" << endl;
// 	for(int i = 0; i < tree.size(); ++i){
// 	    vector<char>& children = tree[i];
// 		if(children[0] != -1 or children[1] != -1){
// 		    char parent = i;
// 		    cout << parent << endl;
// 		    cout << "{" << children[0] << ',' << children[1] << "} " << endl;
// 		}
// 	}
// 	cout << endl;
	
	string ans = getPostorder(tree, root);
	fout << ans << endl;
	
	fin.close();
	fout.close();

	return 0;
}