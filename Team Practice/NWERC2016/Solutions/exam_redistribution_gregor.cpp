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


int p[30];


int main(){
	int N; cin >> N;
	FOR(i,0,N) cin >> p[i];
	FOR(i,0,N) p[i] = p[i] * 100 + i;
	sort(p,p+N);
	reverse(p,p+N);

	int rm = p[0] / 100;
	FOR(i,1,N) rm -= p[i] / 100;

	if (rm <= 0)
		FOR(i,0,N){
			if (i) cout << " ";
			cout << (p[i] % 100) + 1;
		}
	else cout << "impossible";
	cout << endl;
}




















