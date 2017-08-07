#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    vector<vector<bool>> a(m+1, vector<bool>(128, false));
    vector<int> time(128, -1), team(128, -1);
    
    for(; k>0; k--)
    {
        int p, q;
        char r[2], s[8];
        scanf("%d%d%s%s", &p, &q, r, s);
        
        if( s[0]=='Y' && !a[q][ r[0] ] )
        {
            a[q][ r[0] ]=true;
            time[ r[0] ]=p;
            team[ r[0] ]=q;
        }
    }
    
    for(char i='A'; i<'A'+n; i++)
    {
        if( time[i]<0 )
            printf("%c - -\n", i);
        else
            printf("%c %d %d\n", i, time[i], team[i]);
    }
}

/*

5 10 18
0 2 B No
11 2 B Yes
20 3 A Yes
35 8 E No
40 8 E No
45 7 E No
50 10 A Yes
100 4 A No
120 6 B Yes
160 2 E Yes
180 2 A Yes
210 3 B Yes
240 10 B No
250 10 B Yes
270 2 B Yes
295 8 E Yes
295 7 E Yes
299 10 D Yes

*/
