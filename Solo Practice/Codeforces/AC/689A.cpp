#include<cstdio>
int a[4][3]={{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {-1, 0, -1}};

void get(int i, int& x, int& y)
{
    for(x=0; x<4; x++)
        for(y=0; y<3; y++)
            if( a[x][y]==i )
                return ;
}

int x[10]={0}, y[10]={0};

bool check(int n, int i, int j)
{
    for(int k=0; k<n; k++)
    {
        if( i<0 || i>3 || j<0 || j>2 || a[i][j]<0 )
            return false;
        
        i+=x[k+1]-x[k];
        j+=y[k+1]-y[k];
    }
    
    return true;
}

bool solve(int n)
{
    int cnt=0;
    
    for(int i=0; i<4; i++)
        for(int j=0; j<3; j++)
            if( check(n, i, j) )
                cnt++;
    
    return cnt==1;
}

int main()
{
    int n;
    scanf("%d", &n);
    
    for(int i=0; i<n; i++)
    {
        int t;
        scanf("%1d", &t);
        get(t, x[i], y[i]);
    }
    
    printf(solve(n) ? "YES\n" : "NO\n");
}
