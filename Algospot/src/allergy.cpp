/*
 * allergy.cpp
 *
 *  Created on: 2018. 1. 27.
 *      Author: slywind_lee
 */

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
using namespace std;

//

int n, m;
bool info[50][50]; // [친구][음식]
vector< vector<int> > newinfo;
int eat[50]; // [친구]
bool cook[50]; // [음식]
int freq[50]; // [음식]

int best;

// make faster
vector< pair<int, int> > order;

int comp(pair<int, int> &a, pair<int, int> &b){
	return (a.first > b.first);
}

//

void solve(int cooked){

	if(cooked >= best)
		return;

	// 아직 먹을 수 있는 음식이 없는 친구를 찾는다.

	int target = -1;

	for(int i = 0; i < n; i++)
		if(eat[i] == 0){
			target = i;
			break;
		}

	if(target < 0){
		best = (best < cooked) ? best : cooked;
		return;
	}

	// 그 친구에게 먹을 걸 줄 수 있는 음식을 고른다.

	for(int i = 0; i < m; i++){

		int food = order[i].second;

		if(!cook[food] && info[target][food]){

			cook[food] = true;
			//for(int j = 0; j < n; j++)
			//	if(info[j][food]) eat[j]++;

			for(size_t j = 0; j < newinfo[food].size(); j++)
				eat[newinfo[food][j]]++;

			solve(cooked + 1);

			cook[food] = false;
			//for(int j = 0; j < n; j++)
			//	if(info[j][food]) eat[j]--;

			for(size_t j = 0; j < newinfo[food].size(); j++)
				eat[newinfo[food][j]]--;

		}
	}

	return;
}

//

int main(){

	int c; cin >> c;

	while(c-- > 0){
		cin >> n >> m;

		// 친구 정보

		map<string, int> names;
		string str;

		for(int i = 0; i < n; i++){
			cin >> str;
			names.insert(make_pair(str, i));
		}

		// 음식 정보

		newinfo.clear();
		newinfo.resize(m);

		for(int i = 0; i < 50; i++)
			for(int j = 0; j < 50; j++)
				info[i][j] = false;

		order.clear();

		for(int i = 0; i < m; i++){

			cin >> freq[i];

			for(int j = 0; j < freq[i]; j++){
				cin >> str;
				info[names[str]][i] = true;
				newinfo[i].push_back(names[str]);
			}
		}

		for(int i = 0; i < m; i++)
			order.push_back(make_pair(freq[i] , i));

		sort(order.begin(), order.end(), comp);

		// 초기화

		best = m + 1;

		for(int i = 0; i < 50; i++){
			eat[i] = 0;
			cook[i] = false;
		}

		// solve

		solve(0);

		cout << best << endl;
	}

	return 0;
}
