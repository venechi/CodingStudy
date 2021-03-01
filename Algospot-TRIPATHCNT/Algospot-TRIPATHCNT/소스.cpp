#include <iostream>
#include <cstring>

using namespace std;

int cache_value[100][100];
long long int cache_num_of_ways[100][100];
int** triangle;
int n;

void find(int i, int j) {
	if (cache_value[i][j] != -1) return;
	//삼각형의 바닥인 경우, 최대값은 그 위치의 값이고, 경로의 수는 1(기저사례)
	if (i == n - 1) {
		cache_value[i][j] = triangle[i][j];
		cache_num_of_ways[i][j] = 1;
	}
	else {
		//바닥에서 (i+1,j)와 (i+1, j+1)까지의 최대합을 갖는 경로 및 경로 개수를 구한 뒤, 현재 위치의 값과 합산
		find(i + 1, j);
		find(i + 1, j + 1);
		//양 쪽의 최대합이 같은 경우, 현 위치의 값과 합산하고 경로 개수도 합산(여기서 오른쪽 혹은 왼쪽으로 내려갈 수 있으므로)
		if (cache_value[i + 1][j] == cache_value[i + 1][j + 1]) {
			cache_value[i][j] = cache_value[i + 1][j] + triangle[i][j];
			cache_num_of_ways[i][j] = cache_num_of_ways[i + 1][j] + cache_num_of_ways[i + 1][j + 1];
		}
		//왼쪽의 최대합이 큰 경우, 큰 값을 현 위치의 값과 합산하고, 왼쪽의 경로 개수 유지(여기서 왼쪽으로만 내려갈 수 있으므로)
		else if (cache_value[i + 1][j] > cache_value[i + 1][j + 1]) {
			cache_value[i][j] = cache_value[i + 1][j] + triangle[i][j];
			cache_num_of_ways[i][j] = cache_num_of_ways[i + 1][j];
		}
		//오른쪽의 최대합이 큰 경우, 큰 값을 현 위치의 값과 합산하고, 오른쪽의 경로 개수 유지(여기서 오른쪽으로만 내려갈 수 있으므로)
		else {
			cache_value[i][j] = cache_value[i + 1][j + 1] + triangle[i][j];
			cache_num_of_ways[i][j] = cache_num_of_ways[i + 1][j + 1];
		}
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
		memset(cache_num_of_ways, -1, sizeof(long long int) * 100 * 100);

		find(0, 0);
		cout << cache_num_of_ways[0][0] << endl;

		for (int i = 0; i < n; ++i)
			delete[]triangle[i];
		delete[]triangle;
	}
	return 0;
}