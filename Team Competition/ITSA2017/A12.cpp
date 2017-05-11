#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
const lld INF=1LL<<60;
#define edge pair<int,lld>
#define v first
#define w second
vector<vector<edge>> e;
vector<int> s;

int dfs(lld& ans, bool& flag, int n, int u=1)
{
    s[u]=0;
    
    for(const edge& E : e[u])
    {
        if( s[E.v]>=0 )
            continue;
        
        int x=dfs(ans, flag, n, E.v);
        int y=n-x;
        ans+=E.w*min(x, y)<<1;
        s[u]+=x;
        
        if( x==y )
        {
            flag=true;
            ans-=E.w;
        }
    }
    
    return ++s[u];
}

int dfs(int n, int u=1)
{
    for(const edge& E : e[u])
        if( s[E.v]<s[u] && s[E.v]<<1>n )
            return dfs(n, E.v);
    
    return u;
}

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n;
        scanf("%d", &n);
        e.clear();
        e.resize(n+1);
        s.assign(n+1, -1);
        
        for(int i=1; i<n; i++)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            e[u].push_back(edge(v, w));
            e[v].push_back(edge(u, w));
        }
        
        lld ans=0;
        bool flag=false;
        dfs(ans, flag, n);
        
        if( !flag && n>1 )
        {
            lld tmp=INF;
            
            for(const edge& E : e[dfs(n)])
                tmp=min(tmp, E.w);
            
            ans-=tmp;
        }
        
        printf("%lld\n", ans);
    }
}

/*

6

4
1 2 6
2 3 2
3 4 3

6
1 2 5
2 3 9
2 4 4
4 5 8
5 6 7

4
1 2 15
1 3 7
1 4 9

3
1 2 10
2 3 100

2
1 2 1000

1

*/
