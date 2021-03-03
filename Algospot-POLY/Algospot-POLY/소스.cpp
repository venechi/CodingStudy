#include <iostream>
#include <cstring>

using namespace std;

int cache[101][101];
const int MOD = 10000000;

int poly(int upperLineBlocks, int remainingBlocks) {
	if (remainingBlocks == 0) return 1;
	int& ret = cache[upperLineBlocks][remainingBlocks];
	if (ret != -1)return ret;
	ret = 0;
	for (int size = 1; size <= remainingBlocks; ++size) {
		//최초 시작일 경우, 첫 번째 라인에 블록 몇 개가 들어가든 경우의 수는 하나이므로 따로 처리
		if (upperLineBlocks == 0)
			ret = (ret + poly(size, remainingBlocks - size)) % MOD;
		//위에 라인이 있을 경우 윗 줄 블록 개수와 아랫 줄에 채울 블록 개수에 따라 경우의 수가 달라지므로 해당 경우의 수만큼 곱셈 수행
		// ex) 윗줄 2, 아랫줄 3개일 경우
		//	1) 0 0 1 1 0 0	2) 0 0 1 1 0 0	3) 0 0 1 1 0 0	4) 0 0 1 1 0 0  
		//	   1 1 1 0 0 0	   0 1 1 1 0 0	   0 0 1 1 1 0	   0 0 0 1 1 1
		// 의 4가지 경우의 수가 나온다.
		else
			ret = (ret + (poly(size, remainingBlocks - size) * (size + upperLineBlocks - 1)) % MOD) % MOD;
	}
	return ret;
}

int main(void) {
	int testcase, n;
	cin >> testcase;
	for (; testcase > 0; --testcase) {
		cin >> n;
		memset(cache, -1, sizeof(int) * 101 * 101);
		cout << poly(0, n) << endl;
	}
	return 0;
}