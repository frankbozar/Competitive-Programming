#include <list>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cfloat>
#include <climits>
#include <numeric>
#include <iomanip>

using namespace std;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const double PI = 2.0 * acos(0.0);


typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<string> vs;

#define sz(c) int((c).size())
#define all(c) (c).begin(), (c).end()
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FORS(i,a,b,s) for (int i = (a); i < (b); i=i+(s))
#define FORD(i,a,b) for (int i = int(b)-1; i >= (a); i--)
#define FORIT(i,c) for (__typeof__((c).begin()) i = (c).begin(); i != (c).end(); i++)


/////////////////////////////////
// BEGIN geometry library v1.4 //
/////////////////////////////////

//LATEX-BEFEHL: BEGINN FUNKTION Anfang
typedef long double coord;

struct pt{
	//LATEX-BEFEHL: ÄNDERE FARBE ZU red
	coord x,y;
	pt():x(0),y(0){};
	pt(coord _x,coord _y):x(_x),y(_y){};

	//LATEX-BEFEHL: ÄNDERE FARBE ZU darkblue
	pt operator+(const pt& p) { return pt(x+p.x,y+p.y); }
	pt operator-(const pt& p) { return pt(x-p.x,y-p.y); }
	pt operator*(const coord f) { return pt(x*f,y*f); }
	pt operator/(const coord f) { return pt(x/f,y/f); }
	//LATEX-BEFEHL: ÄNDERE FARBE ZU BASIS
    bool operator <(const pt& p) const {
            return x < p.x || (x == p.x && y < p.y);
    }
	coord operator*(const pt& p) { return x*p.x+y*p.y; }
};
double len(pt p) { return sqrt(double(p*p)); }
double phi(pt p) { return atan2((double)p.y,p.x); }
//LATEX-BEFEHL: ENDE FUNKTION

//LATEX-BEFEHL: BEGINN FUNKTION CCW
// ccw test.decides whether three points
// are arranged counterclockwise
// 1=ccw, 0=straight, -1=cw
int ccw(pt p0, pt p1, pt p2) {
	coord d1 =(p1.x-p0.x)*(p2.y-p0.y);
	coord d2 =(p2.x-p0.x)*(p1.y-p0.y);
	return (d1-d2>eps)-(d2-d1>eps);
}
//LATEX-BEFEHL: ENDE FUNKTION

//LATEX-BEFEHL: BEGINN FUNKTION Linienschnitt
// (oo,0)=same, (oo,_)=parallel, (x,y)=point
pt lineIntersect(pt a0, pt a1, pt b0, pt b1) {
	pt d13=a0-b0;
	pt d43=b1-b0;
	pt d21=a1-a0;
	coord un = d43.x*d13.y - d43.y*d13.x;
	coord ud = d43.y*d21.x - d43.x*d21.y;
	if(abs(ud)<eps) return pt(oo,un);
	return pt(a0.x + un*d21.x/ud, a0.y + un*d21.y/ud);
}
//LATEX-BEFEHL: ENDE FUNKTION

//LATEX-BEFEHL: BEGINN FUNKTION Ist Punkt in Intervall?
// 0 = no, 1= on-end-point, 2=strict
int isPointOnSegment(pt p, pt a0, pt a1) {
	if(ccw(a0,a1,p)) return 0;
	coord cx = (p.x-a0.x)*(p.x-a1.x);
	coord cy = (p.y-a0.y)*(p.y-a1.y);
	if(cx > eps || cy > eps) return 0;
	if(cx < -eps || cy < -eps) return 2;
	return 1;
}
//LATEX-BEFEHL: ENDE FUNKTION

//LATEX-BEFEHL: BEGINN FUNKTION Intervallschnitt
// line intersection test.
// decides whether two lines have a common point
// 0 = none, 1=on-end-point, 2=strict
bool isSegmentIntersect(pt a0, pt a1, pt b0, pt b1) {
	int c1=ccw(a0,a1,b0);
	int c2=ccw(a0,a1,b1);
	int c3=ccw(b0,b1,a0);
	int c4=ccw(b0,b1,a1);
	if(c1*c2>0 || c3*c4>0) return 0;
	if(!c1 && !c2 && !c3 && !c4) {
		c1=isPointOnSegment(a0,b0,b1);
		c2=isPointOnSegment(a1,b0,b1);
		c3=isPointOnSegment(b0,a0,a1);
		c4=isPointOnSegment(b1,a0,a1);
		if(c1 && c2 && c3 && c4) return 1+(a0.x!=a1.x || a0.y!=a1.y);
		return max(max(c1,c2),max(c3,c4));
	}
	return 1+(!min(c1,c2) || !min(c3,c4));
}
//LATEX-BEFEHL: ENDE FUNKTION

//LATEX-BEFEHL: BEGINN FUNKTION Konvexitätstest
// 0 = no, 1 = non-strict, 2 = strict
int isConvex(vector<pt>& poly) {
	int ret=2, c=0, n=sz(poly);
	FOR(i,0,n) {
		int cc = ccw(poly[i],poly[(i+1)%n],poly[(i+2)%n]);
		if(!cc)ret=1;
		else if(!c) c=cc;
		else if(c!=cc) return 0;
	}
	return ret;
}
//LATEX-BEFEHL: ENDE FUNKTION

//LATEX-BEFEHL: BEGINN FUNKTION Polygonfläche
// double of area of a simple polygon
// not necessarily convex
coord twoarea(vector<pt>& poly) {
	int n = sz(poly);
	coord ret = 0;
	FOR(i,0,n)
		ret += (poly[(i+1)%n].x-poly[i].x)*(poly[(i+1)%n].y+poly[i].y);
	return abs(ret);
}
//LATEX-BEFEHL: ENDE FUNKTION

//LATEX-BEFEHL: BEGINN FUNKTION Punkt-in-Polygon-Test
// test whether point is inside polygon
// 0=outside, 1=edge, 2=inside
int isInside(pt p, vector<pt>& poly) {
	int numAbove = 0;
	int numIntersects = 0;
	FOR(i,0,sz(poly)) {
		pt p0 = poly[i];
		pt p1 = poly[(i+1)%sz(poly)];
		if(isPointOnSegment(p,p0,p1)) return 1;
		if(p0.y-p.y<=eps && p1.y-p.y<=eps) continue;
		if(p0.y-p.y>eps && p1.y-p.y>eps) continue;
		pt d=p-p0;
		pt d1=p1-p0;
		if(d1.y < 0) d1.y*=-1, d.y*=-1;
		if(d.y*d1.x > d.x*d1.y) {
			if((p0.y-p.y) * (p1.y-p.y) < 0) numIntersects++;
			else  numAbove++;
		}
	}
	return (((numIntersects+(numAbove%2))%2) != 0 ? 2 : 0);
}
//LATEX-BEFEHL: ENDE FUNKTION

//LATEX-BEFEHL: BEGINN FUNKTION konvexe Hülle
// strict: duplicate points and points on edges removed
vector<pt> convexhull(vector<pt> poly) {
	int n = sz(poly), k = 0;
	vector<pt> h(2*n);
	sort(all(poly));
	FOR(i,0,n) {
		while (k > 1 && ccw(h[k-2], h[k-1], poly[i]) <= 0) k--;
		h[k++] = poly[i];
	}
	int t=k;
	FORD(i,0,n-1) {
		while (k>t && ccw(h[k-2], h[k-1], poly[i]) <= 0) k--;
		h[k++] = poly[i];
	}
	h.resize(k>1 ? k-1 : k);
	return h;
}
//LATEX-BEFEHL: ENDE FUNKTION

//LATEX-BEFEHL: BEGINN FUNKTION Polygonschnitt
// assumes intersection is convex
vector<pt> intersect(vector<pt>& p1, vector<pt>& p2) {
	vector<pt> tmp;
	FORIT(it,p1) if(isInside(*it,p2)) tmp.push_back(*it);
	FORIT(it,p2) if(isInside(*it,p1)) tmp.push_back(*it);
	FOR(i,0,sz(p1)) FOR(j,0,sz(p2)) if(isSegmentIntersect(p1[i],p1[(i+1)%sz(p1)],p2[j],p2[(j+1)%sz(p2)])) {
		pt in = lineIntersect(p1[i],p1[(i+1)%sz(p1)],p2[j],p2[(j+1)%sz(p2)]);
		if(abs(in.x-oo)>eps) tmp.push_back(in);
	}
	return convexhull(tmp); // strict
}
//LATEX-BEFEHL: ENDE FUNKTION

// returns poly ccw of a0a1
// assumes intersection is convex
vector<pt> intersect(vector<pt>& p1, pt a0, pt a1) {
	vector<pt> tmp;
	FORIT(it,p1) if(ccw(a0,a1,*it)>0) tmp.push_back(*it);
	FOR(i,0,sz(p1)) {
		pt in = lineIntersect(p1[i],p1[(i+1)%sz(p1)],a0,a1);
		if(abs(in.x-oo)<eps) continue;
		if(isPointOnSegment(in,p1[i],p1[(i+1)%sz(p1)]))
			tmp.push_back(in);
	}
	return convexhull(tmp); // strict
}

//LATEX-BEFEHL: BEGINN FUNKTION Rotiere
// rotate ccw, phi in radians
pt rotate(pt p, double phi) {
	return pt(p.x*cos(phi) - p.y*sin(phi), p.x*sin(phi) + p.y*cos(phi));
}
//LATEX-BEFEHL: ENDE FUNKTION

//LATEX-BEFEHL: BEGINN FUNKTION Polygonschwerpunk
pair<double,double> centerOfMass(vector<pt> poly) {
	int n = sz(poly);
	coord sum=0,sumx=0,sumy = 0;
	FOR(i,0,n) {
		coord tmp = (poly[(i+1)%n].y*poly[i].x)-(poly[(i+1)%n].x*poly[i].y);
		sum += tmp;
		sumx+=(poly[i].x+poly[(i+1)%n].x)*tmp;
		sumy+=(poly[i].y+poly[(i+1)%n].y)*tmp;
	}
	return pair<double,double>((sumx/3.0)/sum,(sumy/3.0)/sum);
}
//LATEX-BEFEHL: ENDE FUNKTION

//LATEX-BEFEHL: BEGINN FUNKTION LOT
// calc "Lot" of p on a0a1
pt closestpt(pt a0, pt a1, pt p) {
	pt d=a1-a0;
	return a0+(d*(d*(p-a0))/(d*d));
}

////////////////////////////
//  END geometry library  //
////////////////////////////


int main(){
	int n; cin >> n;
	vector<pt> p;
	FOR(i,0,n){
		pt x; cin >> x.x >> x.y;
		p.push_back(x);
	}

	vector<pt> tr;

	FOR(i,0,n){
		// check triangle
		pt a = p[i];
		pt b = p[(i+1)%n];
		pt c = p[(i+2)%n];
		vector<pt> tri;
		tri.push_back(a);
		tri.push_back(b);
		tri.push_back(c);

		// check any other point
		bool ok = true;
		FOR(j,3,n) if (isInside(p[(i+j)%n],tri)) ok = false;
		if (!ok) continue;
		pt nc = (c-b)/len(c-b);
		pt na = (a-b)/len(a-b);
		pt normC = (nc + na) / 2;


		// binary search the distance
		double lo = 4000;
		double hi = 30000;
		while (hi - lo > 0.0000000001){
			double mi = (hi+lo)/2;

			pt tree = b + (normC*mi);
			pt ab = closestpt(a,b,tree);
			pt bc = closestpt(b,c,tree);
			if (len(ab-tree) < 4000.0002 || len(bc-tree) < 4000.00002) lo = mi; else hi = mi;
		}

		pt tree = b + (normC*lo);
		if (!isInside(tree,p)) continue;

		tr.push_back(tree);		
	}

	// find two trees
	FORIT(a,tr) FORIT(b,tr) if (len(*a-*b) > 8000.0002){
		cout << fixed << setprecision(10) << a->x << " " << fixed << setprecision(10) << a->y << endl;
		cout << fixed << setprecision(10) << b->x << " " << fixed << setprecision(10) << b->y << endl;
		return 0;
	}
	cout << "impossible" << endl;
}

















