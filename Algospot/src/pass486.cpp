/*
 * pass486.cpp
 *
 *  Created on: 2017. 12. 30.
 *      Author: slywind
 */

#include <iostream>
#include <vector>
#define MAX 10000001
using namespace std;

void calcNFactor(vector<int>& minFactor, vector<int>& nMinFactor, vector<int>& nFactor){

	nFactor[1] = 1;

	for(int i = 2; i < MAX; i++){

		// 소수면 소인수의 개수는 2 (2로 생성시 초기화)

		if(minFactor[i] == i) continue;

		// 아니라면 minFactor로 나눈 결과를 이용하여 계산한다.

		nFactor[i] = (nFactor[i / minFactor[i]] / nMinFactor[i]) * (nMinFactor[i] + 1) ;

	}

	return;
}

void calcMinFactor(vector<int>& minFactor, vector<int>& nMinFactor){

	/* 1과 2는 따로 처리 */

	minFactor[1] = 1;
	nMinFactor[1] = 1;

	/* 소수가 아닌 경우는 넘어감, 소수인 경우는 배수에 대해서 처리 */

	for(int i = 2; i < MAX; i++){

		if(minFactor[i] != 0)
			continue;

		// 소수인 경우

		minFactor[i] = i;

		// 아직 업데이트가 안됐다는 사실은 i가 min factor라는 뜻

		for(int j = i * i; j > 0 && j < MAX; j += i){

			if(minFactor[j] != 0) continue;

			minFactor[j] = i;

			if(minFactor[j / i] == minFactor[j])
				nMinFactor[j] = nMinFactor[j / i] + 1;

		}

	}

	return;
}

/*
 * 1. 에라토스테네스 체를 응용하여 모든 수에 대한 가장 작은 소인수를 계산해 둔다. (minFactor)
 * 2. 그 소인수가 몇 개 곱해져 있는지도 같이 계산한다. (nMinFactor)
 * 3. 소인수분해를 사용하여 각 수의 인수 개수를 구한다. (nFactor)
 */

int main(){


	vector<int> minFactor(MAX, 0);
	vector<int> nMinFactor(MAX, 1);
	vector<int> nFactor(MAX, 2);

	// 전처리

	calcMinFactor(minFactor, nMinFactor);
	calcNFactor(minFactor, nMinFactor, nFactor);

	cout << nFactor[18] << endl;

	// 문제 처리

	int c, n, low, high, cnt;
	cin >> c;

	while(c-- > 0){

		cin >> n >> low >> high;
		cnt = 0;

		for(int i = low; i <= high; i++)
			if(nFactor[i] == n) cnt++;

		cout << cnt << endl;
	}

	return 0;
}
