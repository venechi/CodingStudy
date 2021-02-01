# include <iostream>

using namespace std;

int main(void) {
	int n = 0;
	cin >> n;
	int* arr = new int[n + 1];
	std::fill_n(arr, n, 1000000);
	arr[n] = 0;

	//동적계획법 이용
	for (; n > 0; --n) {
		if (n % 3 == 0) {
			if (arr[n / 3] > arr[n] + 1) arr[n / 3] = arr[n] + 1;
		}
		if (n % 2 == 0) {
			if (arr[n / 2] > arr[n] + 1) arr[n / 2] = arr[n] + 1;
		}
		if (arr[n - 1] > arr[n] + 1) arr[n - 1] = arr[n] + 1;
	}

	cout << arr[1];
	delete[]arr;
	return 0;
}