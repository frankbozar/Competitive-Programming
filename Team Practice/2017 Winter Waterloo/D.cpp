#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
const lld mod=1000000007;
const int N=32;
lld c[N][N], a[N][N*N];

lld C(int n, int m)
{
    if( m<0 || n<m )
        return 0;
    else if( n==m || m==0 )
        return 1;
    
    lld& ans=c[n][m];
    
    if( ans<0 )
        ans=(C(n-1, m-1)+C(n-1, m))%mod;
    
    return ans;
}

lld sol(int n, int m)
{
    if( m<n || m>n*(n+1)>>1 )
        return 0;
    else if( n<=1 )
        return n==m;
    
    lld& ans=a[n][m];
    
    if( ans<0 )
    {
        ans=0;
        m-=n--;
        
        for(int i=0; i<=n; i++)
            for(int j=0; j<=m; j++)
                ans+=sol(i, j)*sol(n-i, m-j)%mod*C(n, i)%mod;
        
        ans%=mod;
    }
    
    return ans;
}

int main()
{
    memset(c, 0xFF, sizeof(c));
    memset(a, 0xFF, sizeof(a));
    int n, m;
    scanf("%d%d", &n, &m);
    printf("%lld\n", sol(n, m));
}
