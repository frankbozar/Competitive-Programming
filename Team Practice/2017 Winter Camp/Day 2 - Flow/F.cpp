#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
const int INF=1<<30;

struct dinic
{
    struct edge
    {
        lld t, c, r;
    };
    
    vector<int> l;
    vector<vector<edge>> e;
    dinic(int n) : e(n+1){}
    
    void add(int u, int v, lld w)
    {
        e[u].push_back({v, w, (lld)e[v].size()});
        e[v].push_back({u, 0, (lld)e[u].size()-1});
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
            int s=Q.front();
            
            for(const edge& E : e[s])
                if( l[E.t]>l[s]+1 && E.c>0 )
                {
                    l[E.t]=l[s]+1;
                    Q.push(E.t);
                }
        }
        
        return l[t]<INF;
    }
    
    lld dfs(int s, int t, lld w=INF*(lld)INF)
    {
        if( s==t || w==0 )
            return w;
        
        lld ans=0;
        
        for(edge& E : e[s])
        {
            if( l[E.t]!=l[s]+1 )
                continue;
            
            lld flow=dfs(E.t, t, min(w, E.c));
            rev(E).c+=flow;
            E.c-=flow;
            ans+=flow;
            w-=flow;
        }
        
        return ans ? ans : l[s]=0;
    }
    
    lld operator()(int s, int t)
    {
        lld ans=0, tmp;
        
        while( bfs(s, t) )
        {
            while( (tmp=dfs(s, t)) )
                ans+=tmp;
        }
        
        return ans;
    }
};

int main()
{
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    int a[m][3];
    
    for(int i=0; i<m; i++)
        for(int j=0; j<3; j++)
            scanf("%d", &a[i][j]);
    
    double ans=0, l=0, r=1e9;
    
    for(int cnt=0; cnt<1000; cnt++)
    {
        double x=(l+r)/2;
        dinic D(n+1);
        
        for(int i=0; i<m; i++)
            D.add(a[i][0], a[i][1], a[i][2]/x);
        
        if( D(1, n)<k )
            r=x;
        else
            ans=l=x;
    }
    
    printf("%f\n", ans*k);
}
