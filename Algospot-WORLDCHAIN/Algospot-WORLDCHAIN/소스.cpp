#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int N_OF_ALPHABET = 'z' - 'a' + 1;

vector<string> words[N_OF_ALPHABET][N_OF_ALPHABET];
vector<vector<int>> adj(N_OF_ALPHABET, vector<int>(N_OF_ALPHABET, 0));
vector<int> startsWith(N_OF_ALPHABET, 0), endsWith(N_OF_ALPHABET, 0);
vector<string> route;

void dfs(int before, int current) {
	--adj[before][current];
	for (int i = 0; i < N_OF_ALPHABET; ++i) {
		if (adj[current][i] > 0) {
			dfs(current, i);
		}
	}
	//위상배열과 같이 경로의 마지막부터 더해진다
	//연산이 끝나면 최장길이의 루트의 역배열이 반환된다.
	route.push_back(words[before][current].back());
	words[before][current].pop_back();
}

string getPath(int NumOFWords) {
	int start = -1, end = -1;
	for (int i = 0; i < N_OF_ALPHABET; ++i) {
		//모든 노드의 인 아웃 간선 수가 같으면 오일러 서킷을 만들 수 있다.
		//그 외에는 오일러 트레일을 만들 수 있는 경우가 있다.
		if (startsWith[i] != endsWith[i]) {
			//인 간선이 아웃 간선보다 1개 많을 경우
			if (startsWith[i] - 1 == endsWith[i]) {
				//인이 아웃보다 1개 많은 노드가 2개 이상이면 오일러 트레일 구성 불가.
				if (start != -1)
					return "IMPOSSIBLE";
				start = i;
			}
			//아웃 간선이 인 간선보다 1개 많을 경우
			else if (startsWith[i] == endsWith[i] - 1) {
				//아웃이 인보다 1개 많은 노드가 2개 이상이면 오일러 트레일 구성 불가.
				if (end != -1)
					return "IMPOSSIBLE";
				end = i;
			}
			//인 간선과 아웃 간선의 수 차이가 1 이상인 경우 오일러 트레일 구성 불가.
			else
				return "IMPOSSIBLE";
		}
	}
	//모든 노드의 인 아웃 간선 수가 동일하거나, 인+1==아웃인 노드 1, 인==아웃+1인 노드 1개만 있는 경우 빼고는
	//오일러 트레일 및 서킷 구성 불가.
	if (!((start != -1 && end != -1) || (start == -1 && end == -1)))
		return "IMPOSSIBLE";
	//오일러 서킷인 경우 모든 노드에서 출발이 가능하므로,
	//간선이 하나라도 있는 첫 번째 노드를 찾아냄.
	if (start == -1) {
		for (int i = 0; i < N_OF_ALPHABET; ++i) {
			if (startsWith[i] != 0) {
				start = i;
				break;
			}
		}
	}
	//route는 전역 변수로, dfs연산이 끝나면 답이 담겨있다.
	route.clear();
	//첫 번째 노드에서 모든 루트 탐색 (dfsAll())
	for (int i = 0; i < N_OF_ALPHABET; ++i) {
		if (adj[start][i] > 0) {
			dfs(start, i);
		}
	}
	//그래프의 컴포넌트가 2개 이상인 경우, 오일러 트레일 및 서킷 구성 불가
	if (route.size() != NumOFWords) return "IMPOSSIBLE";
	string answer = "";
	//연산된 답의 역배열이 정답
	for (vector<string>::reverse_iterator it = route.rbegin(); it != route.rend(); ++it)
		answer = answer + (*it) + " ";
	return answer;
}

int main(void) {
	int testcase, n;
	string input;
	cin >> testcase;
	do {
		cin >> n;
		//초기화를 잘 하자
		for (int i = 0; i < N_OF_ALPHABET; ++i) {
			for (int j = 0; j < N_OF_ALPHABET; ++j) {
				words[i][j].clear();
				adj[i][j] = 0;
			}
			startsWith[i] = 0;
			endsWith[i] = 0;
		}
		//각 단어의 첫 글자와 마지막 글자를 노드로 하는 그래프를 생성한다.
		for (int i = 0; i < n; ++i) {
			cin >> input;
			//sample의 경우 s에서 시작하여 e로 끝나는 간선을 추가한다.
			words[input.at(0) - 'a'][input.at(input.size() - 1) - 'a'].push_back(input);
			//간선의 개수 세기
			++adj[input.at(0) - 'a'][input.at(input.size() - 1) - 'a'];
			//오일러 서킷 혹은 트레일이 있는지 계산을 편하게 하기 위해 각 노드의 인 아웃 간선 개수를 센다.
			++startsWith[input.at(0) - 'a'];
			++endsWith[input.at(input.size() - 1) - 'a'];
		}
		cout << getPath(n) << "\n";
	} while (--testcase);
	return 0;
}