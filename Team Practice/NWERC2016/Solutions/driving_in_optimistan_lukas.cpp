#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <utility>
#include <cstdio>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

typedef __int128 ll;
typedef tuple<int, int, int> three;
ll aritsum(ll n) { return n * (n - 1) / 2; }
ll squaresum(ll n) { return n * (n - 1) * (n - 2) / 6; }
struct Tree {
    int dist;
    ll size, sum;
    Tree() : dist(0), size(0), sum(0) {}
    Tree(ll s, int d, ll _sum) : dist(d), size(s), sum(_sum) {}
};
typedef pair<Tree, ll> ptl;

ll moveup(Tree &x, int h)
{
    ll xsum = x.sum, xsize = x.size;
    int da = x.dist - h;
    x.sum += x.size * da + aritsum(da);
    x.size += da - 1;
    return da * xsum + aritsum(da) * xsize + squaresum(da);
}

ptl merge(Tree ta, Tree tb, int h)
{
    ll la = moveup(ta, h);
    ll lb = moveup(tb, h);
    Tree res(ta.size + tb.size + 1, h, ta.sum + tb.sum);
    return ptl(res, ta.size * tb.sum + la + tb.size * ta.sum + lb);
}

int main()
{
    int n;
    scanf("%d", &n);

    unordered_map<int, Tree> m;
    vector<three> dist;
    vector<ll> l(1, 0);
    rep(i,0,n-1)
    {
        rep(j,i+1,n)
        {
            int x; scanf("%d", &x);
            if (i > 0)
            {
                ll s = (l[i] + l[j] - x) / 2;
                dist.push_back(three(-s, i, j));
            }
            else
            {
                m[j] = Tree(1, x, 0);
                l.push_back(x);
            }
        }
    }

    sort(dist.begin(), dist.end());
    ll total = 0;
    for (three &o : dist)
    {
        int a = get<1>(o), b = get<2>(o);
        if (m.count(a) && m.count(b))
        {
            ptl res = merge(m[a], m[b], -get<0>(o));
            total += res.second;
            if (l[a] < l[b]) m[a] = res.first, m.erase(b);
            else m[b] = res.first, m.erase(a);
        }
    }

    Tree last = m.begin()->second;
    ll remains = moveup(last, 0);
    ll res = total + last.sum + remains;

    cout.precision(15);
    cout << res / double(aritsum(last.size + 1)) << endl;
}
