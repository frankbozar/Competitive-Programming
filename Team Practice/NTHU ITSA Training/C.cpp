#include<cstdio>
typedef long long lld;
const int L=16;
lld f[L]={0};

lld pw(lld x, lld p)
{
    return p==0 ? 1 : pw(x, p-1)*x;
}

lld pp(lld p)
{
    return pw(10, p)-pw(9, p);
}

lld seven(lld x, lld b)
{
    if( x<7 )
        return 0;
    
    lld ten=pw(10, b);
    
    if( x/ten<7 )
        return x/ten*pp(b)+seven(x%ten, b-1);
    else if( x/ten==7 )
        return 7*pp(b)+x%ten+1;
    else
        return (x/ten-1)*pp(b)+pw(10, b)+seven(x%ten, b-1);
}

lld count(lld x, lld b=L-1)
{
    if( x<87 )
        return 0;
    
    lld ten=pw(10, b);
    
    if( x<ten*8 )
        return x/ten*f[b]+count(x%ten, b-1);
    else if( x/ten==8 )
        return 8*f[b]+seven(x%ten, b-1);
    else//if( x/ten==9 )
        return 8*f[b]+pp(b)+count(x%ten, b-1);
}

int main()
{
    f[0]=f[1]=0;
    
    for(int i=2; i<L; i++)
        f[i]=pp(i-1)+f[i-1]*9;
    
    for(lld l, r; scanf("%lld%lld", &l, &r)!=EOF; )
        printf("%lld\n", r-l+1-count(r)+count(l-1));
}
