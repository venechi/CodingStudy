#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, int>> sushi(20);
vector<int> cache;

int main(void) {
	int tc, n, m, price, happiness;
	cin >> tc;
	for (int i = 0; i < tc; ++i) {
		cache = vector<int>(201, 0);
		cin >> n >> m;
		m /= 100;
		for (int i = 0; i < n; ++i) {
			cin >> price >> happiness;
			sushi[i] = { price / 100, happiness };
		}
		for (int i = 1; i <= m; ++i) {
			int &ret = cache[i % 201];
			ret = 0;
			for (int j = 0; j < n; ++j) {
				if (i >= sushi[j].first)
					ret = max(ret, sushi[j].second + cache[(i - sushi[j].first) % 201]);
			}
		}
		cout << cache[m % 201] << endl;
	}
	return 0;
}