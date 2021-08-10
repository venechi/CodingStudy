#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> binominal;

void preCalc(int n, int m) {
	binominal = vector<vector<int>>(n + m + 1, vector<int>(n + m + 1, -1));
	binominal[0][0] = 1;
	for (int i = 1; i <= n + m; ++i) {
		binominal[i][0] = 1;
		for (int j = 1; j < i; ++j) {
			binominal[i][j] = min(binominal[i - 1][j - 1] + binominal[i - 1][j], 1000000001);
		}
		binominal[i][i] = 1;
	}
}

string getKth(int n, int m, int k) {
	if (binominal[m + n][n] < k) return "-1";
	else {
		string answer = "";
		while (m > 0 || n > 0) {
			if (n > 0 && binominal[m + n - 1][m] >= k || m == 0) {
				answer += "a";
				--n;
			}
			else {
				answer += "z";
				k -= binominal[m + n - 1][m];
				--m;
			}
		}
		return answer;
	}
}

int main(void) {
	int n, m, k;
	cin >> n >> m >> k;
	preCalc(n, m);
	cout << getKth(n, m, k) << endl;
	return 0;
}