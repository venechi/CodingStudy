#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int N_OF_ALPHABET = 'z' - 'a' + 1;

//�׷����� ���̿켱Ž������ ��ȯ�ϸ鼭 �� �̻� �� ���� ���� ��� ���
//��ϵ� ��������Ʈ�� �������� �������� ����� ����
void dfs(const vector<vector<bool>>& graph, vector<bool>& visited, vector<int>& order, int node) {
	visited[node] = true;
	for (int i = 0; i < N_OF_ALPHABET; ++i) {
		if (graph[node][i] && !visited[i]) 
			dfs(graph, visited, order, i);
	}
	order.push_back(node);
}

//DAG�� ���� �������ĵ� �׷��� ��ȯ
//DAG�� �ƴϸ� "INVALID HYPOTHESIS" ��ȯ
string topologicalSort(const vector<vector<bool>>& graph) {
	string answer = "";
	vector<bool> visited(N_OF_ALPHABET, false);
	vector<int> order;
	//�׷����� ���� ������Ʈ�� �ƴ� ��츦 ���
	for (int i = 0; i < N_OF_ALPHABET; ++i) {
		if (!visited[i]) dfs(graph, visited, order, i);
	}
	//����Ʈ�� ������ �������ĵ� �׷����� ����
	reverse(order.begin(), order.end());
	//�������ĵ� �׷����� ���� DAG�� �´��� �˻�
	for (int i = 0; i < N_OF_ALPHABET; ++i) {
		for (int j = i + 1; j < N_OF_ALPHABET; ++j) {
			//������ ������ ������ DAG�� �ƴ�.
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