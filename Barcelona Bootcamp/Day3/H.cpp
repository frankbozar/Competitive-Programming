#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=10101;
int b[N]={0}, z[N];
char s[N]={0};

int main()
{
    scanf("%s", s);
    int n=strlen(s), ans=0;
    
    for(int i=0; i<n; i++)
    {
        int t=b[i];
        
        for(int l=0, r=0, j=1; j+i<n; j++)
        {
            if( j>r )
            {
                for(l=r=j; r+i<n && s[r-l+i]==s[r+i]; r++);
                z[j]=r---l;
            }
            else
            {
                int k=j-l;
                
                if( z[k]<r-j+1 )
                    z[j]=z[k];
                else
                {
                    for(l=j; r+i<n && s[r-l+i]==s[r+i]; r++);
                    z[j]=r---l;
                }
            }
            
            int v=min(j, z[j]);
            t=max(t, v);
        }
        
        for(int j=1; j+i<n; j++)
            b[j+i]=max(b[j+i], min(z[j], t));
        
        ans+=t-b[i];
    }
    
    printf("%d\n", ans);
}

/*

abacabacaba

15

*/
