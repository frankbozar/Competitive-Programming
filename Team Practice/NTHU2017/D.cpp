#include<cstdio>
#include<vector>
using namespace std;

int gcd(int a, int b)
{
    return b==0 ? a : gcd(b, a%b);
}

int main()
{
    int n, m;
    scanf("%d", &n);
    vector<int> a(n);
    
    for(int i=0; i<n; i++)
        scanf("%d", &a[i]);
    
    for(scanf("%d", &m); m>0; m--)
    {
        int x, g=0;
        scanf("%d", &x);
        
        for(int i=0; i<n; i++)
            if( a[i]%x==0 )
                g=gcd(g, a[i]);
        
        printf(g==x ? "YES\n" : "NO\n");
    }
}
