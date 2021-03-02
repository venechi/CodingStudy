#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int numArray[100];
int n;
int cache[100][11];

int minimizeSquaredError(int start, int end) {
	int avg = 0;
	for (int i = start; i <= end; ++i)
		avg += numArray[i];
	avg = round((double)avg / ((double)end - start + 1));
	
	int squaredError = 0;
	//범위를 잘 보도록 합시다( = 빼먹어서 한시간 헤맴)
	for (int i = start; i <= end; ++i) {
		squaredError += pow((double)avg - numArray[i], 2);
	}
	return squaredError;
}

int quantize(int start, int s) {
	//더 이상 검토할 것이 없으므로 0을 반환
	if (start == n) return 0;
	//검토할 것이 남았는데 쓸 수 있는 숫자가 없으므로 나올 수 없는 큰 수 반환
	if (s == 0) return 987654321;
	
	int& ret = cache[start][s];
	if (ret != -1) return ret;
	ret = 987654321;
	for (int i = start; i < n; ++i) {
		//앞에서부터 몇 번째 숫자까지를 하나의 그룹으로 해야 최적 해가 되는지 탐색
		ret = min<int>(ret, minimizeSquaredError(start, i) + quantize(i + 1, s - 1));
	}
	return ret;
}

int main(void) {
	int testcase;
	int s;
	cin >> testcase;
	for (; testcase > 0; --testcase) {
		memset(cache, -1, sizeof(int) * 100 * 11);
		cin >> n >> s;
		for (int i = 0; i < n; ++i) cin >> numArray[i];
		//주어진 숫자를 정렬하여, 하나의 숫자로 양자화될 숫자들을 모아놓는다.
		sort(numArray, numArray + n);
		cout << quantize(0, s) << endl;
	}
	return 0;
}