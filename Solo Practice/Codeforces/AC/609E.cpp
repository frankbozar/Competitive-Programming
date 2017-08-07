#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;

#define edge pair<int,int>
#define v first
#define w second
struct lca{
    const int H=20;
    int n;
    vector<int> h;
    vector<vector<int>> p, b;
    lca(const vector<vector<edge>>& e) : n(e.size()-1),//one-base vertex index
    h(n+1, -1), p(H, vector<int>(n+1, -1)), b(H, vector<int>(n+1)){
        p[0][1]=1; b[0][1]=0; dfs(e, 1, 0);
        for(int i=1; i<H; i++) for(int j=1; j<=n; j++){
            p[i][j]=p[i-1][ p[i-1][j] ];
            b[i][j]=max(b[i-1][ p[i-1][j] ], b[i-1][j]);
            //b is something you want to calculate on the path from root
        }
    }
    void dfs(const vector<vector<edge>>& e, int u, int d=0){
        h[u]=++d;
        for(const edge& E : e[u]){
            if( h[E.v]>=0 ) continue;
            p[0][E.v]=u; b[0][E.v]=E.w;
            dfs(e, E.v, d);
        }
    }
    int operator()(int u, int v) const{
        if( h[u]>h[v] ) swap(u, v);
        int ans=0;
        for(int i=0, d=h[v]-h[u]; d>0; d>>=1, i++)
            if( d&1 ) ans=max(ans, b[i][v]), v=p[i][v];
        for(int i=0; u!=v; i++){
            for(; i>0 && p[i][u]==p[i][v]; i--);
            ans=max(ans, max(b[i][u], b[i][v]));
            u=p[i][u], v=p[i][v];
        }
        return ans;
    }
};

struct set
{
    vector<int> p;
    set(int n=0) : p(n+1, -1){}
    
    int find(int x)
    {
        return p[x]<0 ? x : p[x]=find(p[x]);
    }
    
    bool join(int x, int y)
    {
        x=find(x);
        y=find(y);
        
        if( x==y )
            return false;
        
        p[x]=y;
        return true;
    }
};

struct fedge
{
    int u, v, w;
    
    void read()
    {
        scanf("%d%d%d", &u, &v, &w);
    }
    
    bool operator<(const fedge& F) const
    {
        return w<F.w;
    }
};

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    vector<fedge> e(m), f(m);
    vector<vector<edge>> t(n+1);
    
    for(int i=0; i<m; i++)
    {
        fedge F;
        F.read();
        e[i]=f[i]=F;
    }
    
    sort(f.begin(), f.end());
    set S(n);
    lld ans=0;
    
    for(int i=0; n>1 && i<m; i++)
    {
        if( S.join(f[i].u, f[i].v) )
        {
            n--;
            ans+=f[i].w;
            t[ f[i].u ].push_back(edge(f[i].v, f[i].w));
            t[ f[i].v ].push_back(edge(f[i].u, f[i].w));
        }
    }
    
    lca L(t);
    
    for(int i=0; i<m; i++)
        printf("%lld\n", ans+e[i].w-L(e[i].u, e[i].v));
}
