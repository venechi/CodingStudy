#include <iostream>
#include <vector>

using namespace std;

const int MOD = 20091101;

int pSum[100001];
int maxBuy[100001];
int n, k;

//i�� �ڽ����� j�� �ڽ����� ��� k���� ��� ������ �ַ���
//(pSum[i] - pSum[j-1]) % K == 0 �̾�� �� *pSum = 0�� �ڽ����� i�� �ڽ������� �κ���
//���� pSum[i] % k == pSum[j-1] % k �̸� �ǹǷ�, �κ����� �ƴ� �κ��տ� ���� k ��ⷯ ���갪�� �̿��Ѵ�.
//�κ���-��ⷯ �� ����Ʈ���� ���� ���� ������ ������ �� ���ǽĿ� �ش�ǹǷ�, 
//���� ���� ���� �κ��� ������ ��� ���� ����� ���� ������ �ȴ�.
int singleOrder(vector<int>& count) {
	int result = 0;
	for (int i = 0; i < count.size(); ++i)
		result = (result + (count[i] * ((long long int)count[i] - 1)) / 2) % MOD;
	return result;
}

//
int maxOrder() {
	//pSum[i] = s�� ��, i ������ s���� ���� i`
	//���� ���� �ֹ��� �ؾ� �ϹǷ� �ֹ��� ������ �������� ����, ���� ���� ������ �ִ� i` ������ �����Ѵ�.
	vector<int> prev(k, -1);
	for (int i = 0; i <= n; ++i) {
		//pSum[i] = pSum[i-1] + value[i]�ε�, i�� 0�ΰ�� ó���� ���� ���־�� �ϹǷ�, ������ ���� 0�� �տ� �߰��Ͽ� ���ܸ� �����Ѵ�.
		//���� i�� 0�϶� ������ 0���� �ֹ��� �� �� �ִ�.(���� ���� �����̹Ƿ�)
		//i�� 0�� �ƴϸ� �� ���� ���� �����µ�,
		//i�� ���� �ʴ� ����
		maxBuy[i] = (i == 0 ? 0 : maxBuy[i - 1]);
		int loc = prev[pSum[i]];
		//i�� ��� ���� ������
		//pSum[i]�� ���� ���� ������ pSum[i`]�� ���� ���(i>i`)
		//��� ���� �� ���� �ֹ��� �� �� �ִ��� ���Ѵ�.
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