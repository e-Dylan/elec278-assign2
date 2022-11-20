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

Node *buildtree(char values[], int start, int end)
{
    struct node *root = NULL;

    if (values[start] == 'S')
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

void printPostorder(Node *root)
{

    if (root == NULL)
    {
        return;
    }

    printPostorder(root->left);
    printPostorder(root->right);
    printf("%c ", root->data);
}

int main()
{

    char values[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'S', 'S', 'S', 'K'};

    int len = sizeof(values) / sizeof(values[0]);

    struct node *root = buildtree(values, 0, len);

    printf("Postorder traversal:\n");
    printPostorder(root);

    return 0;
}