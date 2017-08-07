#include<cstdio>
#include<queue>
#include<vector>
using namespace std;
char s[128][128];
#define point pair<int,int>
#define x first
#define y second

int bfs(int n, int x, int y)
{
    int cnt=0;
    queue<point> Q;
    
    for(Q.push(point(x, y)); !Q.empty(); Q.pop())
    {
        x=Q.front().x;
        y=Q.front().y;
        cnt++;
        
        for(int i=-1; i<=1; i++)
            for(int j=-1; j<=1; j++)
            {
                if( i==0 && j==0 )
                    continue;
                else if( x+i<0 || x+i>=n )
                    continue;
                else if( y+j<0 || y+j>=n )
                    continue;
                else if( s[x+i][y+j]=='.' )
                    continue;
                else if( s[x+i][y+j]==s[x][y] )
                    return -1;
                else if( s[x+i][y+j]!='#' )
                    continue;
                
                s[x+i][y+j]='2'-s[x][y]+'1';
                Q.push(point(x+i, y+j));
            }
    }
    
    return cnt;
}

bool sol(int n, int m)
{
    vector<int> c(m+1, 0);
    
    if( m==1 )
    {
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                if( s[i][j]=='#' )
                {
                    for(int x=-1; x<=1; x++)
                        for(int y=-1; y<=1; y++)
                        {
                            if( x==0 && y==0 )
                                continue;
                            else if( x+i<0 || x+i>=n )
                                continue;
                            else if( y+j<0 || y+j>=n )
                                continue;
                            else if( s[x+i][y+j]!='.' )
                                return false;
                        }
                    
                    c[1]++;
                    s[i][j]='1';
                }
        
        return c[1]>0;
    }
    else if( m==2 )
    {
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                if( s[i][j]=='#' )
                {
                    int x=c[2]==0 ? 2 : 1 ;
                    s[i][j]='0'+x;
                    c[x]++;
                    int cnt=bfs(n, i, j);
                    
                    if( cnt<0 )
                        return false;
                    else if( cnt>1 )
                        c[3-x]++;
                }
        
        return c[1] && c[2] ;
    }
    else
    {
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                if( s[i][j]=='#' )
                {
                    int x=1+(((i&1)<<1)|(j&1));
                    s[i][j]='0'+x;
                    c[x]++;
                }
        
        for(int i=1; i<=m; i++)
        {
            if( c[i]!=0 )
                continue;
            
            int j=0;
            
            for(int k=1; k<=m; k++)
                if( c[k]>1 )
                    j=k;
            
            if( c[j]<1 )
                return false;
            
            for(int x=0; x<n; x++)
                for(int y=0; y<n; y++)
                    if( s[x][y]=='0'+j )
                    {
                        s[x][y]='0'+i;
                        c[i]++;
                        c[j]--;
                        j=0;
                    }
        }
        
        return true;
    }
}

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        
        for(int i=0; i<n; i++)
            scanf("%s", s[i]);
        
        if( !sol(n, m) )
            printf("Impossible\n");
        else
        {
            printf("Possible\n");
            
            for(int i=0; i<n; i++)
                printf("%s\n", s[i]);
        }
    }
}
