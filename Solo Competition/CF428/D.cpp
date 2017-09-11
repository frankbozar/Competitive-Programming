#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
const lld mod=1000000007;
const int N=1<<20;

lld sol(const vector<lld>& two, vector<vector<int>>& a)
{
    lld ans=0;
    
    for(int i=2; i<N; i++)
    {
        vector<int>& v=a[i];
        sort(v.rbegin(), v.rend());
        lld p=0, x=i;
        
        for(int j=1; !v.empty(); j++)
        {
            lld tmp=two[v.size()-1]*v.size()%mod*(x-p+mod);
            ans=(ans+tmp)%mod;
            p=x;
            x=x*i%mod;
            for(; !v.empty() && v.back()<=j; v.pop_back());
        }
    }
    
    return ans;
}

int main()
{
    vector<lld> md(N, -1), two(N);
    two[0]=1, two[1]=2;
    
    for(int i=2; i<N; i++)
    {
        two[i]=(two[i-1]<<1)%mod;
        
        if( md[i]>0 )
            continue;
        
        for(int j=i; j<N; j+=i)
            md[j]=i;
    }
    
    int n;
    lld ans=0;
    vector<vector<int>> a(N);
    
    for(scanf("%d", &n); n>0; n--)
    {
        int x;
        scanf("%d", &x);
        
        if( x<=1 )
            continue;
        
        for(/*ans+=x*/; x>1; )
        {
            int cnt=0, p=md[x];
            
            for(; x%p==0; x/=p)
                cnt++;
            
            a[p].push_back(x);
        }
    }
    
    ans+=sol(two, a);
    printf("%lld\n", ans%mod);
}
