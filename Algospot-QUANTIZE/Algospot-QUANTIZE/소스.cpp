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
	//������ �� ������ �սô�( = ���Ծ �ѽð� ���)
	for (int i = start; i <= end; ++i) {
		squaredError += pow((double)avg - numArray[i], 2);
	}
	return squaredError;
}

int quantize(int start, int s) {
	//�� �̻� ������ ���� �����Ƿ� 0�� ��ȯ
	if (start == n) return 0;
	//������ ���� ���Ҵµ� �� �� �ִ� ���ڰ� �����Ƿ� ���� �� ���� ū �� ��ȯ
	if (s == 0) return 987654321;
	
	int& ret = cache[start][s];
	if (ret != -1) return ret;
	ret = 987654321;
	for (int i = start; i < n; ++i) {
		//�տ������� �� ��° ���ڱ����� �ϳ��� �׷����� �ؾ� ���� �ذ� �Ǵ��� Ž��
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
		//�־��� ���ڸ� �����Ͽ�, �ϳ��� ���ڷ� ����ȭ�� ���ڵ��� ��Ƴ��´�.
		sort(numArray, numArray + n);
		cout << quantize(0, s) << endl;
	}
	return 0;
}