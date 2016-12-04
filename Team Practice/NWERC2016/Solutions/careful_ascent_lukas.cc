//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <sstream>
#include <queue>
#include <bitset>
#include <utility>
#include <list>
#include <numeric>

#include <cstdio>
#include <cstring>
#include <cmath>
#include <cctype>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
int main() {
    int x, y;
    scanf("%d %d", &x, &y);
    int n; scanf("%d", &n);

    double distance = y;
    rep(i,0,n) {
        int l, u; double f;
        scanf("%d %d %lf", &l, &u, &f);
        distance -= u - l;
        distance += (u - l) * f;
    }

    printf("%.9lf\n", x / distance);
}
