#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
    int n, ans=0;
    scanf("%d", &n);
    vector<int> a(n+2, n<<1), c(n+2, 0);
    
    for(int i=n; i>0; i--)
    {
        c[i]+=c[i+1];
        a[i]=c[i];
        
        if( a[i]<a[i+1] )
        {
            int t=min(i-1, a[i+1]-a[i]-1);
            a[i]+=t;
            c[i-1]++;
            c[i-1-t]--;
            ans++;
        }
    }
    
    printf("%d\n", ans);
    
    for(int i=1; i<=n; i++)
        printf(i==n ? "%d\n" : "%d ", a[i]);
}
