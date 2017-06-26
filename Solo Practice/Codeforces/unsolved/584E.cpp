#include<cstdio>
#include<cstdlib>
#include<vector>
#include<algorithm>
using namespace std;
typedef pair<int, int> data;

int get(vector<int> a)
{
    sort(a.begin(), a.end());
    return a[a.size()>>1];
}

int main()
{
    int n, ans=0;
    scanf("%d", &n);
    vector<int> a(n+1, 0), b(n+1, 0);
    
    for(int i=1; i<=n; i++)
    {
        int x;
        scanf("%d", &x);
        a[x]=i;
    }
    
    for(int i=1; i<=n; i++)
        scanf("%d", &b[i]);
    
    vector<vector<int>> c;
    
    for(int i=1; i<=n; i++)
    {
        if( b[i]==0 )
            continue;
        
        c.resize(c.size()+1);
        
        for(int j=i; b[j]>0; )
        {
            c.back().push_back(j);
            int t=b[j];
            b[j]=0;
            j=a[t];
        }
        
        if( c.back().size()==1 )
            c.pop_back();
    }
    
    vector<data> p;
    
    for(const auto& C : c)
    {
        for(int x : C)
            printf("%3d", x);
        printf("\n");
        
        int m=C.size();
        int t=get(C);
        int i=0;
        for(; C[i]!=t; i++);
        
        for(int x : C)
            ans+=abs(x-t);
        
        for(int j=i-1; j>=0; j--)
            p.push_back(data(t, C[j]));
        
        for(int j=m-1; j>i; j--)
            p.push_back(data(t, C[j]));
    }
    
    printf("%d\n%lu\n", ans, p.size());
    
    for(const data& P : p)
        printf("%d %d\n", P.first, P.second);
}
