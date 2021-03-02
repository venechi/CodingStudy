#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

int n;
const double CHAINCE_OF_RAINING = 0.75;
const int AVAILABLE_WHEN_RAINING = 2;
const int AVAILABLE_WHEN_NOT_RAINING = 1;
double cache[1001][1001];
bool touched[1001][1001];

double snail(int currentHeight, int remainingDays) {
	//기저사례 처리순서 헷갈리지 말자
	if (currentHeight >= n) return 1;
	if (remainingDays == 0) return 0;
	if (touched[currentHeight][remainingDays]) return cache[currentHeight][remainingDays];
	touched[currentHeight][remainingDays] = true;
	return cache[currentHeight][remainingDays] = 
		snail(currentHeight + AVAILABLE_WHEN_RAINING, remainingDays - 1) * CHAINCE_OF_RAINING + snail(currentHeight + AVAILABLE_WHEN_NOT_RAINING, remainingDays - 1) * (1 - CHAINCE_OF_RAINING);
}

int main(void) {
	int testcase, m;
	cin >> testcase;
	for (; testcase > 0; --testcase) {
		cin >> n >> m;
		memset(touched, 0, sizeof(bool) * 1001 * 1001);
		cout << fixed << setprecision(10) << snail(0, m) << endl;
	}
	return 0;
}