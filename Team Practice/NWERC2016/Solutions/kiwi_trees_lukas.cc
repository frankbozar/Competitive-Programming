//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

template <class T>
struct Point {
    typedef T coordType;
    typedef Point P;
    typedef const P & R;
    T x, y;
    explicit Point(T x=T(), T y=T()) : x( x), y( y) { }
    bool operator<(R p) const { return x<p.x || (x==p.x && y<p.y); }
    bool operator==(R p) const { return x==p.x && y==p.y; }
    P operator+(R p) const { return P(x+p.x, y+p.y); }
    P operator-(R p) const { return P(x-p.x, y-p.y); }
    P operator*(T d) const { return P(x*d, y*d); }
    P operator/(T d) const { return P(x/d, y/d); }
    T dot(R p) const { return x*p.x + y*p.y; }
    T cross(R p) const { return x*p.y - y*p.x; }
    T dist2() const { return x*x + y*y; } //distance^2
    double dist() const { return sqrt((double)dist2()); } //length
    P unit() const { return *this/(T)dist(); } //makes dist()=1
};
template <class T>
ostream & operator<<(ostream & os, const Point<T> & p) {
    os << "(" << p.x << "," << p.y << ")";
    return os;
}
template <class T>
istream & operator>>(istream & is, Point<T> & p) {
    is >> p.x >> p.y;
    return is;
}
template <class P>
double segDist(const P& s, const P& e, const P& p) {
        if (s==e) return (p-s).dist();
        typedef typename P::coordType T;
        T d = (e-s).dist2(), t = min(d,max(T(0),(p-s).dot(e-s)));
        return ((p-s)*d-(e-s)*t).dist()/d;
}
typedef Point<double> Poin;

const double eps = 1e-5;
const double radius = 4000 * (1 + eps);

void solve_triangle(vector<Poin> points) {
    vector<Poin> candidates;
    rep(i,0,3) {
        Poin a = points[i];
        Poin b = points[(i + 1) % 3];
        Poin c = points[(i + 2) % 3];
        Poin s = a - b;
        Poin t = c - b;
        // TODO: make this more numerically stable
        double angle = acos(s.dot(t) / s.dist() / t.dist());
        double length = 4000 / sin(angle / 2);
        Poin cand = b + (s.unit() + t.unit()).unit() * length;
        candidates.push_back(cand);
    }

    int q = -1;
    rep(i,0,3) {
        int j = (i + 1) % 3;
        if ((candidates[i] - candidates[j]).dist() >= 8000) q = i;
    }

    if (q == -1) printf("impossible\n");
    else {
        printf("%.9lf %.9lf\n", candidates[q].x, candidates[q].y);
        q = (q + 1) % 3;
        printf("%.9lf %.9lf\n", candidates[q].x, candidates[q].y);
    }
}

int main()
{
    int n; cin >> n;
    vector<Poin> points(n);
    rep(i,0,n) cin >> points[i];

    if (n == 3) {
        solve_triangle(points);
        return 0;
    }

    vector<Poin> candidates;
    rep(i,0,n) {
        Poin a = points[i];
        Poin b = points[(i + 1) % n];
        Poin c = points[(i + 2) % n];
        Poin s = a - b; s = s.unit() * 30000;
        Poin t = c - b; t = t.unit() * 30000;
        Poin u = (s + t) / 2;
        double ulen = u.dist();
        Poin cand = b + u * (ulen - 4000) / ulen; // Candidate point for a tree

        bool ok = true;
        // check if tree grows beyond the fence
        rep(j,0,n) {
            if ((points[j] - cand).dist() < radius) { ok = false; break; }
            double segment_dist = segDist(points[j], points[(j + 1) % n], cand);
            if (segment_dist < radius) { ok = false; break; }
        }
        // check if cand is inside the fence
        int inter = 0; //number of isects with line from cand to (inf,p.y)
        for (auto i = points.begin(), j = points.end()-1; i != points.end(); j = i++) {
            //increment n if segment intersects line from cand
            inter += (max(i->y,j->y) > cand.y && min(i->y,j->y) <= cand.y &&
                    ((*j-*i).cross(cand-*i) > 0) == (i->y <= cand.y));
        }
        if (!(inter&1)) ok = false;

        if (ok) {
            for (Poin& w : candidates)
                if ((w - cand).dist() >= 8000) {
                    printf("%.9lf %.9lf\n", cand.x, cand.y);
                    printf("%.9lf %.9lf\n", w.x, w.y);
                    return 0;
                }

            candidates.push_back(cand);
        }
    }

    cerr << "We should have found a point already!" << endl;
}
