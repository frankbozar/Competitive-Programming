#include<cmath>
#include<cstdio>
#include<vector>
using namespace std;
const int INF=1<<20;
const double EPS=1e-20;

double sol(const vector<vector<int>>& e, int n, int m)
{
    vector<double> d(n+1, 0), p(n+1, 0);
    
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
            d[i]+=e[i][j];
        
        d[i]/=(n-1);
    }
    
    if( n==2 )
        return d[1]*m;
    
    double ans=0;
    
    for(p[1]=1; m>0; m--)
    {
        vector<double> q(n+1, 0);
        
        for(int i=1; i<=n; i++)
        {
            ans+=p[i]*d[i];
            
            for(int j=1; j<=n; j++)
                if( j!=i )
                    q[j]+=p[i]/(n-1);
        }
        
        double det=0;
        
        for(int i=1; i<=n; i++)
        {
            det+=fabs(p[i]-q[i]);
            p[i]=q[i];
        }
        
        if( det<EPS )
        {
            for(int i=1; i<=n; i++)
                ans+=p[i]*d[i]*(m-1);
            
            break;
        }
    }
    
    return ans;
}

int main()
{
    int ncase;
    scanf("%d", &ncase);
    
    for(int cases=1; cases<=ncase; cases++)
    {
        int n, m, k;
        scanf("%d%d%d", &n, &m, &k);
        vector<vector<int>> e(n+1, vector<int>(n+1, INF));
        
        for(; m>0; m--)
        {
            int u ,v ,w;
            scanf("%d%d%d", &u, &v, &w);
            e[u][v]=e[v][u]=w;
        }
        
        for(int i=1; i<=n; i++)
            e[i][i]=0;
        
        for(int k=1; k<=n; k++)
            for(int i=1; i<=n; i++)
                for(int j=1; j<=n; j++)
                    e[i][j]=min(e[i][j], e[i][k]+e[k][j]);
        
        printf("Case #%d: %.10f\n", cases, sol(e, n, k));
    }
}
