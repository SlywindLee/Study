/*
 * fossil.cpp
 *
 *  Created on: 2017. 12. 21.
 *      Author: slywind_lee
 */

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

/* Global Variables */

int n, m;
vector< pair<double, double> > upper[2], lower[2];

/* Functions */

double max(double a, double b){
	return (a > b) ? a : b;
}

double min(double a, double b){
	return (a < b) ? a : b;
}

bool compare_pair(pair<double, double> a, pair<double, double> b){
	return a.first < b.first;
}


double getheight(vector< pair<double, double> > lines, double x){

	// 껍질에서 해당 X좌표에 해당하는 Y좌표를 찾는다.
	// 바이너리 서치로 구현하면 더 빨라질 것.

	for(size_t i = 1; i < lines.size(); i++)
		if(lines[i].first > x){
			double a = lines[i - 1].first, b = lines[i - 1].second, c = lines[i].first, d = lines[i].second;
			return ((d - b) / (c - a)) * (x - a) + b;
		}

	return 0.0;
}

double vertical(double x){

	// upper 중엔 작은것, lower 중엔 큰것

	double u0 = getheight(upper[0], x), u1 = getheight(upper[1], x);
	double l0 = getheight(lower[0], x), l1 = getheight(lower[1], x);


	return min(u0, u1) - max(l0, l1);
}


// fossil

double fossil(){

	// 전역변수 초기화

	upper[0].clear(); upper[1].clear();
	lower[0].clear(); lower[1].clear();

	// 인풋

	cin >> n >> m;

	// 첫번째 점은 저장

	double x, y, prevx, firstx, firsty;

	cin >> firstx >> firsty;
	prevx = firstx;

	// 바로 전 점보다 왼쪽으로 이동 시 upper, 오른쪽으로 이동 시 lower
	// 같은 (수직선 상에 있는) 경우는 일단 upper로 설정

	for(int i = 1; i < n; i++){
		cin >> x >> y;
		if(x <= prevx) upper[0].push_back(make_pair(x, y));
		else lower[0].push_back(make_pair(x, y));
		prevx = x;
	}

	if(firstx <= prevx) upper[0].push_back(make_pair(firstx, firsty));
	else lower[0].push_back(make_pair(firstx, firsty));

	// 첫번째 점은 저장

	cin >> firstx >> firsty;
	prevx = firstx;

	// 바로 전 점보다 왼쪽으로 이동 시 upper, 오른쪽으로 이동 시 lower
	// 같은 (수직선 상에 있는) 경우는 일단 upper로 설정

	for(int i = 1; i < m; i++){
		cin >> x >> y;
		if(x <= prevx) upper[1].push_back(make_pair(x, y));
		else lower[1].push_back(make_pair(x, y));
		prevx = x;
	}

	if(firstx <= prevx) upper[1].push_back(make_pair(firstx, firsty));
	else lower[1].push_back(make_pair(firstx, firsty));

	// 분류 완료 -> Upper 부터 정렬

	sort(upper[0].begin(), upper[0].end(), compare_pair);
	sort(upper[1].begin(), upper[1].end(), compare_pair);

	// 왼쪽 끝 점 추가 후 lower 정렬

	lower[0].push_back(upper[0][0]);
	lower[1].push_back(upper[1][0]);

	sort(lower[0].begin(), lower[0].end(), compare_pair);
	sort(lower[1].begin(), lower[1].end(), compare_pair);

	// 오른쪽 끝 점 추가

	upper[0].push_back(lower[0].back());
	upper[1].push_back(lower[1].back());

	// 두 도형의 겹치는 X 범위 찾기
	// 왼쪽은 더 큰 점, 오른쪽은 더 작은 점

	double left, right;

	left = (upper[0].front().first > upper[1].front().first) ? upper[0].front().first : upper[1].front().first;
	right = (upper[0].back().first < upper[1].back().first) ? upper[0].back().first : upper[1].back().first;

	if(right < left) return -1;

	// 삼분검색


	for(int i = 0; i < 100; i++){

		double aab = (left * 2.0 + right) / 3.0;
		double abb = (left + right * 2.0) / 3.0;

		if(vertical(aab) < vertical(abb))
			left = aab;
		else
			right = abb;
	}

	return max(0.0, vertical(right));
}

/* Main */

/*
int main(){

	cout.precision(10);
	int c; cin >> c;

	while(c-- > 0){
		cout << fossil() << endl;
	}

	return 0;
}

*/
