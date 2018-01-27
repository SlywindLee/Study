#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>

using namespace std;

// Block

vector< vector< pair<int, int> > > rotations;
int blockSize;

// Board

int boardH, boardW;
vector<string> board;

int covered[10][10];
int best, emptyCell;


// 전처리

vector<string> rotate(const vector<string>& arr) {

	vector<string> ret(arr[0].size(), string(arr.size(), ' '));

	for (int i = 0; i < arr.size(); i++)
		for (int j = 0; j < arr[0].size(); j++)
			ret[j][arr.size() - i - 1] = arr[i][j];

	return ret;
}

void generateRotations(vector<string> block) {

	rotations.clear();
	rotations.resize(4);

	for (int rot = 0; rot < 4; rot++) {

		int originY = -1, originX = -1;
		for (int i = 0; i < block.size(); i++)
			for(int j = 0; j < block[i].size(); j++)
				if (block[i][j] == '#') {

					if (originY == -1) {
						originY = i;
						originX = j;
					}

					rotations[rot].push_back(make_pair(i - originY, j - originX));
				}

		block = rotate(block);
	}

	// 중복 제거

	sort(rotations.begin(), rotations.end());
	rotations.erase(unique(rotations.begin(), rotations.end()), rotations.end());

	blockSize = rotations[0].size();

	return;
}

bool set(int y, int x, const vector< pair<int, int> >& block, int delta) {

	bool ret = true;
	int nextY, nextX;

	if (delta < 0) {
		for (int i = 0; i < blockSize; i++) {
			nextY = y + block[i].first; nextX = x + block[i].second;
			if((nextY > -1 && nextY < boardH) && (nextX > -1 && nextX < boardW))
				covered[nextY][nextX]--;
		}
	}
	else {
		for (int i = 0; i < blockSize; i++) {
			nextY = y + block[i].first; nextX = x + block[i].second;
			if ((nextY > -1 && nextY < boardH) && (nextX > -1 && nextX < boardW)) {
				if (covered[nextY][nextX] > 0) ret = false;
				covered[nextY][nextX]++;
			}
			else ret = false;
		}
	}

	return ret;
}

void search(int placed) {

	int y = -1, x = -1;

	//

	for (int i = 0; i < boardH; i++) {
		for(int j = 0; j < boardW; j++)
			if (covered[i][j] == 0) {
				y = i;
				x = j;
				break;
			}
		if (y != -1) break;
	}

	//

	if (y == -1) {
		best = (placed > best) ? placed : best;
		return;
	}

	if (placed + (emptyCell / blockSize) < best)
		return;

	//

	emptyCell -= blockSize;
	for (int i = 0; i < rotations.size(); i++) {
		if (set(y, x, rotations[i], 1))
			search(placed + 1);
		set(y, x, rotations[i], -1);
	}
	emptyCell += blockSize;

	//

	covered[y][x] = 1;
	emptyCell--;
	search(placed);
	covered[y][x] = 0;
	emptyCell++;

	return;
}

int solve() {

	best = 0;
	emptyCell = boardH * boardW;

	for (int i = 0; i < boardH; i++) {
		for (int j = 0; j < boardW; j++) {
			covered[i][j] = 0;
			if (board[i][j] == '#') {
				covered[i][j] = 1;
				emptyCell--;
			}
		}
	}

	search(0);

	return best;
}


int main() {

	int c; cin >> c;

	while (c-- > 0) {

		string str;
		vector<string> block;
		int R, C;

		cin >> boardH >> boardW >> R >> C;

		board.clear();
		for (int i = 0; i < boardH; i++) {
			cin >> str;
			board.push_back(str);
		}

		for (int i = 0; i < R; i++) {
			cin >> str;
			block.push_back(str);
		}

		// 전처리

		generateRotations(block);

		// Solve

		cout << solve() << endl;

	}

	return 0;
}
