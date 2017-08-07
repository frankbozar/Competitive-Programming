#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
const int INF=1<<20;
const int N=6000;

int sol(int n, int m, vector<int>& a, vector<int>& b)
{
    vector<vector<int>> dp(m+1, vector<int>(N, -INF));
    dp[0][0]=0;
    
    for(int i=0; i<n; i++)
        for(int j=min(i, m-1); j>=0; j--)
            for(int k=N-b[i]-1; k>=0; k--)
                dp[j+1][k+b[i]]=max(dp[j+1][k+b[i]], dp[j][k]+a[i]);
    
    int ans=0;
    
    for(int i=0; i<N; i++)
        ans=max(ans, min(i, dp[m][i]));
    
    return ans;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    vector<int> a(n, 0), b(n, 0);
    
    for(int i=0; i<n; i++)
    {
        lld x;
        scanf("%lld", &x);
        
        for(; x%2==0; x/=2)
            a[i]++;
        
        for(; x%5==0; x/=5)
            b[i]++;
    }
    
    printf("%d\n", sol(n, m, a, b));
}
