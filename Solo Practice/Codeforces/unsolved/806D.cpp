#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
const int INF=1<<30;

lld solve(const vector<vector<int>>& e, int n, int u)
{
    lld ans=0;
    vector<int> d(n+1, INF);
    d[u]=0;
    
    for(int k=0; k<n; k++)
    {
        int v=n;
        
        for(int i=0; i<n; i++)
            if( d[v]>d[i] && d[i]>=0 )
                v=i;
        
        ans+=d[v];
        
        for(int i=0; i<n; i++)
        {
            if( i==v )
                continue;
            
            d[i]=min(d[i], e[v][i]);
            
            if( v!=u )
                d[i]=min(d[i], d[v]);
        }
        
        d[v]=-1;
    }
    
    return ans;
}

int main()
{
    int n;
    scanf("%d", &n);
    vector<vector<int>> e(n, vector<int>(n, 0));
    
    for(int i=0; i<n; i++)
    {
        for(int j=i+1; j<n; j++)
        {
            scanf("%d", &e[i][j]);
            e[j][i]=e[i][j];
        }
    }
    
    for(int i=0; i<n; i++)
        printf("%lld\n", solve(e, n, i));
}
