#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long lld;
const lld M=100000007;
const int N=1<<20;

lld pmd(lld x, lld p)
{
    lld ans=1;
    
    for(; p>0; p>>=1)
    {
        if( p&1 )
            ans=ans*x%M;
        
        x=x*x%M;
    }
    
    return ans;
}

lld inv(lld x)
{
    return pmd(x, M-2);
}

lld gcd(lld a, lld b)
{
    return b==0 ? a : gcd(b, a%b);
}

int Z(int m, int n, const int s[], int z[])
{
    lld ans=pmd(m, n);
    lld cnt=1;
    z[0]=n;
    
    for(int l=0, r=0, i=1; i<n; i++)
    {
        if( r<i || r-i<z[i-l] )
        {
            if( r<i ) r=i;
            for(l=i; r<n<<1 && s[r]==s[r-l]; r++);
            z[i]=r---l;
        }else z[i]=z[i-l];
        
        if( z[i]>=n )
        {
            ans+=pmd(m, gcd(n, i));
            cnt++;
        }
    }
    
    return ans%M*inv(cnt)%M;
}

int a[N], z[N];

int main()
{
    for(int n, m; scanf("%d%d", &n, &m) && n>=0 && m>=0; )
    {
        for(int i=0; i<m; i++)
            scanf("%d", &a[i]);
        
        sort(a, a+m);
        
        for(int i=m-1; i>=0; i--)
            a[i]-=a[0];
        
        a[m]=360000;
        
        for(int i=0; i<m; i++)
            a[i]=a[i+1]-a[i];
        
        for(int i=0; i<m; i++)
            a[i+m]=a[i];
        
        printf("%d\n", Z(n, m, a, z));
    }
}

/*

2 4
0 90000 180000 270000

100 5
0 45000 90000 180000 270000

-1 -1

*/
