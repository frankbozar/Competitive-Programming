#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

struct ds
{
    vector<int> p, h, l, s;
    ds(int n) : p(n+1, -1), h(n+1), l(n+1), s(n+1, 1){}
    
    int find(int x)
    {
        return p[x]<0 ? x : p[x]=find(p[x]);
    }
    
    void join(int x, int y)
    {
        x=find(x);
        y=find(y);
        p[x]=y;
        h[y]=max(h[y], h[x]);
        l[y]=min(l[y], l[x]);
        s[y]+=s[x];
    }
};

struct bit
{
    static const int n=1<<22;
    int a[n];
    
    void reset()
    {
        memset(a, 0, sizeof(a));
    }
    
    void add(int p, int v)
    {
        for(; p<n; p+=p&-p)
            a[p]+=v;
    }
    
    int query(int p)
    {
        int ans=0;
        
        for(; p>0; p-=p&-p)
            ans+=a[p];
        
        return ans;
    }
} B, S;

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n, m;
        scanf("%d", &n);
        ds D(n+1);
        B.reset();
        S.reset();
        
        for(int i=0; i<n; i++)
        {
            int y;
            scanf("%*d%d", &y);
            D.l[i]=(y<<2)+3;
            D.h[i]=(y<<2)+2;
            B.add(D.l[i], 1);
            B.add(D.h[i], -1);
            S.add(D.l[i], 1);
            S.add(D.h[i], -1);
        }
        
        for(scanf("%d", &m); m>0; m--)
        {
            char s[8]={0};
            scanf("%s", s);
            
            if( s[0]=='r' )
            {
                int u, v;
                scanf("%d%d", &u, &v);
                u=D.find(u);
                v=D.find(v);
                
                if( u==v )
                    continue;
                
                B.add(D.l[u], -1);
                B.add(D.h[u], 1);
                B.add(D.l[v], -1);
                B.add(D.h[v], 1);
                S.add(D.l[u], -D.s[u]);
                S.add(D.h[u], D.s[u]);
                S.add(D.l[v], -D.s[v]);
                S.add(D.h[v], D.s[v]);
                D.join(u, v);
                u=D.find(u);
                B.add(D.l[u], 1);
                B.add(D.h[u], -1);
                S.add(D.l[u], D.s[u]);
                S.add(D.h[u], -D.s[u]);
            }
            else//if( s[0]=='l' )
            {
                int y;
                scanf("%d.5", &y);
                y=(y<<2)+5;
                printf("%d %d\n", B.query(y), S.query(y));
            }
        }
    }
}

/*

3

10
1 7
5 7
8 6
3 5
5 5
2 3
10 3
7 2
4 1
11 1
11
road 0 1
road 3 5
line 6.5
road 4 2
road 3 8
road 4 7
road 6 9
road 4 1
road 2 7
line 4.5
line 6.5

1
100 100
1
line 100.5

2
10 10
20 20
2
road 0 1
line 15.5

*/
