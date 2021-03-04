#include <iostream>
#include <vector>

using namespace std;

const int MOD = 20091101;

int pSum[100001];
int maxBuy[100001];
int n, k;

//i번 박스부터 j번 박스까지 골라서 k명에게 모두 나누어 주려면
//(pSum[i] - pSum[j-1]) % K == 0 이어야 함 *pSum = 0번 박스부터 i번 박스까지의 부분합
//따라서 pSum[i] % k == pSum[j-1] % k 이면 되므로, 부분합이 아닌 부분합에 대한 k 모듈러 연산값을 이용한다.
//부분합-모듈러 값 리스트에서 같은 값을 가지고 있으면 위 조건식에 해당되므로, 
//같은 값을 갖는 부분합 개수가 몇갠지 세서 경우의 수를 따지면 된다.
int singleOrder(vector<int>& count) {
	int result = 0;
	for (int i = 0; i < count.size(); ++i)
		result = (result + (count[i] * ((long long int)count[i] - 1)) / 2) % MOD;
	return result;
}

//
int maxOrder() {
	//pSum[i] = s일 때, i 이전에 s값을 갖는 i`
	//가장 많은 주문을 해야 하므로 주문의 범위가 작을수록 좋고, 따라서 가장 가까이 있는 i` 값만을 유지한다.
	vector<int> prev(k, -1);
	for (int i = 0; i <= n; ++i) {
		//pSum[i] = pSum[i-1] + value[i]인데, i가 0인경우 처리를 따로 해주어야 하므로, 가상의 원소 0을 앞에 추가하여 예외를 제거한다.
		//따라서 i가 0일때 무조건 0개의 주문을 할 수 있다.(원래 없는 상자이므로)
		//i가 0이 아니면 두 가지 경우로 나뉘는데,
		//i를 사지 않는 경우와
		maxBuy[i] = (i == 0 ? 0 : maxBuy[i - 1]);
		int loc = prev[pSum[i]];
		//i를 사는 경우로 나뉜다
		//pSum[i]와 같은 값을 가지는 pSum[i`]가 있을 경우(i>i`)
		//어느 쪽이 더 많은 주문을 할 수 있는지 비교한다.
		if (loc != -1) maxBuy[i] = max(maxBuy[i], maxBuy[loc] + 1);
		prev[pSum[i]] = i;
	}
	return maxBuy[n];
}

int main(void) {
	int testcase;
	cin >> testcase;
	do {
		cin >> n >> k;
		vector<int> count(k, 0);
		pSum[0] = 0;
		count[0] = 1;
		for (int i = 1; i <= n; ++i) {
			cin >> pSum[i];
			pSum[i] = (pSum[i] + pSum[i - 1]) % k;
			++count[pSum[i]];
		}
		cout << singleOrder(count) << " " << maxOrder() << endl;
	} while (--testcase);
	return 0;
}