#include<cstdio>
typedef long long lld;
lld a[1<<11];

int main()
{
    lld n, k, m;
    scanf("%lld%lld%lld", &n, &k, &m);
    
    for(lld i=0; i<n; i++)
    {
        scanf("%lld", &a[i]);
        a[i]%=m;
    }
    
    
    for(lld i=0; i<=k; i++)
    {
        lld ans=0;
        
        for(int j=n-1; j>=0; j--)
            ans=(ans*i+a[j])%m;
        
        printf(i==k ? "%lld\n" : "%lld ", ans%m);
    }
}

/*

2 4 239
17 3

3 5 11
5 8 1


*/
