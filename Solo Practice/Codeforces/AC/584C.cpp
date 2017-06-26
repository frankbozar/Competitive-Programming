#include<cassert>

#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int N=1<<20;
char a[N]={0}, b[N]={0}, c[N]={0};

char get(char x, char y)
{
    char z;
    
    do{
        z=rand()%26+'a';
    }while( z==x || z==y );
    
    return z;
}

int main()
{
    int n, m, k=0;
    scanf("%d%d%s%s", &n, &m, a, b);
    
    for(int i=0; i<n; i++)
        if( a[i]!=b[i] )
            k++;
    
    if( (k+1)>>1>m )
        printf("-1\n");
    else
    {
        int p=k>>1;
        int q=k>>1;
        m-=(k&1)+p;
        
        if( m>n-k )
        {
            p-=m-n+k;
            q-=m-n+k;
            m-=m-n+k;
        }
        
        for(int i=0; i<n; i++)
        {
            if( a[i]==b[i] )
            {
                if( m-->0 )
                    c[i]=get(a[i], b[i]);
                else
                    c[i]=a[i];
            }
            else
            {
                if( p-->0 )
                    c[i]=a[i];
                else if( q-->0 )
                    c[i]=b[i];
                else
                    c[i]=get(a[i], b[i]);
            }
        }
        
        printf("%s\n", c);
    }
}
