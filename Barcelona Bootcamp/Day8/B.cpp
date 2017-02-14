#include<cstdio>

bool check(char* s)
{
    for(int i=0, c='a'; ; c++)
    {
        while( s[i]=='-' )
            i++;
        
        if( s[i]=='\0' )
            return true;
        else if( s[i]!=c )
            return false;
        
        for(int j=i; s[j]!='\0'; j++)
            if( s[j]==c )
                s[j]='-';
    }
}

int main()
{
    char s[512];
    scanf("%s", s);
    printf(check(s) ? "YES\n" : "NO\n");
}
