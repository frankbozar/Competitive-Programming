#include<cstdio>
#include<vector>
using namespace std;
typedef long long lld;
const lld mod=1000000007;
const int N=1<<10;
static char s[N][N]={{0}};
static lld two[N]={1};

#define data pair<int,int>
#define r first
#define d second

lld sol(vector<data>& a)
{
    if( a.empty() )
        return 1;
    
    int n=a.size(), cnt=0;
    
    for(int i=0; i<n; i++)
    {
        printf("%d %d\n", a[i].r, a[i].d);
        
        cnt+=a[i].r+a[i].d-2;
    }
    
    lld ans=two[cnt];
    
    printf("~~ %d\n", cnt);
    
    for(int i=0; i<n; i++)
    {
        if( a[i].r==1 && a[i].d==1 )
            ans+=two[cnt];
        else if( a[i].r==1 || a[i].d==1 )
            ans+=two[cnt-1];
        else
            ans+=two[cnt-2];
        
        if( a[i].r==1 && a[i].d==1 )
            printf("## %d\n", cnt);
        else if( a[i].r==1 || a[i].d==1 )
            printf("@@ %d\n", cnt-1);
        else
            printf("!! %d\n", cnt-2);
    }
    
    return ans%mod;
}

int main()
{
    for(int i=1; i<N; i++)
        two[i]=(two[i-1]<<1)%mod;
    
    int n, m;
    scanf("%d%d", &n, &m);
    
    for(int i=0; i<n; i++)
        scanf("%s", s[i]);
    
    vector<data> a;
    
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            if( s[i][j]=='.' )
            {
                data D(1, 1);
                for(; s[i+D.r][j]=='.'; s[i+D.r++][j]='x');
                for(; s[i][j+D.d]=='.'; s[i][j+D.d++]='x');
                a.push_back(D);
            }
    
    printf("%lld\n", sol(a));
}
