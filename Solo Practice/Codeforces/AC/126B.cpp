#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

void Z(const char* s, int z[]){
    int n=z[0]=strlen(s);
	for(int l=0, r=0, i=1; i<n; i++)
        if( r<i || r-i<z[i-l] ){
            if( r<i ) r=i;
            for(l=i; r<n && s[r]==s[r-l]; r++);
            z[i]=r---l;
        }else z[i]=z[i-l];
}

const int N=1<<20;
char s[N]={0};
int z[N]={0};

int main()
{
    scanf("%s", s);
    int n=strlen(s);
    Z(s, z);
    
    for(int i=2; i<n; i++)
    {
        if( z[i-1]>=z[i] && z[i]==n-i )
        {
            printf("%.*s\n", z[i], s);
            return 0;
        }
        
        z[i]=max(z[i], z[i-1]);
    }
    
    printf("Just a legend\n");
}
