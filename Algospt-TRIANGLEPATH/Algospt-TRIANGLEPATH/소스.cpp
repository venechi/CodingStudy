#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int cache_value[100][100];
int** triangle;
int n;

void find(int i, int j) {
	if (cache_value[i][j] != -1) return;
	if (i == n - 1) 
		cache_value[i][j] = triangle[i][j];
	else {
		find(i + 1, j);
		find(i + 1, j + 1);
		cache_value[i][j] = triangle[i][j] + max<int>(cache_value[i + 1][j], cache_value[i + 1][j + 1]);
	}
	return;
}

int main(void) {
	int testcase;
	cin >> testcase;
	for (; testcase > 0; --testcase) {
		cin >> n;
		triangle = new int* [n];
		for (int i = 0; i < n; ++i) {
			triangle[i] = new int[n];
			for (int j = 0; j <= i; ++j)
				cin >> triangle[i][j];
		}
		memset(cache_value, -1, sizeof(int) * 100 * 100);
		
		find(0, 0);
		cout << cache_value[0][0] << endl;

		for (int i = 0; i < n; ++i)
			delete[]triangle[i];
		delete[]triangle;
	}
	return 0;
}