#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
const int H=20;

int main()
{
    int n, m, d;
    scanf("%d%d", &n, &d);
    vector<vector<int>> a(H+1, vector<int>(n+1, 0)), b(n+1);
    
    for(int i=1; i<=n; i++)
    {
        int x;
        scanf("%d", &x);
        a[x][i]=1;
        
        for(int h=1; h<=H; h++)
            a[h][i]+=a[h][i-1];
    }
    
    scanf("%d", &m);
    
    for(int i=1; i<=m; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        b[x].push_back(y);
    }
    
    for(int i=1; i<=n; i++)
    {
        sort(b[i].begin(), b[i].end());
        a[0][i]=a[0][i-1]+b[i].size();
    }
    
    lld ans=0;
    
    for(int i=1; i<=n; i++)
    {
        m=b[i].size();
        int r=min(i+d, n);
        int l=i+max(1, d-H*2);
        l=min(l, n+1);
        ans+=(a[0][l-1]-a[0][i])*m;
        
        for(int j=0; j<m; j++)
        {
            for(int k=j+1; k<m; k++)
                if( b[i][k]-b[i][j]<=d )
                    ans++;
            
            for(int x=l; x<=r; x++)
            {
                int h=1;
                
                while( h<H && a[h][x-1]-a[h][i]==0 )
                    h++;
                
                h=min(h, b[i][j]);
                
                for(int y : b[x])
                {
                    int t=min(h, y);
                    
                    if( (b[i][j]-t)+(y-t)+(x-i)<=d )
                        ans++;
                }
            }
        }
    }
    
    printf("%lld\n", ans);
}
