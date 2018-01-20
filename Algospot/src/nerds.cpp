/* Algospot : Nerds */

#include <iostream>
#include <vector>
#include <utility>
using namespace std;

/* Main */

int main(){

	vector< pair<int, int> > points[2], hull[2];
	
	// get inputs
	
	int n; cin >> n;
	for(int i = 0; i < n; i++){
		int a, b, c;
		cin >> a >> b >> c;
		points[a].push_back(make_pair(b, c));
	}
	
	// make hull
	
	
	
	
	
	return 0;
}

/* Functions */

/* Graham Scan */

void grahamScan(vector< pair<int, int> > points, vector< pair<int, int> > hull){


	// 1. y좌표가 가장 작은 점(P0)을 찾는다.


	// 2. P0를 기준으로 각 점들의 코사인값를 구한다.


	// 3. 코사인 값으로 내림차순 정렬한다.


	// 4. 앞에서부터 P0, P1 스택(hull)에 추가


	/*

2. 스택의 최상단에 있던 점을 P2, 그 아래에 있던 점을 P1, 다음 점을 P3이라 할 때, P3이 벡터 P1P2보다 왼쪽에 있는지 오른쪽에 있는지 체크한다. (단, 스택에 점이 1개만 있다면 건너뛰고 4번으로 간다.)

3. P3이 오른쪽에 있다면, 스택에서 P2를 제거하고 2번으로 돌아간다.

4. P3을 스택에 넣는다.

5. 모든 점을 훑었다면 반복문을 종료한다. 그렇지 않을 경우 2번으로 돌아간다.

6. 스택에 남아 있는 점들이 반시계 방향 순서로 볼록 껍질을 이룬다.
	 *
	 *
	 */

	return;
}




