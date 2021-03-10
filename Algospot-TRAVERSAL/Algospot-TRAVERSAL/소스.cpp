#include <iostream>
#include <vector>

using namespace std;

vector<int> pre(100), in(100);

vector<int> getPostOrder(int preS, int preE, int inS, int inE) {
	vector<int> result;
	if (preS > preE) return result;
	if (preS != preE) {
		vector<int> temp;
		int pos;
		for (int i = inS; i <= inE; ++i) {
			if (in[i] == pre[preS]) {
				pos = i;
				break;
			}
		}
		//left
		temp = getPostOrder(preS + 1, preS + (pos - inS), inS, pos - 1);
		for (int i = 0; i < temp.size(); ++i)
			result.push_back(temp[i]);
		//right
		temp = getPostOrder(preS + 1 + (pos - inS), preE, pos + 1, inE);
		for (int i = 0; i < temp.size(); ++i)
			result.push_back(temp[i]);
	}
	//root
	result.push_back(pre[preS]);
	return result;
}

int main(void) {
	int testcase, n;
	cin >> testcase;
	do {
		cin >> n;
		for (int i = 0; i < n; ++i)
			cin >> pre[i];
		for (int i = 0; i < n; ++i)
			cin >> in[i];
		vector<int> post = getPostOrder(0, n - 1, 0, n - 1);
		for (int i = 0; i < n; ++i)
			cout << post[i] << " ";
		cout << "\n";
	} while (--testcase);
	return 0;
}