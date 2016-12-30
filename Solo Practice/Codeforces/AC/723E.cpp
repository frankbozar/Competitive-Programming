#include<cstdio>
#include<vector>
using namespace std;

struct edge
{
    int v, w, r;
};

struct set
{
    vector<int> p;
    set(int n) : p(n+1, -1){}
    
    int find(int x)
    {
        return p[x]<0 ? x : p[x]=find(p[x]);
    }
    
    void join(int x, int y)
    {
        x=find(x);
        y=find(y);
        
        if( x!=y )
            p[x]=y;
    }
    
    bool same(int x, int y)
    {
        return find(x)==find(y);
    }
};

void dfs(vector<vector<edge>>& e, vector<vector<edge>>& f, int u)
{
    while( !e[u].empty() )
    {
        edge E=e[u].back();
        e[u].pop_back();
        
        if( !E.w )
            continue;
        
        f[u].push_back(E);
        e[E.v][E.r].w=0;
        dfs(e, f, E.v);
    }
}

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n, m, ans=0;
        scanf("%d%d", &n, &m);
        vector<vector<edge>> e(n+1), f(n+1);
        set S(n+1);
        
        for(int i=0; i<m; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            e[u].push_back({v, 1, (int)e[v].size()});
            e[v].push_back({u, 1, (int)e[u].size()-1});
            S.join(u, v);
        }
        
        for(int i=1; i<=n; i++)
            if( !(e[i].size()&1) )
                ans++;
        
        for(int i=1; i<=n; i++)
        {
            if( e[i].size()&1 )
            {
                for(int j=i+1; j<=n; j++)
                {
                    if( e[j].size()&1 && S.same(i, j) )
                    {
                        e[i].push_back({j, -1, (int)e[j].size()});
                        e[j].push_back({i, -1, (int)e[i].size()-1});
                        break;
                    }
                }
            }
        }
        
        for(int i=1; i<=n; i++)
            dfs(e, f, i);
        
        printf("%d\n", ans);
        
        for(int i=1; i<=n; i++)
            for(const edge& E : f[i])
                if( E.w==1 )
                    printf("%d %d\n", i, E.v);
    }
}
