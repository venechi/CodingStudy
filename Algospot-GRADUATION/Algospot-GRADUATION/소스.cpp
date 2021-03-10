#include <iostream>
#include <cstring>

using namespace std;

const int INF = 987654321;

int preClass[12], availableClassesInSemester[10];
int numOfClasses, maxClassesPerSemester, maxSemesters, classesToListen;
int cache[10][(1 << 12)];
int minSemesters(int semesters, int taken) {
	//졸업 요건 수강 수를 채웠으면 이번 학기 들을 필요 없으므로 0 반환
	if (classesToListen <= __popcnt(taken)) return 0;
	//수강 수가 모자라는데 남은 학기가 없으므로 최대값(불가능) 반환
	if (semesters == maxSemesters) return INF;
	int& ret = cache[semesters][taken];
	if (ret != -1) return ret;
	ret = INF;

	int possibleClasses = 0;
	//선수과목을 다 들어서 들을 수 있는 수업이면서 아직 듣지 않은 수업들을 추출
	for (int i = 0; i < numOfClasses; ++i)
		//비트 연산은 신중히 하자
		if (((taken & preClass[i]) == preClass[i]) && !((1 << i) & taken)) possibleClasses |= (1 << i);
	//들을 수 있는 수업이 없으면 최대 값 반환
	if (possibleClasses == 0) return ret;
	//들을 수 있는 수업들 중 이번학기에 개설되는 수업들을 추출
	possibleClasses &= availableClassesInSemester[semesters];
	//이번 학기에 개설되고 들을 수 있는 수업들 중 한 학기에 들을 수 있는 최대 과목 수 이하의 과목들을 추출하여 수강 후 졸업까지 최소 몇 학기가 걸리는지 계산
	for (int toTake = possibleClasses; toTake; toTake = ((toTake - 1) & possibleClasses)) {
		if ((__popcnt(toTake) <= maxClassesPerSemester))
			ret = min(ret, minSemesters(semesters + 1, taken | toTake) + 1);
	}
	//수업을 듣지 않고 휴학하는 경우
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