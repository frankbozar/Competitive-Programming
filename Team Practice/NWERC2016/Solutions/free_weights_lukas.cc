//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <vector>
#include <set>
#include <cstdio>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

typedef vector<int> vi;
bool works(int ma, vector<vi>& r) {
    rep(j,0,2) {
        int prev = -1;
        for (int x : r[j]) {
            if (x <= ma) continue;
            if (x == prev) prev = -1;
            else {
                if (prev != -1) return false;
                prev = x;
            }
        }
    }
    return true;
}
int main() {
    int n; scanf("%d", &n);
    vector<vi> r(2, vector<int>(n));
    rep(j,0,2) rep(i,0,n) scanf("%d", &r[j][i]);

    set<int> unique;
    for (int x : r[0]) {
        if (unique.count(x)) unique.erase(x);
        else unique.insert(x);
    }

    int low = unique.empty() ? -1 : *unique.rbegin() - 1, up = 1e9;
    while (low + 1 < up) {
        int m = (low + up) / 2;
        if (works(m, r))
            up = m;
        else
            low = m;
    }
    cout << up << endl;
}
