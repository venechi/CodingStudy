#include <iostream>
#include <vector>

using namespace std;

vector<char> cache(1 << 25, -1);

const vector<vector<pair<int, int>>> blockTypes = {
	//3개짜리
	{{0,0},{0,-1},{1,-1}},
	{{0,0},{-1,0},{-1,-1}},
	{{0,0},{0,1},{-1,1}},
	{{0,0},{1,0},{1,1}},

	{{0,0},{0,1},{1,0}},
	{{0,0},{1,0},{0,-1}},
	{{0,0},{-1,0},{0,-1}},
	{{0,0},{-1,0},{0,1}},

	{{0,0},{-1,0},{-1,1}},
	{{0,0},{0,1},{1,1}},
	{{0,0},{1,0},{1,-1}},
	{{0,0},{0,-1},{-1,-1}},

	//2개짜리
	{{-1,0},{0,0}},
	{{1,0},{0,0}},
	{{0,-1},{0,0}},
	{{0,1},{0,0}}
};

vector<int> blocks;

void setBlock(int& map, int x, int y, bool block) {
	if (block) map = (map | (1 << ((x * 5) + y)));
	else map = (map & (~(1 << ((x * 5) + y))));
}

int getBlockIfAvailable(int x, int y, const vector<pair<int, int>>& blockType) {
	int calX, calY;
	int tempMap = 0;
	for (vector<pair<int,int>>::const_iterator it = blockType.begin(); it != blockType.end(); ++it) {
		calX = x + it->first;
		calY = y + it->second;
		if (calX < 0 || calX >= 5 || calY < 0 || calY >= 5) return 0;
		setBlock(tempMap, calX, calY, true);
	}
	return tempMap;
}

void preCalc() {
	int temp;
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j) {
			for (int k = 0; k < blockTypes.size(); ++k) {
				temp = getBlockIfAvailable(i, j, blockTypes[k]);
				if (temp > 0) blocks.push_back(temp);
			}
		}
	}
}

char calc(int map) {
	char& ret = cache[map];
	if (ret != -1) return ret;
	ret = 0;
	for (int i = 0; i < blocks.size(); ++i) {
		if ((map & blocks[i]) == 0) {
			if(calc(map | blocks[i])==0)
				return ret = 1;
		}
	}
	return ret;
}

int main(void) {
	int tc;
	string input;
	preCalc();
	cin >> tc;
	for (int i = 0; i < tc; ++i) {
		int map = 0;
		for (int i = 0; i < 5; ++i) {
			cin >> input;
			for (int j = 0; j < 5; ++j)
				setBlock(map, i, j, (input[j] == '#'));
		}
		cout << (calc(map) ? "WINNING" : "LOSING") << endl;
	}
	return 0;
}