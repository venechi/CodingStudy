#include <iostream>
#include <vector>

using namespace std;

//�Ϲ����� ���� �˰����� ���� - �ø���(carry) �� �� ���� 0 ���� ó������ ����(�� �ڸ��� �� ��ü�� �߿��ϹǷ�)
vector<int> multiply(const vector<int>& a, const vector<int>& b) {
	vector<int> c(a.size() + b.size() - 1, 0);
	for (int i = 0; i < a.size(); ++i) {
		for (int j = 0; j < b.size(); ++j) {
			c[i + j] += a[i] * b[j];
		}
	}
	return c;
}

//a���� b�� ���� �Լ�(a>=b ��� ����) - ���迭 ���ڿ�
// �ø��� �� ���ڸ� 0 ó������ ����
void subFrom(vector<int>& a, const vector<int>& b) {
	for (int i = 0; i < b.size(); ++i) 
		a[i] -= b[i];
}

//a�� b�� ���ϴ� �Լ� (a + b * 10^k) - ���迭 ���ڿ�
// �ø��� �� ���ڸ� 0 ó������ ����
void addTo(vector<int>& a, const vector<int>& b, int k) {
	a.resize(max<int>(a.size(), b.size() + k));
	for (int i = 0; i < b.size(); ++i)
		a[i + k] += b[i];
}

//ī������ �˰����� ���� - �ø���(carry) �� �� ���� 0 ���� ó������ ����(�� �ڸ��� �� ��ü�� �߿��ϹǷ�)
vector<int> karatsuba(const vector<int>& a, const vector<int>& b){
	if (a.size() == 0 || b.size() == 0) return vector<int>();
	else if (a.size() + b.size() <= 98) return multiply(a, b);//ũ�Ⱑ ���� ��� �Ϲ� �������� ��ü(�Ϲ� ������ �� ����)
	else {
		if (a.size() < b.size()) return karatsuba(b, a);//b�� ũ�Ⱑ a���� Ŭ ��� �ڸ��ٲ�
		int half = a.size() >> 1;
		vector<int> a0(a.begin(), a.begin() + half);//���ڰ� ���迭�� ����Ǿ� �����Ƿ�, ���İ� ���ڰ��� ȥ�� �����Ұ�.
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
		//karatsuba �Լ��� ������ ���迭�� �Է����� �����Ƿ� ������
		for (string::reverse_iterator it = input.rbegin(); it != input.rend(); ++it) {
			if (*it == 'F') member.push_back(0);
			else member.push_back(1);
		}
		cin >> input;
		//karatsuba �Լ��� ������ ���迭�� �Է����� �����Ƿ� ������ 1ȸ, fan�� ��ġ�� ������ ������� �ϱ⿡ ������ 1ȸ, �� 2ȸ�� �Է� �״�� ����
		for (string::iterator it = input.begin(); it != input.end(); ++it) {
			if (*it == 'F') fan.push_back(0);
			else fan.push_back(1);
		}
		vector<int> res = karatsuba(member, fan);
		//�ڸ��ø� �� ���ڸ� 0�� ó���� ���� ���� ���� ����� �� �ڸ����� �Ұ� ����� ������ �� �� �ҹ��ߴ����� ��Ÿ��
		//��-�� ���迡���� 1�� �߻��ϰ�, �������� 0�� �߻��ϹǷ�, �ڸ����� 0�� �ƴ� ��� �������� ������ ���� �������� �ǹ�
		//����� ��� �Ұ� 1:1 ��Ī�� �Ǿ�� ����� �ǹ̰� �����Ƿ�, �ʿ� ���� �ڸ����� �˻����� ����.
		for (int i = member.size() - 1; i < res.size() - member.size() + 1; ++i) {
			if (res[i] == 0) ++count;
		}
		cout << count << endl;
	}
	return 0;
}