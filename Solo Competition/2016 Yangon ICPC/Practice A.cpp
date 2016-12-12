#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
#define book pair<int,int>
#define h first
#define t second
const int INF=0x3F3F3F3F;
int dp[2200][2200];

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n;
        scanf("%d", &n);
        vector<book> a(n);
        
        for(int i=0; i<n; i++)
            scanf("%d%d", &a[i].h, &a[i].t);
        
        sort(a.rbegin(), a.rend());
        memset(dp, 0x3F, sizeof(dp));
        dp[0][0]=0;
        int st=0, ans=INF;
        
        for(int k=0; k<n; k++)
        {
            st+=a[k].t;
            dp[st][0]=a[0].h;
            dp[st-a[k].t][a[k].t]=dp[st-a[k].t][0]+a[k].h;
            
            for(int i=st-a[k].t; i>0; i--)
            {
                for(int j=st-a[k].t-i; j>0; j--)
                {
                    dp[i+a[k].t][j]=min(dp[i+a[k].t][j], dp[i][j]);
                    dp[i][j+a[k].t]=min(dp[i][j+a[k].t], dp[i][j]);
                }
                
                dp[i][st-a[k].t-i]=dp[i][st-a[k].t-i]+a[k].h;
            }
        }
        
        for(int i=1; i<st; i++)
            for(int j=1; i+j<st; j++)
                ans=min((lld)ans, dp[i][j]*(lld)max(max(i, j), st-i-j));
        
        printf("%d\n", ans);
    }
}

/*

2

4
220 29
195 20
200 9
180 30

6
256 20
255 30
254 15
253 20
252 15
251 9

*/