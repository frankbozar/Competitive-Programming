#include<cstdio>
#include<cstring>

int Z(const char* s, int z[]){
    int n=z[0]=strlen(s);
	for(int l=0, r=0, i=1; i<n; i++)
        if( r<i || r-i<z[i-l] ){
            if( r<i ) r=i;
            for(l=i; r<n && s[r]==s[r-l]; r++);
            z[i]=r---l;
        }else z[i]=z[i-l];
    return n;
}

const int N=1<<20;
char s[N]={0};
int c[N]={0}, z[N]={0};

int main()
{
    scanf("%s", s);
    int n=Z(s, z), ans=0;
    
    for(int i=n-1; i>=0; i--)
        c[ z[i] ]++;
    
    for(int i=n-1; i>=0; i--)
        c[i]+=c[i+1];
    
    for(int i=n-1; i>=0; i--)
        if( z[i]==n-i )
            ans++;
    
    printf("%d\n", ans);
    
    for(int i=n-1; i>=0; i--)
        if( z[i]==n-i )
            printf("%d %d\n", z[i], c[ z[i] ]);
}
