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
	//����迭�� ���� ����� ���������� ��������
	//������ ������ ��������� ��Ʈ�� ���迭�� ��ȯ�ȴ�.
	route.push_back(words[before][current].back());
	words[before][current].pop_back();
}

string getPath(int NumOFWords) {
	int start = -1, end = -1;
	for (int i = 0; i < N_OF_ALPHABET; ++i) {
		//��� ����� �� �ƿ� ���� ���� ������ ���Ϸ� ��Ŷ�� ���� �� �ִ�.
		//�� �ܿ��� ���Ϸ� Ʈ������ ���� �� �ִ� ��찡 �ִ�.
		if (startsWith[i] != endsWith[i]) {
			//�� ������ �ƿ� �������� 1�� ���� ���
			if (startsWith[i] - 1 == endsWith[i]) {
				//���� �ƿ����� 1�� ���� ��尡 2�� �̻��̸� ���Ϸ� Ʈ���� ���� �Ұ�.
				if (start != -1)
					return "IMPOSSIBLE";
				start = i;
			}
			//�ƿ� ������ �� �������� 1�� ���� ���
			else if (startsWith[i] == endsWith[i] - 1) {
				//�ƿ��� �κ��� 1�� ���� ��尡 2�� �̻��̸� ���Ϸ� Ʈ���� ���� �Ұ�.
				if (end != -1)
					return "IMPOSSIBLE";
				end = i;
			}
			//�� ������ �ƿ� ������ �� ���̰� 1 �̻��� ��� ���Ϸ� Ʈ���� ���� �Ұ�.
			else
				return "IMPOSSIBLE";
		}
	}
	//��� ����� �� �ƿ� ���� ���� �����ϰų�, ��+1==�ƿ��� ��� 1, ��==�ƿ�+1�� ��� 1���� �ִ� ��� �����
	//���Ϸ� Ʈ���� �� ��Ŷ ���� �Ұ�.
	if (!((start != -1 && end != -1) || (start == -1 && end == -1)))
		return "IMPOSSIBLE";
	//���Ϸ� ��Ŷ�� ��� ��� ��忡�� ����� �����ϹǷ�,
	//������ �ϳ��� �ִ� ù ��° ��带 ã�Ƴ�.
	if (start == -1) {
		for (int i = 0; i < N_OF_ALPHABET; ++i) {
			if (startsWith[i] != 0) {
				start = i;
				break;
			}
		}
	}
	//route�� ���� ������, dfs������ ������ ���� ����ִ�.
	route.clear();
	//ù ��° ��忡�� ��� ��Ʈ Ž�� (dfsAll())
	for (int i = 0; i < N_OF_ALPHABET; ++i) {
		if (adj[start][i] > 0) {
			dfs(start, i);
		}
	}
	//�׷����� ������Ʈ�� 2�� �̻��� ���, ���Ϸ� Ʈ���� �� ��Ŷ ���� �Ұ�
	if (route.size() != NumOFWords) return "IMPOSSIBLE";
	string answer = "";
	//����� ���� ���迭�� ����
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
		//�ʱ�ȭ�� �� ����
		for (int i = 0; i < N_OF_ALPHABET; ++i) {
			for (int j = 0; j < N_OF_ALPHABET; ++j) {
				words[i][j].clear();
				adj[i][j] = 0;
			}
			startsWith[i] = 0;
			endsWith[i] = 0;
		}
		//�� �ܾ��� ù ���ڿ� ������ ���ڸ� ���� �ϴ� �׷����� �����Ѵ�.
		for (int i = 0; i < n; ++i) {
			cin >> input;
			//sample�� ��� s���� �����Ͽ� e�� ������ ������ �߰��Ѵ�.
			words[input.at(0) - 'a'][input.at(input.size() - 1) - 'a'].push_back(input);
			//������ ���� ����
			++adj[input.at(0) - 'a'][input.at(input.size() - 1) - 'a'];
			//���Ϸ� ��Ŷ Ȥ�� Ʈ������ �ִ��� ����� ���ϰ� �ϱ� ���� �� ����� �� �ƿ� ���� ������ ����.
			++startsWith[input.at(0) - 'a'];
			++endsWith[input.at(input.size() - 1) - 'a'];
		}
		cout << getPath(n) << "\n";
	} while (--testcase);
	return 0;
}