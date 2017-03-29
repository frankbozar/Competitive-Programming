#include<cstdio>
#include<vector>
using namespace std;
typedef long long lld;
const lld mod=1000000007;
const int H=25, N=1024;
lld dp[H][N]={{0}};

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    
    for(int i=0; i<=n; i++)
        dp[0][i]=1;
    
    for(int i=1; i<H; i++)
    {
        for(int j=0; j<N; j++)
        {
            for(int k=0; k<N; k++)
                dp[i][j]+=dp[i-1][k]*dp[i-1][j^k]%mod;
            
            dp[i][j]%=mod;
        }
    }
    
    lld ans[N]={0};
    
    for(int i=0; i<H; i++)
    {
        if( (m>>i)&1 )
        {
            for(int j=0; j<N; j++)
                ans[j]=dp[i][j];
            
            for(int h=i+1; h<H; h++)
            {
                if( (m>>h)&1 )
                {
                    lld tmp[N]={0};
                    
                    for(int j=0; j<N; j++)
                    {
                        tmp[j]=ans[j];
                        ans[j]=0;
                    }
                    
                    for(int j=0; j<N; j++)
                    {
                        for(int k=0; k<N; k++)
                            ans[j]+=tmp[k]*dp[h][j^k]%mod;
                        
                        ans[j]%=mod;
                    }
                }
            }
            
            break;
        }
    }
    
    printf("%lld\n", ans[0]);
}
