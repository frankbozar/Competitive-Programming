#include<cmath>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const double PI=acos(-1);

struct circle
{
    double x, y, r;
    
    void read()
    {
        scanf("%lf%lf%lf", &x, &y, &r);
    }
    
    double operator()() const
    {
        return r*r*PI;
    }
    
    double operator()(const circle& C) const
    {
        double dx=x-C.x;
        double dy=y-C.y;
        double dr=r-C.r;
        return dr>0 && dx*dx+dy*dy<=dr*dr;
    }
    
    bool operator<(const circle& C) const
    {
        return r<C.r;
    }
};

vector<vector<double>> dp;
vector<vector<int>> e;
vector<circle> a;

double solve(int u, int t)
{
    double& ans=dp[u][t];
    
    if( ans<0 )
    {
        ans=a[u]();
        
        for(int v : e[u])
        {
            double p=0, q=0;
            
            for(int c : e[v])
            {
                p+=solve(c, 0);
                q+=solve(c, 1);
            }
            
            if( t==0 )
                ans+=min(-a[v]()+p, a[v]()-q);
            else
                ans+=max(-a[v]()+q, a[v]()-p);
        }
    }
    
    return ans;
}

int main()
{
    int n;
    scanf("%d", &n);
    vector<int> d(n, 0);
    e.resize(n);
    a.resize(n);
    dp.assign(n, vector<double>(2, -1));
    
    for(int i=0; i<n; i++)
        a[i].read();
    
    sort(a.begin(), a.end());
    
    for(int i=0; i<n; i++)
        for(int j=i+1; j<n; j++)
            if( a[j](a[i]) )
            {
                e[j].push_back(i);
                d[i]++;
                break;
            }
    
    double ans=0;
    
    for(int i=0; i<n; i++)
        if( d[i]==0 )
            ans+=solve(i, 1);
    
    printf("%.10f\n", ans);
}
