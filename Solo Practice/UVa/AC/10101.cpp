#include<cstdio>
typedef long long lld;
const lld a[4]={10000000, 100000, 1000, 100};
const char* s[4]={"kuti", "lakh", "hajar", "shata"};

int sol(lld x, bool init=false)
{
    if( init && x==0 )
        return printf(" 0");
    else if( x==0 )
        return 0;
    
    int cnt=0;
    
    for(int i=0; i<4; i++)
    {
        int tmp=sol(x/a[i]);
        cnt+=tmp;
        x%=a[i];
        
        if( tmp )
            printf(" %s", s[i]);
    }
    
    if( x>0 )
        cnt+=printf(" %lld", x);
    
    return cnt;
}

int main()
{
    lld x;
    
    for(int cases=1; scanf("%lld", &x)!=EOF;cases++)
    {
        printf("%4d.", cases);
        sol(x, true);
        printf("\n");
    }
}

/*

0
100
1000
10000
100000
1000000
10000000
100000000
1000000000
23764
45897458973958

*/
