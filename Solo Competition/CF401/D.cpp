#include<cstdio>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
char buf[1<<20];

void count(vector<string>& s, int l, int r, int p)
{
    for(int i=l; i<r; i++)
        while( s[i].length()>p )
            s[i].pop_back();
}

void solve(vector<string>& s, int l, int r, int p)
{
    if( l>=r-1 )
        return ;
    
    for(int i=l; i<r; i++)
        if( s[i].length()<=p )
        {
            count(s, l, i, p);
            solve(s, i+1, r, p);
            return ;
        }
    
    for(int i=r-1; i>l; i--)
        if( s[i][p]<s[i-1][p] )
        {
            count(s, l, i, p);
            l=i;
            break;
        }
    
    for(int i=l; i<r; )
    {
        int j=i;
        for(; j<r && s[j][p]==s[i][p]; j++);
        solve(s, i, j, p+1);
        i=j;
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    vector<string> s;
    
    for(int i=0; i<n; i++)
    {
        scanf("%s", buf);
        s.push_back(buf);
    }
    
    //printf("%d\n", solve(s, 0, n, 1));
    solve(s, 0, n, 1);
    
    for(int i=0; i<n; i++)
        printf("%s\n", s[i].c_str());
}
