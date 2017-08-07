#include<cstdio>
#include<cstring>
#include<string>
using namespace std;

string sol(const string& S)
{
    string T, K, N, P;
    
    for(char c : S)
    {
        if( strchr("KACE", c) )
            K+=c;
        else if( strchr("pqrst", c) )
            P+=c;
        else
            N+=c;
    }
    
    if( P=="" )
        return "no WFF possible";
    
    T=P.back();
    
    for(int i=P.size()-2, j=K.size()-1; j>=0 && i>=0; i--, j--)
        T=K[j]+T+P[i];
    
    return N+T ;
}

int main()
{
    for(char s[1<<10]; scanf("%s", s) && strcmp(s, "0"); printf("%s\n", sol(s).c_str()));
}

/*

qKpNq
KKN
0

*/
