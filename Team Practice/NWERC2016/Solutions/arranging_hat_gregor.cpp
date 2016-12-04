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


int mat[40][400];
int dp[44][44][404][15]; // length, from, position, min number
int op[44][44][404][15];

int N,M;

void change(int l, int f, int p, int m){
	if (!l || p == M) return;
	if (l == 1){
		mat[f][p] = max(m,mat[f][p]);
		return;
	}
	int tf = op[l][f][p][m]; 
	if (tf == -1) return;
	FOR(i,0,tf) mat[f+i][p] = m;
	change(tf,f,p+1,0);
	change(l-tf,f+tf,p,m+1);

}


int main(){
	cin >> N >> M;
	FOR(i,0,N) FOR(j,0,M){
		char c; cin >> c;
		mat[i][j] = c - '0';
	}


	FOR(l,1,N+1) FOR(f,0,N) FOR(p,0,M+1) FOR(m,0,11) dp[l][f][p][m] = oo;
	
	FOR(l,1,N+1) FOR(f,0,N+1) FOR(m,0,11) dp[l][f][M][m] = 0;
	FOR(f,0,N) FOR(p,0,M) FOR(m,0,10) dp[0][f][p][m] = 0;
	FOR(f,0,N) FOR(p,0,M) FOR(m,0,10) dp[1][f][p][m] = (mat[f][p] >= m)?0:1;

	FOR(l,2,N+1) FOR(f,0,N-l+1) FORD(p,0,M) FORD(m,0,10){
		int mini = oo;
		int o = -1;
		FOR(tf,0,l+1){
			int val = dp[tf][f][p+1][0] + dp[l - tf][f+tf][p][m+1];
			FOR(i,0,tf) if (mat[f+i][p] != m) val++;
			if (val < mini) mini = val, o = tf;
		}
		dp[l][f][p][m] = mini;
		op[l][f][p][m] = o;
	}
	
	change(N,0,0,0);
	FOR(i,0,N){
		if (i) cout << " ";
		FOR(j,0,M) cout << mat[i][j];
	}
	cout << endl;
}
