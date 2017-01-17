#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
const int INF=0x3FFFFFFF;
#define data pair<int,int>
#define u first
#define v second

int main()
{
    int ncase;
    scanf("%d", &ncase);
    
    for(int cases=1; cases<=ncase; cases++)
    {
        int n, m, k;
        scanf("%d%d%d", &n, &m, &k);
        vector<vector<int>> d(n+1, vector<int>(n+1, INF));
        
        for(int i=1; i<=n; i++)
            d[i][i]=0;
        
        for(int i=1; i<=m; i++)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            d[u][v]=min(d[u][v], w);
            d[v][u]=min(d[v][u], w);
        }
        
        for(int k=1; k<=n; k++)
            for(int i=1; i<=n; i++)
                for(int j=1; j<=n; j++)
                    d[i][j]=min(d[i][j], d[i][k]+d[k][j]);
        
        
        /*
        vector<data> a(k);
        
        for(int i=0; i<k; i++)
            scanf("%d%d", &a[i].u, &a[i].v);
        */
        lld a1=0, a2=0;
        int p=1, q=1;
        
        for(int i=0; i<k; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            
            if( q<0 )
            {
                ans+=d[p][u];
                p=u;
                q=v;
            }
            else
            {
                
                
                
            }
        }
        
        printf("Case #%d: %lld\n", cases, ans);
    }
}

/*

5

7 3
1 5
2 3
2 1
5 1
6 3
4 4
4 5

4 1
0 0
0 2
10 0
10 2

4 2
0 0
0 2
10 0
10 2

7 3
8 5
3 6
9 2
4 5
3 2
1 8
2 8

7 6
8 5
3 6
9 2
4 5
3 2
1 8
2 8

*/
