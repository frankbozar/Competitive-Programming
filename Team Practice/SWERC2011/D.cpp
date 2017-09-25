#include<cstdio>
#include<vector>
using namespace std;
const int INF=1<<30;

bool ok(const vector<int>& a, int n, int m)
{
    int cnt=0;
    
    for(int x : a)
        cnt+=(x+m-1)/m;
    
    return cnt<=n;
}

int main()
{
    for(int n, m; scanf("%d%d", &n, &m) && n>0 && m>0; )
    {
        int ans=-1;
        vector<int> a(n);
        
        for(int i=0; i<n; i++)
            scanf("%d", &a[i]);
        
        for(int l=0, r=INF; l<r; )
        {
            int x=(l+r)>>1;
            
            if( ok(a, m, x) )
                r=ans=x;
            else
                l=x+1;
        }
        
        printf("%d\n", ans);
    }
}

/*

2 7
200000 500000

4 6
120 2680 3400 200

-1 -1

*/
