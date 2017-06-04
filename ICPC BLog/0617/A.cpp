#include<cstdio>

bool ok(int a[7])
{
    int d[4]={28, 29, 30, 31};
    
    for(int k=0; k<4; k++)
    {
        bool ans=a[0]<d[k];
        
        for(int i=1; i<7; i++)
            if( a[i]!=(a[0]+i)%d[k] )
                ans=false;
        
        if( ans )
            return true;
    }
    
    return false;
}

int main()
{
    int a[7];
    
    for(int i=0; i<7; i++)
    {
        scanf("%d", &a[i]);
        a[i]--;
    }
    
    printf(ok(a) ? "Possible\n" : "Impossible\n");
}
