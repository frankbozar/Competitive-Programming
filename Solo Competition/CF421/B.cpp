#include<cstdio>
#include<cstdlib>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;

int main()
{
    int n, m=0, pos=0, neg=0;
    scanf("%d", &n);
    vector<int> a(n+1), c(n<<2, 0);
    lld dev=0;
    
    for(int i=1; i<=n; i++)
    {
        scanf("%d", &a[i]);
        dev+=abs(a[i]-i);
        c[ a[i]-i+n ]++;
        
        if( a[i]>i )
            pos++;
        else if( a[i]<i )
            neg++;
    }
    
    lld ans=dev;
    
    for(int i=1; i<n; i++)
    {
        neg-=a[n-i+1]<n;
        c[ a[n-i+1]-n+n+i-1 ]--;
        neg+=c[n+i-1];
        dev+=-abs(a[n-i+1]-n)+abs(a[n-i+1]-1)-pos+neg;
        pos-=c[n+i];
        c[ a[n-i+1]-1+n+i ]++;
        pos+=a[n-i+1]>1;
        
        if( ans>dev )
        {
            ans=dev;
            m=i;
        }
    }
    
    printf("%lld %d\n", ans, m);
}
