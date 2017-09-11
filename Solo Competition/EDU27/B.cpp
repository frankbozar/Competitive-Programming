#include<cstdio>
#include<cstdlib>
const int INF=1<<20;

int f(int a[6])
{
    return a[0]+a[1]+a[2]-a[3]-a[4]-a[5];
}

int sol(int a[6])
{
    int val=f(a);
    
    if( val==0 )
        return 0;
    
    int v=INF, p=0, q=0;
    
    for(int i=0; i<6; i++)
    {
        for(int j=0; j<10; j+=9)
        {
            int tmp=a[i];
            a[i]=j;
            int t=f(a);
            a[i]=tmp;
            
            if( val*t<=0 )
                return 1;
            
            t=abs(t);
            
            if( v>t )
            {
                v=t;
                p=i;
                q=j;
            }
        }
    }
    
    a[p]=q;
    return sol(a)+1;
}

int main()
{
    int a[6];
    
    for(int i=0; i<6; i++)
        scanf("%1d", &a[i]);
    
    printf("%d\n", sol(a));
}
