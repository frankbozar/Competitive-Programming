//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

typedef vector<int> vi;
vi bfs(vector<int> start, vector<vi>& g) {
    vector<int> dist(g.size(), g.size() + 2);
    queue<int> q;
    for (int x : start) {
        q.push(x);
        dist[x] = 0;
    }

    for (; !q.empty(); q.pop()) {
        int u = q.front();
        for (int x : g[u]) if (dist[x] >= (int)g.size()) {
            dist[x] = dist[u] + 1;
            q.push(x);
        }
    }

    return dist;
}
int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    vi a(m), b(k);
    rep(i,0,m) scanf("%d", &a[i]), --a[i];
    rep(i,0,k) scanf("%d", &b[i]), --b[i];

    vector<vi> g(n);
    vector<vi> rg(n);
    rep(i,0,n) {
        int l; scanf("%d", &l);
        rep(j,0,l) {
            int x; scanf("%d", &x);
            g[i].push_back(x - 1);
            rg[x - 1].push_back(i);
        }
    }

    vi dist[] = {bfs({0}, g), bfs(a, rg), bfs(b, rg)};

    int best = dist[0][0] + dist[1][0] + dist[2][0];
    rep(i,1,n) {
        int cur = dist[0][i] + dist[1][i] + dist[2][i];
        best = min(cur, best);
    }

    if (best >= n) cout << "impossible" << endl;
    else cout << best << endl;
}
