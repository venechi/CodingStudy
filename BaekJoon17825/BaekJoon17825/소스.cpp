#include <iostream>
#include <vector>

using namespace std;

int nums[10];
int map[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,32,22,23,24,30,26,24,28,29,24,31,20,32 };
int score[] = { 0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,13,16,19,25,22,24,28,27,26,30,35,0 };
int pos[4] = { 0,0,0,0 };

int ifGo(int i, int k) {
	//i번째 말을 nums[k]만큼 이동시켰을 때 도착위치를 구함
	//5,10,15에서 시작하는경우 특수루트 5->21, 10->25, 15->27
	int left = nums[k];
	int curPos = pos[i];
	if (curPos == 5) {
		curPos = 21;
		--left;
	}
	else if (curPos == 10) {
		curPos = 25;
		--left;
	}
	else if (curPos == 15) {
		curPos = 27;
		--left;
	}
	for (int l = 0; l < left; ++l) {
		curPos = map[curPos];
	}
	return curPos;
}

int getMax(int k) {
	int maxi = 0;
	if (k < 10) {
		for (int i = 0; i < 4; ++i) {
			if (pos[i] != 32) {
				int target = ifGo(i, k);
				bool isOccupied = false;
				for (int j = 0; j < 4; ++j) {
					if (target != 32 && pos[j] == target) {
						isOccupied = true;
						break;
					}
				}
				if (!isOccupied) {
					int temp = pos[i];
					pos[i] = target;
					maxi = max(maxi, score[target] + getMax(k + 1));
					pos[i] = temp;
				}
			}
		}
	}
	return maxi;
}

int main(void) {
	for (int i = 0; i < 10; ++i) cin >> nums[i];
	cout << getMax(0);
	return 0;
}