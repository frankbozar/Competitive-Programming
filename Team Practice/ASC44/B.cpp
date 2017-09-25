#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const double INF=1e100;

double solve(const vector<vector<double>>& a, int u, int v)
{
    double A=a[v][0]-a[u][0];
    double B=a[v][1]-a[u][1];
    double C=a[v][2]-a[u][2];
    double D=a[v][3]-a[u][3];
    double k1=0, k2=0;
    
    if( A+C>0 )
    {
        k1=(C+D-B)/(A+C);
        k2=(A-D+B)/(A+C);
        
        if( k1>1 )
            k1=1, k2=0;
        
        if( k2>1 )
            k2=1, k1=0;
    }
    
    return min(A*k1+B, C*k2+D);
}

int main()
{
    freopen("braess.in", "rb", stdin);
    freopen("braess.out", "wb", stdout);
    int n;
    scanf("%d", &n);
    vector<vector<double>> a(n+1, vector<double>(4, 0));
    vector<double> ans(4, 0);
    
    for(int i=1; i<=n; i++)
    {
        for(int j=0; j<4; j++)
        {
            scanf("%lf", &a[i][j]);
            a[i][j]+=a[i-1][j];
        }
    }
    
    ans[0]=solve(a, 0, n);
    
    for(int i=0; i<n; i++)
        ans[1]+=solve(a, i, i+1);
    
    vector<double> d(n+1, INF), p(n+1, -INF);
    d[0]=p[0]=0;
    
    for(int i=0; i<n; i++)
    {
        for(int j=i+1; j<=n; j++)
        {
            double t=solve(a, i, j);
            d[j]=min(d[j], d[i]+t);
            p[j]=max(p[j], p[i]+t);
        }
    }
    
    ans[2]=d[n];
    ans[3]=p[n];
    
    for(int i=0; i<4; i++)
        printf("%.10f\n", ans[i]);
}
