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

int a[1000000];
int b[1000000];


int main(){
		int n; cin >> n;
		FOR(i,0,n) cin >> a[i];
		FOR(i,0,n) cin >> b[i];

		int hi = 0;
		FOR(i,0,n) hi = max(hi,max(a[i],b[i]));

		int lo = -1;
		while (lo+1 < hi){
				int mi = (lo+hi)/2;

				// check
				bool ok = true;
				int last = -1;
				FOR(i,0,n) if (a[i] <= mi) continue; else if (last == -1) last = a[i]; else if (last == a[i]) last = -1; else ok = false;
				ok &= last == -1;
				last = -1;
				FOR(i,0,n) if (b[i] <= mi) continue; else if (last == -1) last = b[i]; else if (last == b[i]) last = -1; else ok = false;
				ok &= last == -1;

				if (ok) hi = mi; else lo = mi;
		}

		cout << hi << endl;

}




















