#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<set>
#include<string>
#include<algorithm>
using namespace std;
char s[1<<7][1<<15];
int ans[1<<7];

bool ok(int u, int v, int l, int d)
{
    multiset<string> S;
    
    for(int i=0; i<l; i+=4)
        S.insert(string(s[u]+i, s[u]+i+4));
    
    int cnt=0;
    
    for(int i=0; i<l; i+=4)
    {
        auto it=S.find(string(s[v]+i, s[v]+i+4));
        
        if( it!=S.end() )
        {
            cnt++;
            S.erase(it);
        }
    }
    
    return cnt>=d;
}

int main()
{
    freopen("detect.in", "rb", stdin);
    //freopen("detect.out", "wb", stdout);
    int n;
    scanf("%d", &n);
    
    for(int i=0; i<n; i++)
    {
        scanf("\n%[^\n]", s[i]);
        
        for(int j=0; s[i][j]!='\0'; j+=4)
            sort(s[i]+j, s[i]+j+4);
    }
    
    for(int l=strlen(s[0]), d=l/100, step=0; ; )
    {
        memset(ans, 0, sizeof(ans));
        int u=rand()%n;
        
        for(int v=0; v<n; v++)
            if( v!=u && ok(u, v, l, d) )
                ans[u]=ans[v]=1;
        
        int cnt=0;
        
        for(int i=0; i<n; i++)
            cnt+=ans[i];
        
        if( !ans[u] )
            continue;
        else if( abs(cnt*2-n)<n/9 )
            break;
        else
        {
            if( cnt*2>n )
            {
                if( step>=0 )
                    step=-1;
            }
            else
            {
                if( step<=0 )
                    step=1;
            }
            
            d-=step;
            step*=2;
        }
    }
    
    for(int i=0; i<n; i++)
        printf(ans[i] ? "block\n" : "random\n");
}

