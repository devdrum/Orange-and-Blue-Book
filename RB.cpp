#include <iostream>

using namespace std;

struct Node {
    int mile;
    Node* parent;
    Node* left;
    Node* right;
    int color; // 0 if black, 1 if red
};

class RBTree {
private:
    Node* redBlackRoot;

    Node* grandparent(Node* node) {
        if (node != nullptr && node->parent != nullptr)
            return node->parent->parent;
        return nullptr;
    }

    Node* uncle(Node* node) {
        Node* g = grandparent(node);
        if (g == nullptr)
            return nullptr;
        if (node->parent == g->left)
            return g->right;
        else
            return g->left;
    }

    void rotateLeft(Node* node) {
        Node* right_child = node->right;
        node->right = right_child->left;

        if (right_child->left != nullptr)
            right_child->left->parent = node;

        right_child->parent = node->parent;

        if (node->parent == nullptr)
            redBlackRoot = right_child;
        else if (node == node->parent->left)
            node->parent->left = right_child;
        else
            node->parent->right = right_child;

        right_child->left = node;
        node->parent = right_child;
    }

    void rotateRight(Node* node) {
        Node* left_child = node->left;
        node->left = left_child->right;

        if (left_child->right != nullptr)
            left_child->right->parent = node;

        left_child->parent = node->parent;

        if (node->parent == nullptr)
            redBlackRoot = left_child;
        else if (node == node->parent->left)
            node->parent->left = left_child;
        else
            node->parent->right = left_child;

        left_child->right = node;
        node->parent = left_child;
    }

    void fixViolation(Node* node) {
        while (node != redBlackRoot && node->parent->color == 1) {
            Node* p = node->parent;
            Node* g = grandparent(node);
            Node* u = uncle(node);

            if (u != nullptr && u->color == 1) {
                p->color = 0;
                u->color = 0;
                g->color = 1;
                node = g;
            } else {
                if (p == g->left) {
                    if (node == p->right) {
                        rotateLeft(p);
                        node = p;
                        p = node->parent;
                    }
                    rotateRight(g);
                    swap(p->color, g->color);
                    node = p;
                } else {
                    if (node == p->left) {
                        rotateRight(p);
                        node = p;
                        p = node->parent;
                    }
                    rotateLeft(g);
                    swap(p->color, g->color);
                    node = p;
                }
            }
        }
        redBlackRoot->color = 0;
    }

    void printTreeHelper(Node* node) {
        if (node == nullptr){
            return;
        }

        printTreeHelper(node->left);
        cout << node->mile << " (" << (node->color == 0 ? "Black" : "Red") << ") ";
        printTreeHelper(node->right);
    }

    bool SearchHelper(Node* node, int data) {
        if (node == nullptr){
          return false;
        }
        if(node->mile == data){
          return true;
        }
        else if (data < node->mile){
          return SearchHelper(node->left, data);
        }
        else if(data > node->mile){
          return SearchHelper(node->right, data);
        }
        else{
          return false;
        } 
    }

public:
    RBTree() { // default constructor sets up the redBlackRoot to a null pointer
      redBlackRoot = nullptr;
    }

    void insert(int data) {
        Node* new_node = new Node();
        new_node->mile = data;
        new_node->color = 1; // New nodes are always red
        new_node->parent = nullptr;
        new_node->left = nullptr;
        new_node->right = nullptr;

        if (redBlackRoot == nullptr) {
            redBlackRoot = new_node;
            redBlackRoot->color = 0; // redBlackRoot node should be black
            return;
        }

        Node* current = redBlackRoot;
        Node* parent = nullptr;
        while (current != nullptr) {
            parent = current;
            if (data < current->mile)
                current = current->left;
            else
                current = current->right;
        }

        if (data < parent->mile){
          parent->left = new_node;
        }
        else{
          parent->right = new_node;
        }

        new_node->parent = parent;
        fixViolation(new_node);
    }

    void printTree() {
        printTreeHelper(redBlackRoot);
    }

    bool Search(int data){
      return SearchHelper(redBlackRoot, data);
    }
};

int main() {
    RBTree tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(60);
    tree.insert(70);

    cout << "Printed Red-Black Tree: ";
    tree.printTree();
    cout << endl;

    return 0;
}
