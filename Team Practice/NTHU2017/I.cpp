#include"SunMoon.h"
//#include<cstdio>
//#include<cstdlib>
#include<algorithm>
using namespace std;
typedef long long lld;
const lld N=2147483647;
const lld M=92680;
/*
int ans, cnt, bad;

void initialize()
{
    ans=rand();
    cnt=bad=0;
}

int try_poison(int x)
{
    cnt++;
    bad+=x>ans;
    
    return x<=ans ? 1 : 0 ;
}

void answer(int x)
{
    if( ans!=x || cnt>M || bad>2 )
        printf("%d %d %d %d\n", ans, x, cnt, bad);
}
*/
int main()
{
    for(int z=0; z<1; z++)
    {
        initialize();
        lld k=1, l=M;
        
        for(lld i=M; l<=N && try_poison(l); l+=i--)
            k=l+1;
        
        l=min(l, N+1);
        
        while( k<l && try_poison(k) )
            k++;
        
        answer(k-1);
    }
}
//2017986315 2017986315 92681 2
