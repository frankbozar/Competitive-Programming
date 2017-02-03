#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

struct node
{
    vector<int> e, a;
    int l, r, u, d, p, c;
    node() : a(4, 0), p(4), c(-1){}
    
    void read()
    {
        scanf("%d%d%d%d", &l, &d, &r, &u);
    }
    
    int test(int i)
    {
        if( a[i]==0 )
            return c=i;
        
        return -1;
    }
    
    void link(int u)
    {
        e.push_back(u);
    }
    
    void add(int i)
    {
        if( a[i]++==0 )
            p--;
    }
    
    void sub(int i)
    {
        if( --a[i]==0 )
            p++;
    }
};

struct seg
{
    int i, y, l, r;
    seg(int _i=0, int _y=0, int _l=0, int _r=0) : i(_i), y(_y), l(_l), r(_r){}
    
    bool operator<(const seg& S) const
    {
        return y==S.y ? r<S.r : y<S.y ;
    }
    
    bool operator*(const seg& S) const
    {
        return y==S.y && max(l, S.l)<min(r, S.r) ;
    }
};

void intersect(vector<node>& p, vector<seg>& l, vector<seg>& r, int n)
{
    sort(l.begin(), l.end());
    sort(r.begin(), r.end());
    
    for(int i=0, j=0; i<n && j<n; )
    {
        if( l[i]*r[j] )
        {
            int u=l[i].i, v=r[j].i;
            p[u].link(v);
            p[v].link(u);
        }
        
        (l[i]<r[j] ? i : j)++;
    }
}

bool solve(vector<node>& p, int u=0)
{
    if( u<0 || p[u].c>=0 )
        return true;
    
    for(int i=0; i<4; i++)
    {
        int c=p[u].test(i), l=4, t=-1;
        
        if( c<0 )
            continue;
        
        for(int v : p[u].e)
        {
            p[v].add(c);
            
            if( l>p[v].p )
            {
                l=p[v].p;
                t=v;
            }
        }
        
        if( solve(p, t) )
            return true;
        
        for(int v : p[u].e)
            p[v].sub(c);
    }
    
    return false;
}

int main()
{
    int n;
    scanf("%d", &n);
    vector<node> p(n);
    vector<seg> l, r, u, d;
    
    for(int i=0; i<n; i++)
    {
        node& P=p[i];
        P.read();
        l.push_back(seg(i, P.l, P.d, P.u));
        r.push_back(seg(i, P.r, P.d, P.u));
        u.push_back(seg(i, P.u, P.l, P.r));
        d.push_back(seg(i, P.d, P.l, P.r));
    }
    
    intersect(p, l, r, n);
    intersect(p, d, u, n);
    
    for(int i=0; i<n; i++)
    {
        if( !solve(p, i) )
        {
            printf("NO\n");
            return 0;
        }
    }
    
    printf("YES\n");
    
    for(int i=0; i<n; i++)
        printf("%d\n", p[i].c+1);
}
