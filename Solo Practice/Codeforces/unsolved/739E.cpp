#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef pair<double, int> data;

int main()
{
    int n, a, b;
    scanf("%d%d%d", &n, &a, &b);
    vector<double> p(n), q(n);
    vector<data> P, Q;
    
    for(int i=0; i<n; i++)
    {
        scanf("%lf", &p[i]);
        P.push_back(data(p[i], i));
    }
    
    for(int i=0; i<n; i++)
    {
        scanf("%lf", &q[i]);
        Q.push_back(data(q[i], i));
    }
    
    sort(P.rbegin(), P.rend());
    sort(Q.rbegin(), Q.rend());
    vector<bool> u(n, false);
    double ans=0;
    
    for(int i=0; i<a; i++)
    {
        ans+=P[i].first;
        u[ P[i].second ]=true;
    }
    
    for(int i=0; i<b; i++)
    {
        
        
        
        
        
    }
    
    printf("%f\n", ans);
}
