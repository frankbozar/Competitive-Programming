#include<cstdio>
#include<cstring>
const int N=1<<10;
char s[N][16];
int a[N][8];
int c[N], d[N], e[N]={0};

int main()
{
    for(int m, n; scanf("%d%d", &m, &n) && (m||n); )
    {
        memset(c, 0, sizeof(c));
        memset(d, 0, sizeof(d));
        int ans=0;
        
        for(int i=1; i<=n; i++)
        {
            scanf("%s", s[i]);
            
            for(int j=0; j<m; j++)
                scanf("%d", &a[i][j]);
        }
        
        for(int i=1; i<=n; i++)
        {
            for(int j=0; j<m; j++)
            {
                ++c[ a[i][j] ];
                
                if( !strcmp(s[i], s[ a[i][j] ]) )
                    ans+=d[ a[i][j] ]++==0;
                
                if( e[ a[i][j] ]++==1 )
                    ans+=d[ a[i][j] ]++==0;
            }
            
            for(int j=0; j<m; j++)
                e[ a[i][j] ]--;
        }
        
        for(int i=1; i<=n; i++)
            if( c[i]!=m )
                ans+=d[i]++==0;
        
        if( ans==0 )
            printf("NO PROBLEMS FOUND\n");
        else if( ans==1 )
            printf("1 PROBLEM FOUND\n");
        else
            printf("%d PROBLEMS FOUND\n", ans);
    }
}

/*

2 3
UCM 2 3
UAM 1 3
UPM 1 2

2 3
UCM 2 3
UAM 1 2
UPM 2 2

0 0

*/
