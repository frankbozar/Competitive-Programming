#include<cmath>
#include<cstdio>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;

struct lca{
    const int H=20;
    int n;
    vector<int> h;
    vector<vector<int>> p;
    lca(const vector<vector<int>>& e) : n(e.size()-1), h(n+1, -1), p(H, vector<int>(n+1, -1)){
        p[0][1]=1; dfs(e, 1, 0);
        for(int i=1; i<H; i++) for(int j=1; j<=n; j++) p[i][j]=p[i-1][ p[i-1][j] ];
    }
    void dfs(const vector<vector<int>>& e, int u, int d=0){
        h[u]=++d;
        for(const int v : e[u]){
            if( h[v]>=0 ) continue;
            p[0][v]=u; dfs(e, v, d);
        }
    }
    int operator()(int u, int v) const{
        if( h[u]>h[v] ) swap(u, v);
        for(int i=0, d=h[v]-h[u]; d>0; d>>=1, i++) if( d&1 ) v=p[i][v];
        for(int i=0; u!=v; i++){
            for(; i>0 && p[i][u]==p[i][v]; i--);
            u=p[i][u], v=p[i][v];
        }
        return u;
    }
};

int s;

struct query
{
    int u, v, l, i;
    query(int _u=0, int _v=0, int _l=0, int _i=0) : u(_u), v(_v), l(_l), i(_i){}
    
    bool operator<(const query& Q) const
    {
        return u/s==Q.u/s ? v<Q.v : u<Q.u ;
    }
};

void dfs(const vector<vector<int>>& e, vector<int>& flt, vector<int>& beg, vector<int>& end, int& dfn, int u, int p)
{
    dfn++;
    flt[dfn]=u;
    beg[u]=dfn;
    
    for(int v : e[u])
        if( v!=p )
            dfs(e, flt, beg, end, dfn, v, u);
    
    dfn++;
    flt[dfn]=u;
    end[u]=dfn;
}

void update(const vector<int>& g, const vector<int>& a, vector<int>& o, vector<vector<int>>& c, lld& cnt, int t, int d)
{
    o[t]+=d;
    
    if( o[t]&1 )
    {
        c[ g[t] ][ a[t] ]++;
        cnt+=c[ g[t]^1 ][ a[t] ];
    }
    else
    {
        c[ g[t] ][ a[t] ]--;
        cnt-=c[ g[t]^1 ][ a[t] ];
    }
}

int main()
{
    int n, m;
    scanf("%d", &n);
    s=sqrt(n<<1);
    vector<int> g(n+1, 0), a(n+1, 0);
    vector<vector<int>> e(n+1);
    
    for(int i=1; i<=n; i++)
        scanf("%d", &g[i]);
    
    map<int, int> M;
    
    for(int i=1; i<=n; i++)
    {
        int x;
        scanf("%d", &x);
        
        if( M.find(x)==M.end() )
        {
            int t=M.size();
            M[x]=t;
        }
        
        a[i]=M[x];
    }
    
    for(int i=1; i<n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    
    vector<int> flt((n<<1)|1, 0), beg(n+1, 0), end(n+1, 0);
    int dfn=0;
    dfs(e, flt, beg, end, dfn, 1, 0);
    scanf("%d", &m);
    vector<query> q;
    lca L(e);
    
    for(int i=0; i<m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        int l=L(u, v);
        
        if( l==u )
            q.push_back(query(beg[u], beg[v]+1, -1, i));
        else if( l==v )
            q.push_back(query(beg[v], beg[u]+1, -1, i));
        else if( beg[u]<beg[v] )
            q.push_back(query(end[u], beg[v]+1, l, i));
        else
            q.push_back(query(end[v], beg[u]+1, l, i));
    }
    
    sort(q.begin(), q.end());
    vector<vector<int>> c(2, vector<int>(n+1, 0));
    vector<int> o(n+1, 0);
    vector<lld> ans(m);
    lld cnt=0;
    
    for(int l=1, r=1, i=0; i<m; i++)
    {
        while( r<q[i].v )
            update(g, a, o, c, cnt, flt[r++], 1);
        
        while( r>q[i].v )
            update(g, a, o, c, cnt, flt[--r], -1);
        
        while( l<q[i].u )
            update(g, a, o, c, cnt, flt[l++], -1);
        
        while( l>q[i].u )
            update(g, a, o, c, cnt, flt[--l], 1);
        
        if( q[i].l>0 )
            ans[ q[i].i ]=cnt+c[ g[ q[i].l ]^1 ][ a[ q[i].l ] ];
        else
            ans[ q[i].i ]=cnt;
    }
    
    for(int i=0; i<m; i++)
        printf("%lld\n", ans[i]);
}
