#include <iostream>
#include <cstring>

using namespace std;

int cache_value[100][100];
long long int cache_num_of_ways[100][100];
int** triangle;
int n;

void find(int i, int j) {
	if (cache_value[i][j] != -1) return;
	//�ﰢ���� �ٴ��� ���, �ִ밪�� �� ��ġ�� ���̰�, ����� ���� 1(�������)
	if (i == n - 1) {
		cache_value[i][j] = triangle[i][j];
		cache_num_of_ways[i][j] = 1;
	}
	else {
		//�ٴڿ��� (i+1,j)�� (i+1, j+1)������ �ִ����� ���� ��� �� ��� ������ ���� ��, ���� ��ġ�� ���� �ջ�
		find(i + 1, j);
		find(i + 1, j + 1);
		//�� ���� �ִ����� ���� ���, �� ��ġ�� ���� �ջ��ϰ� ��� ������ �ջ�(���⼭ ������ Ȥ�� �������� ������ �� �����Ƿ�)
		if (cache_value[i + 1][j] == cache_value[i + 1][j + 1]) {
			cache_value[i][j] = cache_value[i + 1][j] + triangle[i][j];
			cache_num_of_ways[i][j] = cache_num_of_ways[i + 1][j] + cache_num_of_ways[i + 1][j + 1];
		}
		//������ �ִ����� ū ���, ū ���� �� ��ġ�� ���� �ջ��ϰ�, ������ ��� ���� ����(���⼭ �������θ� ������ �� �����Ƿ�)
		else if (cache_value[i + 1][j] > cache_value[i + 1][j + 1]) {
			cache_value[i][j] = cache_value[i + 1][j] + triangle[i][j];
			cache_num_of_ways[i][j] = cache_num_of_ways[i + 1][j];
		}
		//�������� �ִ����� ū ���, ū ���� �� ��ġ�� ���� �ջ��ϰ�, �������� ��� ���� ����(���⼭ ���������θ� ������ �� �����Ƿ�)
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