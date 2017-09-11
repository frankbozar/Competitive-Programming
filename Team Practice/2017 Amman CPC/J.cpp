#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
char s[1<<20];

bool ok(const vector<int>& a, int x)
{
    int p=0;
    
    for(int v : a)
        if( v==p )
            p+=x;
    
    return p==a.back()+x;
}

bool ok(const vector<int>& a)
{
    for(int i=1; i<a.back(); i++)
        if( a.back()%i==0 && ok(a, i) )
            return true;
    
    return false;
}

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        scanf(" %[^\n]", s);;
        vector<int> a(1, 0);
        
        for(const char* p=strtok(s, " "); p!=NULL; p=strtok(NULL, " "))
            a.push_back(a.back()+strlen(p)+1);
        
        printf(ok(a) ? "YES\n" : "NO\n");
    }
}
