//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

typedef vector<int> vi;
int main() {
    int n; scanf("%d", &n);
    vector<pair<int, int>> a(n);
    int sum = 0;
    rep(i,0,n) {
        scanf("%d", &a[i].first), a[i].second = i;
        sum += a[i].first;
    }

    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    if (a[0].first > sum / 2)
        printf("impossible\n");
    else {
        rep(i,0,n) printf("%d ", a[i].second + 1);
        printf("\n");
    }
}
