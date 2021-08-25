#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, int>> coords = {
	{0,1},{0,-1},{-1,0},{1,0}
};

int n, k;
vector<vector<int>> map;
vector<vector<int>> pieces;//x,y,d
vector<vector<vector<int>>> stackMap;

vector<int> getStack(int i) {
	vector<int>& piece = pieces[i];
	vector<int>& stack = stackMap[piece[0]][piece[1]];
	vector<int> subStack;
	for(int j=0;j<stack.size();++j){
		if (stack[j] == i) {
			subStack.assign(stack.begin() + j, stack.end());
			stack.resize(j);
			break;
		}
	}
	return subStack;
}

int reverseD(int d) {
	switch (d) {
	case 0: return 1;
	case 1: return 0;
	case 2: return 3;
	case 3: return 2;
	}
}

bool move() {
	for (int i = 0; i < k; ++i) {
		int calX = pieces[i][0] + coords[pieces[i][2]].first, calY = pieces[i][1] + coords[pieces[i][2]].second;
		if (calX < 0 || calX >= n || calY < 0 || calY >= n || map[calX][calY] == 2) {
			pieces[i][2] = reverseD(pieces[i][2]);
			calX = pieces[i][0] + coords[pieces[i][2]].first, calY = pieces[i][1] + coords[pieces[i][2]].second;
		}
		if (!(calX < 0 || calX >= n || calY < 0 || calY >= n || map[calX][calY] == 2)) {
			vector<int> stack = getStack(i);
			//red
			if (map[calX][calY] == 1) {
				for (int j = stack.size() - 1; j >= 0; --j) {
					stackMap[calX][calY].push_back(stack[j]);
					pieces[stack[j]][0] = calX;
					pieces[stack[j]][1] = calY;
				}
			}
			//white
			else {
				for (int j = 0; j < stack.size(); ++j) {
					stackMap[calX][calY].push_back(stack[j]);
					pieces[stack[j]][0] = calX;
					pieces[stack[j]][1] = calY;
				}
			}
			if (stackMap[calX][calY].size() >= 4) return true;
		}
	}
	return false;
}

int main(void) {
	int a, b, c;
	cin >> n >> k;
	map = vector<vector<int>>(n, vector<int>(n));
	pieces = vector<vector<int>>(k);
	stackMap = vector<vector<vector<int>>>(n, vector<vector<int>>(n));
	for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) cin >> map[i][j];
	for (int i = 0; i < k; ++i) {
		cin >> a >> b >> c;
		--a; --b; --c;
		pieces[i] = { a,b,c };
		stackMap[a][b].push_back(i);
	}
	bool finished = false;
	for (int sec = 1; sec <= 1000; ++sec) {
		finished = move();
		if (finished) {
			cout << sec;
			break;
		}
	}
	if (!finished) cout << -1;
	return 0;
}