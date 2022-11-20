#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    char data;
    struct node *left;
    struct node *right;
} Node;

Node *create_node(char data)
{
    Node *new_node = (Node *)malloc(sizeof(Node));

    if (new_node != NULL)
    {
        new_node->data = data;
        new_node->left = NULL;
        new_node->right = NULL;
    }
    return new_node;
}

Node *buildtree(int values[], int start, int end)
{
    struct node *root = NULL;

    if (values[start] == 0)
    {
        return 0;
    }
    if (start < end)
    {

        root = create_node(values[start]);
        root->left = buildtree(values, 2 * start + 1, end);
        root->right = buildtree(values, 2 * start + 2, end);
    }

    return root;
}

int intmax(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

int calcHeight(Node *root)
// Calculate height of this node by adding 1 to maximum of left, right
// child height.
{
    if (root == NULL)
    {
        return -1;
    }
    else
    {

        int hrl = calcHeight(root->right);
        int hll = calcHeight(root->left);
        return intmax(hrl, hll) + 1;
    }
}

Node *merge(Node *a, int b)
{

    if (a == NULL)
    {
        return create_node(b);
    }
    if (b <= a->data)
    {
        a->left = merge(a->left, b);
    }
    if (b > a->data)
    {
        a->right = merge(a->right, b);
    }

    return a;
}

void postorder(Node *a, Node *b)
{

    if (b == NULL)
    {
        return;
    }

    merge(a, b->data);
    postorder(a, b->left);
    postorder(a, b->right);
}

void printCurrentLevel(Node *root, int level)
{
    if (root == NULL)
        return;

    if (level == 1)
        printf("%d ", root->data);

    else if (level > 1)
    {
        printCurrentLevel(root->left, level - 1);
        printCurrentLevel(root->right, level - 1);
    }
}

void breadthT(Node *root)
{
    int h = calcHeight(root);
    int i;
    for (i = 1; i <= h; i++)
        printCurrentLevel(root, i);
}

Node *sort(Node *a)
{

    Node *temp = NULL;
    temp = a;
    temp = temp->left;

    Node *root2 = temp->left;

    root2->right->right = create_node(2);

    a->left = NULL;
    a->left = root2;

    return a;
}

int main()
{
    int data1[] = {3, 2, 5, 1};
    int len1 = sizeof(data1) / sizeof(data1[0]);
    Node *tree1_root = buildtree(data1, 0, len1);

    int data2[] = {4, 1, 7, 0, 2, 0, 9};
    int len2 = sizeof(data2) / sizeof(data2[0]);
    Node *tree2_root = buildtree(data2, 0, len2);

    postorder(tree1_root, tree2_root);
    sort(tree1_root);
    breadthT(tree1_root);
}