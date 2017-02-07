#include<cstdio>
#include<set>
#include<vector>
#include<algorithm>
using namespace std;
const int N=1<<20;
const int INF=0x3FFFFFFF;

struct ST
{
    struct node
    {
        int l, r, x, y, m, val, mvl;
    } p[N];
    
    int root;
    
    int build(const vector<int>& h, int a, int b)
    {
        if( a>=b )
            return -1;
        
        int m=(a+b)/2;
        p[m].m=m;
        p[m].x=a;
        p[m].y=b;
        p[m].val=p[m].mvl=h[m];
        p[m].l=build(h, a, m);
        p[m].r=build(h, m+1, b);
        
        if( p[m].l>=0 )
            p[m].mvl=max(p[m].mvl, p[ p[m].l ].mvl);
        
        if( p[m].r>=0 )
            p[m].mvl=max(p[m].mvl, p[ p[m].r ].mvl);
        
        return m;
    }
    
    int query(int a, int b, int t)
    {
        if( a>=p[t].y || b<=p[t].x )
            return 0;
        else if( a<=p[t].x && p[t].y<=b )
            return p[t].mvl;
        
        int ans=a<=p[t].m && p[t].m<b ? p[t].val : 0 ;
        
        if( p[t].l>=0 )
            ans=max(ans, query(a, b, p[t].l));
        
        if( p[t].r>=0 )
            ans=max(ans, query(a, b, p[t].r));
        
        return ans;
    }
    
    int query(int a, int b)
    {
        return query(a, b+1, root);
    }
} T;

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    vector<int> h(n+1);
    set<int> S;
    
    for(int i=1; i<=n; i++)
    {
        scanf("%d", &h[i]);
        
        if( h[i]==0 )
            S.insert(i);
    }
    
    T.root=T.build(h, 1, n+1);
    
    for(; m>0; m--)
    {
        int l, r, h;
        scanf("%d%d%d", &l, &r, &h);
        auto it=S.lower_bound(l);
        
        if( it!=S.end() && *it<=r )
        {
            printf("Yes\n");
            continue;
        }
        
        if( it!=S.begin() && T.query(1+*--it, l)<h )
        {
            printf("Yes\n");
            continue;
        }
            
        it=S.upper_bound(r);
        
        if( it!=S.end() && T.query(r, *it-1)<h )
        {
            printf("Yes\n");
            continue;
        }
        
        printf("No\n");
    }
}

/*

6 7
0 2 3 1 4 0
1 1 0
4 4 2
2 5 2
2 5 3
3 5 3
3 5 4
5 5 4

6 1
0 2 3 1 4 0
2 5 2

*/
