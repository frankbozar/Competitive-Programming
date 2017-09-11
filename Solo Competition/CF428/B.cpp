#include<cstdio>
#include<algorithm>
using namespace std;

bool sol(int n, int a[4])
{
    int f=n, t=n<<1;
    
    if( a[0]>f )
    {
        t-=(a[0]-f)<<1;
        f=0;
    }
    else
    {
        f-=a[0];
    }
    
    if( a[3]>f )
    {
        a[1]+=a[3]-f;
        a[2]+=a[3]-f;
        f=0;
    }
    else
    {
        f-=a[3];
    }
    
    if( a[2]>t )
    {
        a[2]-=t;
        t=0;
        
        if( f<a[2] )
            return false;
        
        f-=a[2];
        t+=a[2];
    }
    else
    {
        t-=a[2];
    }
    
    return (f<<1)+t>=a[1];
}

int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    int a[4]={0};
    
    for(int i=0; i<k; i++)
    {
        int x;
        scanf("%d", &x);
        a[0]+=x>>2;
        
        if( x&3 )
            a[x&3]++;
    }
    
    printf(sol(n, a) ? "YES\n" : "NO\n");
}
