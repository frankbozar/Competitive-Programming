#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long lld;
const lld INF=1LL<<40;

lld odd(lld maxi, lld mean, lld medi)
{
    lld ans=-INF;
    
    for(lld l=0, r=INF; l<r; )
    {
        lld m=(l+r)>>1;
        lld L=medi*(m+1)+maxi;
        lld R=medi*(m+1)+maxi*(m+1);
        lld M=mean*(m+m+3);
        
        if( L<=M && M<=R )
            r=ans=m;
        else
            l=m+1;
    }
    
    return ans+ans+3;
}

lld even(lld maxi, lld mean, lld medi)
{
    lld ans=-INF;
    
    for(lld l=0, r=INF; l<r; )
    {
        lld m=(l+r)>>1;
        lld L=medi*(m+2)+maxi;
        lld R=medi*(m+2)+maxi*(m+1);
        lld M=mean*(m+m+4);
        
        if( L<=M && M<=R )
            r=ans=m;
        else
            l=m+1;
    }
    
    return ans+ans+4;
}

lld solve(int maxi, int mean, int medi)
{
    if( mean<0 || medi<0 || maxi<mean || maxi<medi )
        return -1;
    else if( maxi!=0 && mean==0 )
        return -1;
    else if( maxi!=0 && mean==maxi )
        return -1;
    else if( maxi==0 )
        return 1;
    else if( maxi==mean<<1 && maxi==medi<<1 )
        return 2;
    else
        return min(odd(maxi, mean, medi), even(maxi, mean, medi));
}

int main()
{
    int ncase;
    scanf("%d", &ncase);
    
    for(int cases=1; cases<=ncase; cases++)
    {
        int mini, maxi, mean, medi;
        scanf("%d%d%d%d", &mini, &maxi, &mean, &medi);
        lld ans=solve(maxi-mini, mean-mini, medi-mini);
        
        if( ans<0 )
            printf("Case #%d: IMPOSSIBLE\n", cases);
        else
            printf("Case #%d: %lld\n", cases, ans);
    }
}

/*

5
6 4 5 1
7 7 8 8
2 2 2 2
3 7 5 5
1 4 3 4

*/
