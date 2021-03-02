#include <iostream>
#include <cstring>

using namespace std;

int n;
int cache[101];
const int MOD = 1000000007;

int tiling2(int start) {
	//타일이 정확히 덮이면 1 반환(덮기 성공)
	if (start == n) return 1;
	//타일이 주어진 공간을 넘어가면 0 반환(덮기 실패)
	if (start == n + 1) return 0;
	int& ret = cache[start];
	if (ret != -1) return ret;
	//a%p + b%p = (a+b)%p 이므로 아래 식이 성립
	return ret = (tiling2(start + 1) + tiling2(start + 2)) % MOD;
}

int asymTiling() {
	memset(cache, -1, sizeof(int) * 101);
	int whole = tiling2(0);
	memset(cache, -1, sizeof(int) * 101);
	//전체 길이가 짝수인 경우, 타일이 대칭형이 되는 경우는 전체 길이의 절반짜리 벽에 채운 타일이 복제된 형태와
	//중간에 길이 2짜리 타일을 채워넣고 (전체길이 / 2 - 1)짜리 길이의 벽에 채운 타일이 복제된 형태가 있으므로
	//이 두 경우를 제한 나머지 경우의 수가 타일링 방법의 수이다.
	if (n % 2 == 0) {
		n /= 2;
		//모듈러 연산 결과를 빼기 연산할 때, 뒤 수가 클 가능성이 있으므로, 앞의 수에 모듈러값을 더한 후 빼고, 결과값에 다시 한번 모듈러 연산을 적용하자
		whole = (whole + MOD - tiling2(0)) % MOD;
		memset(cache, -1, sizeof(int) * 101);
		--n;
		return (whole + MOD - tiling2(0)) % MOD;
	}
	//전체 길이가 홀수인 경우, 타일이 대칭형이 되는 경우는 가운데 길이 1짜리 타일을 채우고 ([전체길이 - 1 ] / 2)짜리 길이의 벽에 채운 타일이 복제된 형태가 있으므로
	//전체 경우의 수에서 이 경우를 제한 나머지 경우의 수가 타일링 방법의 수이다.
	else {
		n = (n - 1) / 2;
		return (whole + MOD - tiling2(0)) % MOD;
	}
}


int main(void) {
	int testcase;
	cin >> testcase;
	for (; testcase > 0; --testcase) {
		cin >> n;
		
		cout << asymTiling() << endl;
	}
	return 0;
}