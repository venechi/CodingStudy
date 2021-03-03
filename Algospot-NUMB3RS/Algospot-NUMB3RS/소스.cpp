#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

bool map[50][50];
int numOfConncectedVillae[50];
double chanceOfDrBe[50];
int numOfVillage, passedDays, jailVillage;

void precalc() {
	//메모리 초기화 및 i번째 마을과 연결된 마을 수 계산(degree 계산)
	memset(chanceOfDrBe, 0, sizeof(double) * 50);
	//시작하는 날 박사는 감옥이 있는 마을에 있으므로 확률 1을 설정
	chanceOfDrBe[jailVillage] = 1;
	for (int i = 0; i < numOfVillage; ++i) {
		numOfConncectedVillae[i] = 0;
		for (int j = 0; j < numOfVillage; ++j) {
			if (map[i][j]) ++numOfConncectedVillae[i];
		}
	}
}

void calc() {
	precalc();
	//전체 확률을 계산하는동안 기존 확률값을 잃으면 안 되므로 계산결과를 임시저장
	double tempChance[50];
	for (; passedDays > 0; --passedDays)
	{
		for (int i = 0; i < numOfVillage; ++i) {
			tempChance[i] = 0;
			for (int j = 0; j < numOfVillage; ++j) {
				//연결된 마을로부터 하루 뒤에 i번째 마을로 넘어올 확률 계산
				if (map[i][j]) tempChance[i] += (chanceOfDrBe[j] / numOfConncectedVillae[j]);
			}
		}
		//계산이 끝났으므로, 확률 업데이트
		memcpy_s(chanceOfDrBe, numOfVillage * sizeof(double), tempChance, numOfVillage * sizeof(double));
	}
}


int main(void) {
	int testcase;	
	int n, temp;
	cin >> testcase;
	for (; testcase > 0; --testcase) {
		cin >> numOfVillage >> passedDays >> jailVillage;
		for (int i = 0; i < numOfVillage; ++i) {
			for (int j = 0; j < numOfVillage; ++j)
				cin >> map[i][j];
		}

		calc();
		
		cin >> n;
		for (; n > 0; --n) {
			cin >> temp;
			cout << fixed << setprecision(8) << chanceOfDrBe[temp] << " ";
		}
		cout << endl;
	}
	return 0;
}