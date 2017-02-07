#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
char s[1000];
int den[1000]={1}, ans[1000]={0};

int main()
{
    int n;
    scanf("%d%s", &n, s);
    int m=strlen(s);
    
    if( s[0]=='N' )
    {
        printf("0\n%d", n);
        
        for(int i=1; i<m; i++)
            printf(" 0");
        
        printf("\n");
        return 0;
    }
    
    for(int i=1; i<m; i++)
    {
        if( s[i]=='Y' )
            den[i]=den[i-1]+1;
        else
            den[i]=den[i-1];
    }
    
    for(int p=m, i=0; i<m; i++)
    {
        double mdn=1;
        int idx=0;
        
        for(int i=0; i<p; i++)
        {
            if( mdn>=den[i]/(i+1.0) )
            {
                mdn=den[i]/(i+1.0);
                idx=i;
            }
        }
        
        p=idx;
        
        for(int i=0; i<=idx; i++)
            ans[i]+=n/(idx+1);
        
        n%=idx+1;
    }
    
    int val=0;
    
    for(int i=0; i<m; i++)
    {
        if( s[i]=='Y' )
            val+=ans[i];
    }
    
    printf("%d\n", val);
    
    for(int i=0; i<m; i++)
        printf(i==m-1 ? "%d\n" : "%d ", ans[i]);
}

/*

23
YNYNNYY

*/
