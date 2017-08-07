#include<cstdio>
#include<algorithm>
using namespace std;

int count(const char* s)
{
    int ans=0;
    
    for(; *s; s++)
        ans+= 'A'<=*s && *s<='Z';
    
    return ans;
}

int main()
{
    scanf("%*d");
    int ans=0;
    
    for(char s[1<<10]; scanf("%s", s)!=EOF; )
        ans=max(ans, count(s));
    
    printf("%d\n", ans);
}
