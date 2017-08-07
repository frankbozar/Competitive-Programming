#include<cstdio>
#include<algorithm>
using namespace std;
const int N=128;
char s[N][N]={{0}};

void count(int n, int m, int& c, int& w, int& h, char C)
{
    c=0;
    int l=N, r=-N, u=N, d=-N;
    
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            if( s[i][j]==C )
            {
                c++;
                l=min(l, i);
                r=max(r, i);
                u=min(u, j);
                d=max(d, j);
            }
    
    w=r-l+1;
    h=d-u+1;
}

bool sol(int n, int m)
{
    int c[3], w[3], h[3];
    const char* C="RGB";
    
    for(int i=0; i<3; i++)
    {
        count(n, m, c[i], w[i], h[i], C[i]);
        
        if( c[i]!=n*m/3 || c[i]!=w[i]*h[i] )
            return false;
    }
    
    if( w[0]==w[1] && w[1]==w[2] && h[0]+h[1]+h[2]==m )
        return true;
    
    if( h[0]==h[1] && h[1]==h[2] && w[0]+w[1]+w[2]==n )
        return true;
    
    return false;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    
    for(int i=0; i<n; i++)
        scanf("%s", s[i]);
    
    printf(sol(n, m) ? "YES\n" : "NO\n");
}
