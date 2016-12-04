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


struct edge {
	int to, cap, flow, oi;
};

#define MAXN 1000000

vector<edge> e[MAXN];
int aug[MAXN];
int pa[MAXN];

void addEdge(int u, int v, int capUV, int capVU) {
	edge uv, vu;
	uv.to = v;
	uv.cap = capUV;
	uv.flow = 0;
	uv.oi = e[v].size();

	vu.to = u;
	vu.cap = capVU;
	vu.flow = 0;
	vu.oi = e[u].size();

	e[u].push_back(uv);
	e[v].push_back(vu);
}

bool findAugPathEK(int src, int sink, int n) {
	static int qu[MAXN]; // pseudo-queue

	FOR(i,0,n)
		pa[i] = -1;
	aug[src] = oo;

	int start = 0, end = 0;
	qu[end++] = src;
	while (start != end) {
		int u = qu[start++];
		FOR(i,0,sz(e[u])) {
			int v = e[u][i].to;
			int curaug = e[u][i].cap - e[u][i].flow;
			if (pa[v] == -1 && curaug > 0) {
				qu[end++] = v;
				aug[v] = min(aug[u], curaug);
				pa[v] = e[u][i].oi;
				if (v == sink)
					return true;
			}
		}
	}
	return false;
}

int calcMaxFlow(int src, int sink, int n) {
	int ret = 0;
	FOR(i,0,n)
		FOR(j,0,sz(e[i]))
			e[i][j].flow = 0;

	while (findAugPathEK(src, sink, n)) {
		int v = sink;
		while (v != src) {
			e[e[v][pa[v]].to][e[v][pa[v]].oi].flow += aug[sink];
			e[v][pa[v]].flow -= aug[sink];
			v = e[v][pa[v]].to;
		}
		ret += aug[sink];
		if (ret >= oo)
			break;
	}
	return ret;
}


int N,Q,I;
int q[100];
int qs[100];


int qt(int qu, int t){ return 2 + qu + t*(Q+1); }

int down(int t){ return 2 + Q + t*(Q+1); }

int main(){
	cin >> N >> Q >> I;
	FOR(i,0,I) cin >> q[i];
	FOR(i,0,I) q[i]--;
	FOR(i,0,Q) cin >> qs[i];
	int sum = 0;
	FOR(i,0,N){
		// one window
		int cap; cin >> cap;
		addEdge(down(2*i+1),1,cap,0);
		FOR(j,0,I){
			int data; cin >> data; sum += data;
			addEdge(0,qt(q[j],2*i),data,0);
		}
		FOR(j,0,Q) addEdge(qt(j,2*i),qt(j,2*i+1),qs[j],0);
		FOR(j,0,Q) addEdge(qt(j,2*i+1),down(2*i+1),oo,0);
		FOR(j,0,Q) addEdge(qt(j,2*i+1),qt(j,2*(i+1)),oo,0);
	}
	int f = calcMaxFlow(0,1,2 + 2*(Q+1)*(N+1));
	if (f == sum) cout << "possible"; else cout << "impossible";
	cout << endl;
}


















