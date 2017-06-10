#include<cstdio>

struct line
{
    int a[6];
    
    bool operator()(const int b[7][7])
    {
        for(int i=0; i<6; i+=2)
            if( !b[ a[i] ][ a[i+1] ] )
                return false;
        
        return true;
    }
};

int main()
{
    line L[8];
    L[0]={0, 0, 0, 3, 0, 6};
    L[1]={1, 1, 0, 3, 1, 5};
    L[2]={2, 2, 2, 3, 2, 4};
    L[3]={3, 0, 3, 1, 3, 2};
    L[4]={3, 4, 3, 5, 3, 6};
    L[5]={4, 2, 4, 3, 4, 4};
    L[6]={5, 1, 5, 3, 5, 5};
    L[7]={6, 0, 6, 3, 6, 6};
    
    int n, a[7][7]={{0}}, b[7][7]={{0}};
    
    for(scanf("%d%*d", &n); n>0; n--)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        x+=3, y+=3;
        a[x][y]=b[y][x]=1;
    }
    
    for(int i=0; i<8; i++)
    {
        n+=L[i](a);
        n+=L[i](b);
    }
    
    printf("%d\n", n);
}
