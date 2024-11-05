
using namespace std;

// change to long long, should make it faster. Can write all Pythagorean triples up to a certain 
// size to file, then read in file

// Function to increment the builder
void incrementBuilder(vector<int>& builder, const vector<int>& capacity);
// Function to factorize a number
vector<int> factorize(int num);

// Retrieve factorization from precomputed data
vector<int>& getFactorization(int num, vector<vector<int>>& factorizations);

vector<vector<int>> generatePythagoreanTriples(int max_base1, int max_base2);