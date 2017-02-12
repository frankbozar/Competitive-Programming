#include<cstdio>
#include<set>
#include<vector>
using namespace std;
#define edge pair<int,int>
#define u first
#define v second

struct ds
{
    vector<int> p, s, c;
    ds(int n) : p(n+1, -1), s(n+1, 1), c(n+1, 0){}
    
    int find(int x)
    {
        return p[x]<0 ? x : p[x]=find(p[x]);
    }
    
    bool join(int x, int y)
    {
        x=find(x);
        y=find(y);
        c[y]++;
        
        if( x==y )
            return false;
        
        p[x]=y;
        s[y]+=s[x];
        c[y]+=c[x];
        return true;
    }
};

vector<int> dfn, low;
vector<vector<int>> e;
set<edge> b;

void dfs(int u, int p=-1, int d=0)
{
    dfn[u]=low[u]=d;
    
    for(int i=e[u].size()-1; i>=0; i--)
    {
        int v=e[u][i];
        
        if( v!=p && dfn[v]>=0 )
            low[u]=min(low[u], dfn[v]);
        else if( dfn[v]<0 )
        {
            dfs(v, u, d+1);
            low[u]=min(low[u], low[v]);
            
            if( dfn[u]<low[v] )
            {
                b.insert(edge(u, v));
                b.insert(edge(v, u));
            }
        }
    }
}

int main()
{
    for(int n, m; scanf("%d%d", &n, &m)!=EOF; )
    {
        ds S(n+1);
        int conn=n;
        e.clear();
        e.resize(n+1);
        dfn.assign(n+1, -1);
        low.assign(n+1, -1);
        b.clear();
        
        for(int i=1; i<=m; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            e[u].push_back(v);
            e[v].push_back(u);
            
            if( S.join(u, v) )
                conn--;
        }
        
        dfs(1);
        S=ds(n+1);
        int ans= conn==1 ? 1 : 0 ;
        
        for(int u=1; u<=n; u++)
            for(int v : e[u])
                if( b.find(edge(u, v))==b.end() )
                    S.join(u, v);
        
        for(int i=1; i<=n; i++)
            if( i==S.find(i) )
                if( S.s[i]!=1 && (S.s[i]%2!=0 || S.s[i]!=S.c[i]*2) )
                    ans=0;
        
        printf("%d\n", ans);
    }
}

/*

2 1
1 2

3 2
1 2
2 3

3 3
1 2
2 3
3 1

*/
