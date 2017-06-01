#include<string>
#include<iostream>
#include<algorithm>
using namespace std;

int main()
{
    string s;
    cin >> s;
    int n=s.length(), ans=n;
    
    for(int i=0; i<n; i++)
    {
        for(int j=0; i+j<=n; j++)
        {
            int cnt=0;
            
            for(int k=0; k<n; k++)
            {
                cnt++;
                
                if( k+j<=n && s.substr(i, j)==s.substr(k, j) )
                    if( j>0 )
                        k+=j-1;
            }
            
            ans=min(ans, cnt+j);
        }
    }
    
    cout << ans << endl ;
}

/*

WNEENWEENEENE
NSEW
EEEEEEEEE

*/
