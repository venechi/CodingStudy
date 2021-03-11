#pragma once
#include <random>
#include <utility>

using namespace std;

template <class T>
class node {
private:
	void calSize() { size = left->size + right->size + 1; }
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