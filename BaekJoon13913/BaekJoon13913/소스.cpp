#include<iostream>
#include<vector>
#include<iterator>

using namespace std;

int main(void) {
	int n, k;
	cin >> n >> k;
	if (k <= n) {
		cout << n - k << "\n";//������ ��ġ(k)�� �������� ��ġ(n)���� �տ� �������, �ɾ�߸� �ϹǷ� �ٷ� ���.
		for (; n >= k; --n)
			cout << n << " ";
	}
	else {
		int* arr = new int[k + 1];
		std::fill_n(arr, k + 1, 1000000);//1000000���� Ŭ �� ����.
		arr[n] = 0;

		for (int i = n; i < k; ++i) {
			if (arr[i - 1] > arr[i] + 1) {//i��ǥ���� i-1��ǥ�� �ٷ� �ɾ�� ���� �ٸ� ������� ȿ�������� �˻�.(�� �ɾ���ų�, ������ �� �����̵��ϴ� �Ͱ� ��)
				arr[i - 1] = arr[i] + 1;
				i -= 2;
				continue;
			}

			if (arr[i + 1] > arr[i] + 1) {//i��ǥ���� i+1��ǥ�� �ٷ� �ɾ�� ���� �ٸ� ������� ȿ�������� �˻�.
				arr[i + 1] = arr[i] + 1;
			}

			if (i * 2 > k) {//�����̵� �� ������ ��ġ�� �پ� ������� �ɾ�� ���ư��� ��.
				if (arr[k] > arr[i] + 1 + (i * 2 - k))//�����̵� �� �ɾ� ���ư��� ���� �ٸ� ������� ȿ�������� �˻�.
					arr[k] = arr[i] + 1 + (i * 2 - k);
			}
			else {
				if (arr[i * 2] > arr[i] + 1)//�����̵� �Ŀ��� ������ ��ġ���� ������ ���, �����̵��� �ٸ� ��Ŀ� ���� ȿ�������� �˻�.
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
					if (current > k) {//�� ��ġ�� ������ ��ġ�� �پ� ���� ��� (�����̵� �� ������ ���)
						if (current % 2 == 0 && arr[current / 2] == arr[k] - (current - k) - 1)//������ �����̵��ؼ� ���� ���.
							route.at(i)->push_back(current / 2);
						else if (current >= k * 2) //�� ��ġ�� ������ ��ġ���� �����̵� Ȥ�� �� �̻��� �������� ���� �����ؾ� �ϴ� ���.(���� �Ұ�����)
							route.erase(route.begin() + i);
						else //������ �Ѱ��� �����Ͽ� ���� ���.
							route.at(i)->push_back(current + 1);
					}
					else if (current == k) {//�� ��ġ�� ������ ���� ���(��� Ž�� ����)
						if (current % 2 == 0 && arr[current / 2] == arr[current] - 1) {//������ �����̵��ؼ� ���� ���.
							route.at(i)->push_back(current / 2);
							new_line = true;
						}
						if (arr[current - 1] == arr[current] - 1) {//������ �� ���� �����Ͽ� ���� ���.
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
						//������ �� ���� �����Ͽ� ���� ���.
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
					else if (current != n) {// �� ��ġ�� �������� �����̰�, ��� ��ġ�� �ƴ� ���.
						if (current % 2 == 0 && arr[current / 2] == arr[current] - 1) {//������ �����̵��ؼ� ���� ���.
							route.at(i)->push_back(current / 2);
							new_line = true;
						}
						if (arr[current - 1] == arr[current] - 1) {//������ �� ���� �����Ͽ� ���� ���.
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
						if (arr[current + 1] == arr[current] - 1) {//������ �� ���� �����Ͽ� ���� ���.
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

		cout << arr[k] << "\n";//������ ��ġ�� �����ϱ� ���� �ּ� Ƚ��.
		for (vector<int>::reverse_iterator it = route[0]->rbegin(); it != route[0]->rend(); ++it)//��� ���
			cout << (*it) << " ";
		delete[]arr;

		for (vector<vector<int>*>::iterator it = route.begin(); it != route.end(); ++it)
			delete (*it);
	}
	return 0;
}