#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int N_OF_ALPHABET = 'z' - 'a' + 1;

//그래프를 깊이우선탐색으로 순환하면서 더 이상 갈 곳이 없을 경우 기록
//기록된 정점리스트를 뒤집으면 위상정렬 결과가 나옴
void dfs(const vector<vector<bool>>& graph, vector<bool>& visited, vector<int>& order, int node) {
	visited[node] = true;
	for (int i = 0; i < N_OF_ALPHABET; ++i) {
		if (graph[node][i] && !visited[i]) 
			dfs(graph, visited, order, i);
	}
	order.push_back(node);
}

//DAG에 대해 위상정렬된 그래프 반환
//DAG가 아니면 "INVALID HYPOTHESIS" 반환
string topologicalSort(const vector<vector<bool>>& graph) {
	string answer = "";
	vector<bool> visited(N_OF_ALPHABET, false);
	vector<int> order;
	//그래프가 단일 컴포넌트가 아닐 경우를 대비
	for (int i = 0; i < N_OF_ALPHABET; ++i) {
		if (!visited[i]) dfs(graph, visited, order, i);
	}
	//리스트를 뒤집어 위상정렬된 그래프를 얻음
	reverse(order.begin(), order.end());
	//위상정렬된 그래프에 대해 DAG가 맞는지 검사
	for (int i = 0; i < N_OF_ALPHABET; ++i) {
		for (int j = i + 1; j < N_OF_ALPHABET; ++j) {
			//역방향 간선이 있으면 DAG가 아님.
			if (graph[order[j]][order[i]]) return "INVALID HYPOTHESIS";
		}
		answer += (char)(order[i] + 'a');
	}
	return answer;
}

string genDicOrder(const vector<string>& words) {
	vector<vector<bool>> graph(N_OF_ALPHABET, vector<bool>(N_OF_ALPHABET, false));
	int len;
	for (int i = 1; i < words.size(); ++i) {
		len = min(words[i - 1].size(), words[i].size());
		for (int j = 0; j < len; ++j) {
			if (words[i - 1][j] != words[i][j]) {
				graph[words[i - 1][j] - 'a'][words[i][j] - 'a'] = true;
				break;
			}
		}
	}
	return topologicalSort(graph);
}

int main(void) {
	int testcase, n;
	cin >> testcase;
	do {
		cin >> n;
		vector<string> words(n);
		for (int i = 0; i < n; ++i)
			cin >> words[i];
		cout << genDicOrder(words) << "\n";
	} while (--testcase);
	return 0;
}