#include <iostream>
#include <cstring>

using namespace std;

int n;
int cache[101];

int tiling2(int start) {
	//타일이 정확히 덮이면 1 반환(덮기 성공)
	if (start == n) return 1;
	//타일이 주어진 공간을 넘어가면 0 반환(덮기 실패)
	if (start == n + 1) return 0;
	int& ret = cache[start];
	if (ret != -1) return ret;
	//a%p + b%p = (a+b)%p 이므로 아래 식이 성립
	return ret = (tiling2(start + 1) + tiling2(start + 2)) % 1000000007;
}

int main(void) {
	int testcase;
	cin >> testcase;
	for (; testcase > 0; --testcase) {
		cin >> n;
		memset(cache, -1, sizeof(int) * 101);
		cout << tiling2(0) << endl;
	}
	return 0;
}