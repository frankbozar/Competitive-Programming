#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

struct data
{
    int o, s, t;
    
    bool operator<(const data& D) const
    {
        return s<D.s;
    }
};

int sum(const vector<int>& a)
{
    int ans=0;
    
    for(int x : a)
        ans+=x;
    
    return ans;
}

int diff(int t, int s)
{
    return (t+1440-s)%1440;
}

int solve(vector<data>& a)
{
    int n=a.size();
    
    if( n<=1 )
        return 2;
    
    sort(a.begin(), a.end());
    a.push_back(a.front());
    int cnt=0, d[2]={0};
    vector<int> g[2];
    
    for(int i=1; i<=n; i++)
    {
        d[ a[i].o ]+=diff(a[i].t, a[i].s);
        
        if( a[i-1].o==a[i].o )
            g[ a[i].o ].push_back(diff(a[i].s, a[i-1].t));
        else
            cnt++;
    }
    
    for(int i=0; i<2; i++)
        for(sort(g[i].begin(), g[i].end()); d[i]+sum(g[i])>720; g[i].pop_back())
            cnt+=2;
    
    return cnt;
}

int main()
{
    int ncase;
    scanf("%d", &ncase);
    
    for(int cases=1; cases<=ncase; cases++)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        vector<data> a(n+m);
        
        for(int i=0; i<n; i++)
        {
            a[i].o=0;
            scanf("%d%d", &a[i].s, &a[i].t);
        }
        
        for(int i=n; i<n+m; i++)
        {
            a[i].o=1;
            scanf("%d%d", &a[i].s, &a[i].t);
        }
        
        printf("Case #%d: %d\n", cases, solve(a));
    }
}

/*

5

1 1
540 600
840 900

2 0
900 1260
180 540

1 1
1439 1440
0 1

2 2
0 1
1439 1440
1438 1439
1 2

3 4
0 10
1420 1440
90 100
550 600
900 950
100 150
1050 1400

*/
