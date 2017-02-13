#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=1<<30;

struct flow
{
    struct edge
    {
        int t, f, c, r, o, i;
        edge(int _t, int _f, int _c, int _r, int _o, int _i) : t(_t), f(_f), c(_c), r(_r), o(_o), i(_i){}
    };
    
    int n;
    vector<int> prv, plv, dis;
    vector<vector<edge>> e;
    flow(int n) : n(n), prv(n+1), plv(n+1), e(n+1){}
    
    void add(int u, int v, int f, int c, int i)
    {
        e[u].push_back(edge(v, f,  c, e[v].size()  , 1, i));
        e[v].push_back(edge(u, 0, -c, e[u].size()-1, 0, i));
    }
    
    edge& rev(const edge& E)
    {
        return e[E.t][E.r];
    }
    
    bool bfs(int s, int t)
    {
        vector<bool> inq(n+1, false);
        dis.assign(n+1, INF);
        dis[s]=0;
        queue<int> Q;
        
        for(Q.push(s); !Q.empty(); Q.pop())
        {
            s=Q.front();
            inq[s]=false;
            
            for(int i=e[s].size()-1; i>=0; i--)
            {
                const edge& E=e[s][i];
                
                if( dis[E.t]>dis[s]+E.c && E.f>0 )
                {
                    dis[E.t]=dis[s]+E.c;
                    prv[E.t]=s;
                    plv[E.t]=i;
                    
                    if( !inq[E.t] )
                    {
                        Q.push(E.t);
                        inq[E.t]=true;
                    }
                }
            }
        }
        
        return dis[t]<INF;
    }
    
    pair<int, int> operator()(int s, int t, int k)
    {
        int fl=0, cs=0;
        
        for(int tf=k-fl; fl<k && bfs(s, t); tf=k-fl)
        {
            for(int u, l, v=t; v!=s; v=u)
            {
                u=prv[v];
                l=plv[v];
                tf=min(tf, e[u][l].f);
            }
            
            for(int u, l, v=t; v!=s; v=u)
            {
                u=prv[v];
                l=plv[v];
                rev(e[u][l]).f+=tf;
                e[u][l].f-=tf;
            }
            
            fl+=tf;
            cs+=tf*dis[t];
        }
        
        return pair<int, int>(fl, cs);
    }
    
    void solve(int s, int t, int k)
    {
        for(int i=0; i<k; i++)
        {
            vector<int> p;
            
            for(int u=s; u!=t; )
            {
                for(; e[u].back().o!=1 || e[u].back().f!=0; e[u].pop_back());
                p.push_back(e[u].back().i);
                int v=e[u].back().t;
                e[u].pop_back();
                u=v;
            }
            
            printf("%lu", p.size());
            
            for(int x : p)
                printf(" %d", x);
            
            printf("\n");
        }
    }
};

int main()
{
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    flow F(n+1);
    
    for(int i=1; i<=m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        F.add(u, v, 1, w, i);
        F.add(v, u, 1, w, i);
    }
    
    pair<int, int> ans=F(1, n, k);
    
    if( ans.first<k )
        printf("-1\n");
    else
    {
        printf("%f\n", ans.second/double(k));
        F.solve(1, n, k);
    }
}

/*

5 8 2
1 2 1
1 3 1
1 4 3
2 5 5
2 3 1
3 5 1
3 4 1
5 4 1

*/
