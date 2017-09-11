#include<cstdio>

int main()
{
    freopen("anniversary.in", "rb", stdin);
    freopen("anniversary.out", "wb", stdout);
    int w, h, ax, ay, bx, by;
    scanf("%d%d%d%d%d%d", &w, &h, &ax, &ay, &bx, &by);
    
    if( ax!=bx )
        printf("%d %d %d %d\n", ax, 0, bx, h);
    else
        printf("%d %d %d %d\n", 0, ay, w, by);
}
