#include<cstdio>
#include<set>
#include<vector>
#include<algorithm>
using namespace std;

bool ok(vector<int>& a, int l, multiset<int>& S)
{
    multiset<int> T;
    
    for(int x : a)
        if( S.find(l-x)!=S.end() )
        {
            S.erase(S.find(l-x));
            T.insert(l-x);
        }
    
    a.push_back(l);
    
    if( T.size()==a.size()-1 )
        return true;
    
    a.pop_back();
    
    for(int x : T)
        S.insert(x);
    
    return false;
}

bool sol(vector<int>& ans, const vector<int>& a, multiset<int>& S, const int n, const int l, int i)
{
    if( ans.size()==n-1 )
        return ok(ans, l, S);
    
    for(; i+1+ans.size()>=n; i--)
    {
        if( ok(ans, a[i], S) )
        {
            if( sol(ans, a, S, n, l, i-1) )
                return true;
            
            for(int j=a.size()-2; j>=0; j--)
                S.insert(ans.back()-a[j]);
            
            ans.pop_back();
        }
    }
    
    return false;
}

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n;
        scanf("%d", &n);
        int m=n*(n-1)/2;
        vector<int> a(m);
        
        for(int i=0; i<m; i++)
            scanf("%d", &a[i]);
        
        sort(a.begin(), a.end());
        int l=a.back();
        set<int> S;
        
        for(int i=0; i<m; i++)
        {
            for(int j=i+1; j<m; j++)
                if( a[i]+a[j]==l )
                {
                    S.insert(a[i]);
                    S.insert(a[j]);
                }
        }
        
        multiset<int> T(a.begin(), a.end());
        vector<int> b(S.rbegin(), S.rend());
        vector<int> ans(1, 0);
        sol(ans, b, T, n, l, b.size()-1);
        
        for(int i=0; i<n; i++)
            printf(i==n-1 ? "%d\n" : "%d ", ans[i]);
    }
}
