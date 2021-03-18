#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> map;
vector<bool> visited;
vector<int> status;

enum {
	//0b001
	UNWATCHED = 1,
	//0b010
	WATCHED = 2,
	//0b100
	INSTALLED = 4
};

//dfs를 이용한다
void check(int pos) {
	visited[pos] = true;
	for (int i = 0; i < map[pos].size(); ++i) {
		int next = map[pos][i];
		//자식놈
		if (!visited[next]) {
			check(next);
			//자식이 감시되고 있지 않으면
			if (status[next] & UNWATCHED) {
				//부모에 카메라 설치
				status[pos] = (INSTALLED | WATCHED);
				//자식 감시됨
				status[next] = WATCHED;
			}
			//자식에게 카메라가 설치됐으면
			else if (status[next] & INSTALLED) {
				//부모 감시됨
				//비트 반전 연산자는 '~'이다. ('!'아님 -> bool 연산자로 true/false로 바꿔버림)
				status[pos] &= (~UNWATCHED);
				status[pos] |= WATCHED;
			}
		}
	}
}

int main(void) {
	int testcase;
	int g, h;
	int from, to;
	int count;
	cin >> testcase;
	for (int i = 0; i < testcase; ++i) {
		count = 0;
		cin >> g >> h;
		map = vector<vector<int>>(g, vector<int>());
		status = vector<int>(g, UNWATCHED);
		visited = vector<bool>(g, false);
		for (int i = 0; i < h; ++i) {
			cin >> from >> to;
			map[from].push_back(to);
			map[to].push_back(from);
		}
		//문제에 루트없는 트리라는 것이 명시되어 있으므로(한 번 지나간 갤러리를 다시 지나기 위해서는 전에 지난 복도를 반드시 지나야 함),
		//트리의 리프부터 시작하여 문제를 풀 수 있다.
		for (int i = 0; i < g; ++i) {
			if (!visited[i]) check(i);
			//컴포넌트의 구성요소가 1개인 경우 UNWATCHED로 남아있으므로 카메라를 설치한다.
			if (status[i] & (INSTALLED | UNWATCHED)) ++count;
		}
		cout << count << "\n";
	}
	return 0;
}