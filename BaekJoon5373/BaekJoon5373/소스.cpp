#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class cube {
private :
	vector<vector<char>> virtical;
	vector<vector<char>> horizontal;

	//true : sync virt to hori, false: sync hori to virt 
	void sync(int d) {
		if (d) {
			horizontal[0][3] = virtical[3][0];
			horizontal[0][4] = virtical[3][1];
			horizontal[0][5] = virtical[3][2];

			horizontal[1][3] = virtical[4][0];
			horizontal[1][4] = virtical[4][1];
			horizontal[1][5] = virtical[4][2];

			horizontal[2][3] = virtical[5][0];
			horizontal[2][4] = virtical[5][1];
			horizontal[2][5] = virtical[5][2];


			horizontal[0][9] = virtical[11][2];
			horizontal[0][10] = virtical[11][1];
			horizontal[0][11] = virtical[11][0];

			horizontal[1][9] = virtical[10][2];
			horizontal[1][10] = virtical[10][1];
			horizontal[1][11] = virtical[10][0];

			horizontal[2][9] = virtical[9][2];
			horizontal[2][10] = virtical[9][1];
			horizontal[2][11] = virtical[9][0];
		}
		else {
			virtical[3][0] = horizontal[0][3];
			virtical[3][1] = horizontal[0][4];
			virtical[3][2] = horizontal[0][5];

			virtical[4][0] = horizontal[1][3];
			virtical[4][1] = horizontal[1][4];
			virtical[4][2] = horizontal[1][5];

			virtical[5][0] = horizontal[2][3];
			virtical[5][1] = horizontal[2][4];
			virtical[5][2] = horizontal[2][5];


			virtical[11][0] = horizontal[0][11];
			virtical[11][1] = horizontal[0][10];
			virtical[11][2] = horizontal[0][9];

			virtical[10][0] = horizontal[1][11];
			virtical[10][1] = horizontal[1][10];
			virtical[10][2] = horizontal[1][9];

			virtical[9][0] = horizontal[2][11];
			virtical[9][1] = horizontal[2][10];
			virtical[9][2] = horizontal[2][9];
		}
	}

	void faceTurn(vector<vector<char>::iterator> begin, char direction) {
		vector<vector<char>> temp(3, vector<char>(3));
		if (direction == '+') {
			for (int i = 0; i < 3; ++i) {
				for (int j = 0; j < 3; ++j) {
					temp[j][3-i-1] = (*(begin[i] + j));
				}
			}
		}
		else {
			for (int i = 0; i < 3; ++i) {
				for (int j = 0; j < 3; ++j) {
					temp[3-j-1][i] = (*(begin[i] + j));
				}
			}
		}
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				(*(begin[i] + j)) = temp[i][j];
			}
		}
	}

public:
	cube() {
		virtical = {
			//U
			{'w','w','w'},
			{'w','w','w'},
			{'w','w','w'},
			//F
			{'r','r','r'},
			{'r','r','r'},
			{'r','r','r'},
			//D
			{'y','y','y'},
			{'y','y','y'},
			{'y','y','y'},
			//B
			{'o','o','o'},
			{'o','o','o'},
			{'o','o','o'}
		};
		horizontal = {
			//L			  //F		   //R			//B
			{'g','g','g', 'r','r','r', 'b','b','b', 'o','o','o'},
			{'g','g','g', 'r','r','r', 'b','b','b', 'o','o','o'},
			{'g','g','g', 'r','r','r', 'b','b','b', 'o','o','o'},
		};
		//virtical = {
		//	//U
		//	{'1','2','3'},
		//	{'4','5','6'},
		//	{'7','8','9'},
		//	//F
		//	{'1','2','3'},
		//	{'4','5','6'},
		//	{'7','8','9'},
		//	//D
		//	{'1','2','3'},
		//	{'4','5','6'},
		//	{'7','8','9'},
		//	//B
		//	{'1','2','3'},
		//	{'4','5','6'},
		//	{'7','8','9'}
		//};
		//horizontal = {
		//	//L			  //F		   //R			//B
		//	{'1','2','3', '1','2','3', '1','2','3', '9','8','7'},
		//	{'4','5','6', '4','5','6', '4','5','6', '6','5','4'},
		//	{'7','8','9', '7','8','9', '7','8','9', '3','2','1'},
		//};
	}

	void turn(char face, char direction) {
		switch (face) {
		case 'U':
			faceTurn({ virtical[0].begin(), virtical[1].begin(), virtical[2].begin() }, direction);
			if (direction == '+') {
				char temp[3] = { horizontal[0][0], horizontal[0][1], horizontal[0][2] };
				horizontal[0].erase(horizontal[0].begin(), horizontal[0].begin() + 3);
				horizontal[0].push_back(temp[0]);
				horizontal[0].push_back(temp[1]);
				horizontal[0].push_back(temp[2]);
			}
			else {
				char temp[3] = { horizontal[0][9], horizontal[0][10], horizontal[0][11] };
				horizontal[0].erase(horizontal[0].begin() + 9, horizontal[0].end());
				horizontal[0].emplace(horizontal[0].begin(), temp[2]);
				horizontal[0].emplace(horizontal[0].begin(), temp[1]);
				horizontal[0].emplace(horizontal[0].begin(), temp[0]);
			}
			//true : sync virt to hori, false: sync hori to virt 
			sync(false);
			break;
		case 'D':
			faceTurn({ virtical[6].begin(), virtical[7].begin(), virtical[8].begin() }, direction);
			if (direction == '+') {
				char temp[3] = { horizontal[2][9], horizontal[2][10], horizontal[2][11] };
				horizontal[2].erase(horizontal[2].begin() + 9, horizontal[2].end());
				horizontal[2].emplace(horizontal[2].begin(), temp[2]);
				horizontal[2].emplace(horizontal[2].begin(), temp[1]);
				horizontal[2].emplace(horizontal[2].begin(), temp[0]);
			}
			else {
				char temp[3] = { horizontal[2][0], horizontal[2][1], horizontal[2][2] };
				horizontal[2].erase(horizontal[2].begin(), horizontal[2].begin() + 3);
				horizontal[2].push_back(temp[0]);
				horizontal[2].push_back(temp[1]);
				horizontal[2].push_back(temp[2]);
			}
			sync(false);
			break;
		case 'F':
			faceTurn({ virtical[3].begin(), virtical[4].begin(), virtical[5].begin() }, direction);
			faceTurn({ horizontal[0].begin() + 3, horizontal[1].begin() + 3,horizontal[2].begin() + 3 }, direction);
			if (direction == '+') {
				vector<char> temp = virtical[2];
				virtical[2][0] = horizontal[2][2];
				virtical[2][1] = horizontal[1][2];
				virtical[2][2] = horizontal[0][2];

				horizontal[2][2] = virtical[6][2];
				horizontal[1][2] = virtical[6][1];
				horizontal[0][2] = virtical[6][0];

				virtical[6][2] = horizontal[0][6];
				virtical[6][1] = horizontal[1][6];
				virtical[6][0] = horizontal[2][6];

				horizontal[0][6] = temp[0];
				horizontal[1][6] = temp[1];
				horizontal[2][6] = temp[2];
			}
			else {
				vector<char> temp = virtical[2];
				virtical[2][0] = horizontal[0][6];
				virtical[2][1] = horizontal[1][6];
				virtical[2][2] = horizontal[2][6];

				horizontal[0][6] = virtical[6][2];
				horizontal[1][6] = virtical[6][1];
				horizontal[2][6] = virtical[6][0];

				virtical[6][2] = horizontal[2][2];
				virtical[6][1] = horizontal[1][2];
				virtical[6][0] = horizontal[0][2];

				horizontal[2][2] = temp[0];
				horizontal[1][2] = temp[1];
				horizontal[0][2] = temp[2];
			}
			break;
		case 'B':
			faceTurn({ virtical[9].begin(), virtical[10].begin(), virtical[11].begin() }, direction);
			faceTurn({ horizontal[0].begin() + 9, horizontal[1].begin() + 9,horizontal[2].begin() + 9 }, direction);
			if (direction == '+') {
				vector<char> temp = virtical[0];
				virtical[0][0] = horizontal[0][8];
				virtical[0][1] = horizontal[1][8];
				virtical[0][2] = horizontal[2][8];

				horizontal[0][8] = virtical[8][2];
				horizontal[1][8] = virtical[8][1];
				horizontal[2][8] = virtical[8][0];

				virtical[8][2] = horizontal[2][0];
				virtical[8][1] = horizontal[1][0];
				virtical[8][0] = horizontal[0][0];

				horizontal[2][0] = temp[0];
				horizontal[1][0] = temp[1];
				horizontal[0][0] = temp[2];
			}
			else {
				vector<char> temp = virtical[0];
				virtical[0][0] = horizontal[2][0];
				virtical[0][1] = horizontal[1][0];
				virtical[0][2] = horizontal[0][0];

				horizontal[2][0] = virtical[8][2];
				horizontal[1][0] = virtical[8][1];
				horizontal[0][0] = virtical[8][0];

				virtical[8][2] = horizontal[0][8];
				virtical[8][1] = horizontal[1][8];
				virtical[8][0] = horizontal[2][8];

				horizontal[0][8] = temp[0];
				horizontal[1][8] = temp[1];
				horizontal[2][8] = temp[2];
			}
			break;
		case 'L':
			faceTurn({ horizontal[0].begin(), horizontal[1].begin(), horizontal[2].begin() }, direction);
			if (direction == '+') {
				char temp[3] = { virtical[9][0], virtical[10][0], virtical[11][0] };
				for (int i = virtical.size() - 1; i >= 3; --i) {
					virtical[i][0] = virtical[i - 3][0];
				}
				virtical[0][0] = temp[0];
				virtical[1][0] = temp[1];
				virtical[2][0] = temp[2];
			}
			else {
				char temp[3] = { virtical[0][0], virtical[1][0], virtical[2][0] };
				for (int i = 3; i < virtical.size(); ++i) {
					virtical[i - 3][0] = virtical[i][0];
				}
				virtical[9][0] = temp[0];
				virtical[10][0] = temp[1];
				virtical[11][0] = temp[2];
			}
			sync(true);
			break;
		case 'R':
			faceTurn({ horizontal[0].begin() + 6, horizontal[1].begin() + 6, horizontal[2].begin() + 6 }, direction);
			if (direction == '+') {
				char temp[3] = { virtical[0][2], virtical[1][2], virtical[2][2] };
				for (int i = 3; i < virtical.size(); ++i) {
					virtical[i - 3][2] = virtical[i][2];
				}
				virtical[9][2] = temp[0];
				virtical[10][2] = temp[1];
				virtical[11][2] = temp[2];
			}
			else {
				char temp[3] = { virtical[9][2], virtical[10][2], virtical[11][2] };
				for (int i = virtical.size() - 1; i >= 3; --i) {
					virtical[i][2] = virtical[i - 3][2];
				}
				virtical[0][2] = temp[0];
				virtical[1][2] = temp[1];
				virtical[2][2] = temp[2];
			}
			sync(true);
			break;
		}
	}

	void printU() {
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				cout << virtical[i][j];
			}
			cout << "\n";
		}
	}

	void print() {
		for (int i = 0; i < 3; ++i) {
			for(int j=0;j<3;++j) cout << setw(2) << " ";
			for (int j = 0; j < 3; ++j) cout << setw(2) << virtical[i][j];
			cout << "\n";
		}
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 9; ++j) {
				cout << setw(2) << horizontal[i][j];
			}
			cout << "\n";
		}
		for (int i = 6; i < 12; ++i) {
			for (int j = 0; j < 3; ++j) cout << setw(2) << " ";
			for (int j = 0; j < 3; ++j) cout << setw(2) << virtical[i][j];
			cout << "\n";
		}

		cout << "virtical\n";
		for (int i = 0; i < virtical.size(); ++i) {
			for (int j = 0; j < virtical[i].size(); ++j) {
				cout << setw(2) << virtical[i][j];
			}
			cout << "\n";
		}
		cout << "horizontal\n";
		for (int i = 0; i < horizontal.size(); ++i) {
			for (int j = 0; j < horizontal[i].size(); ++j) {
				cout << setw(2) << horizontal[i][j];
			}
			cout << "\n";
		}
	}
};




int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int tc;
	cin >> tc;
	for (int i = 0; i < tc; ++i) {
		int n;
		string ins;
		cin >> n;
		cube c;
		for (int i = 0; i < n; ++i) {
			cin >> ins;
			c.turn(ins[0], ins[1]);
		}
		//c.print();
		c.printU();
	}
	return 0;
}