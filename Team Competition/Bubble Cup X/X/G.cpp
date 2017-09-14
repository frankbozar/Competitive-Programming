#include<cstdio>
#include<cstring>

struct trie
{
    int n, m, a[5000005][7];
    
    trie()
    {
        memset(this, 0, sizeof(trie));
    }
    
    void insert(const char* s)
    {
        int p=0;
        
        for(int i=0; s[i]!='\0'; i++)
        {
            int b=s[i]-'a';
            
            if( a[p][b]==0 )
                a[p][b]=++n;
            
            p=a[p][b];
        }
        
        a[p][5]++;
    }
    
    int query(const char* t)
    {
        m++;
        int ans=0;
        gen(ans, 0, t);
        return ans;
    }
    
    void gen(int& ans, int p, const char* t)
    {
        if( *t=='\0' )
        {
            if( a[p][6]<m )
            {
                a[p][6]=m;
                ans+=a[p][5];
            }
        }
        else if( *t!='?' )
        {
            if( a[p][*t-'a'] )
                gen(ans, a[p][*t-'a'], t+1);
        }
        else
        {
            gen(ans, p, t+1);
        
            for(int i=0; i<5; i++)
                if( a[p][i] )
                    gen(ans, a[p][i], t+1);
        }
    }
} T;

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    
    for(; n>0; n--)
    {
        char s[64]={0};
        scanf("%s", s);
        T.insert(s);
    }
    
    for(; m>0; m--)
    {
        char s[64]={0};
        scanf("%s", s);
        printf("%d\n", T.query(s));
    }
}
