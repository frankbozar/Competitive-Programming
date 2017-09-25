#include<cstdio>
#include<vector>
using namespace std;
const double EPS=1e-12;

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n, k;
        scanf("%d%d", &n, &k);
        vector<int> a(n+1, 0);
        int ans[2]={0, k};
        
        for(int i=1; i<=n; i++)
        {
            scanf("%1d", &a[i]);
            a[i]+=a[i-1];
        }
        
        for(double l=0, r=1; r-l>EPS; )
        {
            double m=(l+r)/2;
            int tmp[2]={0, n+1};
            
            for(int i=0, j=k; j<=n; j++)
            {
                if( a[i]-m*i>=a[j-k]-m*(j-k) )
                    i=j-k;
                
                if( a[i]-m*i<=a[j]-m*j )
                {
                    if( tmp[1]-tmp[0]>j-i )
                        tmp[0]=i, tmp[1]=j;
                }
            }
            
            if( tmp[1]>n )
                r=m;
            else
                l=m, ans[0]=tmp[0], ans[1]=tmp[1];
        }
        
        printf("%d %d\n", ans[0]+1, ans[1]);
    }
}

/*

2

17 5
00101011011011010

20 4
11100111100111110000

*/
