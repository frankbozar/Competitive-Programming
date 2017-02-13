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
        int t, c, r, o;
        edge(int _t, int _c, int _r, int _o) : t(_t), c(_c), r(_r), o(_o){}
    };
    
    vector<int> l;
    vector<vector<edge>> e;
    dinic(int n) : e(n+1){}
    
    void add(int u, int v, int w)
    {
        e[u].push_back(edge(v, w, e[v].size()  , 1));
        e[v].push_back(edge(u, w, e[u].size()-1, 1));
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
    
    int dfs(int s, int t, int num=1)
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
        
        while( ans<2 && bfs(s, t) )
            while( (tmp=dfs(s, t)) )
                ans+=tmp;
        
        return ans;
    }
    
    void solve(int s, int t)
    {
        for(int i=0; i<2; i++)
        {
            for(int u=s; u!=t; )
            {
                for(; e[u].back().o!=1 || e[u].back().c!=0; e[u].pop_back());
                printf("%d ", u);
                int v=e[u].back().t;
                e[u].pop_back();
                u=v;
            }
            
            printf("%d\n", t);
        }
    }
};

int main()
{
    int n, m, s, t;
    scanf("%d%d%d%d", &n, &m, &s, &t);
    dinic D(n+1);
    
    for(int i=0; i<m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        D.add(u, v, 1);
    }
    
    if( D(s, t)<2 )
        printf("NO\n");
    else
    {
        printf("YES\n");
        D.solve(s, t);
    }
}

/*

3 1 1 3
1 3

3 2 1 3
1 3
1 3

3 3 1 3
1 2
1 3
2 3

3 4 1 3
1 2
1 2
2 3
2 3

*/
