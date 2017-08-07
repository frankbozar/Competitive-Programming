#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=1<<30;

int main()
{
    int n;
    scanf("%d", &n);
    vector<int> a(n+1, -1), b(n+1, -1);
    vector<int> u(n+1, INF), p(n+1, 0);
    vector<int> v(n+1, -INF), q(n+1, 0);
    
    for(int i=1; i<=n; i++)
        scanf("%d", &a[i]);
    
    for(int i=1; i<=n; i++)
    {
        scanf("%d", &b[i]);
        
        for(int j=n; j>0; j--)
        {
            if( a[j]!=b[i] )
                continue;
            
            if( b[i]<u[j-1] )
            {
                if( q[j]<p[j-1]+1 )
                    q[j]=p[j-1]+1, v[j]=b[i];
                else if( q[j]==p[j-1]+1 )
                    v[j]=min(v[j], b[i]);
            }
            else
                u[j]=max(u[j], b[i]);
            
            if( b[i]>v[j-1] )
            {
                if( p[j]<q[j-1]+1 )
                    p[j]=q[j-1]+1, u[j]=b[i];
                else if( p[j]==q[j-1]+1 )
                    u[j]=max(u[j], b[i]);
            }
            else
                v[j]=min(v[j], b[i]);
        }
        
        for(int j=1; j<=n; j++)
        {
            if( p[j]<p[j-1] )
                p[j]=p[j-1], u[j]=u[j-1];
            else if( p[j]==p[j-1] )
                u[j]=max(u[j], u[j-1]);
            
            if( q[j]<q[j-1] )
                q[j]=q[j-1], v[j]=v[j-1];
            else if( q[j]==q[j-1] )
                v[j]=min(v[j], v[j-1]);
        }
    }
    
    printf("%d\n", max(p[n], q[n]));
}
