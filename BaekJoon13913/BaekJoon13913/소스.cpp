#include<iostream>
#include<vector>
#include<iterator>

using namespace std;

int main(void) {
	int n, k;
	cin >> n >> k;
	if (k <= n) {
		cout << n - k << "\n";//동생의 위치(k)가 수빈이의 위치(n)보다 앞에 있을경우, 걸어가야만 하므로 바로 출력.
		for (; n >= k; --n)
			cout << n << " ";
	}
	else {
		int* arr = new int[k + 1];
		std::fill_n(arr, k + 1, 1000000);//1000000보다 클 수 없음.
		arr[n] = 0;

		for (int i = n; i < k; ++i) {
			if (arr[i - 1] > arr[i] + 1) {//i좌표에서 i-1좌표로 바로 걸어가는 것이 다른 방법보다 효율적인지 검사.(쭉 걸어오거나, 후퇴한 뒤 순간이동하는 것과 비교)
				arr[i - 1] = arr[i] + 1;
				i -= 2;
				continue;
			}

			if (arr[i + 1] > arr[i] + 1) {//i좌표에서 i+1좌표로 바로 걸어가는 것이 다른 방법보다 효율적인지 검사.
				arr[i + 1] = arr[i] + 1;
			}

			if (i * 2 > k) {//순간이동 후 동생의 위치를 뛰어 넘은경우 걸어서만 돌아가야 함.
				if (arr[k] > arr[i] + 1 + (i * 2 - k))//순간이동 후 걸어 돌아가는 것이 다른 방법보다 효율적인지 검사.
					arr[k] = arr[i] + 1 + (i * 2 - k);
			}
			else {
				if (arr[i * 2] > arr[i] + 1)//순간이동 후에도 동생의 위치보다 이전인 경우, 순간이동이 다른 방식에 비해 효율적인지 검사.
					arr[i * 2] = arr[i] + 1;
			}
		}

		vector<vector<int>*> route;
		vector<int>* temp = NULL;
		route.push_back(new vector<int>());
		route.at(0)->push_back(k);

		bool finished = false;
		bool new_line = false;
		int current;
		while (!finished) {
			finished = true;
			for (int i = 0; i < route.size(); ++i) {

				current = route.at(i)->back();
				new_line = false;
				if (current != n) {
					finished = false;
					if (current > k) {//현 위치가 동생의 위치를 뛰어 넘은 경우 (순간이동 후 후퇴한 경우)
						if (current % 2 == 0 && arr[current / 2] == arr[k] - (current - k) - 1)//이전에 순간이동해서 왔을 경우.
							route.at(i)->push_back(current / 2);
						else if (current >= k * 2) //현 위치가 동생의 위치에서 순간이동 혹은 그 이상의 움직임을 통해 도착해야 하는 경우.(도달 불가영역)
							route.erase(route.begin() + i);
						else //이전에 한걸음 후퇴하여 왔을 경우.
							route.at(i)->push_back(current + 1);
					}
					else if (current == k) {//현 위치가 동생과 같을 경우(경로 탐색 시작)
						if (current % 2 == 0 && arr[current / 2] == arr[current] - 1) {//이전에 순간이동해서 왔을 경우.
							route.at(i)->push_back(current / 2);
							new_line = true;
						}
						if (arr[current - 1] == arr[current] - 1) {//이전에 한 걸음 전진하여 왔을 경우.
							if (new_line) {
								temp = new vector<int>(*(route.at(i)));
								temp->pop_back();
								temp->push_back(current - 1);
								route.push_back(temp);
								temp = NULL;
							}
							else {
								route.at(i)->push_back(current - 1);
								new_line = true;
							}
						}
						//이전에 한 걸음 후퇴하여 왔을 경우.
						if (new_line) {
							temp = new vector<int>(*(route.at(i)));
							temp->pop_back();
							temp->push_back(current + 1);
							route.push_back(temp);
							temp = NULL;
						}
						else
							route.at(i)->push_back(current + 1);
					}
					else if (current != n) {// 현 위치가 동생보다 이전이고, 출발 위치가 아닌 경우.
						if (current % 2 == 0 && arr[current / 2] == arr[current] - 1) {//이전에 순간이동해서 왔을 경우.
							route.at(i)->push_back(current / 2);
							new_line = true;
						}
						if (arr[current - 1] == arr[current] - 1) {//이전에 한 걸음 전진하여 왔을 경우.
							if (new_line) {
								temp = new vector<int>(*(route.at(i)));
								temp->pop_back();
								temp->push_back(current - 1);
								route.push_back(temp);
								temp = NULL;
							}
							else {
								route.at(i)->push_back(current - 1);
								new_line = true;
							}
						}
						if (arr[current + 1] == arr[current] - 1) {//이전에 한 걸음 후퇴하여 왔을 경우.
							if (new_line) {
								temp = new vector<int>(*(route.at(i)));
								temp->pop_back();
								temp->push_back(current + 1);
								route.push_back(temp);
								temp = NULL;
							}
							else
								route.at(i)->push_back(current + 1);
						}
					}
				}
			}
		}

		cout << arr[k] << "\n";//동생의 위치에 도달하기 위한 최소 횟수.
		for (vector<int>::reverse_iterator it = route[0]->rbegin(); it != route[0]->rend(); ++it)//경로 출력
			cout << (*it) << " ";
		delete[]arr;

		for (vector<vector<int>*>::iterator it = route.begin(); it != route.end(); ++it)
			delete (*it);
	}
	return 0;
}