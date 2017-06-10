#include<cstdio>
typedef long long lld;
const lld mod=1000000007;
const int N=1<<20;
char s[N]={0};

int main()
{
    lld ans=0, cnt=0;
    scanf("%s", s);
    
    for(int i=N-1; i>=0; i--)
    {
        if( s[i]=='b' )
            cnt++;
        else
        {
            ans+=cnt;
            cnt=(cnt<<1)%mod;
        }
    }
    
    printf("%lld\n", ans%mod);
}
