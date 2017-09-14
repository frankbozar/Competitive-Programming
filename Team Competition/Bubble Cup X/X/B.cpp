#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
typedef long long lld;
const lld mod=1000000007;
const int N=128;

struct matrix
{
    int n, m;
    lld a[N][N];
    
    matrix(int _n, int _m) : n(_n), m(_m)
    {
        memset(a, 0, sizeof(a));
    }
    
    matrix operator*(const matrix& M) const
    {
        matrix ans(n, M.m);
        
        for(int i=0; i<n; i++)
            for(int j=0; j<M.m; j++)
            {
                for(int k=0; k<m; k++)
                    ans.a[i][j]+=a[i][k]*M.a[k][j]%mod;
                
                ans.a[i][j]%=mod;
            }
        
        return ans;
    }
    
    matrix operator^(int p) const
    {
        matrix ans(n, n);
        
        for(int i=0; i<n; i++)
            ans.a[i][i]=1;
        
        for(matrix x=*this; p>0; p>>=1)
        {
             if( p&1 )
                 ans=ans*x;
            
            x=x*x;
        }
        
        return ans;
    }
};

int main()
{
    int m, k, n;
    scanf("%d%d%d", &m, &k, &n);
    vector<int> a(m), b(m), c(m);
    
    for(int i=0; i<m; i++)
        scanf("%d", &a[i]);
    
    for(int i=0; i<m; i++)
        scanf("%d", &b[i]);
    
    for(int i=0; i<m; i++)
        scanf("%d", &c[i]);
    
    matrix A(n, 1);
    
    for(int i=0; i<m; i++)
        A.a[ a[i]%n ][0]++;
    
    matrix B(n, n);
    
    for(int i=0; i<m; i++)
        for(int j=0; j<n; j++)
            B.a[(j+b[i])%n][j]++;
        
    matrix C(n, n);
    
    for(int i=0; i<m; i++)
        for(int j=0; j<n; j++)
            C.a[(j+b[i]+c[i])%n][j]++;
    
    B=B^(k-2);
    A=B*A;
    A=C*A;
    printf("%lld\n", A.a[0][0]);
}
