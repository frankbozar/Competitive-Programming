#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
const int inf=1<<30;
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
    
    edge& rev(const edge& E)
    {
        return e[E.t][E.r];
    }
    
    void add(int u, int v, lld w)
    {
        e[u].push_back(edge(v, w, e[v].size()));
        e[v].push_back(edge(u, 0, e[u].size()-1));
    }
    
    bool bfs(int s, int t)
    {
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
            if( l[E.t]==l[s]+1 && E.c>0 )
            {
                lld flow=dfs(E.t, t, min(num, E.c));
                rev(E).c+=flow;
                E.c-=flow;
                ans+=flow;
                num-=flow;
            }
        }
        
        return ans>0 ? ans : l[s]=0 ;
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

int id(int m, int i, int j)
{
    m=m*2+1;
    return i*m+j;
}

int main()
{
    int n, m, k;
    lld s=0;
    scanf("%d%d%d", &n, &m, &k);
    vector<int> a(k), b(m);
    
    for(int i=0; i<k; i++)
    {
        scanf("%d", &a[i]);
        a[i]--;
    }
    
    for(int i=0; i<m; i++)
        scanf("%d", &b[i]);
    
    dinic D((n+1)*(m*2+1)+2);
    
    for(int i=0; i<n; i++)
    {
        vector<int> c(m, 0);
        int v;
        scanf("%d", &v);
        
        for(int j=0; j<k; j++)
        {
            int x;
            scanf("%d", &x);
            c[ a[j] ]+=x;
            s+=x;
        }
        
        for(int j=0; j<m; j++)
        {
            D.add((n+1)*(m*2+1), id(m, i, j*2), c[j]);
            D.add(id(m, i, j*2), id(m, i, j*2+1), b[j]);
            D.add(id(m, i, j*2+1), id(m, i, m*2), INF);
            D.add(id(m, i, j*2+1), id(m, i+1, j*2), INF);
        }
        
        D.add(id(m, i, m*2), (n+1)*(m*2+1)+1, v);
    }
    
    printf(D((n+1)*(m*2+1), (n+1)*(m*2+1)+1)>=s ? "possible\n" : "impossible\n");
}

/*

2 2 2
1 2
3 3
5 2 2
5 2 2

2 2 2
1 2
3 3
1 2 2
5 2 2

*/