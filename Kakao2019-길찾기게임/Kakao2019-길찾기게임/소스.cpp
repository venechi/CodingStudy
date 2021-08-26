#include <string>
#include <vector>
#include <queue>

using namespace std;

class node {
public:
    int x;
    int y;
    int num;
    node* left;
    node* right;
    node(int x, int y, int num) {
        this->x = x;
        this->y = y;
        this->num = num;
        left = NULL;
        right = NULL;
    }
    ~node() {
        if (left != NULL) delete left;
        if (right != NULL) delete right;
    }
};

class tree {
private:
    node* head;
    vector<int> temp;
public:
    tree() {
        head = NULL;
    }
    ~tree() {
        if (head != NULL) delete head;
    }
    void addNode(int x, int y, int num, node* cur) {
        if (cur->x < x) {
            if (cur->right != NULL) addNode(x, y, num, cur->right);
            else cur->right = new node(x, y, num);
        }
        else {
            if (cur->left != NULL) addNode(x, y, num, cur->left);
            else cur->left = new node(x, y, num);
        }
    }
    void add(int x, int y, int num) {
        if (head == NULL) head = new node(x, y, num);
        else addNode(x, y, num, head);
    }
    void pre(node* cur) {
        temp.push_back(cur->num);
        if (cur->left != NULL) pre(cur->left);
        if (cur->right != NULL) pre(cur->right);
    }
    vector<int> preOrder() {
        temp.clear();
        pre(head);
        return temp;
    }
    void post(node* cur) {
        if (cur->left != NULL) post(cur->left);
        if (cur->right != NULL) post(cur->right);
        temp.push_back(cur->num);
    }
    vector<int> postOrder() {
        temp.clear();
        post(head);
        return temp;
    }
};

class cmp {
public:
    bool operator()(const vector<int>& a, const vector<int>& b) {
        return a[1] < b[1];
    }
};

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    priority_queue<vector<int>, vector<vector<int>>, cmp> pq;
    for (int i = 0; i < nodeinfo.size(); ++i) {
        nodeinfo[i].push_back(i + 1);
        pq.push(nodeinfo[i]);
    }
    tree t;
    while(!pq.empty()) {
        vector<int> cur = pq.top(); pq.pop();
        t.add(cur[0], cur[1], cur[2]);
    }
    return { t.preOrder(), t.postOrder() };
}

int main(void) {
    auto ans = solution({ {5,3},{11,5},{13,3},{3,5},{6,1},{1,3},{8,6},{7,2},{2,2} });
    //ans should be : [[7,4,6,9,1,8,5,2,3],[9,6,5,8,1,4,3,2,7]]
}