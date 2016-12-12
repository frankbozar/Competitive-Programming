#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

void Z(const vector<int>& a, vector<int>& h, int n)
{
    vector<int> z(n<<1, n<<1);
    
    for(int l=0, r=0, i=1; i<n; i++)
    {
        if( i>r )
        {
            for(l=r=i; r<n<<1 && a[r-l]==a[r]; r++);
            z[i]=r---l;
        }
        else
        {
            int k=i-l;
            
            if( z[k]<r-i+1 )
                z[i]=z[k];
            else
            {
                for(l=i; r<n<<1 && a[r-l]==a[r]; r++);
                z[i]=r---l;
            }
        }
        
        if( z[i]>=n )
            h[i]++;
    }
}

int solution(vector<vector<int>>& a)
{
    if( a.empty() || a.front().empty() )
        return 0;
    
    int n=a.size(), p=0, q=0;
    int m=a.front().size();
    vector<int> v(m, 0), h(n, 0);
    
    for(int i=0; i<n; i++)
    {
        vector<int> tmp(m<<1);
        
        for(int j=0; j<m; j++)
            tmp[j]=tmp[j+m]=a[i][j];
        
        Z(tmp, v, m);
    }
    
    for(int i=0; i<m; i++)
    {
        vector<int> tmp(n<<1);
        
        for(int j=0; j<n; j++)
            tmp[j]=tmp[j+n]=a[j][i];
        
        Z(tmp, h, n);
    }
    
    for(int i=0; i<m; i++)
        if( v[i]>=n )
            p++;
    
    for(int i=0; i<n; i++)
        if( h[i]>=m )
            q++;
    
    return (p+1)*(q+1);
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    vector<vector<int>> a(n, vector<int>(m));
    
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            scanf("%d", &a[i][j]);
    
    printf("%d\n", solution(a));
}

/*

4 6
1 2 1 2 1 2
3 4 3 4 3 4
1 2 1 2 1 2
3 4 3 4 3 4

*/