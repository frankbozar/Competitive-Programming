#include<cstdio>
#include<algorithm>
using namespace std;
int a[4], d, p;

void add(int& s, int& t)
{
    if( ++t==a[s] )
    {
        s=(s+3)&3;
        t=0;
    }
}

bool ok(int x, int y)
{
    int s=(x+y-1)&3;
    int t=0;
    
    for(int i=0; i<min(x, y); i++)
        add(s, t);
    
    for(int k=0; k<3; k++)
        for(int u=0; u<4; u++)
        {
            if( u==0 && s==d && t==p )
                return true;
            
            for(int i=0; i<2; i++)
                add(s, t);
        }
    
    return false;
}

int main()
{
    int ans=0;
    
    for(int i=0; i<4; i++)
        scanf("%d", &a[i]);
    
    scanf("%d%d", &d, &p);
    d--;
    p--;
    
    for(int i=1; i<=6; i++)
        for(int j=i; j<=6; j++)
            if( ok(i, j) )
                ans++;
    
    printf("%d\n", ans);
}
