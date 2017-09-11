#include<cstdio>
#include<cstdlib>
#include<set>
#include<bitset>
#include<vector>
using namespace std;
typedef bitset<1<<21> bs;
const int INF=1000000;

vector<int> sol(const vector<int>& a)
{
    int n=a.size();
    set<int> S;
    
    for(int i=0; i<n; i++)
        for(int j=i+1; j<n; j++)
            S.insert(abs(a[i]-a[j]));
    
    vector<int> b;
    bs B;
    
    for(int i=1; i<=INF; i++)
    {
        if( B[i] )
            continue;
        
        b.push_back(i);
        
        if( b.size()==n )
            return b;
        
        for(int x : S)
            B[i+x]=true;
    }
    
    b.clear();
    return b;
}

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n;
        scanf("%d", &n);
        vector<int> a(n);
        
        for(int i=0; i<n; i++)
            scanf("%d", &a[i]);
        
        vector<int> b=sol(a);
        printf(b.empty() ? "NO\n" : "YES\n");
        
        for(int i=b.size()-1; i>=0; i--)
            printf(i==0 ? "%d\n" : "%d ", b[i]);
    }
}
