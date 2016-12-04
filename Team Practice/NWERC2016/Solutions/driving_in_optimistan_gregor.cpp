// 
// 
#include <list>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cfloat>
#include <climits>
#include <numeric>
#include <iomanip>

using namespace std;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const double PI = 2.0 * acos(0.0);


typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<string> vs;

#define sz(c) int((c).size())
#define all(c) (c).begin(), (c).end()
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FORS(i,a,b,s) for (int i = (a); i < (b); i=i+(s))
#define FORD(i,a,b) for (int i = int(b)-1; i >= (a); i--)
#define FORIT(i,c) for (__typeof__((c).begin()) i = (c).begin(); i != (c).end(); i++)

int dst[2000][2000];
int N;


double sts[2000];
vi adj[2000];
vector<ll> d[2000];


// returns number of nodes
void reconstruct(vi nodes){
	if (sz(nodes) < 2) return;
	// take two nodes
	int x = nodes[0];
	int y = nodes[1];
	
	map<int,vector<pii> > subtrees;

	// build node groups	
	FORIT(i,nodes){
		int perpen = (dst[x][*i] + dst[*i][y] - dst[x][y]) / 2;
		subtrees[dst[x][*i] - perpen].push_back(make_pair(*i,perpen));
	}
	
	// insert root node if necessary and build distances
	int last = 0;
	int prev = x;
	FORIT(tree,subtrees){
		int root = -1;
		FORIT(i,tree->second) if (!i->second) {root = i->first; break;}
		// add root
		if (root == -1) {
			FORIT(i,tree->second) dst[N][i->first] = dst[i->first][N] = i->second;
			root = N++;
		}

		vector<int> st;
		st.push_back(root);
		FORIT(i,tree->second) if (i->first != root) st.push_back(i->first);
		
		reconstruct(st);
		
		int length = tree->first - last;
		if (prev != root){
			adj[prev].push_back(root);
			d[prev].push_back(length);
		}
		prev = root;
		last = tree->first;
	}
	
	return;
}

ll calSTS(int x){
	double & v = sts[x] = 1;
	FOR(i,0,sz(adj[x]))
		v += calSTS(adj[x][i]) + d[x][i] - 1;
	return v;
}

double calculate(int x){
	double res = 0;
	FOR(i,0,sz(adj[x])){
		double above = sts[0] - sts[adj[x][i]] - d[x][i] + 1;
		double below = sts[adj[x][i]];
		
		res += above*below*d[x][i]  +  (above+below)*d[x][i]*(d[x][i]-1)/2  +  double(d[x][i])*(d[x][i]-1)*(d[x][i]-2)/6;
		res += calculate(adj[x][i]);
	}
	
	return res;
}


int main(){
	cin >> N;
	FOR(i,0,N) dst[i][i] = 0;
	FOR(i,0,N) FOR(j,i+1,N) cin >> dst[i][j], dst[j][i] = dst[i][j];
	
	vi allNodes;
	FOR(i,0,N) allNodes.push_back(i);
	
	reconstruct(allNodes);
	calSTS(0);

	long double ans = calculate(0);
	
	cout << fixed << setprecision(15) << 2 * ans / (sts[0]*(sts[0]-1))  << endl;
}













