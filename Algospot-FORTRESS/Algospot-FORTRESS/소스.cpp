#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


typedef struct castle {
	int x;
	int y;
	int rad;
	vector<castle> node;
	castle(int x, int y, int rad) :x(x), y(y), rad(rad) {}
	castle(int x, int y, int rad, vector<castle> node) :x(x), y(y), rad(rad), node(node) {}
}castle;

typedef struct comparator {
	//성 b가 a안에 있을 경우 true 반환
	bool operator() (const castle& a, const castle& b) {
		if (pow(a.x - b.x, 2) + pow(a.y - b.y, 2) < pow(a.rad, 2))
			return true;
		else
			return false;
	}
}commparator;

comparator in;
int longest;

void buildCastle(castle& root, const castle& leaf) {
	bool isIn = false;
	for (int i = 0; i < root.node.size(); ++i) {
		if (in(root.node[i], leaf)) {
			isIn = true;
			buildCastle(root.node[i], leaf);
			break;
		}
	}
	if (!isIn)root.node.push_back(leaf);
}

int getMaxDepth(const castle& root) {
	//잎이 없으면 현재 subtree는 depth 0
	if (root.node.size() == 0) return 0;
	int depth = 0;
	int first = -1, second = 0, temp;
	for (int i = 0; i < root.node.size(); ++i) {
		//각 잎을 root로 하는 subtree의 depth를 구하고 1을 더해 현재 root와 해당 잎만을 가진 subtree의 depth를 구함.
		temp = getMaxDepth(root.node[i]) + 1;
		if (temp > second) {
			if (temp > first) {
				if (first == -1) first = temp;
				else {
					second = first;
					first = temp;
				}
			}
			else
				second = temp;
		}
		depth = max(depth, temp);
	}
	//현재 subtree에서 root를 경유하는 가장 긴 잎-잎 경로와 현재까지 찾은 가장 긴 잎-잎 경로 중 긴 것을 찾는다.
	longest = max(longest, first + second);
	//현재 subtree의 depth 반환
	return depth;
}

int main(void) {
	int testcase, n, x, y, rad;
	cin >> testcase;
	do {
		cin >> n;
		cin >> x >> y >> rad;
		castle root(x, y, rad);
		while(--n) {
			cin >> x >> y >> rad;
			buildCastle(root, castle(x, y, rad));
		}
		longest = 0;
		cout << max(longest, getMaxDepth(root)) << "\n";
	} while (--testcase);
	return 0;
}