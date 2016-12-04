//Solution by lukasP (Lukáš Poláček)
//Time complexity: O(n)
#include <iostream>
#include <set>
#include <vector>
#include <cassert>
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
    Point(const P& a) : x(a.x), y(a.y) { }
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

typedef Point<double> Poin;
vector<Poin> points;
const double eps = 1e-9;

int next(int i, int size) { return (i + 1) % size; }

bool insideTriangle(Poin x, vector<Poin>& t) {
    double area = abs((t[1] - t[0]).cross(t[2] - t[0]));
    double area_from_x = 0;
    rep(i,0,3)
        area_from_x += abs((t[next(i, 3)] - x).cross(t[i] - x));
    return abs(area - area_from_x) / area < eps;
}

template <class P>
int lineIntersection(const P& s1, const P& e1, const P& s2,
        const P& e2, P& r) {
    if ((e1-s1).cross(e2-s2)) { //if not parallell
        r = s2-(e2-s2)*(e1-s1).cross(s2-s1)/(e1-s1).cross(e2-s2);
        return 1;
    } else return -((e1-s1).cross(s2-s1)==0 || s2==e2);
}

pair<int, int> sort_pair(int a, int b) {
    if (a < b) return make_pair(a, b);
    return make_pair(b, a);
}

pair<int, int> find_diagonal(vector<int>& p) {
    int head = p.size() / 2;
    set<int> tri;
    tri.insert(head); tri.insert(next(head, p.size()));
    tri.insert(int(head + p.size() - 1) % (int)p.size());
    Poin a = points[p[int(head + p.size() - 1) % (int)p.size()]];
    Poin b = points[p[head]];
    Poin c = points[p[next(head, p.size())]];

    bool orientation = (a - b).cross(c - b) > 0;

    vector<int> candidates;
    if (orientation) { // angle less than 180 degrees, easy case
        vector<Poin> triangle = {a, b, c};
        rep(x,0,(int)p.size()) if (tri.count(x) == 0 && insideTriangle(points[p[x]], triangle))
            candidates.push_back(x);
        tri.erase(head);
        if (candidates.empty()) return make_pair(*tri.begin(), *(++tri.begin()));
    } else { // angle more than 180 degrees, we need to find an edge on the opposite side of b
        Poin dir = (b - a) + (b - c);
        vector<Poin> triangle = {b};
        tri = {head};

        int q = -1;
        double best_distance = 1e10;
        rep(i,0,p.size()) {
            int j = next(i, p.size());
            if ((int)i == head || j == head) continue;
            Poin& x = points[p[i]];
            Poin& y = points[p[j]];
            if (dir.cross(x - b) * dir.cross(y - b) <= 0) {
                // x -- y intersects with b --> dir

                // cout << p[i] << " " << p[j] << " / " << x << " - " << y
                // << " intersects with direction " << dir << " from " << b << endl;
                double end_distance = max((x - b).dist(), (y - b).dist());

                // calculate the distance of the intersection of p[i] -- p[j] with b --> dir
                Poin intersection;
                lineIntersection(b, b + dir.unit() * (end_distance + 47), x, y, intersection);
                double distance = (intersection - b).dist();
                if (distance < best_distance) {
                    best_distance = distance;
                    q = i;
                }
            }
        }
        assert(q >= 0);

        int r = next(q, p.size());
        tri.insert(q); tri.insert(r);
        triangle.push_back(points[p[q]]);
        triangle.push_back(points[p[r]]);

        set<int> neighbors = {next(head, p.size()), (head + (int)p.size() - 1) % (int)p.size()};
        rep(x,0,(int)p.size()) if (tri.count(x) == 0 && insideTriangle(points[p[x]], triangle)
                && neighbors.count(x) == 0)
            candidates.push_back(x);
        tri.erase(head);
        for (int x : tri) if (neighbors.count(x)) tri.erase(x);
        if (candidates.empty()) return sort_pair(head, *tri.begin());
    }

    int x = *tri.begin(), y = *(++tri.begin());
    Poin X = points[p[x]], Y = points[p[y]];
    Poin dir2 = Y - X;
    Poin perpen(-dir2.y, dir2.x);
    double value = perpen.dot(X), best = 0;
    int res = -1;
    // 'candidates' contains all points strictly inside 'triangle'
    // Now we select the point farthest away from the line passing through X and Y
    for (int z : candidates)
        if (abs(perpen.dot(points[p[z]]) - value) > best) {
            best = abs(perpen.dot(points[p[z]]) - value);
            res = z;
        }
    return sort_pair(head, res);
}

void plant_tree_into_part(vector<int> p) {
    while (p.size() > 3) {
        // p always contains points of a cut with an ear
        auto cut = find_diagonal(p);
        assert(cut.first < cut.second);
        // cout << "cut at: " << p[cut.first] << " " << p[cut.second] << endl;
        vector<int> part;
        for (int i = cut.first; i <= cut.second; i++) part.push_back(p[i]);
        p = part;
    }

    assert(p.size() == 3);

    Poin a = points[p[0]];
    Poin b = points[p[1]];
    Poin c = points[p[2]];
    Poin s = a - b; s = s.unit() * 30000;
    Poin t = c - b; t = t.unit() * 30000;
    Poin u = (s + t) / 2;
    double ulen = u.dist();
    Poin tree = b + u * (ulen - 4000) / ulen;
    printf("%.9lf %.9lf\n", tree.x, tree.y);
}

void solve_triangle() {
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

int main() {
    int n; cin >> n;
    points.resize(n);
    rep(i,0,n) cin >> points[i];

    if (n == 3) {
        solve_triangle();
        return 0;
    }

    vector<int> p;
    rep(i,0,n) p.push_back(i);

    auto cut = find_diagonal(p);
    // cout << "cut at: " << p[cut.first] << " " << p[cut.second] << endl;
    vector<int> part[2];
    for (int i = cut.first; i <= cut.second; i++) part[0].push_back(p[i]);
    for (int i = cut.second; i <= cut.first + n; i++) part[1].push_back(p[i % n]);

    plant_tree_into_part(part[0]);
    plant_tree_into_part(part[1]);
}
