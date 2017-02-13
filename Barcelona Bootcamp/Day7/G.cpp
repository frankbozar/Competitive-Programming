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
    
    vector<int> l, d, p;
    vector<vector<edge>> e;
    dinic(int n) : d(n+1, 0), e(n+1){}
    
    void add(int u, int v, int w, int W)
    {
        e[u].push_back(edge(v, w, e[v].size()));
        e[v].push_back(edge(u, W, e[u].size()-1));
        d[u]++, d[v]++;
    }
    
    edge& rev(const edge& E)
    {
        return e[E.t][E.r];
    }
    
    bool bfs(int s, int t, int k)
    {
        l.assign(e.size(), INF);
        l[s]=1;
        queue<int> Q;
        
        for(Q.push(s); !Q.empty(); Q.pop())
        {
            s=Q.front();
            
            for(const edge& E : e[s])
            {
                if( l[E.t]>l[s]+1 && E.c>=k )
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
        
        for(; p[s]>0; p[s]--)
        {
            edge& E=e[s][ p[s]-1 ];
            
            if( l[E.t]==l[s]+1 )
            {
                int flow=dfs(E.t, t, min(E.c, num));
                rev(E).c+=flow;
                E.c-=flow;
                ans+=flow;
                num-=flow;
                
                if( num<=0 )
                    break;
            }
        }
        
        return ans>0 ? ans : l[s]=0;
    }
    
    int operator()(int s, int t)
    {
        int ans=0, tmp;
        
        while( bfs(s, t, k) )
        {
            p=d;
            
            while( (tmp=dfs(s, t)) )
                ans+=tmp;
        }
        
        return ans;
    }
};

int n;

inline int id(int x, int y)
{
    return (n+1)*x+y;
}

int main()
{
    scanf("%d", &n);
    dinic D((n+1)*(n+1));
    vector<int> a((n+1)*(n+1), 0), b((n+1)*(n+1), 0);
    vector<int> c((n+1)*(n+1), 0), d((n+1)*(n+1), 0);
    
    for(int x=0; x<=n; x++)
        for(int y=0; y<n; y++)
        {
            int w;
            scanf("%d", &w);
            a[id(x, y)]=w;
        }
    
    for(int x=0; x<n; x++)
        for(int y=0; y<=n; y++)
        {
            int w;
            scanf("%d", &w);
            b[id(x, y)]=w;
        }
    
    for(int x=0; x<=n; x++)
        for(int y=1; y<=n; y++)
        {
            int w;
            scanf("%d", &w);
            c[id(x, y-1)]=w;
        }
    
    for(int x=1; x<=n; x++)
        for(int y=0; y<=n; y++)
        {
            int w;
            scanf("%d", &w);
            d[id(x-1, y)]=w;
        }
    
    for(int x=0; x<=n; x++)
        for(int y=0; y<=n; y++)
        {
            if( x<n )
                D.add(id(x, y), id(x+1, y), b[id(x, y)], d[id(x, y)]);
            
            if( y<n )
                D.add(id(x, y), id(x, y+1), a[id(x, y)], c[id(x, y)]);
        }
    
    printf("%d\n", D(id(0, 0), id(n, n)));
}

/*

1
1 2
3 4
5 6
7 8

*/
