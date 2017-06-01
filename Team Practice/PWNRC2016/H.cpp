#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
using namespace std;
const int N=1<<8, M=N*N, A=M, B=M+M;
const int step[4][2]={{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
const int diag[4][2]={{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
char s[N][N]={{0}}, t[N][N]={{0}};
int n, m;

struct ds
{
    vector<int> p;
    ds() : p(M*3, -1){}
    
    int find(int x)
    {
        return p[x]<0 ? x : p[x]=find(p[x]) ;
    }
    
    bool join(int x, int y)
    {
        x=find(x);
        y=find(y);
        
        if( x==y )
            return false;
        
        p[x]=y;
        return true;
    }
    
    bool same(int x, int y)
    {
        return find(x)==find(y);
    }
} S;

int id(int x, int y)
{
    return x*N+y;
}

void setc(int x, int y, char c)
{
    s[x][y]=c;
}

int countx(int x, int y)
{
    int cnt=0;
    
    for(int k=0; k<4; k++)
        if( s[ x+step[k][0] ][ y+step[k][1] ]=='X' )
            cnt++;
    
    return cnt;
}

int counts(int x, int y)
{
    int cnt=0;
    
    for(int k=0; k<4; k++)
        if( S.same(id(x, y), id(x+step[k][0], y+step[k][1])) )
            cnt++;
    
    return cnt;
}

int countn(int x, int y)
{
    int cnt=0;
    
    for(int k=0; k<4; k++)
        if( S.same(id(x, y), id(x+step[k][0], y+step[k][1])+M) )
            cnt++;
    
    return cnt;
}

bool ok(int x, int y)
{
    if( s[x][y]=='.' || s[x][y]=='C' )
        return false;
    
    bool any=false;
    
    if( countx(x, y)-countn(x, y)<=2 )
    {
        for(int k=0; k<4; k++)
        {
            int p=x+step[k][0];
            int q=y+step[k][1];
            int u=id(x, y);
            int v=id(p, q);
            
            if( s[p][q]=='X' && !S.same(u, v+M) )
            {
                any=any||S.join(u, v);
                any=any||S.join(u+M, v+M);
            }
        }
    }
    
    return any;
}

bool isc(int x, int y)
{
    if( s[x][y]!='X' )
        return false;
    
    for(int k=0; k<4; k++)
        if( s[ x+step[k][0] ][ y+step[k][1] ]!='X' )
            return false;
    
    for(int k=0; k<4; k++)
        if( s[ x+diag[k][0] ][ y+diag[k][1] ]!='.' )
            return false;
    
    return true;
}

int count(const char *c)
{
    int cnt=n*m;
    
    for(bool any=true; any; )
    {
        any=false;
    
        for(int i=1; i<=n; i++)
            for(int j=1; j<=m; j++)
                if( t[i][j]=='.' || (t[i][j]!=c[0] && t[i][j]!=c[1] && t[i][j]!=c[2] && t[i][j]!=c[3] ) )
                {
                    for(int k=0; k<4; k++)
                        if( t[ i+step[k][0] ][ j+step[k][1] ]=='\0' )
                            t[i][j]='\0', any=true;
                    
                    for(int k=0; k<4; k++)
                        if( t[ i+diag[k][0] ][ j+diag[k][1] ]=='\0' )
                            t[i][j]='\0', any=true;
                }
    }
    
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
            if( t[i][j]!='.' )
                cnt--;
    
    return cnt;
}

int main()
{
    scanf("%d%d", &n, &m);
    
    for(int i=1; i<=n; i++)
        scanf("%s", &s[i][1]);
    
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
            if( isc(i, j) )
            {
                setc(i, j, 'C');
                S.join(id(i-1, j), id(i+1, j));
                S.join(id(i-1, j)+M, id(i+1, j)+M);
                S.join(id(i, j-1), id(i, j+1));
                S.join(id(i, j-1)+M, id(i, j+1)+M);
                S.join(id(i-1, j), id(i, j-1)+M);
                S.join(id(i-1, j)+M, id(i, j-1));
            }
    
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
        {
            if( s[i][j]=='A' )
            {
                S.join(id(i, j), A);
                S.join(id(i, j)+M, B);
                setc(i, j, 'X');
            }
            else if( s[i][j]=='B' )
            {
                S.join(id(i, j)+M, A);
                S.join(id(i, j), B);
                setc(i, j, 'X');
            }
        }
    
    for(bool any=true; any; )
    {
        any=false;
        
        for(int i=1; i<=n; i++)
            for(int j=1; j<=m; j++)
                if( ok(i, j) )
                    any=true;
    }
    
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
            if( s[i][j]=='X' )
            {
                if( S.same(id(i, j), A) )
                    s[i][j]='A';
                else
                    s[i][j]='B';
            }
    
    memcpy(t, s, sizeof(s));
    int A=count("ACZ");
    memcpy(t, s, sizeof(s));
    int B=count("BCZ");
    memcpy(t, s, sizeof(s));
    int C=A+B-count("ABC");
    printf("%d %d %d\n", A-C, B-C, C);
}

/*

7 7
AXXXX..
X...X..
X.XXXXX
X.X.X.X
XXXXX.X
..X...X
..XXXXB

11 13
XXXXXXA......
X.....X......
X..XXXXXXXXX.
X..X..X....X.
X..X..XXX..XX
X..B....X...X
X..X.XXXX...X
X..X.X......X
XX.XXXXXX...X
.X...X..X.XXX
.XXXXX..XXX..

6 7
..XXB..
..X.X..
XXXXXXX
A.X.X.X
X.XXXXX
XXXXXX.

7 7
..XXX..
..X.X..
XXXXXXX
X.X.X.X
X.XXB.X
X.....X
AXXXXXX

*/
