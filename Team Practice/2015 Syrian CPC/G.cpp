#include<stdio.h>
#include<algorithm>

using namespace std;

int main()
{
    int T;
    scanf("%d",&T);
    
    for(int t = 0; t < T; t++)
    {
        int n;
        scanf("%d",&n);
        
        char a[3][128*3];
        
        for(int i = 0; i < 3; i++)
            scanf("%s", a[i]);
        
        int ans = 0;
        
        for(int i = 0; i < n; i++)
        {
            int cnt = 0;
            
            for(int j = 0; j < 3; j++)
                for(int k = 0; k < 3; k++)
                    cnt += a[j][k+3*i] == '*' ? 4 : 0;
            
            ans = max(ans, cnt);
        }	
        
        printf("%d\n", ans);
    }
    
    
    
    return 0;
}
