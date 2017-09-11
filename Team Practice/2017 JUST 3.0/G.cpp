#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1<<18;

struct trie
{
    int n, a[N][27], b[N];
    
    void reset()
    {
        memset(this, 0, sizeof(trie));
    }
    
    void insert(const char* s)
    {
        for(int p=0, i=0; s[i]!='\0'; i++)
        {
            int c=s[i]-'a';
            
            if( !a[p][c] )
                a[p][c]=++n;
            
            p=a[p][c];
            b[i]=max(b[i], ++a[p][26]);
        }
    }
    
    int query(int x)
    {
        return b[x-1];
    }
} T;

char s[N];

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        
        for(T.reset(); n>0; n--)
        {
            scanf("%s", s);
            int l=strlen(s);
            
            for(int i=0; i<l-i-1; i++)
                swap(s[i], s[l-i-1]);
            
            T.insert(s);
        }
        
        for(; m>0; m--)
        {
            int x;
            scanf("%d", &x);
            printf("%d\n", T.query(x));
        }
    }
}
