#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=1<<30;

int gcd(int a, int b)
{
    return b==0 ? a : gcd(a, b) ;
}

int main()
{
    for(int n; scanf("%d", &n) && n>=2; )
    {
        vector<int> a(n);
        
        for(int i=0; i<n; i++)
            scanf("%d", &a[i]);
        
        vector<vector<int>> d(n+1, vector<int>(n, INF));
        
        for(int i=0; i<2; i++)
            d[i].assign(n, 0);
        
        for(int k=2; k<=n; k++)
        {
            for(int i=0; i<n; i++)
            {
                int j=i+k%n;
                
                for(int l=1; l<k; l++)
                    d[i][j]=min(d[i][j], d[l][i]+d[k-l][i+l%n]);
                
                d[i][j]+=gcd(a[i], a[j])+(k==);
            }
        }
        
        int ans=INF;
        
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                if(  )
        
        printf("%d\n", ans);
    }
}
