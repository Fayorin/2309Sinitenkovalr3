#include <iostream>
#include <queue>
#include<fstream>
#include<chrono>
enum Color {
   black,
   red
};
struct Node {
    int key;
    Color color;
    Node* left;
    Node* right;
    Node* parent;

    Node(int value) {
        key = value;
        color = red;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
    Node()
    {
        key = 0;
        color = black;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
   
};


class BinaryTree {
public:
    Node* root;
    Node* leaf;
    BinaryTree() {
        leaf = new Node();
        root = leaf ;
        
    }
    ~BinaryTree()
    {
        //delete_tree(root);
    }

   /* void delete_tree(Node* cur)
    {
        if (cur)
        {
            delete_tree(cur->left);
            delete_tree(cur->right);
            delete cur;
        }
    }*/
    void Insert(int value);
    Node* searchKey(Node* z, int key);
    void LeftRotate(Node* z);
    void DeleteFix(Node* x);
    void Transplant(Node* u, Node* v);
    void RightRotate(Node* z);
    void InsertFix(Node* z);
    void Delete(int key);
    Node* successor(Node* z);
    Node* minimum(Node* z);
    Node* maximum(Node* z);
    Node* predecessor(Node* z);
    void PrintPostOrder(Node* root);
    void PrintInOrder(Node* root);
    void PrintDepth(Node* root);
    void PrintPreOrder(Node* root);
    void print(int number);
    int max(int a, int b) {
        if (a > b) return a;
        else return b;
    }
    int tree_height(Node* root) {
        int right_height;
        int left_height;
        if (root == leaf)
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
void BinaryTree:: LeftRotate(Node* z)
{
    Node* y = z->right;
    z->right = y->left;
    if (y->left != leaf) {
        y->left->parent = z;
    }
    y->parent = z->parent;
    if (z->parent == nullptr) {
        this->root = y;
    }
    else if (z == z->parent->left) {
        z->parent->left = y;
    }
    else {
        z->parent->right = y;
    }
    y->left = z;
    z->parent = y;
}
void BinaryTree::RightRotate(Node* z){
Node* y = z->left;
z->left = y->right;
if (y->right != leaf) {
    y->right->parent = z;
}
y->parent = z->parent;
if (z->parent == nullptr) {
    this->root = y;
}
else if (z == z->parent->right) {
    z->parent->right = y;
}
else {
    z->parent->left = y;
}
y->right = z;
z->parent = y;
  }
void BinaryTree:: InsertFix(Node* k) {
    Node* u;
    while (k->parent->color == red) {
        if (k->parent == k->parent->parent->right) {
            u = k->parent->parent->left;
            if (u->color == red) {
                u->color = black;
                k->parent->color = black;
                k->parent->parent->color = red;
                k = k->parent->parent;
            }
            else {
                if (k == k->parent->left) {
                    k = k->parent;
                    RightRotate(k);
                }
                k->parent->color = black;
                k->parent->parent->color = red;
                LeftRotate(k->parent->parent);
            }
        }
        else {
            u = k->parent->parent->right;

            if (u->color == red) {
                u->color = black;
                k->parent->color = black;
                k->parent->parent->color = red;
                k = k->parent->parent;
            }
            else {
                if (k == k->parent->right) {
                    k = k->parent;
                    LeftRotate(k);
                }
                k->parent->color = black;
                k->parent->parent->color = red;
                RightRotate(k->parent->parent);
            }
        }
        if (k == root) {
            break;
        }
    }
    root->color = black;
}
void BinaryTree::Insert(int value) {
        Node* node = new Node;
        node->parent = nullptr;
        node->key = value;
        node->left = leaf;
        node->right = leaf;
        node->color = red;

        Node* y = nullptr;
        Node* x = this->root;

        while (x != leaf) {
            y = x;
            if (node->key < x->key) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }

        node->parent = y;
        if (y == nullptr) {
            root = node;
        }
        else if (node->key < y->key) {
            y->left = node;
        }
        else {
            y->right = node;
        }

        if (node->parent == nullptr) {
            node->color = black;
            return;
        }

        if (node->parent->parent == nullptr) {
            return;
        }
    InsertFix(node);
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
void BinaryTree::Transplant(Node* u, Node* v)
{
    if (u->parent == leaf)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else u->parent->right = v;
    v->parent = u->parent;
}

void BinaryTree::DeleteFix(Node* x)
{
    Node* w;
    while (x != root && x->color == black)
    {
        if (x == x->parent->left) {
            w = x->parent->right;
            if (w->color == red)
            {
                w->color = black;
                x->parent->color = red;
                LeftRotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == black && w->right->color == black) {
                w->color = red;
                x = x->parent;
            }
            else if (w->right->color == black)
            {
                w->left->color = black;
                w->color = red;
                RightRotate(w);
                w = x->parent->right;
            }
            w->color = x->parent->color;
            x->parent->color = black;
            w->right->color = black;
            LeftRotate(x->parent);
            x = root;
        }
        else {
            w = x->parent->left;
            if (w->color == red)
            {
                w->color = black;
                x->parent->color = red;
                RightRotate(x->parent);
                w = x->parent->left;
            }
            if (w->right->color == black && w->left->color == black)
            {
                w->color = red;
                x = x->parent;
            }
            else if (w->left->color == black)
            {
                w->right->color = black;
                w->color = red;
                LeftRotate(w);
                w = x->parent->left;
            }
            w->color = x->parent->color;
            x->parent->color = black;
            w->left->color = black;
            RightRotate(x->parent);
            x = root;
        }
    }
    x->color = black;
}
void  BinaryTree::Delete(int value) {
    Node* z = root;
    z = searchKey(z, value);
    // возвращаем, если ключ не найден в дереве
    if (z == nullptr)
        return;
    Node* y = z;
    Node* x;
    Color y_original_color = y->color;
    if (z->left == leaf)
    {
        x = z->right;
        Transplant(z, z->right);
    }
    else if (z->right == leaf)
    {
        x = z->left;
        Transplant(z, z->left);
    }
    else { 
        y = minimum(z->right); 
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z)
            x->parent = y;
        else Transplant(y, y->right);
        y->right = z->right;
        y->right->parent = y;
        Transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;

    }
    if (y_original_color == black)
        DeleteFix(x);
}

void BinaryTree::PrintDepth(Node* root) {
    std::queue<Node*> q;
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
void BinaryTree::PrintPreOrder(Node* root) {//Прямой обход
    if (root) {
        std::cout << "%d " << root->key;
        PrintPreOrder(root->left);
        PrintPreOrder(root->right);
    }
}
void BinaryTree:: PrintInOrder(Node* root) {//Симметричный обход
    if (root) {
        PrintInOrder(root->left);
        std::cout << "%d " << root->key;
        PrintInOrder(root->right);
    }
}
void BinaryTree:: PrintPostOrder(Node* root) { // Обратный обход
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
    std::ifstream f;
    const int N = 10000;
    f.open("test.txt");
    BinaryTree T;
    int g;
    auto begin = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    for (int i = 0; i < N; i++)
    {

        f >> g;
        T.Insert(g);
    }
    ////std:: cout<<T.tree_height(T.root);
   // Node* d = new Node(45158);
    T.Insert(45158);
    std::fstream s;
    s.open("Delete.txt", std::ios::app);
   // s<< T.tree_height(T.root)<<std::endl;
    begin = std::chrono::steady_clock::now();
    T.Delete(45158);
    end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << ' ';
    s << N << ' ' << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << std::endl;
    f.close();
    return;
}