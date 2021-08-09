#include <iostream>
#include <queue>
#include <vector>
#include <set>

using namespace std;

int main(void) {
	int a, b, c;
	cin >> a >> b >> c;
	queue<vector<int>> q;
	set<int> possibles;
	set<vector<int>> visited;
	vector<int> container = { 0,0,c };
	vector<int> new_c;
	int toMove;
	visited.insert(container);
	q.push(container);
	while (!q.empty()) {
		container = q.front(); q.pop();
		if(container[0] == 0) possibles.insert(container[2]);
		if (container[0] != 0) {
			//b,c
			if (container[1] != b) {
				toMove = min(container[0], b - container[1]);
				new_c = { container[0] - toMove, container[1] + toMove, container[2] };
				if (visited.find(new_c) == visited.end()) {
					q.push(new_c);
					visited.insert(new_c);
				}
			}
			if (container[2] != c) {
				toMove = min(container[0], c - container[2]);
				new_c = { container[0] - toMove, container[1], container[2] + toMove };
				if (visited.find(new_c) == visited.end()) {
					q.push(new_c);
					visited.insert(new_c);
				}
			}
		}
		if (container[1] != 0) {
			//a,c
			if (container[0] != a) {
				toMove = min(container[1], a - container[0]);
				new_c = { container[0] + toMove, container[1] - toMove, container[2] };
				if (visited.find(new_c) == visited.end()) {
					q.push(new_c);
					visited.insert(new_c);
				}
			}
			if (container[2] != c) {
				toMove = min(container[1], c - container[2]);
				new_c = { container[0], container[1] - toMove, container[2] + toMove };
				if (visited.find(new_c) == visited.end()) {
					q.push(new_c);
					visited.insert(new_c);
				}
			}
		}
		if (container[2] != 0) {
			//a,b
			if (container[0] != a) {
				toMove = min(container[2], a - container[0]);
				new_c = { container[0] + toMove, container[1], container[2] - toMove };
				if (visited.find(new_c) == visited.end()) {
					q.push(new_c);
					visited.insert(new_c);
				}
			}
			if (container[1] != b) {
				toMove = min(container[2], b - container[1]);
				new_c = { container[0], container[1] + toMove, container[2] - toMove };
				if (visited.find(new_c) == visited.end()) {
					q.push(new_c);
					visited.insert(new_c);
				}
			}
		}
	}
	for (auto it = possibles.begin(); it != possibles.end(); ++it) cout << *it << " ";
	return 0;
}