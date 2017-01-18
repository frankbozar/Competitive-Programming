#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=1<<30;

struct ds
{
    vector<int> p;
    ds(int n) : p(n+1){}
    
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
};

struct dinic
{
    struct edge
    {
        int t, c, r;
    };
    
    vector<int> l;
    vector<vector<edge>> e;
    dinic(int n) : e(n+1){}
    
    void add(int u, int v, int w)
    {
        e[u].push_back({v, w, (int)e[v].size()});
        e[v].push_back({u, 0, (int)e[u].size()-1});
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
    
    int dfs(int s, int t, int w=INF)
    {
        if( s==t || w==0 )
            return w;
        
        int ans=0;
        
        for(edge& E : e[s])
        {
            if( l[E.t]!=l[s]+1 )
                continue;
            
            int flow=dfs(E.t, t, min(w, E.c));
            rev(E).c+=flow;
            E.c-=flow;
            ans+=flow;
            w-=flow;
        }
        
        return ans ? ans : l[s]=0;
    }
    
    int operator()(int s, int t)
    {
        int ans=0, tmp;
        
        while( bfs(s, t) )
        {
            while( (tmp=dfs(s, t)) )
                ans+=tmp;
        }
        
        return ans;
    }
};

void dfs(const vector<vector<int>>& e, vector<int>& a, vector<bool>& u, int i)
{
    if( u[i] )
        return ;
    
    a.push_back(i);
    u[i]=true;
    
    for(int j : e[i])
        dfs(e, a, u, j);
}

int main()
{
    int N=1<<20;
    vector<bool> p(N, true);
    p[0]=p[1]=false;
    
    for(int i=0; i*i<N; i++)
        if( p[i] )
            for(int j=i*i; j<N; j+=i)
                p[j]=false;
    
    int n;
    scanf("%d", &n);
    dinic D(n+2);
    vector<int> a(n+1, 0);
    
    for(int i=1; i<=n; i++)
    {
        scanf("%d", &a[i]);
        
        if( a[i]&1 )
            D.add(0, i, 2);
        else
            D.add(i, n+1, 2);
        
        for(int j=1; j<i; j++)
        {
            if( p[ a[i]+a[j] ] )
            {
                if( a[i]&1 )
                    D.add(i, j, 1);
                else
                    D.add(j, i, 1);
            }
        }
    }
    
    if( D(0, n+1)!=n )
    {
        printf("Impossible\n");
        return 0;
    }
    
    vector<vector<int>> e(n+1);
    
    for(int i=1; i<=n; i++)
        for(const auto& E : D.e[i])
            if( a[i]&1 && E.c==0 )
            {
                e[i].push_back(E.t);
                e[E.t].push_back(i);
            };
    
    vector<bool> u(n+1, false);
    vector<vector<int>> ans(n+1);
    int cnt=0;
    
    for(int i=1; i<=n; i++)
    {
        if( !u[i] )
        {
            cnt++;
            dfs(e, ans[i], u, i);
        }
    }
    
    printf("%d\n", cnt);
    
    for(int i=1; i<=n; i++)
        if( !ans[i].empty() )
        {
            printf("%lu", ans[i].size());
            
            for(int j=ans[i].size()-1; j>=0; j--)
                printf(" %d", ans[i][j]);
            
            printf("\n");
        }
}
