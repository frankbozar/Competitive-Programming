#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

bool check(vector<vector<int> > a)
{
    for(int i = 1; i <= 5; i++)
        if( a[0][i]+a[1][i] == 0 )
            return false;
    
    return true;
}

vector<vector<int> > merge(vector<vector<int> > a, int i, int j)
{
    if( a[0][i] > 0 )
        a[0][i]--;
    else
        return a;
    
    if( a[0][j] > 0 )
        a[0][j]--;
    else
        return a;
    
    a[1][i+j]++;
    return a;
}


int main()
{
    int n;
    scanf("%d",&n);
    
    for(int t = 0; t < n; t++)
    {
        vector<vector<int> > a = vector<vector<int> >(2, vector<int>(16,0));
        char inp[16];
        bool ans = false;
        scanf("%s",inp);
        
        for(int i = 0; i < 7; i++)
            a[0][ inp[i]-'A'+1 ]++;
        
        ans |= check(a);
        
        for(int i = 1; i <= 5; i++)
            for(int j = i; j <= 5; j++)
                ans |= check(merge(a, i, j));
        
        for(int i = 1; i <= 5; i++)
            for(int j = i; j <= 5; j++)
            {
                vector<vector<int> >tmp = merge(a, i, j);
                
                for(int ii = 1; ii <= 5; ii++)
                    for(int jj = i; jj <= 5; jj++)
                        ans |= check(merge(tmp, ii, jj));
            }
        
        puts(ans ? "YES" : "NO");
        
    }
    
    
    
    return 0;
}
