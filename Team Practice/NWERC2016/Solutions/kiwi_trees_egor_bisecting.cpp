/*

Consider a vertex of the allowed region. For this vertex there are at least two edges of polygon, to which the distance is exactly 4.

Given the constrains for the input, these two edges must be back-to-back. Thus the algorithm:

   only for "convex" vertices (i.e. inner angle<180°):
        calculate the bisecting and a point on it which is 4m from both sides.
        check that the distance from this point to all edges is at least 4m (if this point is outside, the distance will be less than 4m) 

Running time: O(n^2)
*/

#include <bits/stdc++.h>
using namespace std;

typedef pair<double, double> Point;
typedef Point Vec;
typedef pair<Point, Point> Line;
typedef vector<Point> Points;

const double DIST=4000.0;
const double EPS=1e-6;

#define XX first
#define YY second 

Point operator+(const Point &a, const Point &b){return make_pair(a.XX+b.XX, a.YY+b.YY);}
Point operator-(const Point &a, const Point &b){return make_pair(a.XX-b.XX, a.YY-b.YY);}
double operator*(const Point &a, const Point &b){return a.XX*b.XX+a.YY*b.YY;}
Point operator*(double f, const Point &a){return make_pair(f*a.XX, f*a.YY);}
double len(const Point &p){ return sqrt(p.XX*p.XX+p.YY*p.YY);}
double cross(const Point &v, const Point &w){ return v.XX*w.YY-v.YY*w.XX;}
ostream &operator<<(ostream &s, const Point &p){ s << "("<<p.XX<<","<<p.YY<<")";}
double dist(const Point &a, const Point &b){ return len(a-b);}
void norm(Point &a){ double d=len(a); a.XX/=d; a.YY/=d;}



Point get_dir(const Point &start, const Point &end){
    Point diff=end-start;
    return 1/len(diff)*diff;
}

bool skip_flag=false;
Point get_point_on_bisecting(const Point &a, const Point &b, const Point &c, double D){
    Vec A=a-b;norm(A);
    Vec C=c-b;norm(C);
    
    Vec bisect=A+C;
    
    double F=D/cross(A, bisect);//cross is non zero because of the input constrains
    skip_flag=F<0.0;//non convex angle
    
    return b+F*bisect;
}



double dist2line(const Point &p, const Point &lineA, const Point &lineB){
    Vec dir=get_dir(lineA, lineB);
    Vec v=p-lineA;
    double len=dist(lineA, lineB);
    double dist_proj=dir*v;
    if(dist_proj>0.0 && dist_proj<len)//nearest point between A and B
        return fabs(v*make_pair(dir.YY, -dir.XX));
    else
        return min(dist(p,lineB), dist(p, lineA));
}

double min_dist(const Points &points, const Point &p, double early_exit){
    double res=dist2line(p, points.front(), points.back());
    for(size_t i=1;i<points.size();i++){
        res=min(res, dist2line(p, points[i], points[i-1]));
        //cerr << i <<" "<< res << points[i] <<points[i-1]<<"\n";
        if(early_exit>res)
          break;
    }
    return res;
}

int main(){
    size_t n;
    cin >> n;
    
    Points points(n);
    for(auto &p:points)
        cin >> p.XX >> p.YY;
    
    Points cands;    
    for(size_t i=0;i<n;i++){
        size_t next=(i+1)%n;
        size_t prev=(i+n-1)%n;
        
        Point cand=get_point_on_bisecting(points[prev], points[i], points[next], DIST);
        if(skip_flag)//only "convex" vertices!
          continue;
        if(min_dist(points, cand, DIST-EPS)+EPS>=DIST){
            cands.push_back(cand);
        }
    }
    
    //ok now check the candidates:
    for(size_t i=0;i<cands.size();i++){
        for(size_t j=i+1;j<cands.size();j++)
           if (dist(cands[i], cands[j])+EPS>2.0*DIST){
                cout << setprecision(17);
                cout << cands[i].XX << " " << cands[i].YY <<"\n";
                cout << cands[j].XX << " " << cands[j].YY <<"\n";
                return 0;
           }
    }
    
    cout << "impossible\n";
}


