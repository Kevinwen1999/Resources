#include <bits/stdc++.h>
#define EPS 1e-9
using namespace std;
// POINTS, LINES, VECTORS, DOT/CROSS PRODUCT
const double PI = acos(-1.0);
struct point
{
    double x, y;
    point() {x = y = 0.0;}
    point(double a, double b) {x = a; y = b;}
    bool operator == (point other) const
    {
        return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS));
    }
}p1, p2, p3;
double dist(point a, point b)
{
    return hypot(a.x-b.x, a.y-b.y);
}
struct line { double a, b, c;};
void point_to_line(point a, point b, line &l)
{
    if (fabs(a.x-b.x) < EPS)
    {
        l.a = 1.0; l.b = 0.0; l.c = -a.x;
    }
    else
    {
        l.a = -(double) (a.y-b.y) / (a.x-b.x);
        l.b = 1.0;
        l.c = -(double) (l.a * a.x) - a.y;
    }
}
struct vec {double x, y; vec(double a, double b) {x = a; y = b;}};
vec tovec(point a, point b){return vec(b.x - a.x, b.y-a.y);}
vec scale (vec v, double s) {return vec(v.x*s, v.y*s);}
point translate (point p, vec v) { return point(p.x + v.x, p.y + v.y);}
double magnitude (vec v) {return sqrt(v.x*v.x + v.y*v.y);}
double dot(vec a, vec b) {return (a.x*b.x + a.y*b.y);}
double norm_sq(vec v) {return v.x*v.x + v.y*v.y;}
double dist_to_line(point p, point a, point b, point &c)
{
    // c = a + u * ab
    // projection : dot(ap,ab) / sq(ab)
    vec ap = tovec(a,p), ab = tovec(a,b);
    double u = dot(ap,ab) / norm_sq(ab);
    c = translate(a, scale(ab, u));
    return dist(p,c);
}
double dist_to_lineseg(point p, point a, point b, point &c)
{
    vec ap = tovec(a,p), ab = tovec(a,b);
    double u = dot(ap,ab) / norm_sq(ab);
    if (u < 0.0)
    {
        c = point(a.x, a.y); return dist(p,a);
    }
    if (u > 1.0)
    {
        c = point(b.x, b.y); return dist(p,b);
    }
    return dist_to_line(p,a,b,c);
}
double angle(point a, point o, point b) //return angle AOB in rad, times 180.0/pi to get degree
{
    vec oa = tovec(o,a); vec ob = tovec(o,b);
    return acos(dot(oa, ob)/ sqrt(norm_sq(oa)*norm_sq(ob)));
}
double cross(vec a, vec b) {return a.x*b.y - a.y*b.x;}
double CCW (point p, point q, point r) {return cross(tovec(p,q), tovec(p,r)) > 0;} //return true if point R is on left side of line PQ
bool collinear (point p, point q, point r) {return fabs(cross(tovec(p,q), tovec(p,r)) ) < EPS;}
// POLYGONS
double perimeter (const vector<point> &P)
{
    double result = 0.0;
    for (int i = 0; i < (int)P.size()-1; i++)
        result+=dist(P[i], P[i+1]);
    return result;

}
double area (const vector<point> &P)
{
    double result = 0.0, x1, x2, y1, y2;
    for (int i = 0; i < (int)P.size()-1; i++)
    {
        x1 = P[i].x; x2 = P[i+1].x;
        y1 = P[i].y; y2 = P[i+1].y;
        result +=(x1*y2 - x2*y1);
    }
    return fabs(result) / 2.0;
}
bool isConvex (const vector<point> &P)
{
    int sz = (int)P.size();
    if (sz <= 3) return false;
    bool isLeft = CCW(P[0], P[1], P[2]);
    for (int i = 1; i < sz-1; i++)
    {
        if (CCW(P[i], P[i+1], P[(i+2) == sz ? 1 : i+2]) != isLeft)
            return false;
        return true;
    }
}
bool inPolygon (point pt, const vector<point> &P)
{
    if ((int)P.size() == 0) return false;
    double sum = 0;
    for (int i = 0; i < (int)P.size()-1; i++)
    {
        if (CCW(pt, P[i], P[i+1]))
            sum += angle(P[i], pt, P[i+1]);
        else
            sum -= angle(P[i], pt, P[i+1]);
    }
    return fabs(fabs(sum) - 2*PI) < EPS;
}
point pivot(0,0);
bool angleCmp(point a, point b)
{
    if (collinear(pivot, a, b))
    {
        return dist(pivot, a) < dist(pivot, b);
    }
    double d1x = a.x - pivot.x, d1y = a.y - pivot.y;
    double d2x = b.x - pivot.x, d2y = b.y - pivot.y;
    return (atan2(d1y, d1x) - atan2(d2y, d2x) < 0);
}
vector <point> CH(vector <point> &P)
{
    int i, j, n = (int)P.size();
    if (n <= 3)
    {
        if (!(P[0] == P[n-1])) P.push_back(P[0]);
        return P;
    }
    int P0 = 0;
    for (int i = 1; i < n; i++)
    {
        if (P[i].y < P[P0].y || (P[i].y == P[P0].y && P[i].x > P[P0].x))
            P0 = i;
    }
    point temp = P[0]; P[0] = P[P0]; P[P0] = temp;
    pivot = P[0];
    sort(++P.begin(), P.end(), angleCmp);
    //ccw test
    vector <point> S;
    S.push_back(P[n-1]); S.push_back(P[0]); S.push_back(P[1]);
    i = 2;
    while (i < n)
    {
        j = (int)S.size()-1;
        if (CCW(S[j-1], S[j], P[i]))
            S.push_back(P[i++]);
        else
            S.pop_back();
    }
    return S;
}
bool cmp(point a, point b) 
{
    if(a.x != b.x)
        return a.x < b.x;
    return a.y < b.y;
}
vector <point> monotone_chain(vector <point> P)
{
    vector <point> CH;
    sort(P.begin(), P.end(), cmp);
    int m= 0, t, n = (int)P.size();
    for (int i = 0; i < n; i++)
    {
        while(m >= 2 && CCW(CH[m-2], CH[m-1], P[i]) <= 0)
            CH.pop_back(), m--;
        CH.push_back(P[i]), m++;
    }
    for (int i = n-1, t = m + 1; i > 0; i--)
    {
        while (m > t && CCW(CH[m-2], CH[m-1], P[i]) <= 0)
            CH.pop_back(), m--;
        CH.push_back(P[i]), m++;
    }
    return CH;
}
int main()
{

}

