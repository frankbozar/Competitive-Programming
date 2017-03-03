#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int N=1<<20;
char s[N]={0}, t[N]={0};
int a[N]={0}, n, m;

int ok(int x)
{
    vector<int> b(a+x, a+n);
    sort(b.begin(), b.end());
    int p=0;
    
    for(int d : b)
    {
        if( s[d]==t[p] )
            if( ++p>=m )
                return true;
    }
    
    return false;
}

int main()
{
    scanf("%s%s", s, t);
    n=strlen(s);
    m=strlen(t);
    
    for(int i=0; i<n; i++)
    {
        scanf("%d", &a[i]);
        a[i]--;
    }
    
    int ans=-1;
    
    for(int l=0, r=n; l<r; )
    {
        int x=(l+r)>>1;
        
        if( !ok(x) )
            r=x;
        else
        {
            l=x+1;
            ans=x;
        }
    }
    
    printf("%d\n", ans);
}

/*

ababcba
abb
5 3 4 1 7 6 2

bbbabb
bb
1 6 3 4 2 5

*/
