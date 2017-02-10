#include<cstdio>
typedef long long lld;
const int H=15, L=6000;
lld a[H][L][2]={0};

int main()
{
    lld n, m, ans=0;
    scanf("%lld%lld", &n, &m);
    a[0][1][1]=1;
    a[1][2][0]=a[1][2][1]=1;
    a[1][3][1]=1;
    
    for(int h=2; h<H; h++)
    {
        for(int l=1<<h; l<=n; l++)
        {
            for(int i=1<<(h-1), j=l-i; j>i; j--, i++)
            {
                a[h][l][0]+=a[h-1][i][1]*a[h-1][j][1];
                
                if( !(i&7) )
                    a[h][l][0]%=m;
            }
            
            a[h][l][0]<<=1;
            
            if( !(l&1) )
                a[h][l][0]+=a[h-1][l>>1][1]*a[h-1][l>>1][1];
            
            a[h][l][1]=a[h][l][0]%=m;
            
            for(int i=1<<(h-1), j=l-i; j>=1<<h; j--, i++)
            {
                a[h][l][1]+=a[h-1][i][1]*a[h][j][0];
                
                if( !(i&7) )
                    a[h][l][1]%=m;
            }
            
            a[h][l][1]%=m;
        }
    }
    
    for(int h=0; h<H; h++)
        ans+=a[h][n][1];
        
    printf("%lld\n", ans%m);
}
