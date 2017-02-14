#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=1<<30;

struct flow
{
    struct edge
    {
        int t, f, c, r;
        edge(int _t, int _f, int _c, int _r) : t(_t), f(_f), c(_c), r(_r){}
    };
    
    int n;
    vector<int> prv, plv, dis;
    vector<vector<edge>> e;
    flow(int n) : n(n), prv(n+1), plv(n+1), e(n+1){}
    
    void add(int u, int v, int f, int c)
    {
        e[u].push_back(edge(v, f,  c, e[v].size()));
        e[v].push_back(edge(u, f, -c, e[u].size()-1));
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
    
    vector<int> operator()(int s, int t, int k)
    {
        int fl=0;
        vector<int> ans;
        
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
            
            for(int i=0; i<tf; i++)
                ans.push_back(dis[t]);
        }
        
        return ans;
    }
};

int main()
{
    for(int n, m, k; scanf("%d%d%d", &n, &m, &k)!=EOF; )
    {
        scanf("%d%d%d", &n, &m, &k);
        flow F(n);
        
        for(int i=0; i<m; i++)
        {
            fprintf(stderr, "~~ %d\n", i);
            
            
            int u, v, w;
            
            scanf("%d%d%d", &u, &v, &w);
            
            fprintf(stderr, "!! %d %d %d\n", u, v, w);
            
            F.add(u, v, w, 1);
        }
        
        vector<int> t=F(0, n-1, k);
        
        for(int x : t)
            printf("%d ", x);
        printf("\n");
    }
}

/*

5 6 4
0 1 2
0 3 1
1 2 1
2 3 1
1 4 1
3 4 2

3 3 10
0 1 1
1 2 1
0 2 1

2 0 1

*/
