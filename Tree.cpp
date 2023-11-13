#include <iostream>
#include <queue>
#include<fstream>
#include<chrono>
#include <chrono>
#include <algorithm>
#include <cmath>
struct Node {
    int key;
    Node* left;
    Node* right;
    Node* parent;

    Node(int value) {
       key = value;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};

class BinaryTree {
public:
    Node* root;

    BinaryTree() {

        root= nullptr;
    }
    ~BinaryTree()
    {
        delete_tree(root);
    }

    void delete_tree(Node* cur)
    {
        if (cur)
        {
            delete_tree(cur->left);
            delete_tree(cur->right);
            delete cur;
        }
    }
   void Insert(Node* z);
   void PrintDepth(Node* root);
   Node* searchKey(Node* z, int key);
   void Delete(Node* root, int key);
   Node* successor(Node* z);
   Node* minimum(Node* z);
   Node* maximum(Node* z);
   Node* predecessor(Node* z);
   void printInOrder(Node* node);
   void print(int number);
   int max(int a, int b) {
       if (a > b) return a;
       else return b;
   }
   int tree_height(Node* root) {
       int right_height;
       int left_height;
       if (root == NULL)
           return 0;
       else {
           left_height = tree_height(root->left);
           right_height = tree_height(root->right);

           return max(left_height, right_height) + 1;
       }
   }
};
Node* BinaryTree::searchKey(Node* z, int value) {
    if (z == NULL || value == z->key)
        return z;
    if (value < z->key)
        return searchKey(z->left, value);
        else return searchKey(z->right, value);
}
void BinaryTree:: Insert(Node* z) {

    Node* y = nullptr;
    Node* x = root;
    while (x != nullptr) {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == nullptr)
        root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;
}
Node* BinaryTree::minimum(Node* z) {
    Node* temp = z;
    while (temp->left != NULL)
        temp = temp->left;
    return temp;
}
Node* BinaryTree::maximum(Node* z) {
    Node* temp = z;
    while (temp->right != NULL)
        temp = temp->right;
    return temp;
}
Node* BinaryTree::successor(Node* z)
{
    Node* y;
    if (z->right != NULL)
        return minimum(z->right);
    y = z->parent;
    while (y != NULL && z == y->right)
    {
        z = y;
        y = y->parent;
    }
    return y;
}
Node* BinaryTree::predecessor(Node* z)
{
    Node* y;
    if (z->left != NULL)
        return maximum(z->left);
    y = z->parent;
    while (y != NULL && z == y->left)
    {
        z = y;
        y = y->parent;
    }
    return y;
}
void  BinaryTree::Delete(Node* root, int value) {
    Node* z = root;

    // поиск ключа и установка его родительского указателя
    z=searchKey(z, value);
    // возвращаем, если ключ не найден в дереве
    if (z == nullptr)
        return;

    Node* y;
    if (z->left == nullptr || z->right == nullptr) {
        y = z;
    }
    else {
        y = successor(z);
    }
    Node* x;
    if (y->left != nullptr) {
        x = y->left;
    }
    else {
        x = y->right;
    }
    if (x != nullptr) {
        x->parent = y->parent;
    }
    if (y->parent == nullptr) {
        root = x;
    }
    else {
        if (y == y->parent->left) {
            y->parent->left = x;
        }
        else {
            y->parent->right = x;
        }
    }
    if (y != z) {
        z->key = y->key;
    }
    delete y;
}

void BinaryTree:: PrintDepth(Node* root) {
   std:: queue<Node*> q;
    q.push(root);
    while (q.empty() == false) {
        Node* node = q.front();
        std::cout << node->key << " ";
        q.pop();
        if (node->left != NULL)
            q.push(node->left);
        if (node->right != NULL)
            q.push(node->right);
    }
}
void PrintPreOrder(Node* root) {//Прямой обход
    if (root) {
        std::cout<<"%d "<<root->key;
        PrintPreOrder(root->left);
        PrintPreOrder(root->right);
    }
}
void PrintInOrder(Node* root) {//Симметричный обход
    if (root) {
        PrintInOrder(root->left);
        std::cout << "%d " << root->key;
        PrintInOrder(root->right);
    }
}
void PrintPostOrder(Node* root) { // Обратный обход
    if (root) {
        PrintPostOrder(root->left);
        PrintPostOrder(root->right);
        std::cout << "%d " << root->key;
    }
}
void BinaryTree::print(int number) {
    switch (number)
    {
    case 1: PrintInOrder(root);
    case 2: PrintPostOrder(root);
    case 3: PrintPreOrder(root);
    case 4: PrintDepth(root);
    }
}

void main() {
    std:: ifstream f;
    const int N = 100000;
    f.open("test.txt");
    BinaryTree T;
    int g;
    auto begin = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
   for (int i = 0; i < N; i++)
    {

       f >> g;
        Node* z = new Node(g);
        T.Insert(z);
    }
  //std:: cout<<T.tree_height(T.root);
  Node* d = new Node(45158);
  T.Insert(d);
  std::fstream s;
  s.open("Delete.txt",std::ios::app);
  begin = std::chrono::steady_clock::now();
  T.Delete(T.root, 45158);
    end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << ' ';
   s << N<<' '<< std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << std::endl;
    f.close();
    return;
}