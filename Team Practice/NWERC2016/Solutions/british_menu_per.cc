// Half-expecting this to be wrong because I wrote a quick and dirty
// SCC without thinking properly, relying on the special graph
// structure.
#include <bits/stdc++.h>
using namespace std;
const int oo = 1<<30;

vector<int> adj[1<<20];
int scc_id[1<<20], scc_idx[1<<20], scc_sz[1<<20]{};
int opt[1<<20][1<<6]{};

int Opt(int u, int seen=0) {
  seen |= 1 << scc_idx[u];
  int &ret = opt[u][seen];
  if (!ret) {
    for (auto v: adj[u]) {
      if (scc_id[v] != scc_id[u]) ret = max(ret, Opt(v));
      else if (!(seen & 1 << scc_idx[v])) ret = max(ret, Opt(v, seen));
    }
    ++ret;
  }
  return ret;
}

int depth[1<<20]{}, par[1<<20];

int dfs(int u, int d) {
  depth[u] = d;
  int ans = u;
  for (auto v: adj[u]) {
    if (!depth[v]) v = dfs(v, d+1);
    else while (depth[v] == oo && v != par[v]) v = par[v];
    if (depth[v] < depth[ans]) ans = v;
  }
  depth[u] = oo;
  return par[u] = ans;
}

int main(void) {
  int n, m, ans = 0;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    adj[a].push_back(b);
  }
  for (int i = 1; i <= n; ++i) {
    if (!depth[i]) dfs(i, 1);
    int r = i;
    while (par[r] != r) r = par[r];
    scc_id[i] = r;
    scc_idx[i] = scc_sz[r]++;
  }
  for (int i = 1; i <= n; ++i)
    ans = max(ans, Opt(i));
  printf("%d\n", ans);
}
