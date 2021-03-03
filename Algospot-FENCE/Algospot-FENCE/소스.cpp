#include <iostream>
#include <algorithm>

using namespace std;

int board[20000];

int maxFence(int start, int end) {
	if (start == end) return board[start];
	int mid = (start + end) / 2;
	int left = mid, right = mid + 1;

	int height = min<int>(board[left], board[right]);
	int maxArea = (right - left + 1) * height;

	while (left != start || right != end) {
		if (left - 1 >= start) {
			if (right + 1 <= end) {
				//left, right�� Ȯ�� ����
				if (board[left - 1] > board[right + 1]) {
					//left�� Ȯ���ϴ°��
					height = min<int>(board[--left], height);
				}
				else {
					//right�� Ȯ���ϴ� ���
					height = min<int>(board[++right], height);
				}
			}
			else {
				//left�θ� Ȯ�尡��
				height = min<int>(board[--left], height);
			}
		}
		else {
			//right�θ� Ȯ�� ����
			height = min<int>(board[++right], height);
		}
		maxArea = max<int>((right - left + 1) * height, maxArea);
	}
	//���� ū �簢���� �߾ӿ� ���� ���� ���, ���� ���ݿ� ���� ���, ������ ���ݿ� ���� ���� ������ ã�´�
	return max<int>(maxArea, max<int>(maxFence(start, mid), maxFence(mid + 1, end)));
}

int main(void) {
	int testcase, n;
	cin >> testcase;
	for (; testcase > 0; --testcase) {
		cin >> n;
		for (int i = 0; i < n; ++i) cin >> board[i];
		cout << maxFence(0, n - 1) << endl;
	}
	return 0;
}