#include <iostream>
#include <vector>
#include <random>
#include <utility>

using namespace std;

vector<int> moved(50000);

//이진탐색트리(트립) 구현
//가장 간단한 이진탐색트리는
//입력의 형태에 따라, 최악의 경우 연결리스트가 되는 데 반해
//트립은 랜덤함수와 우선순위의 제약조건 추가로 인해, 최악의 경우가 될 확률을 극단적으로 줄임
template <class T>
class node {
private:
	void calSize() { size = (left != NULL ? left->size : 0) + (right != NULL ? right->size : 0) + 1; }
public:
	node<T>* left;
	node<T>* right;
	int size;
	int priority;
	T key;
	node(const T& key) : key(key), left(NULL), right(NULL), size(1), priority(rand()) {}
	void setLeft(node<T>* newLeft) { left = newLeft; calSize(); }
	void setRight(node<T>* newRight) { right = newRight; calSize(); }
};

template <class T>
class binary_search_tree {
private:
	node<T>* root;
	void terminateTree(node<T>* root) {
		if (root->left != NULL) terminateTree(root->left);
		if (root->right != NULL) terminateTree(root->right);
		delete root;
	}

	pair<node<T>*, node<T>*> splitNode(node<T>* root, const T& value) {
		if (root == NULL) return { NULL, NULL };
		if (root->key < value) {
			pair<node<T>*, node<T>*> splitted = splitNode(root->right, value);
			root->setRight(splitted.first);
			return { root, splitted.second };
		}
		else {
			pair<node<T>*, node<T>*> splitted = splitNode(root->left, value);
			root->setRight(splitted.second);
			return { root, splitted.first };
		}
	}

	node<T>* insertNewNode(node<T>* root, node<T>* newNode) {
		if (root == NULL) return newNode;
		else {
			if (root->priority > newNode->priority) {
				if (root->key < newNode->key)
					root->setRight(insertNewNode(root->right, newNode));
				else
					root->setLeft(insertNewNode(root->left, newNode));
				return root;
			}
			else {
				pair<node<T>*, node<T>*> splitted = splitNode(root, newNode->key);
				newNode->setLeft(splitted.first);
				newNode->setRight(splitted.second);
				return newNode;
			}
		}
	}

	//max(a) < min(b)일 경우 사용
	node<T>* merge(node<T>* a, node<T>* b) {
		if (a == NULL) return b;
		if (b == NULL) return a;
		if (a->priority < b->priority) {
			b->setLeft(merge(a, b->left));
			return b;
		}
		else {
			a->setRight(merge(a->right, b));
			return a;
		}
	}

	node<T>* deleteNode(node<T>* root, const T& value) {
		if (root->key == value) {
			node<T>* ret = merge(root->left, root->right);
			delete root;
			return ret;
		}
		else {
			if (root->key > value)
				root->setLeft(deleteNode(root->left, value));
			else
				root->setRight(deleteNode(root->right, value));
			return root;
		}
	}

	T kthValue(node<T>* root, int k) {
		int leftSize = 0;
		if (root->left != NULL) leftSize = root->left->size;
		if (leftSize + 1 == k) return root->key;
		if (leftSize + 1 > k) return kthValue(root->left, k);
		else return kthValue(root->right, k - leftSize - 1);
	}
public:
	binary_search_tree() {
		root = NULL;
	}

	~binary_search_tree() {
		if (root != NULL) terminateTree(root);
	}

	void insertValue(const T& value) {
		root = insertNewNode(root, new node<T>(value));
	}

	void deleteValue(const T& value) {
		root = deleteNode(root, value);
	}

	T kth(int k) {
		if (root != NULL) {
			if (root->size < k) return kthValue(root, root->size);
			return kthValue(root, k);
		}
		return 0;
	}
};

//문제는 쉬운데 트립 구현이 어렵다
//처음이라 그런가..
void recoverArray(int n) {
	binary_search_tree<int> original;
	int pos;
	for (int i = 0; i < n; ++i) original.insertValue(i + 1);
	while (n--) {
		pos = n - moved[n];
		moved[n] = original.kth(pos + 1);
		original.deleteValue(moved[n]);
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	int testcase, n;
	cin >> testcase;
	do {
		cin >> n;
		for (int i = 0; i < n; ++i) cin >> moved[i];
		recoverArray(n);
		for (int i = 0; i < n; ++i) cout << moved[i] << " ";
		cout << "\n";
	} while (--testcase);
	return 0;
}