#include <iostream>
#include <string>

using namespace std;

string reverse(string::iterator& it) {
	if (*it == 'b' || *it == 'w') return string(1, *it);
	else {
		string UL = reverse(++it);
		string UR = reverse(++it);
		string DL = reverse(++it);
		string DR = reverse(++it);
		return "x" + DL + DR + UL + UR;
	}
}

string FlipQuadtree(string quadtree) {
	string::iterator it = quadtree.begin();
	return reverse(it);
}

int main(void) {
	int testcase;
	string quadtree;
	cin >> testcase;
	for (; testcase > 0; --testcase) {
		cin >> quadtree;
		cout << FlipQuadtree(quadtree) << endl;
	}
	return 0;
}