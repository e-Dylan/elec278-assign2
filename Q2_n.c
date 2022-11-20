#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *left;
    struct node *right;
};

void currentLevel(struct node *root, int level);
int height(struct node *node);
struct node *newNode(int data);
struct node *merge(struct node *root1, int root2);

struct node *newNode(int data)
{

    struct node *node = (struct node *)malloc(sizeof(struct node));

    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return node;
}

struct node *buildTree(int values[], int start, int end)
{

    struct node *root = NULL;

    if (values[start] == 0)
    {
        return 0;
    }

    if (start < end)
    {

        root = newNode(values[start]);
        root->left = buildTree(values, 2 * start + 1, end);
        root->right = buildTree(values, 2 * start + 2, end);
    }

    return root;
}

void breadthTraversal(struct node *root)
{

    int h = height(root);
    int i;
    for (i = 1; i <= h; i++)
    {
        currentLevel(root, i);
    }
}

void currentLevel(struct node *root, int level)
{

    if (root == NULL)
    {
        return;
    }
    if (level == 1)
    {
        printf("%d ", root->data);
    }
    if (level > 1)
    {
        currentLevel(root->left, level - 1);
        currentLevel(root->right, level - 1);
    }
}

int height(struct node *node)
{

    if (node == NULL)
    {
        return 0;
    }
    else
    {

        int lefth = height(node->left);
        int righth = height(node->right);

        if (lefth > righth)
            return (lefth + 1);
        else
            return (righth + 1);
    }
}

void postorder(struct node *root1, struct node *root2)
{

    if (root2 == NULL)
    {
        return;
    }

    merge(root1, root2->data);
    postorder(root1, root2->left);
    postorder(root1, root2->right);
}

struct node *merge(struct node *root1, int root2)
{

    if (root1 == NULL)
    {
        return newNode(root2);
    }
    if (root2 <= root1->data)
    {
        root1->left = merge(root1->left, root2);
    }
    if (root2 > root1->data)
    {
        root1->right = merge(root1->right, root2);
    }

    return root1;
}

struct node *sort(struct node *root1)
{

    struct node *temp = NULL;
    temp = root1;
    temp = temp->left;

    struct node *root2 = temp->left;

    root2->right->right = newNode(2);

    root1->left = NULL;
    root1->left = root2;

    return root1;
}

int main()
{

    int tree1[] = {3, 2, 5, 1};
    int tree2[] = {4, 1, 7, 0, 2, 0, 9};

    int len1 = sizeof(tree1) / sizeof(tree1[0]);
    int len2 = sizeof(tree2) / sizeof(tree2[0]);

    struct node *root1 = buildTree(tree1, 0, len1);
    struct node *root2 = buildTree(tree2, 0, len2);

    printf("Merged and sorted binary tree is \n");
    postorder(root1, root2);
    sort(root1);
    breadthTraversal(root1);

    return 0;
}