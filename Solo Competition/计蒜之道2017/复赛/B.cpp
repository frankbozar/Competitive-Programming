#include<cstdio>
#include<cstdlib>

int gcd(int a, int b)
{
    return b==0 ? a : gcd(b, a%b);
}

int a[256][256]={{0}};

int main()
{
    int n;
    scanf("%d%*d", &n);
    
    for(int i=1; i<=n; i++)
    {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        int dx=x2-x1;
        int dy=y2-y1;
        int g=gcd(abs(dx), abs(dy));
        dx/=g;
        dy/=g;
        
        for(int x=x1, y=y1; x!=x2 || y!=y2; )
        {
            a[x][y]=i;
            x+=dx;
            y+=dy;
        }
        
        a[x2][y2]=i;
    }
    
    for(scanf("%d", &n); n>0; n--)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        printf("%d\n", a[x][y]);
    }
}
