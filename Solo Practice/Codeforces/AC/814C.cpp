#include<cstdio>
#include<algorithm>
using namespace std;
char s[1<<20]={0};

int f(int n, int m, char c)
{
    int ans=m;
    
    for(int j=0, i=0; i<n; i++)
    {
        for(j=max(i, j); j<n && (s[j]==c || m>0); j++)
            m-=s[j]!=c;
        
        ans=max(ans, j-i);
        m+=s[i]!=c;
    }
    
    return ans;
}

int main()
{
    int n, m;
    
    for(scanf("%d%s%d", &n, s, &m); m>0; m--)
    {
        int k;
        char c;
        scanf("%d %c", &k, &c);
        printf("%d\n", f(n, k, c));
    }
}
