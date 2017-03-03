#include<cstdio>
#include<algorithm>
using namespace std;

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    n%=6;
    
    if( m==0 )
    {
        switch( n )
        {
            case 0:
            case 5:
                printf("0\n");
                break;
            case 1:
            case 2:
                printf("1\n");
                break;
            default:
                printf("2\n");
        }
    }
    else if( m==1 )
    {
        switch( n )
        {
            case 1:
            case 4:
                printf("0\n");
                break;
            case 0:
            case 3:
                printf("1\n");
                break;
            default:
                printf("2\n");
        }
    }
    else//if( m==2 )
    {
        switch( n )
        {
            case 2:
            case 3:
                printf("0\n");
                break;
            case 4:
            case 5:
                printf("1\n");
                break;
            default:
                printf("2\n");
        }
    }
}
