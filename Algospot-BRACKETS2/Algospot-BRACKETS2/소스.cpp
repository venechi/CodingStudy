#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main(void) {
	int testcase;
	string input, answer;
	char current;
	cin >> testcase;
	do {
		stack<char> s;
		answer = "YES";
		cin >> input;
		for (int i = 0; i < input.size(); ++i) {
			current = input.at(i);
			if (current == '(' || current == '{' || current == '[')
				s.push(current);
			else {
				if (!s.empty() && ((current == ')' && s.top() == '(') || (current == '}' && s.top() == '{') || (current == ']' && s.top() == '[')))
					s.pop();
				else {
					answer = "NO";
					break;
				}
			}
		}
		if (!s.empty()) answer = "NO";
		cout << answer << endl;
	} while (--testcase);
	return 0;
}