#include<cassert>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
const int N=1<<20, INF=1<<30;
const char* del=" \t\r\n";
char buf[N];

struct edge
{
    int u, v, w;
};

int dijk(const vector<edge>& e, const vector<int>& t, const int n)
{
    vector<int> d(n+1, INF);
    d[n]=0;
    
    for(int i=0; i<n; i++)
        for(const edge& E : e)
            d[E.v]=min(d[E.v], d[E.u]+E.w);
    
    int ans=0;
    
    for(int u : t)
        ans=max(ans, d[u]);
    
    return ans;
}

bool check(const char* s)
{
    for(; *s!='\0'; s++)
        if( '0'<=*s && *s<='9' )
            return true;
    
    return false;
}

int main()
{
    for(int n; scanf("%d ", &n)!=EOF; )
    {
        vector<edge> e;
        
        for(int u, v, w; fgets(buf, N-1, stdin) && sscanf(buf, "%d%d%d", &u, &v, &w)==3; )
            e.push_back(edge({u, v, w}));
        
        while( !check(buf) )
            fgets(buf, N-1, stdin);
        
        vector<int> t;
        
        for(const char* p=strtok(buf, del); p!=NULL; p=strtok(NULL, del))
            t.push_back(atoi(p));
        
        int q;
        int g=e.size();
        
        for(scanf("%d", &q); q>0; q--)
        {
            int m;
            e.resize(g);
            
            for(scanf("%d", &m); m>0; m--)
            {
                int x;
                scanf("%d", &x);
                e.push_back({n, x, 0});
            }
            
            printf("%d\n", dijk(e, t, n));
        }
    }
}

/*

5

0 1 96
0 2 14
1 2 37
2 3 19
3 4 75

1 1

1
2 0 3
5
0 1 57
0 2 48
1 2 90
2 4 19
3 4 52

2 4

1
2 0 3

*/