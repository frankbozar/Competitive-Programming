#include<cstdio>
#include<cstring>
#include<set>
#include<vector>
#include<algorithm>
using namespace std;
const int N=1<<21;

struct trie
{
    int a[N][27], n;
    
    trie()
    {
        memset(this, 0, sizeof(trie));
    }
    
    void reset()
    {
        for(; n>=0; n--)
            memset(a[n], 0, sizeof(int)*27);
        
        n=0;
    }
    
    vector<int> insert(const char* s, int t)
    {
        vector<int> ans;
        
        for(int p=0; *s; s++)
        {
            int b=*s-'a';
            
            if( !a[p][b] )
                a[p][b]=++n;
            
            p=a[p][b];
            a[p][26]+=t;
            ans.push_back(p);
        }
        
        return ans;
    }
} T;

int cnt(const vector<vector<int>>& e, vector<vector<int>>& d, int u, int c)
{
    int& ans=d[u][c];
    
    if( ans<0 )
    {
        if( !T.a[u][26] )
            c=0;
        
        ans=c;
        
        for(int v : e[u])
        {
            if( c )
                ans+=cnt(e, d, v, 0);
            else
                ans+=max(cnt(e, d, v, 0), cnt(e, d, v, 1));
        }
    }
    
    return ans;
}

int sol(const vector<vector<int>>& a, const vector<vector<int>>& b, int n, int m)
{
    vector<vector<int>> e(m+1), d(m+1, vector<int>(2, -1));
    vector<int> in(m+1, 0);
    
    for(int i=0; i<n; i++)
        for(int j=b[i].size()-1; j>=0; j--)
            e[ b[i][j] ].push_back(a[i][j+1]);
    
    for(int i=1; i<=m; i++)
    {
        set<int> S(e[i].begin(), e[i].end());
        e[i].assign(S.begin(), S.end());
        
        for(int j : e[i])
            in[j]++;
    }
    
    int ans=0;
    
    for(int i=1; i<=m; i++)
        if( in[i]==0 )
            ans+=max(cnt(e, d, i, 0), cnt(e, d, i, 1));
    
    return ans;
}

char s[N];

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        T.reset();
        int n;
        scanf("%d", &n);
        vector<vector<int>> a(n), b(n);
        
        for(int i=0; i<n; i++)
        {
            scanf("%s", s);
            a[i]=T.insert(s+0, 1);
            b[i]=T.insert(s+1, 0);
        }
        
        printf("%d\n", sol(a, b, n, T.n));
    }
}
