#include<cmath>
#include<cstdio>
#include<vector>
using namespace std;
const int STEP=100000;
//const double EPS=1e-4;

void bf(const vector<double>& p, vector<int>& c, int n, int m, int x, double& ans, double q=1)
{
    if( n==0 )
    {
        for(int i=1; i<x; i++)
            if( c[i]==1 )
                return;
        
        if( c[x]==1 )
            ans+=q;
        
        return ;
    }
    
    for(int i=1; i<=m; i++)
    {
        c[i]++;
        bf(p, c, n-1, m, x, ans, q*p[i]);
        c[i]--;
    }
}

double sol(const vector<double>& p, int n, int m, int x)
{
    double ans=0;
    vector<int> c(m+1, 0);
    bf(p, c, n-1, m, x, ans);
    return ans;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    
    if( m==1 )
    {
        printf("1\n");
        return 0;
    }
    
    vector<double> p(m+1, 1.0/m);
    double EPS=1e-6;
    
    for(int step=0; step<STEP; step++)
    {
        if( step%100==0 )
            EPS/=1;
        
        double q=0;
        int b=0;
        
        for(int i=1; i<=m; i++)
        {
            double t=sol(p, n, m, i);
            
            if( q<t )
                q=t, b=i;
        }
        
        p[b]+=EPS;
        
        for(int i=1; i<=m; i++)
            p[i]/=(1+EPS);
    }
    
    for(int i=1; i<=m; i++)
        printf("%.4f\n", p[i]);
}
