#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct Treenode
{
    char data[20];
    struct Treenode *leftChild;
    struct Treenode *rightChild;
    struct Treenode *next;
    struct Treenode *mother;

} Treenode;

Treenode *Root = NULL;

Treenode *createNode(char new_data[])
{
    Treenode *new_node = (Treenode *)malloc(sizeof(Treenode));
    bool check_operrand = false;
    char operand[] = "+-*/^";
    for (int i = 0; i < strlen(operand); i++) // loop for check num
        if (new_data[0] == operand[i])
        {
            check_operrand = true;
            break;
        }

    if (check_operrand)
    {
        new_node->data[0] = new_data[0];
        new_node->data[1] = '\0'; // set end char array
    }
    else
    {
        strcpy(new_node->data, new_data);
    }
    new_node->leftChild = NULL; // set all child node is null
    new_node->rightChild = NULL;

    return new_node;
}

// stack
void push(Treenode *node_add)
{
    if (Root == NULL)
        Root = node_add;
    else
    {
        node_add->next = Root;
        Root = node_add;
    }
}

Treenode *pop()
{
    if (Root == NULL)
    {
        printf("Stack is empty\n");
        return 0;
    }
    Treenode *re_node = Root;
    Root = Root->next;
    return re_node;
}

// tree
Treenode *pushtree(Treenode *node_lef, Treenode *node_right, Treenode *mother)
{
    mother->leftChild = node_lef;
    node_lef->mother = mother; // set mother
    node_right->mother = mother;
    mother->rightChild = node_right;
    return mother;
}

void preinorder(Treenode *node_print) // Postfix
{
    if (node_print != NULL)
    {
        bool check_operrand = false;
        char operand[] = "+-*/^";
        for (int i = 0; i < strlen(operand); i++) // loop for check num
            if (node_print->data[0] == operand[i])
            {
                check_operrand = true;
                break;
            }

        if (check_operrand)
        {
            printf("(");
            preinorder(node_print->leftChild);
            printf("%s", node_print->data);
            preinorder(node_print->rightChild);
            printf(")");
        }
        else
            printf("%s", node_print->data);
    }
}

bool isleft(Treenode *node_check)
{
    return (node_check->leftChild == NULL && node_check->rightChild == NULL);
}

int sumnode(Treenode *node_sum)
{
    if (node_sum == NULL)
        return 0;

    if (node_sum->leftChild == NULL && node_sum->rightChild == NULL)
    {
        return atoi(node_sum->data);
    }
    int leftValue = sumnode(node_sum->rightChild);
    int rightValue = sumnode(node_sum->leftChild);

    if (node_sum->data[0] == '+')
        return leftValue + rightValue;
    if (node_sum->data[0] == '-')
        return leftValue - rightValue;
    if (node_sum->data[0] == '*')
        return leftValue * rightValue;
    if (node_sum->data[0] == '/')
        return leftValue / rightValue;

    return 0;
}

// num node
int numNode(Treenode *node_num)
{
    if (node_num == NULL)
        return 0;
    return 1 + numNode(node_num->leftChild) + numNode(node_num->leftChild);
}
// call function
/// cut befor finished
int call_numNode()
{
    return numNode(Root);
}

void callopera()
{
    preinorder(Root);
}
int call_sumnode()
{
    return sumnode(Root);
}