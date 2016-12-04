//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

int n, m;
int best[41][41][401][10];
int split[41][41][401][10];
int solve(vector<string>& a, int start, int end, int pos, int digit) {
    if (pos == m || start == end) return 0;
    if (digit >= 10) return n * m + 47;

    auto& ref = best[start][end][pos][digit];
    if (ref < n * m + 47) return ref;

    int cost = 0;
    rep(k,start,end) {
        int current = cost + solve(a, start, k, pos + 1, 0) + solve(a, k, end, pos, digit + 1);
        if (current < ref) {
            split[start][end][pos][digit] = k;
            ref = current;
        }
        if (k < end) cost += a[k][pos] != ('0' + digit);
    }
    int current = cost + solve(a, start, end, pos + 1, 0);
    if (current < ref) {
        split[start][end][pos][digit] = end;
        ref = current;
    }
    return ref;
}
void reconstruct(vector<string>& a, int start, int end, int pos, int digit) {
    if (digit >= 10 || pos >= m || start == end) return;
    auto& s = split[start][end][pos][digit];
    rep(i,start,s) a[i][pos] = '0' + digit;
    reconstruct(a, start, s, pos + 1, 0);
    reconstruct(a, s, end, pos, digit + 1);
}
int main() {
    scanf("%d %d", &n, &m);
    vector<string> a(n);
    rep(i,0,n) {
        cin >> a[i];
        if (a[i].size() < (size_t)m) a[i] = string(m - a[i].size(), '0') + a[i];
    }

    rep(i,0,41) rep(j,0,41) rep(k,0,401) rep(l,0,10)
        best[i][j][k][l] = n * m + 47;

    solve(a, 0, n, 0, 0);
    reconstruct(a, 0, n, 0, 0);
    rep(i,0,n) cout << a[i] << endl;
}
