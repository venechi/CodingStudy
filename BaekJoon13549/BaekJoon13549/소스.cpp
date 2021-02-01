#include<iostream>

using namespace std;

int main(void) {
	int n, k;
	cin >> n >> k;
	if (k <= n) cout << n - k;//������ ��ġ(k)�� �������� ��ġ(n)���� �տ� �������, �ɾ�߸� �ϹǷ� �ٷ� ���. 
	else {
		int* arr = new int[k + 1];
		std::fill_n(arr, k + 1, 1000000);//1000000���� Ŭ �� ����.
		arr[n] = 0;

		for (int j = 0; j < k + 1; ++j) {
			std::printf("%8d", j);
		}
		cout << endl;
		for (int i = n; i < k; ++i) {
			if (arr[i - 1] > arr[i] + 1) {//i��ǥ���� i-1��ǥ�� �ٷ� �ɾ�� ���� �ٸ� ������� ȿ�������� �˻�.(�� �ɾ���ų�, ������ �� �����̵��ϴ� �Ͱ� ��)
				arr[i - 1] = arr[i] + 1;
				i -= 2;
				continue;
			}
			if (arr[i + 1] > arr[i] + 1)//i��ǥ���� i+1��ǥ�� �ٷ� �ɾ�� ���� �ٸ� ������� ȿ�������� �˻�.
				arr[i + 1] = arr[i] + 1;
			if (i * 2 > k) {//�����̵� �� ������ ��ġ�� �پ� ������� �ɾ�� ���ư��� ��.
				if (arr[k] > arr[i] + (i * 2 - k))//�����̵� �� �ɾ� ���ư��� ���� �ٸ� ������� ȿ�������� �˻�.
					arr[k] = arr[i] + (i * 2 - k);
			}
			else {
				if (arr[i * 2] > arr[i])//�����̵� �Ŀ��� ������ ��ġ���� ������ ���, �����̵��� �ٸ� ��Ŀ� ���� ȿ�������� �˻�.
					arr[i * 2] = arr[i];
			}

			for (int j = 0; j < k + 1; ++j) {
				std::printf("%8d", arr[j]);
			}
			cout << endl;
		}

		cout << arr[k];//������ ��ġ�� �����ϱ� ���� �ּ� Ƚ��.
		delete[]arr;
	}
	return 0;
}