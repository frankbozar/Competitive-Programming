#include<cstdio>
const double EPS=1e-12;

double f(double a, double r)
{
    return a/(1-r);
}

double game(double p, int t, int w, int l, double x)
{
    if( x<EPS )
        return 0;
    else if( l>=t && l-w>=2 )
        return 0;
    else if( w>=t && w-l>=2 )
        return x;
    else if( w==t-1 && l==t-1 )
        return f(x*p*p, p*(1-p)*2);
    else
        return game(p, t, w+1, l, x*p)+game(p, t, w, l+1, x*(1-p));
}

double set(double g, double t, int w, int l, double x)
{
    if( x<EPS )
        return 0;
    else if( l>=6 && l-w>=2 )
        return 0;
    else if( w>=6 && w-l>=2 )
        return x;
    else if( w==6 && l==6 )
        return x*t;
    else
        return set(g, t, w+1, l, x*g)+set(g, t, w, l+1, x*(1-g));
}

double match(double s, int w, int l, double x)
{
    if( x<EPS )
        return 0;
    else if( l>=2 )
        return 0;
    else if( w>=2 )
        return x;
    else
        return match(s, w+1, l, x*s)+match(s, w, l+1, x*(1-s));
}

int main()
{
    for(double p; scanf("%lf", &p) && p>=0; )
    {
        double g=game(p, 4, 0, 0, 1);
        double t=game(p, 7, 0, 0, 1);
        double s=set(g, t, 0, 0, 1);
        double m=match(s, 0, 0, 1);
        printf("%.12f %.12f %.12f\n", g, s, m);
    }
}

/*

0.5
0.3
0.7
-1

*/
