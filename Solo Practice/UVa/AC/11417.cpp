#include<cstdio>
#include<algorithm>
using namespace std;

int main()
{
    for(int n; scanf("%d", &n) && n>0; )
    {
        int ans=0;
        
        for(int i=1; i<n; i++)
            for(int j=i+1; j<=n; j++)
                ans+=__gcd(i, j);
        
        printf("%d\n", ans);
    }
}