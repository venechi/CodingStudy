#include <iostream>
#include <cstring>

using namespace std;

const int INF = 987654321;

int preClass[12], availableClassesInSemester[10];
int numOfClasses, maxClassesPerSemester, maxSemesters, classesToListen;
int cache[10][(1 << 12)];
int minSemesters(int semesters, int taken) {
	//���� ��� ���� ���� ä������ �̹� �б� ���� �ʿ� �����Ƿ� 0 ��ȯ
	if (classesToListen <= __popcnt(taken)) return 0;
	//���� ���� ���ڶ�µ� ���� �бⰡ �����Ƿ� �ִ밪(�Ұ���) ��ȯ
	if (semesters == maxSemesters) return INF;
	int& ret = cache[semesters][taken];
	if (ret != -1) return ret;
	ret = INF;

	int possibleClasses = 0;
	//���������� �� �� ���� �� �ִ� �����̸鼭 ���� ���� ���� �������� ����
	for (int i = 0; i < numOfClasses; ++i)
		//��Ʈ ������ ������ ����
		if (((taken & preClass[i]) == preClass[i]) && !((1 << i) & taken)) possibleClasses |= (1 << i);
	//���� �� �ִ� ������ ������ �ִ� �� ��ȯ
	if (possibleClasses == 0) return ret;
	//���� �� �ִ� ������ �� �̹��б⿡ �����Ǵ� �������� ����
	possibleClasses &= availableClassesInSemester[semesters];
	//�̹� �б⿡ �����ǰ� ���� �� �ִ� ������ �� �� �б⿡ ���� �� �ִ� �ִ� ���� �� ������ ������� �����Ͽ� ���� �� �������� �ּ� �� �бⰡ �ɸ����� ���
	for (int toTake = possibleClasses; toTake; toTake = ((toTake - 1) & possibleClasses)) {
		if ((__popcnt(toTake) <= maxClassesPerSemester))
			ret = min(ret, minSemesters(semesters + 1, taken | toTake) + 1);
	}
	//������ ���� �ʰ� �����ϴ� ���
	return ret = min(ret, minSemesters(semesters + 1, taken));
}

int main(void) {
	int testcase, n, input, result;
	cin >> testcase;
	do {
		memset(cache, -1, sizeof(int) * 10 * (1 << 12));
		cin >> numOfClasses >> classesToListen >> maxSemesters >> maxClassesPerSemester;
		for (int i = 0; i < numOfClasses; ++i) {
			preClass[i] = 0;
			cin >> n;
			for (int j = 0; j < n; ++j) {
				cin >> input;
				preClass[i] |= (1 << input);
			}
		}
		for (int i = 0; i < maxSemesters; ++i) {
			availableClassesInSemester[i] = 0;
			cin >> n;
			for (int j = 0; j < n; ++j) {
				cin >> input;
				availableClassesInSemester[i] |= (1 << input);
			}
		}
		result = minSemesters(0, 0);
		if (result != INF) cout << result << endl;
		else cout << "IMPOSSIBLE" << endl;
	} while (--testcase);
	return 0;
}