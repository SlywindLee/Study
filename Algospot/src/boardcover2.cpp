/*
 * boardcover2.cpp
 *
 *  Created on: 2018. 1. 22.
 *      Author: slywind
 */


#include <iostream>
#include <vector>
#include <stack>
#include <utility>
#define BOARDSIZE 10

using namespace std;

// global variables

int H, W, R, C;
char board[BOARDSIZE][BOARDSIZE], ablock[2][BOARDSIZE][BOARDSIZE];
vector< vector< pair<int, int> > > blocks;

void swap(int& a, int& b);
void saveBlock(size_t n);
void makePossibleBlock();

bool isAvailableLoc(int x, int y, int b);

// main

int main(){

	// get inputs

	cin >> H >> W >> R >> C;

	H--; W--; R--; C--;

	for(int i = 0; i <= H; i++)
		cin >> board[i];

	for(int i = 0; i <= R; i++)
		cin >> ablock[0][i];

	// pre-calc

	blocks.clear();

	makePossibleBlock();

	return 0;
}

// functions

void swap(int& a, int& b){
	int t = a; a = b; b = t;
}

void saveBlock(size_t n){

	vector< pair<int, int> > b;

	// convert to coordinate using base point(left-upper)

	int x = -1, y = -1;

	for(int i = 0; i <= R; i++){
		for(int j = 0; j <= C; j++)
			if(ablock[n][i][j] == '#'){
				if(x < 0){ x = i; y = j; b.push_back(make_pair(0, 0)); continue; }
				b.push_back(make_pair(i - x, j - y));
			}

	}
	// push

	blocks.push_back(b);

	return;
}

void makePossibleBlock(){

	// save

	saveBlock(0);

	// rotate & save

	for(int n = 0; n < 3; n++){

		// rotate

		for(int i = 0; i <= R; i++)
			for(int j = 0; j <= C; j++)
				ablock[(n + 1) % 2][C - j][i] = ablock[n % 2][i][j];

		swap(R, C);

		// save

		saveBlock((n + 1) % 2);
	}

	// eliminate dulplicates

	stack<int> d;

	for(int i = 1; i <= 3; i++)
		for(int j = 0; j < i; j++){

			bool same = true;

			for(size_t k = 0; k < blocks[i].size(); k++)
				if(blocks[i][k] != blocks[j][k]){ same = false; break;}

			if(same){ d.push(i); break; }
		}

	while(!d.empty()){
		blocks.erase(blocks.begin() + d.top());
		d.pop();
	}

	return;
}

//

bool isAvailableLoc(int x, int y, int b){

	// b : block num

	for(int i = 0; i < blocks[b].size(); i++)
		if(board[x + blocks[b][i].first][y + blocks[b][i].second] == '#') return false;

	return true;
}

void convertBoardStatus(int x, int y, int b, char status){

	for(int i = 0; i < blocks[b].size(); i++)
		board[x + blocks[b][i].first][y + blocks[b][i].second] = status;

	return;
}


