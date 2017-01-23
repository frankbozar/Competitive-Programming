#include<cstdio>
#include<vector>
using namespace std;
typedef long long lld;
const int N=60;

bool check(const vector<lld>& a, const vector<lld>& b, const vector<lld>& c, const int n)
{
    for(int x : a)
        if( x<0 )
            return false;
    
    vector<int> d(N, 0);
    
    for(int i=0; i<n; i++)
        for(int j=0; j<N; j++)
            d[j]+=(a[i]>>j)&1;
    
    for(int i=0; i<n; i++)
    {
        lld B=0, C=0;
        
        for(int j=0; j<N; j++)
        {
            if( !((a[i])>>j&1) )
                C+=(1LL<<j)*d[j];
            else
            {
                B+=(1LL<<j)*d[j];
                C+=(1LL<<j)*n;
            }
        }
        
        if( B!=b[i] || C!=c[i] )
            return false;
    }
    
    return true;
}

int main()
{
    int n;
    scanf("%d", &n);
    vector<lld> a(n), b(n), c(n);
    lld s=0;
    
    for(int i=0; i<n; i++)
    {
        scanf("%lld", &b[i]);
        s+=b[i];
    }
    
    for(int i=0; i<n; i++)
    {
        scanf("%lld", &c[i]);
        s+=c[i];
    }
    
    s/=n<<1;
    
    for(int i=0; i<n; i++)
        a[i]=(b[i]+c[i]-s)/n;
    
    if( !check(a, b, c, n) )
        printf("-1\n");
    else
    {
        for(int i=0; i<n; i++)
            printf(i==n-1 ? "%lld\n" : "%lld ", a[i]);
    }
}
