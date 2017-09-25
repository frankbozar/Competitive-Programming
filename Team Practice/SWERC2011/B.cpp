#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=1<<30;
const int N=1<<14;

struct BCC
{
    struct edge
    {
        int v, i;
        edge(int _v=0, int _i=0) : v(_v), i(_i){}
    };
    
    vector<vector<edge>> edg;
    vector<int> brg, dfn, low;
    
    BCC(const vector<pair<int, int>>& e) : edg(N), brg(e.size(), 0), dfn(N, 0), low(N, 0)
    {
        for(int i=e.size()-1; i>=0; i--)
            edg[e[i].first].push_back(edge(e[i].second, i));
        
        for(int i=0; i<N; i++)
            if( !dfn[i] )
                dfs(i);
    }
    
    void dfs(int u, int p=-1, int d=0)
    {
        dfn[u]=low[u]=++d;
        for(const edge& E : edg[u]){
            if( E.v!=p && dfn[E.v]>0 ) low[u]=min(low[u], dfn[E.v]);
            else if( dfn[E.v]==0 ){
                dfs(E.v, u, d);
                low[u]=min(low[u], low[E.v]);
                if( d<low[E.v] ) brg.push_back(E.i);
            }
        }
    }
};

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

struct ds
{
    vector<int> p, s;
    ds(int n) : p(n+1, -1), s(n+1, 1){}
    
    int find(int x)
    {
        return p[x]<0 ? x : p[x]=find(p[x]);
    }
    
    void join(int x, int y)
    {
        x=find(x);
        y=find(y);
        
        if( x!=y )
        {
            p[x]=y;
            s[y]+=s[x];
        }
    }
};

int main()
{
    for(int n; scanf("%d", &n) && n>0; )
    {
        vector<pair<int, int>> e(n<<1);
        
        for(int i=0; i<n<<1; i++)
            scanf("%d%d", &e[i].first, &e[i].second);
        
        int ans=0;
        BCC B(e);
        ds S(N);
        
        for(int i=0; i<n<<1; i+=2)
        {
            if( B.brg[i] || B.brg[i+1] )
            {
                B.brg[i]=B.brg[i+1]=1;
                ans++;
            }
            else
            {
                S.join(e[i].first, e[i].second);
                S.join(e[i+1].first, e[i+1].second);
            }
        }
        
        Dinic D(n+N+2);
        int s=n+N;
        int t=n+N+1;
        
        for(int i=0; i<n; i++)
            D.add(s, i, 1);
        
        for(int i=0; i<n<<1; i++)
            if( !B.brg[i] )
                D.add(i>>1, n+S.find(e[i].first), 1);
        
        for(int i=0; i<N; i++)
            if( S.s[i]>1 && S.find(i)==i )
                D.add(n+i, t, S.s[i]-1);
        
        printf("%d\n", (ans+D(s, t))<<1);
    }
}

/*

4
0 1 0 5
5 1 0 5
1 2 0 1
1 5 2 0

6
1 4 1 4
2 4 2 4
0 3 0 3
0 4 0 4
4 3 4 3
1 3 1 3

0

*/
