#include<cstdio>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=1<<20;
typedef long long lld;
#define data pair<lld,int>
#define v first
#define c second
vector<data> e;

int h(lld& q, lld b, lld v, int c)
{
    for(; c>0 && q<b; c--)
        q*=v;
    
    return c;
}

int g(lld a, lld b, int n, lld p=1, lld q=1, int i=0, int cnt=0)
{
    if( a<=p && b<=q )
        return cnt;
    else if( i>=n )
        return INF;
    else if( b<=q )
    {
        lld t=p;
        int r=h(t, a, e[i].v, e[i].c);
        return g(a, b, n, t, q, i+1, cnt+e[i].c-r);
    }
    else if( a<=p )
    {
        lld t=q;
        int r=h(t, b, e[i].v, e[i].c);
        return g(a, b, n, p, t, i+1, cnt+e[i].c-r);
    }
    else
    {
        int ans=INF;
        
        for(int j=0; j<=e[i].c; j++)
        {
            lld t=q;
            int r=h(t, b, e[i].v, e[i].c-j);
            
            if( a<=p )
            {
                ans=min(ans, g(a, b, n, p, t, i+1, cnt+e[i].c-r));
                break;
            }
            
            if( r==0 )
                ans=min(ans, g(a, b, n, p, t, i+1, cnt+e[i].c));
                
            p*=e[i].v;
        }
        
        return ans;
    }
}

int f(int a, int b, int h, int w, int n)
{
    return g((a+h-1)/h, (b+w-1)/w, n);
}

int main()
{
    int a, b, h, w, n;
    scanf("%d%d%d%d%d", &a, &b, &h, &w, &n);
    map<lld, int> M;
    
    for(int i=0; i<n; i++)
    {
        int x;
        scanf("%d", &x);
        M[x]++;
    }
    
    n=M.size();
    e.assign(M.rbegin(), M.rend());
    int ans=min(f(a, b, h, w, n), f(a, b, w, h, n));
    printf("%d\n", ans>=INF ? -1 : ans);
}

/*

3 3 2 4 4
2 5 4 10

3 3 3 3 5
2 3 5 4 2

5 5 1 2 3
2 2 3

3 4 1 1 3
2 3 2

100000 100000 1 1 100
2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2

100000 100000 1 1 17
2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59

*/
