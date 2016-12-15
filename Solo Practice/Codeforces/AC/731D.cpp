#include<cstdio>
#include<vector>
using namespace std;

void solve(const vector<int>& a, const vector<int>& b, int c, vector<int>& t)
{
    for(int n=a.size(), m=b.size(), i=0; ; i++)
    {
        if( i>=n )
        {
            t[0]++;
            t[c]--;
            break;
        }
        else if( i>=m )
            break;
        else if( a[i]<b[i] )
        {
            t[0]++;
            t[c-b[i]+1]--;
            t[c-a[i]+1]++;
            t[c]--;
            break;
        }
        else if( a[i]>b[i] )
        {
            t[c-a[i]+1]++;
            t[c-b[i]+1]--;
            break;
        }
    }
}

int count(vector<int>& t, int n, int c)
{
    for(int i=0; i<c; i++)
    {
        if( i>0 )
            t[i]+=t[i-1];
        
        if( t[i]>=n-1 )
            return i;
    }
    
    return -1;
}

int main()
{
    int n, c;
    scanf("%d%d", &n, &c);
    vector<vector<int>> a(n);
    vector<int> t(c+1, 0);
    
    for(int i=0; i<n; i++)
    {
        int l;
        scanf("%d", &l);
        a[i].resize(l);
        
        for(int j=0; j<l; j++)
            scanf("%d", &a[i][j]);
    }
    
    for(int i=1; i<n; i++)
        solve(a[i-1], a[i], c, t);
    
    printf("%d\n", count(t, n, c));
}