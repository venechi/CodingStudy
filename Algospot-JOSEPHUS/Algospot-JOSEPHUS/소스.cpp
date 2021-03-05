#include <iostream>
#include <list>

using namespace std;

int main(void) {
	int testcase;
	int n, k;
	cin >> testcase;
	do {
		cin >> n >> k;
		list<int> people;
		for (int i = 0; i < n; ++i)
			people.push_back(i + 1);
		list<int>::iterator kill = people.begin();
		//people.erase(people.end())를 수행시에는 리스트의 헤드 정보가 날아가는 듯 하다.
		//더 이상 people 정보에 정상적으로 접근할 수 없게된다.
		//멤버함수는 동작을 하는 듯 하나, 실제 정보에 접근이 불가능하며, 런타임 오류를 내니 주의하자(주소정보가 날아가서 그런 듯 하다)
		while (people.size() > 2) {
			kill = people.erase(kill);
			if (kill == people.end()) kill = people.begin();
			for (int i = 1; i < k; ++i) {
				++kill;
				if (kill == people.end()) kill = people.begin();
				//위에 쓰인 것처럼 people.end()를 erase함수로 지워버리지 않도록 주의
			}
		}
		cout << people.front() << " " << people.back() << endl;
	} while (--testcase);
	return 0;
}