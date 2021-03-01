#include <iostream>
#include <algorithm>

using namespace std;

//LIS[길이]: 주어진 순열에서 '길이' 만큼 긴 부분순열을 구성할 때, 가능한 부분순열 중 마지막 원소의 크기가 가장 작은 순열의 마지막 원소값을 저장.
//{5, 6, 7, 1, 2}의 순열에서 가능한 길이 2짜리 부분순열은 {5, 6}, {6, 7}, {1, 2} 인데, 이 중 2를 저장함
//이유는 다음 입력으로 3 혹은 4가 들어왔을 때, {1, 2} 부분순열의 뒤에 붙일 수 있지만, 다른 부분순열엔 붙일 수 없기 때문. (최대 가능성)
int LIS[501];

//이진 탐색이 가능한 이유는, 부분순열에서 가능한 가장 작은 원소로 배열을 구성할 경우, 해당 배열도 순증가하기 때문.
int binarySearch(int end, int target) {
	int start = 0, pivot;
	//현재 검사하는 부분수열의 길이보다 하나 작은 길이의 부분수열의 가능한 가장 작은 마지막 원소보다 새로 입력받은 원소의 크기가 크고(순증가),
	//현재 검사하는 부분수열의 길이에서 가능한 가장 작은 마지막 원소보다 새로 입력받은 원소의 크기가 작을 경우(가능한 가장 작은 원소일 경우)의 위치 추출
	while (true) {
		pivot = (start + end) / 2;
		if (LIS[pivot] <= target) {
			if (LIS[pivot + 1] >= target)
				return pivot + 1;
			else
				start = pivot;
		}
		else
			end = pivot;
	}
}

int main(void) {
	int testcase;
	//계산의 편의를 위해 길이 0, 마지막 숫자 0인 가상 부분순열 산입(입력 최솟값이 1이므로 그보다 작은 0 사용)
	LIS[0] = 0;
	int n, input, tempPos, res;
	cin >> testcase;
	for (; testcase > 0; --testcase) {
		res = 1;
		cin >> n;
		for (int i = 0; i < n; ++i) {
			cin >> input;
			//입력 최대값이 100000이므로 그 이상의 값으로 초기화
			LIS[i + 1] = 100001;
			tempPos = binarySearch(i + 1, input);
			LIS[tempPos] = input;
			//최대 길이 추출(계산 끝나고 이진탐색으로 찾아도 되나, 귀찮아서 계산할때마다 그 당시의 최대부분수열 길이를 추출)
			res = max<int>(res, tempPos);
		}
		cout << res << endl;
	}
	return 0;
}