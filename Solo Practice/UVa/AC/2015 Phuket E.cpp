#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long lld;
const int mod=1000000007;
int a[60000], b[200], c[60000][2000], d[200][2000];

int C(int n, int m)
{
    if( m<0 || m>n )
        return 0;
    else if( m>n-m )
        return C(n, n-m);
    else if( m==0 )
        return 1;
    
    int& ans=c[n][m];
    
    if( ans<0 )
        ans=(C(n-1, m-1)+C(n-1, m))%mod;
    
    return ans;
}

lld H(int n, int m)
{
    return C(m+n-1, n-1);
}

int solve(int n, int m)
{
    memset(d, 0, sizeof(d));
    d[0][0]=1;
    
    for(int s=0, i=1; i<n; i++)
    {
        s+=b[i-1];
        
        for(int j=0; j<=min(s+b[i], m); j++)
            for(int k=0; k<=min(b[i], j); k++)
                d[i][j]=(d[i][j]+d[i-1][j-k]*H(s, k))%mod;
    }
    
    return d[n-1][m];
}

int main()
{
    memset(c, -1, sizeof(c));
    int ncase;
    scanf("%d", &ncase);
    
    for(int cases=1; cases<=ncase; cases++)
    {
        int n, m, k=0;
        scanf("%d%d", &n, &m);
        
        for(int i=1; i<=n; i++)
            scanf("%d", &a[i]);
        
        sort(a, a+n+1);
        
        for(int i=1; i<=n; i++)
        {
            if( a[i]==a[i-1] )
                b[k-1]++;
            else
                b[k++]=1;
        }
        
        printf("Case %d: %d\n", cases, solve(k, m));
    }
}

/*

3
3 1
1 2 3
3 1
1 2 2
3 2
1 2 3

*/
