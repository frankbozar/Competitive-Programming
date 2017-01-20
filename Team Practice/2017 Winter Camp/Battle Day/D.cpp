#include<cstdio>
#include<map>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

struct CLOCK
{
    int h;
    CLOCK(int _h=0) : h(_h){}
    
    CLOCK operator+(int n) const
    {
        return CLOCK((h+n+12)%12);
    }
    
    bool operator<(const CLOCK& C) const
    {
        return h<C.h;
    }
};

int n;

struct CLOCKs
{
    long long val;
    vector<CLOCK> c;
    
    void read()
    {
        c.resize(n);
        
        for(int i=0; i<n; i++)
        {
            scanf("%d", &c[i].h);
            c[i].h=12-c[i].h;
        }
        
        hash();
    }
    
    void hash()
    {
        
        sort(c.begin(), c.end());
        val=0;
        
        for(int i=0; i<n; i++)
            val=val*12+c[i].h;
    }
    
    bool operator<(const CLOCKs& C) const
    {
        return val<C.val;
    }
    
    vector<CLOCKs> next(int a, int b) const
    {
        vector<CLOCKs> ans;
        CLOCKs p;
        make(ans, p, a, b);
        return ans;
    }
    
    void make(vector<CLOCKs>& ans, CLOCKs& p, int a, int b, int i=0) const
    {
        if( a<0 || a>n-i )
            return ;
        else if( i==n )
        {
            CLOCKs t=p;
            t.hash();
            ans.push_back(t);
            return ;
        }
        
        p.c.push_back(c[i]+b);
        make(ans, p, a-1, b, i+1);
        p.c.pop_back();
        p.c.push_back(c[i]);
        make(ans, p, a, b, i+1);
        p.c.pop_back();
    }
};

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int m, ans=-1;
        scanf("%d%d", &n, &m);
        vector<pair<int, int>> t(m);
        CLOCKs C;
        C.read();
        
        
        
        for(int i=0; i<m; i++)
        {
            scanf("%d%d", &t[i].first, &t[i].second);
            t[i].second=-t[i].second;
        }
        
        map<CLOCKs, int> M;
        queue<CLOCKs> Q;
        
        for(Q.push(C); !Q.empty(); Q.pop())
        {
            const CLOCKs& C=Q.front();
            
            if( C.val==0 )
            {
                ans=M[C];
                break;
            }
            
            if( M[C]>=8 )
                continue;
            
            for(int i=0; i<m; i++)
                for(const CLOCKs& D : C.next(t[i].first, t[i].second))
                    if( M.find(D)==M.end() )
                    {
                        M[D]=M[C]+1;
                        Q.push(D);
                    }
        }
        
        printf("%d\n", ans);
    }
}

/*

2
4 2
7 10 7 9
3 2
3 3
2 1
4 5
1 -1

*/
