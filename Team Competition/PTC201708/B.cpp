
#include<cstdio>

using namespace std;

typedef long long lld;

const int N=33;

lld dp[N+2];

int main()
{
    dp[1]=1;
    for(int i=2; i<=N; i++)
    {
        for(int j=1; j<=i-1; j++)
            dp[i]+=dp[j]*dp[i-j];
    }
    int T;
    for(scanf("%d", &T); T>0; T--)
    {
        int n;
        scanf("%d", &n);
        n++;
        printf("%lld\n", dp[n]);

    }



}
