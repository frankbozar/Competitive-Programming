#include<cstdio>
#include<algorithm>
using namespace std;
const int INF=1<<30;

int main()
{
    int n, l=-INF, r=INF;
    scanf("%d", &n);
    int a[n][2];
    
    for(int i=0; i<n; i++)
        scanf("%d%d", &a[i][0], &a[i][1]);
    
    for(int s=0, i=n-1; i>=0 && l<r; i--)
    {
        s+=a[i][0];
        
        if( a[i][1]==1 )
            l=max(l, 1900+s);
        else
            r=min(r, 1900+s);
    }
    
    if( l>=r )
        printf("Impossible\n");
    else if( r>=INF )
        printf("Infinity\n");
    else
        printf("%d\n", r-1);
}
