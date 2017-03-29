#include<cstdio>
#include<vector>
using namespace std;
const int INF=1<<30;

struct set
{
    vector<int> p, s;
    
    set(int n) : p(n+1, -1), s(n+1, 0)
    {
        for(int i=1; i<=n; i++)
            scanf("%d", &s[i]);
    }
    
    int find(int x)
    {
        return p[x]<0 ? x : p[x]=find(p[x]);
    }
    
    void join(int x, int y)
    {
        x=find(x);
        y=find(y);
        
        if( x!=y )
        {
            s[y]+=s[x];
            p[x]=y;
        }
    }
    
    int get(int x)
    {
        return s[find(x)];
    }
};

struct road
{
    int u, v, w;
    
    void read()
    {
        scanf("%d%d%d", &u, &v, &w);
    }
};

bool check(const vector<road>& a, set S, int n, int x)
{
    for(const road& r : a)
        if( r.w<=x )
            S.join(r.u, r.v);
    
    for(int i=1; i<=n; i++)
        if( S.get(i)<0 )
            return false;
    
    return true;
}

int main()
{
    for(int n; scanf("%d", &n)!=EOF; )
    {
        set S(n);
        int m, ans=-1;
        scanf("%d", &m);
        vector<road> a(m);
        
        for(int i=0; i<m; i++)
            a[i].read();
        
        for(int l=0, r=INF; l<r; )
        {
            int x=(l+r)>>1;
            
            if( check(a, S, n, x) )
                ans=r=x;
            else
                l=x+1;
        }
        
        printf("%d\n", ans);
    }
}
