#include <stdio.h>
#include <stdlib.h>

struct node
{
    char data;
    struct node *left;
    struct node *right;
};

struct node *newNode(char data)
{

    struct node *node = (struct node *)malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return node;
}

struct node *buildTree(char values[], int start, int end)
{

    struct node *root = NULL;

    if (values[start] == 'S')
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

void printPostorder(struct node *node)
{

    if (node == NULL)
    {
        return;
    }

    printPostorder(node->left);
    printPostorder(node->right);
    printf("%c ", node->data);
}

int main()
{

    char values[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'S', 'S', 'S', 'K'};

    int len = sizeof(values) / sizeof(values[0]);

    struct node *root = buildTree(values, 0, len);

    printf("Postorder traversal of binary tree is \n");
    printPostorder(root);

    return 0;
}