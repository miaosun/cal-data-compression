//GenHuffmanCode.cpp

#include "MinPriorityQueue.cpp"

using namespace std;

class Node {
public:
    string name;
    int f;
    Node *left, *right;
    string code;

    Node() {
        name = "";
        code = "";
        f = INT_MAX;
        left = right = 0;
    }

    Node(int ff, string n = "") {
        name = n;
        f = ff;
        left = right = 0;
        code = "";
    }

    ~Node() {
        delete left;
        delete right;
    }

    bool operator<(Node &param) {
        return f < param.f;
    }

    bool operator>(Node &param) {
        return f > param.f;
    }

    bool operator==(Node &param) {
        return f == param.f;
    }

    static void display(Node*, bool);
    static void encode(Node*);

    friend ostream& operator <<(ostream&, Node&);
};

void Node::display(Node* node, bool leavesOnly = 1) {
    if (node == 0) {
        return;
    }
    display(node->left, leavesOnly);
    if (leavesOnly) {
        if (node->left == 0 && node->right == 0) {
            cout << *node << ", ";
        }
    } else {
        cout << *node << ", ";
    }
    display(node->right, leavesOnly);
}

void Node::encode(Node* node) {
    if (node == 0) {
        return;
    }
    if (node->left != 0) {
        node->left->code = node->code + "0";
    }
    if (node->right != 0) {
        node->right->code = node->code + "1";
    }
    encode(node->left);
    encode(node->right);
}

ostream& operator <<(ostream &out, Node &node) {
    out << node.name << "(" << node.f << ")" << ":" << node.code;
    return out;
}

void HuffmanCode(int *freqs, string* names, int length) {
    Q<Node> *q = new Q<Node > (length);
    for (int i = 0; i < length; i++) {
        q->insert(new Node(freqs[i], names[i]));
    }

    for (int i = 0; i < length - 1; i++) {
        Node *x = q->extractMin();
        Node *y = q->extractMin();
        Node *z = new Node(x->f + y->f, x->name + y->name);
        z->left = x;
        z->right = y;
        q->insert(z);
    }
    Node *root = q->extractMin();
    cout << "Full tree (inorder):\n";
    Node::display(root, 0);
    cout << "\nHuffman Code:\n";
    Node::encode(root);
    Node::display(root);
}

int main(int argc, char** argv) {
    int freqs[] = {45, 13, 12, 16, 9, 5};
    string names[] = {"a", "b", "c", "d", "e", "f"};
    HuffmanCode(freqs, names, 6);
    return 0;
}

/*
Output

Full tree (inorder):
a(45):, acbfed(100):, c(12):, cb(25):, b(13):, cbfed(55):, f(5):, fe(14):, e(9):, fed(30):, d(16):, 
Huffman Code:
a(45):0, c(12):100, b(13):101, f(5):1100, e(9):1101, d(16):111,

*/