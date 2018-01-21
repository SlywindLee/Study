/*
 * minastirith.cpp
 *
 *  Created on: 2018. 1. 21.
 *      Author: slywind
 *
 *
 */

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
using namespace std;

const double PI = 2.0 * acos(0.0);
const int INF = 987654321;

int min(int a, int b);
void convertPointToRange(vector<double>& x, vector<double>& y, vector<double>& r, vector< pair<double, double> >& ranges);
int solveLinear(double begin, double end, vector< pair<double, double> >& ranges);
int solveCircular(vector< pair<double, double> >& ranges);

/* Main */

int main(){

	int c; cin >> c;

	while(c-- > 0){

		// get points

		int n;

		cin >> n;

		vector<double> x(n, 0.0), y(n, 0.0), r(n, 0.0);

		for(int i = 0; i < n; i++)
			cin >> x[i] >> y[i] >> r[i];

		// covert points to ranges

		vector< pair<double, double> > ranges;

		convertPointToRange(x, y, r, ranges);

		// solve

		int ret = solveCircular(ranges);

		if(ret >= INF) cout << "IMPOSSIBLE" << endl;
		else cout << ret << endl;

	}

	return 0;
}

/* Functions */

int min(int a, int b){
	return (a < b) ? a : b;
}

void convertPointToRange(vector<double>& x, vector<double>& y, vector<double>& r, vector< pair<double, double> >& ranges){

	for(size_t i = 0; i < x.size(); i++){
		double loc = fmod(2 * PI + atan2(y[i], x[i]), 2 * PI);
		double range = 2.0 * asin(r[i] / 16.0);
		ranges.push_back(make_pair(loc - range, loc + range));
	}

	return;
}


int solveLinear(double begin, double end, vector< pair<double, double> >& ranges){

	int used = 0, idx = 0;

	while(begin < end) {

		double maxCover = -1;
		while(idx < ranges.size() && ranges[idx].first <= begin) {
			maxCover = (maxCover > ranges[idx].second) ? maxCover : ranges[idx].second;
			idx++;
		}

		if(maxCover <= begin) return INF;

		begin = maxCover;
		used++;
	}

	return used;
}


int solveCircular(vector< pair<double, double> >& ranges) {

	int ret = INF;

	// why?
	sort(ranges.begin(), ranges.end());

	for(size_t i = 0; i < ranges.size(); i++)
		if(ranges[i].first < 0 || ranges[i].second > 2 * PI){

			double begin = fmod(ranges[i].second, 2 * PI);
			double end = fmod(ranges[i].first + 2 * PI, 2 * PI);

			//

			ret = min(ret, solveLinear(begin, end, ranges) + 1);
		}

	return ret;
}




