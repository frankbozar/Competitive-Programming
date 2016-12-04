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

#define MAXN 1000000

vi adj[MAXN][2];
int ccomp, comp[MAXN];
vi st;

void dfs(int n, int c, int dir){
		if (comp[n] != -1) return;
		comp[n] = c;
		FOR(i,0,sz(adj[n][dir]))
				dfs(adj[n][dir][i],c,dir);
		if (!dir) st.push_back(n);
}


void kosaraju(int n) {
		memset(comp,-1,sizeof(comp));
		st.clear();
		FOR(i,0,n) dfs(i,0,0);

		reverse(all(st));
		memset(comp,-1,sizeof(comp));

		ccomp = 0;
		FOR (i,0,sz(st))
				if (comp[st[i]] == -1) dfs(st[i],ccomp++,1);
}


vi cadj[MAXN][2];
vi oadj[MAXN];
map<int,set<int> > nodes;
map<int,vector<pii> > inside;



int p, v[MAXN]; // temp: node colour
int fg; // output: cycle found (0/1)
int od[MAXN]; // output: nodes in order


void dfs(int a) {
		if(v[a]==1) fg = 1;
		if(v[a]) return;
		v[a] = 1; // grey
		FOR(i,0,sz(cadj[a][1])) dfs(cadj[a][1][i]);
		v[a] = 2; // black
		od[p] = a; p--;
}
void topsort(int n) {
		FOR(i,0,n) v[i]=0; //white
		fg=0; p=n-1;
		FOR(i,0,n) if(!v[i]) dfs(i);
}


map<int,int> dp[MAXN];

int lpath[MAXN];

void clpath(int i, set<int> allowed, int d){
	if (d > lpath[i]){
		lpath[i] = d;
	}
	allowed.erase(i);
	FORIT(j,adj[i][0]) if (allowed.count(*j)) clpath(*j,allowed,d+1);
}

int main(){
		int N,M; cin >> N >> M;
		FOR(i,0,N) adj[i][0].clear(), adj[i][1].clear(), cadj[i][0].clear(), cadj[i][1].clear(), oadj[i].clear(), lpath[i] = -1;
		FOR(i,0,M){
				int x,y; cin >> x >> y; x--,y--;
				adj[x][0].push_back(y);
				adj[y][1].push_back(x);
		}

		kosaraju(N);

		// build the contracted graph
		FOR(i,0,N) nodes[comp[i]].insert(i);
		FOR(i,0,N) FORIT(j,adj[i][0]) if (comp[i] == comp[*j]) inside[comp[i]].push_back(make_pair(i,*j));
		else cadj[comp[i]][0].push_back(comp[*j]), cadj[comp[*j]][1].push_back(comp[i]), oadj[comp[*j]].push_back(i);


		topsort(ccomp);

		// run the longest path DP
		
		int maxP = 0;

		FOR(i,0,ccomp) FORIT(s,nodes[i]) {
			//cout << "PROC " << i << " with " << *s << endl;
			FORIT(j,nodes[i]) lpath[*j] = -1;
			clpath(*s,nodes[i],1);
			int lp = 0;
			FORIT(j,adj[*s][1]) if (i != comp[*j]) {
				int oval = dp[comp[*j]][*j];
				//cout << "EDGE " << *s << "<-" << *j << " with " << oval << endl;
				if (oval > lp) lp = oval;
			}

			FORIT(j,nodes[i]) if (dp[i][*j] < lp + lpath[*j]) {
				dp[i][*j] = lp + lpath[*j];
				//cout << "write " << dp[i][*j] << " to " << *j << endl;
				if (dp[i][*j] > maxP) maxP = dp[i][*j];
			}
		}

		cout << maxP << endl;
}



























