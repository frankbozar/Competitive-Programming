#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=1<<25;

struct Dinic{
    struct edge{
        int t, c, r;
        edge(int _t, int _c, int _r): t(_t), c(_c), r(_r){}
    };
    vector<int> l;
    vector<vector<edge>> e;
    Dinic(int n) : e(n+1){}
    void add(int u, int v, int w){//directed
        e[u].push_back(edge(v, w, e[v].size()));
        e[v].push_back(edge(u, 0, e[u].size()-1));
    }
    edge& rev(const edge& E){
        return e[E.t][E.r];
    }
    bool bfs(int s, int t){
        l.assign(e.size(), INF);
        l[s]=1;
        queue<int> Q;
        for(Q.push(s); !Q.empty(); Q.pop()){
            s=Q.front();
            for(const edge& E : e[s])
                if( E.c>0 && l[E.t]>l[s]+1 ){
                    l[E.t]=l[s]+1;
                    Q.push(E.t);
                }
        }
        return l[t]<INF;
    }
    int dfs(int s, int t, int num=INF){
        if( s==t || num==0 ) return num;
        int ans=0;
        for(edge& E : e[s])
            if( E.c>0 && l[s]+1==l[E.t] ){
                int tmp=dfs(E.t, t, min(num, E.c));
                rev(E).c+=tmp, ans+=tmp;
                E.c-=tmp, num-=tmp;
            }
        return ans>0 ? ans : l[s]=0;
    }
    int operator()(int s, int t){
        int ans=0, tmp=0;
        while( bfs(s, t) )
            while( (tmp=dfs(s, t)) )
                ans+=tmp;
        return ans;
    }
};

int main()
{
    int n, m, x, y;
    scanf("%d%d%d%d", &n, &m, &x, &y);
    vector<vector<int>> e(n+1, vector<int>(n+1, INF));
    int s=0, t=n+n+1, ans=-1;
    Dinic D(n+n+2);
    
    for(; x>0; x--)
    {
        int v;
        scanf("%d", &v);
        D.add(s, v, 1);
    }
    
    for(; m>0; m--)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        e[u][v]=min(e[u][v], w);
        e[v][u]=min(e[v][u], w);
    }
    
    for(int i=1; i<=n; i++)
    {
        e[i][i]=0;
        D.add(n+i, t, 1);
    }
    
    for(int k=1; k<=n; k++)
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
                e[i][j]=min(e[i][j], e[i][k]+e[k][j]);
    
    for(int l=0, r=INF; l<r; )
    {
        m=(l+r)>>1;
        Dinic P=D;
        
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
                if( e[i][j]<=m )
                    P.add(i, n+j, 1);
        
        if( P(s, t)>=y )
            r=ans=m;
        else
            l=m+1;
    }
    
    printf("%d\n", ans);
}
