#include <iostream>
#include <vector>

using namespace std;

//일반적인 곱셈 알고리즘의 변형 - 올림수(carry) 및 맨 앞의 0 등을 처리하지 않음(각 자리수 그 자체가 중요하므로)
vector<int> multiply(const vector<int>& a, const vector<int>& b) {
	vector<int> c(a.size() + b.size() - 1, 0);
	for (int i = 0; i < a.size(); ++i) {
		for (int j = 0; j < b.size(); ++j) {
			c[i + j] += a[i] * b[j];
		}
	}
	return c;
}

//a에서 b를 빼는 함수(a>=b 라고 가정) - 역배열 숫자용
// 올림수 및 앞자리 0 처리하지 않음
void subFrom(vector<int>& a, const vector<int>& b) {
	for (int i = 0; i < b.size(); ++i) 
		a[i] -= b[i];
}

//a에 b를 더하는 함수 (a + b * 10^k) - 역배열 숫자용
// 올림수 및 앞자리 0 처리하지 않음
void addTo(vector<int>& a, const vector<int>& b, int k) {
	a.resize(max<int>(a.size(), b.size() + k));
	for (int i = 0; i < b.size(); ++i)
		a[i + k] += b[i];
}

//카라츠바 알고리즘의 변형 - 올림수(carry) 및 맨 앞의 0 등을 처리하지 않음(각 자리수 그 자체가 중요하므로)
vector<int> karatsuba(const vector<int>& a, const vector<int>& b){
	if (a.size() == 0 || b.size() == 0) return vector<int>();
	else if (a.size() + b.size() <= 98) return multiply(a, b);//크기가 작을 경우 일반 연산으로 대체(일반 연산이 더 빠름)
	else {
		if (a.size() < b.size()) return karatsuba(b, a);//b의 크기가 a보다 클 경우 자리바꿈
		int half = a.size() >> 1;
		vector<int> a0(a.begin(), a.begin() + half);//숫자가 역배열로 저장되어 있으므로, 공식과 숫자관계 혼동 주의할것.
		vector<int> a1(a.begin() + half, a.end());
		vector<int> b0(b.begin(), b.begin() + min<int>(b.size(), half));
		vector<int> b1(b.begin() + min<int>(b.size(), half), b.end());
		vector<int> z0 = karatsuba(a0, b0);
		vector<int> z2 = karatsuba(a1, b1);

		addTo(a0, a1, 0); addTo(b0, b1, 0);
		vector<int> z1 = karatsuba(a0, b0);
		subFrom(z1, z0);
		subFrom(z1, z2);

		addTo(z0, z1, half);
		addTo(z0, z2, half << 1);
		return z0;
	}
}

int main(void) {
	int testcase = 0;
	cin >> testcase;
	for (; testcase > 0; --testcase) {
		string input;
		vector<int> member, fan;
		int count = 0;

		cin >> input;
		//karatsuba 함수가 숫자의 역배열을 입력으로 받으므로 리버스
		for (string::reverse_iterator it = input.rbegin(); it != input.rend(); ++it) {
			if (*it == 'F') member.push_back(0);
			else member.push_back(1);
		}
		cin >> input;
		//karatsuba 함수가 숫자의 역배열을 입력으로 받으므로 리버스 1회, fan의 배치를 역으로 뒤집어야 하기에 리버스 1회, 총 2회로 입력 그대로 받음
		for (string::iterator it = input.begin(); it != input.end(); ++it) {
			if (*it == 'F') fan.push_back(0);
			else fan.push_back(1);
		}
		vector<int> res = karatsuba(member, fan);
		//자리올림 및 앞자리 0의 처리를 하지 않은 곱셈 결과는 각 자리수가 팬과 멤버의 포옹이 몇 번 불발했는지를 나타냄
		//남-남 관계에서만 1이 발생하고, 나머지는 0이 발생하므로, 자리수가 0이 아닌 경우 누군가가 포옹을 하지 못했음을 의미
		//멤버는 모두 팬과 1:1 매칭이 되어야 결과에 의미가 있으므로, 필요 없는 자리수는 검사하지 않음.
		for (int i = member.size() - 1; i < res.size() - member.size() + 1; ++i) {
			if (res[i] == 0) ++count;
		}
		cout << count << endl;
	}
	return 0;
}