#include<cstdio>
#include<set>
#include<queue>
#include<vector>
using namespace std;

int n;

struct vec
{
    vector<int> a;
    vec() : a(n){}
    
    void read()
    {
        for(int i=0; i<n; i++)
            scanf("%d", &a[i]);
    }
    
    void print() const
    {
        for(int i=0; i<n; i++)
            printf(i==n-1 ? "%d\n" : "%d ", a[i]);
    }
    
    bool operator<(const vec& V) const
    {
        return a>V.a;
    }
    
    vec operator+(const vec& V) const
    {
        vec s;
        
        for(int i=0; i<n; i++)
            s.a[i]=a[i]+V.a[i];
        
        return s;
    }
};

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int k, m;
        scanf("%d%d%d", &n, &k, &m);
        vector<vec> a(k);
        priority_queue<vec> PQ;
        set<vec> S;
        
        for(int i=0; i<k; i++)
        {
            a[i].read();
            
            if( S.find(a[i])==S.end() )
            {
                PQ.push(a[i]);
                S.insert(a[i]);
            }
        }
        
        for(; m>1; m--)
        {
            vec V=PQ.top();
            PQ.pop();
            
            for(int i=0; i<k; i++)
            {
                vec U=V+a[i];
                
                if( S.find(U)==S.end() )
                {
                    PQ.push(U);
                    S.insert(U);
                }
            }
        }
        
        PQ.top().print();
    }
}
