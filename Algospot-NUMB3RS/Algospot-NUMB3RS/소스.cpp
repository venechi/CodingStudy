#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

bool map[50][50];
int numOfConncectedVillae[50];
double chanceOfDrBe[50];
int numOfVillage, passedDays, jailVillage;

void precalc() {
	//�޸� �ʱ�ȭ �� i��° ������ ����� ���� �� ���(degree ���)
	memset(chanceOfDrBe, 0, sizeof(double) * 50);
	//�����ϴ� �� �ڻ�� ������ �ִ� ������ �����Ƿ� Ȯ�� 1�� ����
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
	//��ü Ȯ���� ����ϴµ��� ���� Ȯ������ ������ �� �ǹǷ� ������� �ӽ�����
	double tempChance[50];
	for (; passedDays > 0; --passedDays)
	{
		for (int i = 0; i < numOfVillage; ++i) {
			tempChance[i] = 0;
			for (int j = 0; j < numOfVillage; ++j) {
				//����� �����κ��� �Ϸ� �ڿ� i��° ������ �Ѿ�� Ȯ�� ���
				if (map[i][j]) tempChance[i] += (chanceOfDrBe[j] / numOfConncectedVillae[j]);
			}
		}
		//����� �������Ƿ�, Ȯ�� ������Ʈ
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