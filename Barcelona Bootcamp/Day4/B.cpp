#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
char s[1<<20], t[1<<10];

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        scanf("%s%s", s, t);
        vector<vector<int>> p(26);
        int n=strlen(s);
        int m=strlen(t);
        
        for(int i=0; i<n; i++)
            p[ s[i]-'a' ].push_back(i);
        
        for(int i=0; i<26; i++)
            p[i].push_back(n+1);
        
        vector<int> a(m+2, n+1);
        a[0]=0;
        
        for(int i=0; i<m; i++)
        {
            int ch=t[i]-'a';
            
            for(int j=i; j>=0; j--)
            {
                int it=*lower_bound(p[ch].begin(), p[ch].end(), a[j]);
                a[j+1]=min(a[j+1], it+1);
            }
        }
        
        for(int i=m; i>=0; i--)
            if( a[i]<a[i+1] )
            {
                printf("%d\n", i);
                break;
            }
    }
}

/*

1
abcdefghijklmnopqrstuvwxyz
bbddee

1
abcdefghi
bbddee

*/
