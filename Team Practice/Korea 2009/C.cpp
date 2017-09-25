#include<cstdio>
#include<vector>
using namespace std;
const int INF=1<<30;

bool ok(const vector<int>& a, const vector<int>& b, int n, int m)
{
    int v[3]={0}, p=m, q=m;
    
    for(int i=n; i>0; i--)
    {
        if( a[i]>0 && b[i]>0 )
            v[0]++;
        else if( a[i]>0 )
            v[1]++;
        else if( b[i]>0 )
            v[2]++;
        
        p-=a[i]-a[i-1];
        q-=b[i]-b[i-1];
        
        if( p<0 )
        {
            
            
            
        }
        
        
        
    }
    
    return true;
}

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n, ans=-1;
        scanf("%d", &n);
        vector<int> a(n+1, 0), b(n+1, 0);
        
        for(int i=1; i<=n; i++)
        {
            scanf("%d%d", &a[i], &b[i]);
            a[i]+=a[i-1];
            b[i]+=b[i-1];
        }
        
        for(int l=0, r=INF; l<r; )
        {
            int m=(l+r)>>1;
            
            if( ok(a, b, n, m) )
                r=ans=m;
            else
                l=m+1;
        }
        
        printf("%d\n", ans);
    }
}

/*

3

1
1 1

3
3 2
0 3
2 0

6
0 1
1 1
1 2
1 1
1 1
6 0

*/
