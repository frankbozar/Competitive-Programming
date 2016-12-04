// randomized brute force solution, false negative probability < 10^{-8}
#include <bits/stdc++.h>
using namespace std;

int main(void) {
  int n; cin >> n;
  vector<int> S(n), P(n);
  for (auto &s: S) cin >> s;
  iota(P.begin(), P.end(), 1);
  for (int tries = 0; tries < 500; ++tries) {
    random_shuffle(P.begin(), P.end());
    int have = S[P[0]-1], given = 0;
    for (int i = 1; i < n; ++i) {
      given += S[P[i]-1];
      if (have < S[P[i]-1]) given = -999;
    }
    if (given >= have) {
      for (auto p: P) cout << p << " ";
      return 0;
    }
  }
  printf("impossible\n");
}
