#include<cstdio>
#include<vector>
using namespace std;
typedef long long lld;
const int INF=0x3FFFFFFF;

int main()
{
    int n, m, t, len=0;
    lld ans=0;
    scanf("%d%d", &n, &m);
    vector<vector<int>> d(n+1, vector<int>(n+1, INF));
    
    for(int i=0; i<m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        d[u][v]=d[v][u]=w;
    }
    
    scanf("%d", &t);
    vector<vector<int>> a(t);
    
    for(int i=0; i<t; i++)
    {
        int l;
        scanf("%d", &l);
        len+=l+l-1;
        
        for(int j=0; j<l; j++)
        {
            int x;
            scanf("%d", &x);
            a[i].push_back(x);
            
            if( j>0 )
                ans+=d[ a[i][j] ][ a[i][j-1] ]<<1;
        }
    }
    
    vector<int> p(n+1, -1);
    p[1]=0;
    
    for(int i=0; i<n; i++)
        for(int j=1; j<=n; j++)
            if( p[j]>=0 )
                for(int k=1; k<=n; k++)
                    if( p[k]<0 && d[j][k]<INF )
                        p[k]=j;
    
    if( p[n]<0 )
    {
        printf("-1\n");
        return 0;
    }
    
    vector<int> last;
    
    for(int u=n; u!=1; u=p[u])
    {
        last.push_back(u);
        ans+=d[u][ p[u] ];
    }
    
    len+=last.size();
    
    for(int i=0; i<t; i++)
    {
        printf("%lu 1", len-t+1);
        
        for(int k=1; k<a[i].size(); k++)
            printf(" %d", a[i][k]);
        
        for(int k=a[i].size()-2; k>=0; k--)
            printf(" %d", a[i][k]);
        
        for(int j=0; j<t; j++)
        {
            if( j==i )
                continue;
            
            for(int k=1; k<a[j].size(); k++)
                printf(" %d", a[j][k]);
            
            for(int k=a[j].size()-2; k>=0; k--)
                printf(" %d", a[j][k]);
        }
        
        for(int k=last.size()-1; k>=0; k--)
            printf(" %d", last[k]);
        
        printf("\n");
    }
}

/*

5 4
1 2 10
2 3 30
2 4 30
1 4 100
15
2 1 2
3 1 2 3
2 1 4
2 1 2
3 1 2 3
2 1 4
2 1 2
3 1 2 3
2 1 4
2 1 2
3 1 2 3
2 1 4
2 1 2
3 1 2 3
2 1 4

*/
