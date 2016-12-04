#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

vector<int> cost[1<<17];
int candy[1<<17]{};
multiset<pii> avail[1<<17];
multiset<int> spent[1<<17];

int down(int f) {
  if (spent[f].empty() || avail[f].empty() || -*spent[f].begin() <= avail[f].begin()->first)
    return false;
  avail[f].insert(pii(-*spent[f].begin(), 1<<20));
  candy[f] -= *spent[f].begin();
  spent[f].erase(spent[f].begin());
  return true;
}

int up(int f) {
  int r = 0, c, l;
  while (!avail[f].empty()) {
    if (avail[f].begin()->first >= candy[f]) {
      if (down(f)) --r;
      else break;
    }
    tie(c, l) = *avail[f].begin();
    avail[f].erase(avail[f].begin());
    spent[f].insert(-c);
    candy[f] -= c;
    if (l+1 < cost[f].size())
      avail[f].insert(pii(cost[f][l+1], l+1));
    ++r;
  }
  return r;
}

int main(void) {
  int F, N;
  scanf("%d", &F);
  unordered_map<string, pii> idx;
  char name[50];
  for (int i = 1; i <= F; ++i) {
    int S;
    scanf("%d", &S);
    cost[i].resize(S-1);
    for (int j = 0; j < S-1; ++j) {
      scanf("%s%d", name, &cost[i][j]);
      idx[name] = pii(i, j);
    }
    scanf("%s", name);
    idx[name] = pii(i, S-1);
  }
  scanf("%d", &N);
  int T[N], tail = 0, ans = 0, levelups = 0, fam, lev;
  for (int i = 0; i < N; ++i) {
    scanf("%d%s", T+i, name);
    tie(fam, lev) = idx[name];
    candy[fam] += 4;
    if (lev < cost[fam].size())
      avail[fam].insert(pii(cost[fam][lev], lev));
    levelups += up(fam);
    while (tail < i && T[tail] <= T[i]-1800) ++tail;
    ans = max(ans, 100*(N + (i-tail+1)) + 1000*levelups);
  }
  printf("%d\n", ans);
  return 0;
}
