#include<cmath>
#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const double PI=atan(1)*4;
#define cake pair<double,double>
#define r first
#define h second

double area(double r, double h)
{
    return 2*PI*r*h;
}

double area(double r)
{
    return PI*r*r;
}

int main()
{
    int ncase;
    scanf("%d", &ncase);
    
    for(int cases=1; cases<=ncase; cases++)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        vector<cake> a(n);
        
        for(int i=0; i<n; i++)
            scanf("%lf%lf", &a[i].r, &a[i].h);
        
        sort(a.begin(), a.end());
        priority_queue<double, vector<double>, greater<double>> PQ;
        double ans=0, sum=0;
        
        for(int i=0; i<n; i++)
        {
            double tmp=area(a[i].r, a[i].h);
            
            if( PQ.size()==m-1 )
                ans=max(ans, sum+tmp+area(a[i].r));
            
            PQ.push(tmp);
            sum+=tmp;
            
            if( PQ.size()>m-1 )
            {
                sum-=PQ.top();
                PQ.pop();
            }
        }
        
        printf("Case #%d: %.10f\n", cases, ans);
    }
}
