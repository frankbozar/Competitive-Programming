#include<queue>
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
using namespace std;
const int INF=1<<25;

struct costflow
{
    struct edge
    {
        int t, f, c, r;
        edge(int _t, int _f, int _c, int _r) : t(_t), f(_f), c(_c), r(_r){}
    };
    
    int n;
    vector<int> prv, plv, dis;
    vector<vector<edge>> e;
    costflow(int _n) : n(_n), prv(n+1), plv(n+1), e(n+1){}
    
    void add(int u, int v, int f, int c)
    {
        e[u].push_back(edge(v, f, c, e[v].size()));
        e[v].push_back(edge(u, 0, -c, e[u].size()-1));
    }
    
    edge& rev(const edge& E)
    {
        return e[E.t][E.r];
    }
    
    bool bfs(int s, int t)
    {
        dis.assign(n+1, INF);
        dis[s]=0;
        queue<int> Q;
        
        for(Q.push(s); !Q.empty(); Q.pop())
        {
            s=Q.front();
            
            for(int i=e[s].size()-1; i>=0; i--)
            {
                const edge& E=e[s][i];
                
                if( dis[E.t]>dis[s]+E.c && E.f>0 )
                {
                    dis[E.t]=dis[s]+E.c;
                    prv[E.t]=s;
                    plv[E.t]=i;
                    Q.push(E.t);
                }
            }
        }
        
        return dis[t]<INF;
    }
    
    pair<int, int> operator()(int s, int t)
    {
        int fl=0, cs=0;
        
        for(int tf=INF; bfs(s, t); tf=INF)
        {
            for(int l, u, v=t; v!=s; v=u)
            {
                u=prv[v];
                l=plv[v];
                tf=min(tf, e[u][l].f);
            }
            
            for(int l, u, v=t; v!=s; v=u)
            {
                u=prv[v];
                l=plv[v];
                e[u][l].f-=tf;
                rev(e[u][l]).f+=tf;
            }
            
            cs+=tf*dis[t];
            fl+=tf;
        }
        
        return pair<int, int>(fl, cs);
    }
};

int main()
{
    int n, m, k;
    string s;
    cin >> n >> s >> m ;
    costflow C(n+2);
    
    for(; m>0; m--)
    {
        string t;
        int p;
        cin >> t >> p ;
        
        for(int l=t.length(), j=0; j<=n-l; j++)
            if( s.substr(j, l)==t )
                C.add(j+1, j+l+1, 1, -p);
    }
    
    cin >> k ;
    
    for(int i=0; i<=n; i++)
        C.add(i, i+1, k, 0);
    
    cout <<  -C(0, n+1).second << endl ;
}

/*

6
abacba
2
aba 6
ba 3
3

*/
