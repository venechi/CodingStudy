#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int ALPHABET = 'Z' - 'A' + 1;

class node {
public:
	int ifTab = -1;
	node* next[ALPHABET] = { NULL };
	node() {}
	node(int ifTab): ifTab(ifTab) {}
	~node() {
		for (int i = 0; i < ALPHABET; ++i) {
			if (next[i] != NULL) delete next[i];
		}
	}
};

node* head;
vector<pair<string, int>> dic;

int calc(string target) {
	node* cur = head;
	for (int i = 0; i < target.size(); ++i) {
		cur = cur->next[target[i] - 'A'];
		if (cur == NULL) return target.length();
		else {
			if (dic[cur->ifTab].first == target) {
				return min(i + 2, (int)target.length());
			}
		}
	}
	//입력하려는 문자열을 다 입력했더라도 확률 및 사전 순서때문에 Tab을 이용해서는 입력이 불가능한 경우가 있음
	//이 때는 문자열을 일일히 쳐야 함.
	return target.length();
}

int comp(pair<string, int> a, pair<string, int>b) {
	if (a.second == b.second) return a.first < b.first;
	else return a.second > b.second;
}

int main(void) {
	ios::sync_with_stdio(false);
	int tc;
	cin >> tc;
	for (int i = 0; i < tc; ++i) {
		int n, m, p;
		string word;
		cin >> n >> m;
		dic = vector<pair<string, int>>(n);
		for (int i = 0; i < n; ++i) {
			cin >> word >> p;
			dic[i] = { word, p };
		}
		sort(dic.begin(), dic.end(), comp);
		
		//precalc
		head = new node;
		node* cur;
		for (int i = 0; i < n; ++i) {
			cur = head;
			word = dic[i].first;
			for(int j=0;j<word.length();++j){
				if(cur->next[word[j] - 'A'] == NULL)
					cur->next[word[j] - 'A'] = new node(i);
				cur = cur->next[word[j] - 'A'];
			}
		}

		int cnt = m - 1;
		for (int i = 0; i < m; ++i) {
			cin >> word;
			cnt += calc(word);
		}
		cout << cnt << endl;
		delete head;
	}
	return 0;
}