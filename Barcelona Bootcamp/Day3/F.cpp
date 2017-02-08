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
                if( l[E.t]>l[s]+1 && E.c>0 )
                {
                    l[E.t]=l[s]+1;
                    Q.push(E.t);
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
                int flow=dfs(E.t, t, min(num, E.c));
                rev(E).c+=flow;
                E.c-=flow;
                ans+=flow;
                num-=flow;
            }
        }
        
        return ans>0 ? ans : l[s]=0 ;
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

int main()
{
    int n;
    scanf("%d", &n);
    vector<int> a(n);
    
    for(int i=0; i<n; i++)
        scanf("%d", &a[i]);
    
    for(int i=0; i<n; i++)
    {
        int x;
        scanf("%d", &x);
        
        if( i==0 )
            a[i]+=x;
    }
    
    for(int i=0; i<n; i++)
    {
        if( a[0]<a[i] )
        {
            printf("NO\n");
            return 0;
        }
    }
    
    int s=0, c=0;
    int t=n*n+n+1;
    dinic D(t+1);
    
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            int v;
            scanf("%d", &v);
            
            if( j<=i )
                continue;
            else if( i==0 )
                continue;
            else if( v>0 )
            {
                c+=v;
                int id=i*n+j+1;
                D.add(s, id, v);
                D.add(id, n*n+i+1, v);
                D.add(id, n*n+j+1, v);
            }
        }
        
        D.add(n*n+i+1, t, a[0]-a[i]);
    }
    
    printf(D(s, t)==c ? "YES\n" : "NO\n");
}

/*

3
1 2 2
1 1 1
0 0 0
0 0 0
0 0 0

3
1 2 2
1 1 1
0 0 0
0 0 1
0 1 0

3
1 2 2
0 0 0
0 0 0
0 0 0
0 0 0

*/
