#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=1<<10;
vector<int> dp(1<<24, -1);

int h(int a, int b, int c)
{
    return a*128*128+b*128+c;
}

int f(int a, int b, int c)
{
    if( a<0 || b<0 || c<0 )
        return INF;
    else if( a+b==0 )
        return c-(c+3)/4;
    else if( b+c==0 )
        return a-(a+3)/4;
    else if( c+a==0 )
        return b/2;
    
    int& ans=dp[h(a, b, c)];
    
    if( ans<0 )
    {
        ans=INF;
        ans=min(ans, f(a-1, b, c-1)+1);
        ans=min(ans, f(a, b-2, c)+1);
        ans=min(ans, f(a-2, b-1, c)+2);
        ans=min(ans, f(a, b-1, c-2)+2);
        ans=min(ans, f(a-4, b, c)+3);
        ans=min(ans, f(a, b, c-4)+3);
    }
    
    return ans;
}

int solve(int n, vector<int> a)
{
    if( n==2 )
    {
        return a[1]/2;
    }
    else if( n==3 )
    {
        int t=min(a[1], a[2]);
        a[1]-=t;
        a[2]-=t;
        t+=a[1]-(a[1]+2)/3;
        t+=a[2]-(a[2]+2)/3;
        return t;
    }
    else if( n==4 )
    {
        return f(a[1], a[2], a[3]);
    }
    
    return 0;
}

int main()
{
    int ncase;
    scanf("%d", &ncase);
    
    for(int cases=1; cases<=ncase; cases++)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        vector<int> a(m, 0);
        
        for(int i=0; i<n; i++)
        {
            int x;
            scanf("%d", &x);
            a[x%m]++;
        }
        
        printf("Case #%d: %d\n", cases, n-solve(m, a));
    }
}
