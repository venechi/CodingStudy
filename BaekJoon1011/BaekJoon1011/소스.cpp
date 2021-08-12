#include <iostream>

using namespace std;

int main(void) {
	int tc;
	cin >> tc;
	for (int i = 0; i < tc; ++i) {
		int x, y, d;
		int cnt;
		cin >> x >> y;
		d = y - x;
		int low = 1, mid, high = 46341;
		while (low < high) {
			mid = (low + high) / 2;
			if (mid * (mid + 1) > d) high = mid;
			else low = mid + 1;
		}
		--low;
		cnt = low * 2;
		d -= (low * (low + 1));
		if (d > 0) {
			if (d <= low + 1) ++cnt;
			else cnt += 2;
		}
		cout << cnt << endl;
	}
	return 0;
}