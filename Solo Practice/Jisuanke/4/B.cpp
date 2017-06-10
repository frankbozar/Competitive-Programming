#include<cstdio>

struct point
{
    int x, y;
    point(int _x=0, int _y=0) : x(_x), y(_y){}
    
    void read()
    {
        scanf("%d%d", &x, &y);
    }
    
    point operator-(const point& P) const
    {
        return point(x-P.x, y-P.y);
    }
    
    bool operator==(const point& P) const
    {
        return x==P.x && y==P.y ;
    }
};

int main()
{
    int n;
    scanf("%d", &n);
    point ans;
    
    for(int c=0, i=0; i<n; i++)
    {
        point p, q;
        p.read();
        q.read();
        point d=q-p;
        
        if( c==0 )
            ans=d;
        
        c+= ans==d ? 1 : -1 ;
    }
    
    printf("%d %d\n", ans.x, ans.y);
}
