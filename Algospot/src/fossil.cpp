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

/* Functions */







bool compare_pair(pair<double, double> a, pair<double, double> b){
	return a.first < b.first;
}

void fossil(){

	int n, m;
	vector< pair<double, double> > upper[2], lower[2];

	cin >> n >> m;

	// ù��° ���� ����

	double x, y, prevx, firstx, firsty;

	cin >> firstx >> firsty;
	prevx = firstx;

	// �ٷ� �� ������ �������� �̵� �� upper, ���������� �̵� �� lower
	// ���� (������ �� �ִ�) ���� �ϴ� upper�� ����

	for(int i = 1; i < n; i++){
		cin >> x >> y;
		if(x <= prevx) upper[0].push_back(make_pair(x, y));
		else lower[0].push_back(make_pair(x, y));
		prevx = x;
	}

	if(firstx <= prevx) upper[0].push_back(make_pair(firstx, firsty));
	else lower[0].push_back(make_pair(firstx, firsty));

	// ù��° ���� ����

	cin >> firstx >> firsty;
	prevx = firstx;

	// �ٷ� �� ������ �������� �̵� �� upper, ���������� �̵� �� lower
	// ���� (������ �� �ִ�) ���� �ϴ� upper�� ����

	for(int i = 1; i < m; i++){
		cin >> x >> y;
		if(x <= prevx) upper[1].push_back(make_pair(x, y));
		else lower[1].push_back(make_pair(x, y));
		prevx = x;
	}

	if(firstx <= prevx) upper[1].push_back(make_pair(firstx, firsty));
	else lower[1].push_back(make_pair(firstx, firsty));

	// �з� �Ϸ� -> Upper ���� ����

	sort(upper[0].begin(), upper[0].end(), compare_pair);
	sort(upper[1].begin(), upper[1].end(), compare_pair);

	// ���� �� �� �߰� �� lower ����

	lower[0].push_back(upper[0][0]);
	lower[1].push_back(upper[1][0]);

	sort(lower[0].begin(), lower[0].end(), compare_pair);
	sort(lower[1].begin(), lower[1].end(), compare_pair);

	// ������ �� �� �߰�

	upper[0].push_back(lower[0].back());
	upper[1].push_back(lower[1].back());

	// �� ������ ��ġ�� X ���� ã��
	// ������ �� ū ��, �������� �� ���� ��

	double left, right;

	left = (upper[0].front().first > upper[1].front().first) ? upper[0].front().first : upper[1].front().first;
	right = (upper[0].back().first < upper[1].back().first) ? upper[0].back().first : upper[1].back().first;



	return;
}

/* Main */

int main(){

	fossil();

	return 0;
}
