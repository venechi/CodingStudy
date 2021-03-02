#include <iostream>
#include <cstring>
#include <algorithm>
#include <climits>

using namespace std;

//메모이제이션 배열
int JLIS[101][101];
//입력배열
int aList[101], bList[101];
//입력 원소 개수
int n, m;

int getJLIS(int a, int b, long long int lastValue) {
	if (JLIS[a][b] != -1) return JLIS[a][b];
	//적어도 현재 원소 하나짜리 배열은 항상 가능하므로 ret = 1로 시작.
	int ret = 1;
	//이전에 결정된 마지막 원소보다 큰 값을 포함한 subList들을 대상으로 재귀호출
	for (int i = a + 1; i <= n; ++i) {
		if (aList[i] > lastValue)
			ret = max<int>(ret, getJLIS(i, b, aList[i]) + 1);
	}
	for (int i = b + 1; i <= m; ++i) {
		if(bList[i] > lastValue)
			ret = max<int>(ret, getJLIS(a, i, bList[i]) + 1);
	}
	return JLIS[a][b] = ret;
}

int main(void) {
	int testcase;
	cin >> testcase;
	for (; testcase > 0; --testcase) {
		cin >> n >> m;
		for (int i = 1; i <= n; ++i) cin >> aList[i];
		for (int i = 1; i <= m; ++i) cin >> bList[i];
		memset(JLIS, -1, sizeof(int) * 101 * 101);
		//각 배열에 0번째 가상 원소를 삽입 후 해당 원소부터 가장 길게 만들 수 있는 배열 길이 추출
		//입력 범위가 32비트 정수 전체이므로 그보다 작은 LLONG_MIN을 초기값으로 사용
		//가상 원소가 포함된 결과물이므로 결과값에서 -1 한 결과가 정답. 
		cout << getJLIS(0, 0, LLONG_MIN) - 1 << endl;
	}
	return 0;
}