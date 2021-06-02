#include <iostream>
#include <vector>

using namespace std;

int map;
vector<int> cache(174763, -2);

/*
o: 2
x: 1
.: 0
*/
const vector<int> winSet = {
	//x(01) 대상, o(10)은 좌쉬프트 한번 후 이용
	86016,//첫 번째 가로줄
	1344,//두 번째 가로줄
	21,//세 번째 가로줄
	66576,//첫 번째 세로줄
	16644,//두 번째 세로줄
	4161,//세 번째 세로줄
	65793,//우하향 대각선
	4368//우상향 대각선
};

//개당 2비트씩 총 18비트

int getStone(int x, int y) {
	return ((map & (3 << ((x * 3 + y)*2))) >> ((x * 3 + y)*2));
}

void setStone(int x, int y, int stone) {
	map = (map & ~(3 << ((x * 3 + y)*2)));
	if (stone == 0) return;
	map = (map | (stone << ((x * 3 + y)*2)));
}

int checkWin() {
	for (int i = 0; i < winSet.size(); ++i) {
		if ((winSet[i] & map) == winSet[i]) return 1;
	}
	for (int i = 0; i < winSet.size(); ++i) {
		if ((((winSet[i] << 1) & map) == (winSet[i] << 1))) return 2;
	}
	return 0;
}

int calc(int turn) {
	int &ret = cache[map];
	if (ret != -2) return ret;
	int win = checkWin();
	int emptyCnt = 0;
	if (win != 0) {
		if (win == turn) return ret = 1;
		else return ret = -1;
	}
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (getStone(i, j) == 0) {
				++emptyCnt;
				setStone(i, j, turn);
				ret = max(ret, calc((turn == 1 ? 2 : 1)) * -1);
				setStone(i, j, 0);
			}
		}
	}
	if (emptyCnt == 0) ret = 0;
	return ret;
}

int main(void) {
	int tc;
	cin >> tc;
	string input;
	for (int i = 0; i < tc; ++i) {
		map = 0;
		int turn = 1;
		for (int i = 0; i < 3; ++i) {
			cin >> input;
			for (int j = 0; j < 3; ++j) {
				if (input[j] == 'x') {
					setStone(i, j, 1);
					++turn;
				}
				else if (input[j] == 'o') {
					setStone(i, j, 2);
					--turn;
				}
				else setStone(i, j, 0);
			}
		}
		int res = calc(turn);
		if (res == 0) cout << "TIE" << endl;
		else {
			if (res == 1) {
				cout << (turn == 1 ? 'x' : 'o') << endl;
			}
			else {
				cout << (turn != 1 ? 'x' : 'o') << endl;
			}
		}
	}
	return 0;
}