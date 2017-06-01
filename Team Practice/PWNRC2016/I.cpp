#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=1<<20;

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
                int tmp=dfs(E.t, t, min(E.c, num));
                rev(E).c+=tmp;
                E.c-=tmp;
                ans+=tmp;
                num-=tmp;
            }
        }
        
        return ans>0 ? ans : l[s]=0 ;
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
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    dinic D(n+m+k+3);
    
    for(int i=1; i<=n; i++)
    {
        int l;
        
        for(scanf("%d", &l); l>0; l--)
        {
            int t;
            scanf("%d", &t);
            D.add(n+t, i, 1);
        }
        
        D.add(i, 0, 1);
    }
    
    vector<int> p(m+1, k+1), d(k+2, INF);
    
    for(int i=1; i<=k; i++)
    {
        int l;
        
        for(scanf("%d", &l); l>0; l--)
        {
            int t;
            scanf("%d", &t);
            p[t]=i;
        }
        
        scanf("%d", &d[i]);
    }
    
    for(int i=1; i<=m; i++)
        D.add(n+m+p[i], n+i, 1);
    
    for(int i=1; i<=k+1; i++)
        D.add(n+m+k+2, n+m+i, d[i]);
    
    printf("%d\n", D(n+m+k+2, 0));
}

/*

4 3 1
2 1 2
2 1 2
1 3
1 3
2 1 2 1

*/
