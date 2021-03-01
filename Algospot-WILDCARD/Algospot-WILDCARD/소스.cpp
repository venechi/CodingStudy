#include <iostream>
#include <vector>
//sort��
#include <algorithm>
//memset��
#include <cstring>

using namespace std;

class MinerRegExp {
private:
	string pattern;
	string str;
	//���ڼ��� �ִ� 100 cache[w][s]�� �����̸�, �ǹ̴� pattern�� (w,pattern.size()-1) �� substring�� str�� (s, str.size()-1)�� substring�� match �Ǵ����� ĳ��
	char cache[101][101];
	bool matcher(char w, char s) {
		//ĳ�̵� ����� ������ ��ȯ
		if (cache[w][s] != -1) return cache[w][s];
		//substring���� �� �� ù ���ڰ� ������ Ȥ�� ?�� ���� ó���Ǵ��� ��, �������� ���ȣ��� ó��
		if (w < pattern.size() && s < str.size() && (pattern[w] == '?' || pattern[w] == str[s])) return cache[w][s] = matcher(w + 1, s + 1);
		// pattern�� ���� ���, str�� �������� �˻�
		if (w == pattern.size()) return cache[w][s] = (s == str.size());
		// pattern�� substring�� ù ���ڰ� * �ΰ��, *�� �߰��� �� ���ڸ� �Ҵ��� ������ �˻� (�Ҵ����� �ʴ� ��� || (str�� substring�� ���� ��� && �Ҵ��ϴ� ���))
		if (pattern[w] == '*') return cache[w][s] = (matcher(w + 1, s) || (s < str.size() && matcher(w, s + 1)));
		// �� ���� ���� ��Ī ����
		return cache[w][s] = false;
	}
public:
	MinerRegExp() {
		pattern = "";
		str = "";
	}
	void setPattern(string pattern) {
		this->pattern = pattern;	
	}
	void setFileName(string fileName) {
		this->str = fileName;
	}
	bool match() {
		memset(cache, -1, 101 * 101 * sizeof(char));
		return matcher(0, 0);
	}
};

int main(void) {
	int testcase = 0;
	string pattern, fileName;
	MinerRegExp reg;
	vector<string> answer;
	int n = 0;
	cin >> testcase;

	for (; testcase > 0; --testcase) {
		answer.clear();
		cin >> pattern;
		reg.setPattern(pattern);
		cin >> n;
		for (; n > 0; --n) {
			cin >> fileName;
			reg.setFileName(fileName);
			if (reg.match()) answer.push_back(fileName);
		}
		sort(answer.begin(), answer.end());
		for (vector<string>::iterator it = answer.begin(); it != answer.end(); ++it)
			cout << *it << endl;
	}

	return 0;
}