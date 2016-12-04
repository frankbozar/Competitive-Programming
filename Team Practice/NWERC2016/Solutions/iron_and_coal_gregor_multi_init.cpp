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

const int oo = 0x3f3f3f;
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



int N,M,K;

vi adj[200000];
vi badj[200000];

int d0[200000];
int d1[200000];
int d2[200000];


void bfs(vi* a, vi s, int* d){
	FOR(i,0,N+2) d[i] = oo;
	FORIT(i,s) d[*i] = 0;
	queue<pii> q;
	FORIT(i,s) q.push(make_pair(*i,0));

	while (sz(q)){
		int n = q.front().first;
		int dst = q.front().second;
		q.pop();

		FORIT(i,a[n]) if (d[*i] == oo){
			d[*i] = dst + 1;
			q.push(make_pair(*i,d[*i]));
		}
	}
}


void add(int a,int b){
	adj[a].push_back(b);
	badj[b].push_back(a);
}

int main(){
	cin >> N >> M >> K;
	vi a,b,c;
	c.push_back(0);
	FOR(i,0,M){
		int m; cin >> m;
		a.push_back(m-1);
	}
	FOR(i,0,K){
		int k; cin >> k;
		b.push_back(k-1);
	}

	FOR(i,0,N){
		int n; cin >> n;
		FOR(j,0,n){
			int a; cin >> a;
			add(i,a-1);
		}
	}

	bfs(badj,a,d0);
	bfs(badj,b,d1);
	bfs(adj,c,d2);


	//FOR(i,0,N+2) cout << d0[i] << " " << d1[i] << " " << d2[i] << endl;

	int mini = oo;
	FOR(i,0,N) if (d0[i] + d1[i] + d2[i] < mini) mini = d0[i] + d1[i] + d2[i];

	if (mini == oo) cout << "impossible" << endl; else cout << mini << endl;


}
