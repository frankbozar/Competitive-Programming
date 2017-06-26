#include<cstdio>
#include<set>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
#define bridge pair<lld,lld>
#define l first
#define i second

struct gap
{
    lld l, r, i;
    gap(lld _l=0, lld _r=0, lld _i=0) : l(_l), r(_r), i(_i){}
    
    bool operator<(const gap& G) const
    {
        return r<G.r;
    }
};

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    vector<lld> l(n), r(n);
    
    for(int i=0; i<n; i++)
        scanf("%lld%lld", &l[i], &r[i]);
    
    vector<gap> g;
    
    for(int i=1; i<n; i++)
        g.push_back(gap(l[i]-r[i-1], r[i]-l[i-1], i));
    
    set<bridge> b;
    
    for(int i=1; i<=m; i++)
    {
        lld x;
        scanf("%lld", &x);
        b.insert(bridge(x, i));
    }
    
    sort(g.begin(), g.end());
    vector<int> a(n, 0);
    
    for(const gap& G : g)
    {
        auto it=b.lower_bound(bridge(G.l, 0));
        
        if( it==b.end() || it->l>G.r )
        {
            a[0]=-1;
            break;
        }
        else
        {
            a[G.i]=it->i;
            b.erase(it);
        }
    }
    
    if( a[0]<0 )
        printf("No\n");
    else
    {
        printf("Yes\n");
        
        for(int i=1; i<n; i++)
            printf(i==n-1 ? "%d\n" : "%d ", a[i]);
    }
}
