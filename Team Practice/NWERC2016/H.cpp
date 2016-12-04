#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long lld;

lld solve(int n)
{
    lld ans=0;
    
    for(int p=0, i=n-1; i>=0; i--)
    {
        int q;
        scanf("%1d", &q);
        p^=q;
        ans=(ans<<1)|p;
    }
    
    return ans;
}

int main()
{
    int n;
    scanf("%d", &n);
    printf("%lld\n", abs(solve(n)-solve(n))-1);
}

/*

3 001 111
3 110 100

*/