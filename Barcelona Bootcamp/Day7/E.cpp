#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=1<<30;

struct dinic
{
    struct edge
    {
        int t, c, r;
        edge(int _t, int _c, int _r) : t(_t), c(_c), r(_r){}
    };
    
    vector<int> l;
    vector<vector<edge>> e;
    dinic(int n) : e(n+1){}
    
    void add(int u, int v, int w)
    {
        e[u].push_back(edge(v, w, e[v].size()));
        e[v].push_back(edge(u, 0, e[u].size()-1));
    }
    
    edge& rev(const edge& E)
    {
        return e[E.t][E.r];
    }
    
    bool bfs(int s, int t)
    {
        l.assign(e.size(), INF);
        l[s]=1;
        queue<int> Q;
        
        for(Q.push(s); !Q.empty(); Q.pop())
        {
            s=Q.front();
            
            for(const edge& E : e[s])
            {
                if( l[E.t]>l[s]+1 && E.c>0 )
                {
                    l[E.t]=l[s]+1;
                    Q.push(E.t);
                }
            }
        }
        
        return l[t]<INF;
    }
    
    int dfs(int s, int t, int num=INF)
    {
        if( s==t || num==0 )
            return num;
        
        int ans=0;
        
        for(edge& E : e[s])
        {
            if( l[E.t]==l[s]+1 )
            {
                int flow=dfs(E.t, t, min(E.c, num));
                rev(E).c+=flow;
                E.c-=flow;
                ans+=flow;
                num-=flow;
            }
        }
        
        return ans>0 ? ans : l[s]=0;
    }
    
    int operator()(int s, int t)
    {
        int ans=0, tmp;
        
        while( bfs(s, t) )
            while( (tmp=dfs(s, t)) )
                ans+=tmp;
        
        return ans;
    }
};


int main()
{
    int n, m, k, ans=0;
    scanf("%d%d%d", &n, &m, &k);
    vector<int> c(m+1);
    dinic D(n+m+k+2);
    int s=0, t=n+m+k+1;
    
    for(int i=1; i<=n; i++)
    {
        int l;
        scanf("%d", &l);
        D.add(m+i, t, l);
        ans+=l;
        
        for(scanf("%d", &l); l>0; l--)
        {
            int x;
            scanf("%d", &x);
            D.add(x, m+i, INF);
        }
    }
    
    for(int i=1; i<=m; i++)
    {
        scanf("%d", &c[i]);
        D.add(s, i, c[i]);
    }
    
    for(int i=1; i<=k; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        int d=c[u]+c[v]-w;
        D.add(n+m+i, t, d);
        D.add(u, n+m+i, INF);
        D.add(v, n+m+i, INF);
        ans+=d;
    }
    
    printf("%d\n", ans-D(s, t));
}

/*

3 4 2
100 2 1 2
100 1 3
100 1 4
20 20 50 150
1 2 30
3 4 180

1 2 1
100 1 2
20 40
1 2 51

*/
