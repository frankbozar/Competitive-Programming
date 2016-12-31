#include<cstdio>
#include<vector>
using namespace std;
#define food pair<int,int>
#define x first
#define y second

bool check(const vector<int>& q, int n, int i)
{
    int x=(i+n)%n;
    int y=(x+1)%n;
    int z=(x+2)%n;
    return q[x]!=q[y] || q[y]!=q[z] || q[z]!=q[x];
}

bool can(const vector<int>& p, vector<int>& q, int n, int i, int v)
{
    q[i]=v;
    q[ p[i] ]=-v;
    return  check(q, n, i-2) &&     check(q, n, i-1) &&     check(q, n, i) &&
            check(q, n, p[i]-2) &&  check(q, n, p[i]-1) &&  check(q, n, p[i]) ;
}

bool solve(const vector<int>& p, vector<int>& q, int n, int i=0)
{
    if( i>=n )
        return true;
    else if( q[i]!=0 )
        return solve(p, q, n, i+1);
    else if( can(p, q, n, i, 1) && solve(p, q, n, i+1) )
        return true;
    else if( can(p, q, n, i, -1) && solve(p, q, n, i+1) )
        return true;
    
    q[i]=0;
    q[ p[i] ]=0;
    return false;
}

int main()
{
    int n;
    scanf("%d", &n);
    vector<food> a(n);
    vector<int> p(n<<1, 0), q(n<<1, 0);
    
    for(int i=0; i<n; i++)
    {
        scanf("%d%d", &a[i].x, &a[i].y);
        a[i].x--;
        a[i].y--;
        p[ a[i].x ]=a[i].y;
        p[ a[i].y ]=a[i].x;
    }
    
    if( !solve(p, q, n<<1) )
    {
        printf("-1\n");
        return 0;
    }
    
    for(int i=0; i<n; i++)
    {
        q[ q[ a[i].x ]<0 ? a[i].x : a[i].y ]=2;
        printf("%d %d\n", q[ a[i].x ], q[ a[i].y ]);
    }
}