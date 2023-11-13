#include <iostream>
#include <queue>
#include<chrono>
#include<fstream>
struct Node {
    int key;
    int height;
    Node* left;
    Node* right;
    Node* parent;

    Node(int value) {
        key = value;
        height = 1;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};

class BinaryTree {
private:
    

public:
    Node* root;
    BinaryTree() {

        root = nullptr;
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
    int max(int a, int b) {
        if (a > b) return a;
        else return b;
    }
    int height(Node* z) {
        if (z == NULL)
            return 0;
        return z->height;
    }

    Node* rightRotate(Node* z) {
        Node* x = z->left;
        Node* y = x->right;
        x->right = z;
        z->left = y;
        z->height = max(height(z->left),
            height(z->right)) +
            1;
        x->height = max(height(x->left),
            height(x->right)) +
            1;
        return x;
    }

    Node* leftRotate(Node* z) {
        Node* y = z->right;
        Node* x = y->left;
        y->left = z;
        z->right = x;
        z->height = max(height(z->left),
            height(z->right)) +
            1;
        y->height = max(height(y->left),
            height(y->right)) +
            1;
        return y;
    }
    int getBalance(Node* N)
    {
        if (N == NULL)
            return 0;
        return height(N->left) - height(N->right);
    }
    Node* Insert(Node* node, int key)
    {
        if (node == NULL)
            return (new Node(key));
        if (key < node->key)
            node->left = Insert(node->left, key);
        else if (key > node->key)
            node->right = Insert(node->right, key);
        else
            return node;

 
        node->height = 1 + max(height(node->left),
            height(node->right));

        int balance = getBalance(node);
 
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        if (balance < -1 && key > node->right->key)
            return leftRotate(node);
        if (balance > 1 && key > node->left->key)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        } 
        if (balance < -1 && key < node->right->key)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }


        return node;
    }
    Node* deleteNode(Node* root, int key) {
        if (root == NULL)
            return root;
        if (key < root->key)
            root->left = deleteNode(root->left, key);
        else if (key > root->key)
            root->right = deleteNode(root->right, key);
        else {
            if ((root->left == NULL) ||
                (root->right == NULL)) {
                Node* temp = root->left ? root->left : root->right;
                if (temp == NULL) {
                    temp = root;
                    root = NULL;
                }
                else
                    *root = *temp;
                free(temp);
            }
            else {
                Node* temp = minimum(root->right);
                root->key = temp->key;
                root->right = deleteNode(root->right,
                    temp->key);
            }
        }

        if (root == NULL)
            return root;

        // balance the tree
        root->height = 1 + max(height(root->left),
            height(root->right));
        int balanceFactor = getBalance(root);
        if (balanceFactor > 1) {
            if (getBalance(root->left) >= 0) {
                return rightRotate(root);
            }
            else {
                root->left = leftRotate(root->left);
                return rightRotate(root);
            }
        }
        if (balanceFactor < -1) {
            if (getBalance(root->right) <= 0) {
                return leftRotate(root);
            }
            else {
                root->right = rightRotate(root->right);
                return leftRotate(root);
            }
        }
        return root;
    }

    Node* searchKey(Node* z, int key);
    Node* successor(Node* z);
    Node* minimum(Node* z);
    Node* maximum(Node* z);
    Node* predecessor(Node* z);
    void PrintPostOrder(Node* root);
    void PrintInOrder(Node* root);
    void PrintDepth(Node* root);
    void PrintPreOrder(Node* root);
    void print(int number);
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
void BinaryTree::PrintInOrder(Node* root) {//Симметричный обход
    if (root) {
        PrintInOrder(root->left);
        std::cout << "%d " << root->key;
        PrintInOrder(root->right);
    }
}
void BinaryTree::PrintPostOrder(Node* root) { // Обратный обход
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
    const int N = 100000;
    f.open("test.txt");
    BinaryTree T;
    int g;
    auto begin = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    for (int i = 0; i < N; i++)
    {

        f >> g;
        T.root=T.Insert(T.root, g);
    }
  //std:: cout<<T.tree_height(T.root);
   //Node* d = new Node(45158);
   T.Insert(T.root,45158);
    std::fstream s;
    s.open("Delete.txt", std::ios::app);
     //s<< T.tree_height(T.root)<<std::endl;
    begin = std::chrono::steady_clock::now();
    T.deleteNode(T.root, 45158);
    end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << ' ';
    s << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << std::endl;
    //T.delete_tree(T.root);
    f.close();
    return;
}