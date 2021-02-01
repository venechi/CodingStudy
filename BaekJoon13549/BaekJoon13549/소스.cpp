#include<iostream>

using namespace std;

int main(void) {
	int n, k;
	cin >> n >> k;
	if (k <= n) cout << n - k;//동생의 위치(k)가 수빈이의 위치(n)보다 앞에 있을경우, 걸어가야만 하므로 바로 출력. 
	else {
		int* arr = new int[k + 1];
		std::fill_n(arr, k + 1, 1000000);//1000000보다 클 수 없음.
		arr[n] = 0;

		for (int j = 0; j < k + 1; ++j) {
			std::printf("%8d", j);
		}
		cout << endl;
		for (int i = n; i < k; ++i) {
			if (arr[i - 1] > arr[i] + 1) {//i좌표에서 i-1좌표로 바로 걸어가는 것이 다른 방법보다 효율적인지 검사.(쭉 걸어오거나, 후퇴한 뒤 순간이동하는 것과 비교)
				arr[i - 1] = arr[i] + 1;
				i -= 2;
				continue;
			}
			if (arr[i + 1] > arr[i] + 1)//i좌표에서 i+1좌표로 바로 걸어가는 것이 다른 방법보다 효율적인지 검사.
				arr[i + 1] = arr[i] + 1;
			if (i * 2 > k) {//순간이동 후 동생의 위치를 뛰어 넘은경우 걸어서만 돌아가야 함.
				if (arr[k] > arr[i] + (i * 2 - k))//순간이동 후 걸어 돌아가는 것이 다른 방법보다 효율적인지 검사.
					arr[k] = arr[i] + (i * 2 - k);
			}
			else {
				if (arr[i * 2] > arr[i])//순간이동 후에도 동생의 위치보다 이전인 경우, 순간이동이 다른 방식에 비해 효율적인지 검사.
					arr[i * 2] = arr[i];
			}

			for (int j = 0; j < k + 1; ++j) {
				std::printf("%8d", arr[j]);
			}
			cout << endl;
		}

		cout << arr[k];//동생의 위치에 도달하기 위한 최소 횟수.
		delete[]arr;
	}
	return 0;
}