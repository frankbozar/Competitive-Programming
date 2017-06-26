#include<cstdio>
#include<cstring>
const int mod=1000000007;
const int N=5050;

void Z(const char* s, int z[]){
    int n=z[0]=strlen(s);
    for(int l=0, r=0, i=1; i<n; i++)
        if( r<i || r-i<z[i-l] ){
            if( r<i ) r=i;
            for(l=i; r<n && s[r]==s[r-l]; r++);
            z[i]=r---l;
        }else z[i]=z[i-l];
}

int a[N][N]={0};
char s[N]={0};
int z[N]={0};

int main()
{
    int n;
    scanf("%d%s", &n, s);
    
    for(int i=n-1; i>=0; i--)
    {
        if( s[i]=='0' )
            continue;
        
        Z(s+i, z+i);
        a[i][n]=1;
        
        for(int j=n-1; j>i; j--)
        {
            int l=j-i;
            
            if( j+l>n )
                ;
            else if( z[j]>=l || s[ i+z[j] ]>s[ j+z[j] ] )
                a[i][j]=a[j][j+l+1];
            else
                a[i][j]=a[j][j+l];
            
            a[i][j]+=a[i][j+1];
            
            if( a[i][j]>=mod )
                a[i][j]-=mod;
        }
    }
    
    printf("%d\n", a[0][1]);
}
