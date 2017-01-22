#include<cmath>
#include<cstdio>
#include<set>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;
typedef map<double, double> MAP;
typedef MAP::iterator iter;
const double INF=1e10;
const double EPS=1e-8;

double area(double h, double l, double r=0)
{
    return (l+r)*h*.5;
}

void solve(vector<iter>& erase, vector<pair<double, double>>& insert, double& ans, iter it, double x, double y)
{
    double p=it->first;
    double q=it->second;
    
    if( p+fabs(q)<=x || x+fabs(y)<=p )
        continue;
    
    erase.push_back(it);
    
    if( y<0 )
    {
        if( q<0 )
        {
            
            
        }
        else
        {
            
            
            
        }
    }
    else
    {
        
        
        
    }
}

double query(MAP& M, int x, int y, double ans)
{
    vector<iter> erase;
    vector<pair<double, double>> insert;
    iter it=M.upper_bound(x-y);
    
    if( it==M.begin() )
    {
        M[x-y]=y;
        ans+=area(y, y);
    }
    else
    {
        for(--it; it!=M.end() && it.first<x; ++it)
            solve(erase, insert, ans, it->first, it.second, x-y, y);
    }
    
    iter it=M.upper_bound(x);
    
    if( it==M.begin() )
    {
        M[x]=-y;
        ans+=area(y, y);
    }
    else
    {
        for(--it; it!=M.end() && it.first<x; ++it)
            solve(erase, insert, ans, it, x, -y);
    }
    
    return ans;
}

struct data
{
    lld x, a, b, c;
    
    void read()
    {
        scanf("%lld%lld%lld%lld", &x, &a, &b, &c);
    }
    
    int gen()
    {
        int ans=x;
        x=(x*a+b)%c+1;
        return ans;
    }
};

int main()
{
    int ncase;
    scanf("%d", &ncase);
    
    for(int cases=1; cases<=ncase; cases++)
    {
        int n;
        scanf("%d", &n);
        data X, Y;
        X.read();
        Y.read();
        double ans=0;
        
        for(MAP M; n>0; n--)
            ans+=query(M, X.gen(), Y.gen(), ans);
        
        /*
        for(int i=0; i<n; i++)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            p.push_back(pole(x, y));
        }
        */
        
        printf("Case #%d: %f\n", cases, ans);
    }
}

/*

3

1
4 2

2
4 2
6 3

3
4 2
6 3
5 1

*/
/*

1
5
1 1 0 100
1 0 0 100

*/
