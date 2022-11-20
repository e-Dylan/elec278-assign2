#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    int height;
    struct node *left;
    struct node *right;
} Node;

Node *newNode(int data)
{

    Node *node = (Node *)malloc(sizeof(Node));

    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    return (node);
}

int intmax(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

Node *rightRotate(Node *root)
{

    Node *x = root->left;
    Node *y = x->right;

    x->right = root;
    root->left = y;

    root->height = intmax(height(root->left), height(root->right)) + 1;
    x->height = intmax(height(x->left), height(x->right)) + 1;

    return x;
}

Node *leftRotate(Node *root)
{

    Node *x = root->right;
    Node *y = x->left;

    x->left = root;
    root->right = y;

    root->height = intmax(height(root->left), height(root->right)) + 1;
    x->height = intmax(height(x->left), height(x->right)) + 1;

    return x;
}

int height(Node *tree)
{

    if (tree == NULL)
    {
        return 0;
    }

    return tree->height;
}

int getBalance(Node *t)
{

    if (t == NULL)
    {
        return 0;
    }

    return height(t->left) - height(t->right);
}

void preOrder(Node *root)
{

    if (root != NULL)
    {
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

Node *insert(Node *node, int data)
{

    if (node == NULL)
    {
        return (newNode(data));
    }

    if (data < node->data)
    {
        node->left = insert(node->left, data);
    }
    else if (data > node->data)
    {
        node->right = insert(node->right, data);
    }
    else
    {
        return node;
    }

    node->height = 1 + intmax(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && data < node->left->data)
    {
        return rightRotate(node);
    }
    if (balance < -1 && data > node->right->data)
    {
        return leftRotate(node);
    }
    if (balance > 1 && data > node->left->data)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && data < node->right->data)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

int main()
{

    int values[] = {12, 8, 18, 5, 9, 17, 4, 2};
    Node *root = NULL;

    for (int i = 0; i < 8; i++)
    {
        root = insert(root, values[i]);
    }

    printf("Balanced preorder traversal of the binary tree is: \n");
    preOrder(root);

    return 0;
}