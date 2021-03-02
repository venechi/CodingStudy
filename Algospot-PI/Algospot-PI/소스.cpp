#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <climits>

using namespace std;

int score[10002];
string input;

int scoring(int s, int length) {
	bool check = true;
	//숫자가 등차 수열을 이룰 때
	int gap = input.at(s + 1) - input.at(s);
	for (int i = 2; i < length; ++i) {
		if (input.at(s + i) - input.at(s + i - 1) != gap) {
			check = false;
			break;
		}
	}
	if (check) {
		//모든 숫자가 같을 때
		if (gap == 0)
			return 1;
		//숫자가 1씩 단조 증가하거나 감소할 때
		else if (gap == 1 || gap == -1)
			return 2;
		else
			return 5;
	}
	check = true;
	//두 개의 숫자가 번갈아가며 나타날 때
	for (int i = 2; i < length; ++i) {
		gap *= -1;
		if (input.at(s + i) - input.at(s + i - 1) != gap) {
			check = false;
			break;
		}
	}
	if (check) return 4;
	//어떤 특징도 없을 경우
	return 10;
}

int getMinScore(int s) {
	int& ret = score[s];
	//더 이상 남은 문자열이 없으면 0 반환
	if (input.size() == s) return ret = 0;
	if (ret != -1) return ret;
	ret = 987654321;
	for (int i = 3; i < 6; ++i) {
		//문자열에서 3,4,5글자를 잘랐을 때의 최적해를 비교하여 가장 작은 값 반환
		//주어진 문자열이 3개 미만인 경우 재귀호출 및 점수평가 함수에 진입하지 못하므로 987654321 반환
		if (s + i <= input.size())
			ret = min<int>(ret, scoring(s, i) + getMinScore(s + i));
	}
	return ret;
}

int main(void) {
	int testcase;
	cin >> testcase;
	for (; testcase > 0; --testcase) {
		cin >> input;
		memset(score, -1, sizeof(int) * 10000);
		cout << getMinScore(0) << endl;
	}
	return 0;
}