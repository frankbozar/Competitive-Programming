#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;

lld gcd(lld a, lld b)
{
    return b==0 ? a : gcd(b, a%b);
}

lld lcm(lld a, lld b)
{
    return a/gcd(a, b)*b;
}

int main()
{
    int n;
    scanf("%d", &n);
    vector<int> a(n+1, 0);
    
    for(int i=1; i<=n; i++)
        scanf("%d", &a[i]);
    
    int m=1;
    lld g=1;
    
    for(int i=1; i<=n; i++)
    {
        vector<int> u(n+1, 0);
        
        for(int l=0, s=i; ; u[s]=l++, s=a[s])
        {
            if( u[s] )
            {
                m=max(m, u[s]);
                g=lcm(g, l-u[s]);
                break;
            }
        }
    }
    
    printf("%lld\n", (m+g-1)/g*g);
}
