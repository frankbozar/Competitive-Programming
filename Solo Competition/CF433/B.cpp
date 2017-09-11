#include<cstdio>
#include<map>
#include<vector>
using namespace std;
typedef long long lld;
const int N=1<<20;
const lld INF=1LL<<60;
typedef pair<int, int> data;

lld sol(vector<map<int, int>>& P, vector<map<int, int>>& Q, int n, int m)
{
    vector<vector<data>> a(N), b(N);
    
    for(int i=1; i<=n; i++)
    {
        if( P[i].empty() || Q[i].empty() )
            return -1;
        
        vector<data> s(P[i].begin(), P[i].end());
        int k=s.size();
        
        for(int j=1; j<k; j++)
            s[j].second=min(s[j].second, s[j-1].second);
        
        for(int j=0; j<k; j++)
            a[ s[j].first ].push_back(data(i, s[j].second));
        
        s.assign(Q[i].begin(), Q[i].end());
        k=s.size();
        
        for(int j=k-2; j>=0; j--)
            s[j].second=min(s[j].second, s[j+1].second);
        
        for(int j=0; j<k; j++)
            b[ s[j].first ].push_back(data(i, s[j].second));
    }
    
    vector<lld> s(N, INF), t(N, INF);
    vector<int> w(n+1, 0);
    int cnt=0;
    lld tmp=0;
    
    for(int i=0; i<N; i++)
    {
        for(const data& D : a[i])
        {
            cnt+=w[D.first]==0;
            tmp+=D.second-w[D.first];
            w[D.first]=D.second;
        }
        
        if( cnt==n )
            s[i]=tmp;
    }
    
    w.assign(n+1, 0);
    cnt=tmp=0;
    
    for(int i=N-1; i>=0; i--)
    {
        for(const data& D : b[i])
        {
            cnt+=w[D.first]==0;
            tmp+=D.second-w[D.first];
            w[D.first]=D.second;
        }
        
        if( cnt==n )
            t[i]=tmp;
    }
    
    lld ans=INF;
    
    for(int i=0; i+m+1<N; i++)
        ans=min(ans, s[i]+t[i+m+1]);
    
    return ans>=INF ? -1 : ans ;
}

int main()
{
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    vector<map<int, int>> P(n+1), Q(n+1);
    
    for(; m>0; m--)
    {
        int d, f, t, c;
        scanf("%d%d%d%d", &d, &f, &t, &c);
        
        if( f==0 )
        {
            if( Q[t].find(d)==Q[t].end() )
                Q[t][d]=c;
            else
                Q[t][d]=min(Q[t][d], c);
        }
        else//if( t==0 )
        {
            if( P[f].find(d)==P[f].end() )
                P[f][d]=c;
            else
                P[f][d]=min(P[f][d], c);
        }
    }
    
    printf("%lld\n", sol(P, Q, n, k));
}
