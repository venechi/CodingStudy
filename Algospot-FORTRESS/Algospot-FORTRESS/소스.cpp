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
	//�� b�� a�ȿ� ���� ��� true ��ȯ
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
	//���� ������ ���� subtree�� depth 0
	if (root.node.size() == 0) return 0;
	int depth = 0;
	int first = -1, second = 0, temp;
	for (int i = 0; i < root.node.size(); ++i) {
		//�� ���� root�� �ϴ� subtree�� depth�� ���ϰ� 1�� ���� ���� root�� �ش� �ٸ��� ���� subtree�� depth�� ����.
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
	//���� subtree���� root�� �����ϴ� ���� �� ��-�� ��ο� ������� ã�� ���� �� ��-�� ��� �� �� ���� ã�´�.
	longest = max(longest, first + second);
	//���� subtree�� depth ��ȯ
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