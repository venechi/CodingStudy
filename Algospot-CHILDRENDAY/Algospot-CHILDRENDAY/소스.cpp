#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int append(int current, int edge, int mod) {
	current = current * 10 + edge;
	if (current >= mod)
		return mod + (current % mod);
	else return current;
}

int main(void) {
	int testcase, m, n, current, next;
	string numbers;
	queue<int> Q;
	cin >> testcase;
	for (int i = 0; i < testcase; ++i) {
		cin >> numbers >> n >> m;
		//가능한 가장 작은 수를 생성하기 위해서 이용가능한 숫자를 오름차순으로 정렬한다.
		sort(numbers.begin(), numbers.end());
		//(0 ~ n-1)까지는 전체 수가 m+n 이하인 경우, (n ~ 2n-1)까지는 전체 수가 m+n 이상인 경우에 사용
		vector<int> parent(2 * n, -1), choice(2 * n, -1);
		parent[0] = 0;
		Q.push(0);
		while (!Q.empty()) {
			current = Q.front();
			Q.pop();
			for (int i = 0; i < numbers.size(); ++i) {
				//현재 노드에서 어느 간선을 택했을 때 나오는 다음 노드를 구함
				next = append(current, int(numbers[i] - '0'), n);
				//이전에 도달한 적 없는경우
				//이전에 도달한 경우는 먼저 도달한 경우가 최소값이므로 업데이트 하지 않는다.
				if (parent[next] == -1) {
					//next의 이전상태는 current;
					parent[next] = current;
					//current에서 어떤 숫자를 추가했는지 정보 기록
					//mod연산값을 이용하므로 이 정보가 없이는 원래상태로 유일하게 돌아올 수 없다.
					choice[next] = int(numbers[i] - '0');
					//목표에 도달한 경우 루프 탈출
					if (next == n + m) {
						while (!Q.empty()) Q.pop();
						break;
					}
					//추가 탐색을 위해 큐에 삽입
					else
						Q.push(next);
				}
			}
		}
		if (parent[n + m] == -1)cout << "IMPOSSIBLE\n";
		else {
			string answer = "";
			current = m + n;
			while (parent[current] != current) {
				answer += char(choice[current] + '0');
				current = parent[current];
			}
			reverse(answer.begin(), answer.end());
			cout << answer << "\n";
		}
	}
	return 0;
}