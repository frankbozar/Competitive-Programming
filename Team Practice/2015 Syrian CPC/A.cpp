#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long lld;
const lld INF=1LL<<60;

int main()
{
    int N, n;
    
    for(scanf("%d", &N); N>0; N--)
    {
        lld l=0, r=INF;
        
        for(scanf("%d", &n); n>0; n--)
        {
            lld x;
            char c;
            scanf("%lld %c", &x, &c);
            
            if( c=='+' )
                l+=x+25;
            else
                r=min(r, l+x+24);
        }
        
        printf("%lld\n", max(0LL, r-l+1));
    }
}

/*

3

3
512 -
128 +
256 +

4
80 +
70 +
200 -
150 +

3
100 -
100 -
540 -

*/
