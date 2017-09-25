#include<cstdio>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;

void print(int x, int m=-1)
{
    if( m<0 )
        printf("%d solutions\n", x);
    else
    {
        for(int i=m-1; i>=0; i--)
            printf("%d", (x>>i)&1);
        
        printf("\n");
    }
}

vector<int> gen(const vector<int>& a, int b, int l, int r)
{
    vector<int> ans;
    
    for(int x : a)
    {
        int cnt=0;
        
        for(int i=l; i<r; i++)
            cnt+=((x>>i)&1)==((b>>i)&1);
        
        ans.push_back(cnt);
    }
    
    return ans;
}

void sol(int n, int m, vector<int>& a, vector<int>& c)
{
    int cnt=0, ans=0;
    
    if( m<=15 )
    {
        for(int i=(1<<m)-1; i>=0; i--)
            if( gen(a, i, 0, m)==c )
                cnt++, ans=i;
    }
    else
    {
        map<vector<int>, pair<int, int>> M;
        int l=m>>1, r=m-l;
        
        for(int i=(1<<l)-1; i>=0; i--)
        {
            vector<int> D=gen(a, i, 0, l);
            auto it=M.find(D);
            
            if( it==M.end() )
                M[D].first=1, M[D].second=i;
            else
                M[D].first++;
        }
        
        for(int i=(1<<r)-1; i>=0; i--)
        {
            vector<int> D=gen(a, i<<l, l, m);
            bool ok=true;
            
            for(int j=0; j<n; j++)
            {
                D[j]=c[j]-D[j];
                
                if( D[j]<0 )
                    ok=false;
            }
            
            auto it=M.find(D);
            
            if( !ok || it==M.end() )
                continue;
            
            cnt+=it->second.first;
            ans=(i<<l)|it->second.second;
        }
    }
    
    if( cnt==1 )
        print(ans, m);
    else
        print(cnt);
}

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        vector<int> a(n, 0), c(n);
        
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<m; j++)
            {
                int b;
                scanf("%1d", &b);
                a[i]=(a[i]<<1)|b;
            }
            
            scanf("%d", &c[i]);
        }
        
        sol(n, m, a, c);
    }
}

/*

3

3 5
01101 4
10100 3
00011 3

3 5
01101 0
10100 3
00011 2

4 4
0000 2
1010 2
0101 2
1111 2

*/
