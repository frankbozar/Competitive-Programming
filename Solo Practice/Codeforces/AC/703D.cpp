#include<cstdio>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;

struct bit{
    int w, h;//1<=x<=w, 1<=y<=h
    vector<vector<int>> a;
    bit(int _w, int _h=1) : w(_w), h(_h), a(w+1, vector<int>(h+1, 0)){}
    void add(int val, int x, int y=1){
        for(; x<=w; x+=x&-x)
            for(int yy=y; yy<=h; yy+=yy&-yy)
                a[x][yy]^=val;
    }
    int query(int x, int y=1){
        int res=0;
        for(; x>0; x-=x&-x)
            for(int yy=y; yy>0; yy-=yy&-yy)
                res^=a[x][yy];
        return res;
    }
};

struct query
{
    int l, r, i;
    
    bool operator<(const query& Q) const
    {
        return r<Q.r ;
    }
};

int main()
{
    int n, m;
    scanf("%d", &n);
    vector<int> a(n+1, 0), b(n+1, 0), c(n+1, 0), p(n+1, 0);
    map<int, int> M;
    
    for(int i=1; i<=n; i++)
    {
        scanf("%d", &a[i]);
        
        if( M[ a[i] ]==0 )
            M[ a[i] ]=i;
        
        b[i]=M[ a[i] ];
        p[i]=p[i-1]^a[i];
    }
    
    scanf("%d", &m);
    vector<query> q(m);
    vector<int> ans(m);
    
    for(int i=0; i<m; i++)
    {
        scanf("%d%d", &q[i].l, &q[i].r);
        q[i].l--;
        q[i].i=i;
    }
    
    sort(q.begin(), q.end());
    bit B(n);
    
    for(int j=0, i=1; j<m && i<=n; i++)
    {
        if( c[ b[i] ]!=0 )
            B.add(a[i], c[ b[i] ]);
        
        B.add(a[i], i);
        c[ b[i] ]=i;
        
        for(; j<m && q[j].r==i; j++)
            ans[ q[j].i ]=(B.query(i)^B.query(q[j].l))^(p[i]^p[q[j].l]);
    }
    
    for(int i=0; i<m; i++)
        printf("%d\n", ans[i]);
}
