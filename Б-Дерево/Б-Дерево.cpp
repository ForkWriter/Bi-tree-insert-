#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

const int t = 3;

struct BNode 
{
    int keys[2 * t];
    BNode* children[2 * t + 1];
    BNode* parent;
    int count;
    int countSons;
    bool leaf;
};

class BiTree
{
private:
    BNode *root;
    BNode *partition(BNode* node);
    void insert_key(int key, BNode* node);
    void sort(BNode* node);
    void vivod(int n, BNode* node);
    void tabl(int n);
public:
    BiTree();
    void insert(int key);
    void vivod();
};

BiTree::BiTree()
{
    root = nullptr;
}

void BiTree::insert_key(int key, BNode* node) 
{
    node->keys[node->count] = key;
    node->count ++;
    sort(node);
}

void BiTree::sort(BNode* node) 
{
    for (int i = 0; i <= node->count-1; i++)
    {
        int num = i;
        for (int j = i + 1; j <= node->count-1; j++)
        {
            if (node->keys[i] > node->keys[j])
                num = j;
        }
int buff = node->keys[i];
        node->keys[i] = node->keys[num];
        node->keys[num] = buff;
    }
}

BNode *BiTree::partition(BNode* node)
{
    if (node->count < (2 * t - 1)) 
        return 0;
    BNode *Lch = new BNode;
    BNode *Rch = new BNode;

    for (int i = 0; i <= t - 2; i++) 
        Lch->keys[i] = node->keys[i];
    Lch->count = t - 1;
    if (node->countSons != 0)
    {
        for (int i = 0; i <= t - 1; i++)
        {
            Lch->children[i] = node->children[i];
            Lch->children[i]->parent = Lch;
        }
        for (int i = t; i <= (2 * t); i++) 
            Lch->children[i] = nullptr;
        Lch->leaf = false;
        Lch->countSons = t - 1;
    }
    else 
    {
        Lch->leaf = true;
        Lch->countSons = 0;
        for (int i = 0; i <= (2 * t); i++) 
            Lch->children[i] = nullptr;
    }

    for (int i = 0; i <= (t - 1); i++) 
        Rch->keys[i] = node->keys[i + t];
    Rch->count = t;
    if (node->countSons != 0) 
    {
        for (int i = 0; i <= (t); i++) 
        {
            Rch->children[i] = node->children[i + t];
            Rch->children[i]->parent = Rch;
        }
        for (int i = t + 1; i <= (2 * t); i++) Rch->children[i] = nullptr;
        Rch->leaf = false;
        Rch->countSons = t;
    }
    else 
    {
        Rch->leaf = true;
        Rch->countSons = 0;
        for (int i = 0; i <= (2 * t); i++) 
            Rch->children[i] = nullptr;
    }

    if (node->parent == nullptr) 
    {
        node->keys[0] = node->keys[t - 1];
        for (int j = 1; j <= (2 * t - 1); j++) 
            node->keys[j] = 0;
        node->children[0] = Lch;
        node->children[1] = Rch;
        for (int i = 2; i <= (2 * t); i++) 
            node->children[i] = nullptr;
        node->parent = nullptr;
        node->leaf = false;
        node->count = 1;
        node->countSons = 2;
        Lch->parent = node;
        Rch->parent = node;
    }
    else 
    {
        insert_key(node->keys[t - 1], node->parent);
        for (int i = 0; i <= (2 * t); i++) 
        {
            if (node->parent->children[i] == node) 
                node->parent->children[i] = nullptr;
        }
        for (int i = 0; i <= (2 * t); i++) 
        {
            if (node->parent->children[i] == nullptr) 
            {
                for (int j = (2 * t); j > (i + 1); j--) 
                    node->parent->children[j] = node->parent->children[j - 1];
                node->parent->children[i + 1] = Rch;
                node->parent->children[i] = Lch;
                break;
            }
        }
        Lch->parent = node->parent;
        Rch->parent = node->parent;
        node->parent->leaf = false;
        BNode* par = node->parent;
        delete node;
        return par;
    }
}

void BiTree::insert(int key)
{
    if (root == nullptr)
    {
        BNode* node = new BNode();
        node->keys[0] = key;
        node->count++;
        node->countSons = 0;
        for (int i = 0; i <= (2 * t); i++) 
            node->children[i] = nullptr;
        node->leaf = true;
        node->parent = nullptr;
        root = node;
    }
    else
    {
        BNode *node = root;
        while (!node->leaf)
        {
            for (int i = 0; i < node->count; i++)
            {
                if (key <= node->keys[i])
                {
                    node = node->children[i];
                    break;
                }
                if (key > node->keys[i] && i==node->count-1)
                {
                    node = node->children[node->count];
                    break;
                }
            }
        }
        insert_key(key, node);
        while (node->count == 2 * t)
        {
            if (node == root) 
            {
                partition(node);
                break;
            }
            else 
            {
                node=partition(node);
            }
        }
    }
}

void BiTree::tabl(int n)
{
    for (int i = 0; i < n; i++)
        cout << "\t";
}

void BiTree::vivod(int n,BNode* node)
{
    tabl(n);
    cout << "lvl "<<n+1<<": ";
    for (int i = 0; i <= node->count - 1; i++)
    {
        cout << node->keys[i] << " ";
    }
    cout << endl;
    for (int i = 0; i <= node->count; i++)
    {
        if(!node->leaf)
            vivod(n + 1, node->children[i]);
    }
}



void BiTree::vivod()
{
    system("cls");
    vivod(0, root);
}

int main()
{
    srand(time(0));
    BiTree b;
    int j;
    //Добавление 100000 рандомных элементов
    for (int i = 0; i < 20; i++)
        b.insert(rand() % 100 + 1);


    //Добавление 100000 элементов от 0 до 100 с плотностью вероятности p = x * 0.02
    /*double raspr[101]{ 0 };
    for (int i = 1; i < 101; i++)
    {
        raspr[i] = (raspr[i - 1] + i * 0.02);
    }
    for (int i = 1; i < 101; i++)
    {
        raspr[i] = 100 * raspr[i];
    }
    for (int i = 0; i < 100000; i++)
    {
        int Number = rand() % 10101;
        for (int j = 0; j < 101; j++)
        {
            if (Number <= raspr[j])
            {
                b.insert(j);
                break;
            }
        }
    }*/
    b.vivod();
}