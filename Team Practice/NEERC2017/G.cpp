#include<cstdio>
#include<set>
#include<vector>
#include<algorithm>
using namespace std;
typedef pair<int, int> data;

struct lca
{
    const int H=20;
    int n, dfn=0, cnt=0, ans=0;
    vector<int> h, s, r, o, a;
    vector<vector<int>> c, p;
    vector<set<data>> S;

    lca(int _n) : n(_n), h(n+1, 0), s(n+1, 0), r(n+1, 0), o(n+1, 0), a(n+1, 0), c(n+1), p(H, vector<int>(n+1, 1)), S(n+1)
    {
        for(int i=2; i<=n; i++)
        {
            scanf("%d", &p[0][i]);
            c[ p[0][i] ].push_back(i);
        }
        
        for(int u : c[1])
            dfs(u, u);
        
        for(int i=1; i<H; i++)
            for(int j=1; j<=n; j++)
                p[i][j]=p[i-1][ p[i-1][j] ];
    }
    
    void dfs(int root, int u, int d=0)
    {
        h[u]=d++;
        s[u]=c[u].empty();
        r[u]=root;
        o[u]=dfn++;
        
        for(int v : c[u])
        {
            dfs(root, v, d);
            s[u]+=s[v];
        }
    }
    
    int query(int u, int v) const
    {
        if( h[u]>h[v] )
            swap(u, v);
        
        for(int i=0, d=h[v]-h[u]; d>0; d>>=1, i++)
            if( d&1 )
                v=p[i][v];
        
        for(int i=0; u!=v; i++)
        {
            for(; i>0 && p[i][u]==p[i][v]; i--);
            u=p[i][u];
            v=p[i][v];
        }
        
        return u;
    }
    
    void operator()(int x)
    {
        if( x<0 )
        {
            x=-x;
            S[ r[x] ].erase(data(o[x], x));
            cnt-=S[ r[x] ].empty();
        }
        else
        {
            cnt+=S[ r[x] ].empty();
            S[ r[x] ].insert(data(o[x], x));
        }
        
        x=r[x];
        int tmp=0;
        
        if( !S[x].empty() )
        {
            int l=query(S[x].begin()->second, S[x].rbegin()->second);
            tmp=s[l]-S[x].size();
        }
        
        ans+=tmp-a[x];
        a[x]=tmp;
        printf("%d %d\n", cnt, ans);
    }
};

int main()
{
    //freopen("gangsters.in", "rb", stdin);
    //freopen("gangsters.out", "wb", stdout);
    int n, m;
    scanf("%d%d", &n, &m);
    
    for(lca L(n); m>0; m--)
    {
        char c;
        int x;
        scanf(" %c%d", &c, &x);
        
        if( c=='-' )
            L(-x);
        else
            L(x);
    }
}

/*

7 6
1 2 1 3 3 3
+ 4
+ 5
+ 6
+ 7
- 6
- 5

*/
