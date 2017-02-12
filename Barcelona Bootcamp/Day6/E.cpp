#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
const lld INF=1LL<<60;

struct dinic
{
    struct edge
    {
        int t;
        lld c;
        int r;
        edge(int _t, lld _c, int _r) : t(_t), c(_c), r(_r){}
    };
    
    vector<int> l;
    vector<vector<edge>> e;
    dinic(int n) : e(n+1){}
    
    void add(int u, int v, lld w)
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
        const int inf=e.size()+1;
        l.assign(e.size(), inf);
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
        
        return l[t]<inf;
    }
    
    lld dfs(int s, int t, lld num=INF)
    {
        if( s==t || num==0 )
            return num;
        
        lld ans=0;
        
        for(edge& E : e[s])
        {
            if( l[E.t]==l[s]+1 )
            {
                lld flow=dfs(E.t, t, min(num, E.c));
                rev(E).c+=flow;
                E.c-=flow;
                ans+=flow;
                num-=flow;
            }
        }
        
        return ans ? ans : l[s]=0 ;
    }
    
    lld operator()(int s, int t)
    {
        lld ans=0, tmp;
        
        while( bfs(s, t) )
            while( (tmp=dfs(s, t)) )
                ans+=tmp;
        
        return ans;
    }
};

int main()
{
    for(int n; scanf("%d", &n)!=EOF; )
    {
        int s=n+n+2;
        int t=n+n+3;
        dinic D(t+1);
        
        for(int i=0; i<n; i++)
        {
            lld x;
            scanf("%lld", &x);
            D.add(i, i+1, x);
        }
        
        for(int i=0; i<n; i++)
        {
            lld x;
            scanf("%lld", &x);
            D.add(i+n+1, i+1+n+1, x);
        }
        
        for(int i=1; i<=n+n+1; i++)
        {
            lld x;
            scanf("%lld", &x);
            D.add((i-1)/2, i/2+n+1, x);
        }
        
        D.add(s, 0, INF);
        D.add(n+n+1, t, INF);
        printf("%lld\n", D(s, t));
    }
}

/*

1
2
2
1 3 1
3
1 4 7
2 5 8
2 3 3 2 1 2 4

*/
