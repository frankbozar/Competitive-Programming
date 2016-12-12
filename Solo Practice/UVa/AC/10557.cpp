#include<cstdio>
#include<vector>
using namespace std;
const int INF=1<<20;

void solve(const vector<vector<int>>& d, const int n)
{
    
    
    
    
}

int main()
{
    for(int n; scanf("%d", &n) && n>0; )
    {
        vector<int> d(n+1, vector<int>(n+1, INF));
        
        for(int i=1; i<=n; i++)
        {
            d[i][i]=0;
            int c, l;
            
            for(scanf("%d%d", &c, &l); l>0; l--)
            {
                int j;
                scanf("%d", &j);
                d[i][j]=min(d[i][j], -c);
            }
        }
        
        for(int k=1; k<=n; k++)
            for(int i=1; i<=n; i++)
                for(int j=1; j<=n; j++)
                {
                    if( d[i][k] )
                    d[i][j]=min(d[i][k]+d[k][j]);
                }
        
        solve(d, n);
    }
}