#include <stdio.h>
#include <stdlib.h>
#define Size 7
// Declare structure of Linked List
struct node
{
    int data;
    struct node *next;
};
// array of pointer
struct node *hash_table[Size];
void insertChain(int value)
{

    struct node *new_node;
    new_node = (struct node *)malloc(sizeof(struct node));
    // struct node *ptr = hash_table[value % 7]; // add head to travel
    new_node->data = value;
    new_node->next = hash_table[value % 7];
    hash_table[value % 7] = new_node;
}

void printChain()
{
    for (int i = 0; i < 7; i++)
    {
        struct node *ptr = hash_table[i];
        printf("chain[%d]-->", i);
        while (ptr != NULL)
        {
            printf("%d-->", ptr->data);
            ptr = ptr->next;
        }
        printf("NULL\n");
    }
}
int main()
{
    int i;
    for (i = 0; i < Size; i++) // initialize a chained hash table
        hash_table[i] = NULL;
    insertChain(15);
    insertChain(22);
    insertChain(95);
    insertChain(56);
    insertChain(12);
    insertChain(27);
    insertChain(63);
    printChain();
    return 0;
}
