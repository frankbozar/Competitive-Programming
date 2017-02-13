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

int id(int x, int y, int n, int m)
{
    return m*x+y;
}

int main()
{
    int n, m, w, b, g;
    scanf("%d%d%d%d%d", &n, &m, &w, &b, &g);
    int s=n*m, t=n*m+1;
    dinic D(t+1);
    
    for(int x=0; x<n; x++)
    {
        char a[m+1];
        scanf("%s", a);
        
        for(int y=0; y<m; y++)
        {
            if( a[y]=='W' )
                D.add(s, id(x, y, n, m), b);
            else//if( a[y]=='B' )
                D.add(id(x, y, n, m), t, w);
        }
    }
    
    for(int x=0; x<n; x++)
        for(int y=0; y<m; y++)
        {
            if( x>0 )
            {
                D.add(id(x-1, y, n, m), id(x, y, n, m), g);
                D.add(id(x, y, n, m), id(x-1, y, n, m), g);
            }
            
            if( y>0 )
            {
                D.add(id(x, y-1, n, m), id(x, y, n, m), g);
                D.add(id(x, y, n, m), id(x, y-1, n, m), g);
            }
        }
    
    printf("%d\n", D(s, t));
}

/*

3 2 10 12 1
BW
WB
BW

3 2 0 0 1
BW
WB
BW

*/
