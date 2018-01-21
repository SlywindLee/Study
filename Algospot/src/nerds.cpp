#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include <cmath>
using namespace std;

/* def of vector */

const double PI = 2.0 * acos(0.0);

struct vector2 {

	double x, y;

	explicit vector2(double x_ = 0, double y_ = 0) : x(x_), y(y_) {};

	// comparison

	bool operator == (const vector2& rhs) const {
		return x == rhs.x && y == rhs.y;
	}

	bool operator < (const vector2& rhs) const {
		return x != rhs.x ? x < rhs.x : y < rhs.y;
	}

	// plus and minus, multiplication

	vector2 operator + (const vector2& rhs) const {
		return vector2(x + rhs.x, y + rhs.y);
	}

	vector2 operator - (const vector2& rhs) const {
		return vector2(x - rhs.x, y - rhs.y);
	}

	vector2 operator * (double rhs) const {
		return vector2(x * rhs, y * rhs);
	}

	//

	double norm() const { return hypot(x, y); }

	vector2 normalize() const {
		return vector2(x / norm(), y / norm());
	}

	double polar() const { return fmod(atan2(y, x) + 2 * PI, 2 * PI); }

	double dot(const vector2& rhs) const {
		return x * rhs.x + y * rhs.y;
	}

	double cross(const vector2& rhs) const {
		return x * rhs.y - rhs.x * y;
	}

	vector2 project(const vector2& rhs) const {
		vector2 r = rhs.normalize();
		return r * r.dot(*this);
	}

};

double ccw(vector2 a, vector2 b) {
	return a.cross(b);
}

double ccw(vector2 p, vector2 a, vector2 b) {
	return ccw(a - p, b - p);
}


/* Prototypes */

void makeConvexHull(vector<vector2>& points, vector<vector2>& hull);
bool isInside(vector2 q, const vector<vector2>& p);
bool segmentIntersects(vector2 a, vector2 b, vector2 c, vector2 d);
bool polygonIntersects(const vector<vector2>& p, const vector<vector2>& q);

/* Main */

/*
int main() {

	int c; cin >> c;

	while (c-- > 0) {
		vector<vector2> points[2];

		// Get Inputs

		int n, a;
		double b, c;

		cin >> n;

		for (int i = 0; i < n; i++) {
			cin >> a >> b >> c;
			points[a].push_back(vector2(b, c));
		}

		// Make Convex Hull

		vector<vector2> hull[2];

		makeConvexHull(points[0], hull[0]);
		makeConvexHull(points[1], hull[1]);

		if (polygonIntersects(hull[0], hull[1]))
			cout << "THEORY IS INVALID" << endl;
		else
			cout << "THEORY HOLDS" << endl;
	}

	return 0;
}

*/

/* Functions */

void makeConvexHull(vector<vector2>& points, vector<vector2>& hull) {

	// find the lowest point & add in the hull

	int lowest = 0;

	for (size_t i = 1; i < points.size(); i++)
		if (points[lowest].y > points[i].y) lowest = i;

	hull.push_back(points[lowest]);

	points.erase(points.begin() + lowest);

	// sort by angular

	vector< pair<double, vector2> > sorted;

	for (size_t i = 0; i < points.size(); i++)
		sorted.push_back( make_pair((points[i] - hull[0]).polar(), points[i]) );

	sort(sorted.begin(), sorted.end());

	// complete convex hull

	hull.push_back(sorted[0].second);
	int n = 1;

	for (size_t i = 1; i < sorted.size(); i++) {

		if (ccw(hull[n - 1], hull[n], sorted[i].second) <= 0) {
			hull.pop_back(); n--;
		}

		hull.push_back(sorted[i].second);
		n++;
	}

	return;
}

bool isInside(vector2 q, const vector<vector2>& p) {

	int crosses = 0;

	for (int i = 0; i < p.size(); i++) {

		int j = (i + 1) % p.size();

		if ((p[i].y > q.y) != (p[j].y > q.y)) {
			double atX = (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y) + p[i].x;
			if (q.x < atX) crosses++;
		}
	}

	return crosses % 2 > 0;
}

void swap(vector2& a, vector2& b) {
	vector2 t = a;
	a = b;
	b = t;
}

bool segmentIntersects(vector2 a, vector2 b, vector2 c, vector2 d) {

	double ab = ccw(a, b, c) * ccw(a, b, d);
	double cd = ccw(c, d, a) * ccw(c, d, b);

	if (ab == 0 && cd == 0) {
		if (b < a) swap(a, b);
		if (d < c) swap(c, d);
		return !(b < c || d < a);
	}

	return ab <= 0 && cd <= 0;
}


bool polygonIntersects(const vector<vector2>& p, const vector<vector2>& q) {

	int n = p.size(), m = q.size();

	if (isInside(p[0], q) || isInside(q[0], p)) return true;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (segmentIntersects(p[i], p[(i + 1) % n], q[j], q[(j + 1) % m]))
				return true;

	return false;
}
