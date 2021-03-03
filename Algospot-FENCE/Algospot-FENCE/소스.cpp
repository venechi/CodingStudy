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
				//left, right로 확장 가능
				if (board[left - 1] > board[right + 1]) {
					//left로 확장하는경우
					height = min<int>(board[--left], height);
				}
				else {
					//right로 확장하는 경우
					height = min<int>(board[++right], height);
				}
			}
			else {
				//left로만 확장가능
				height = min<int>(board[--left], height);
			}
		}
		else {
			//right로만 확장 가능
			height = min<int>(board[++right], height);
		}
		maxArea = max<int>((right - left + 1) * height, maxArea);
	}
	//가장 큰 사각형이 중앙에 걸쳐 있을 경우, 왼쪽 절반에 있을 경우, 오른쪽 절반에 있을 경우로 나누어 찾는다
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