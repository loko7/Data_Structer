#include <stdio.h>

typedef struct
{
    char alphabet;
    int frequency;
} node;

int main()
{
    node str[50];
    str[1].alphabet = 'A';           // Example initialization
    printf("%c\n", str[1].alphabet); // Access and print alphabet
    printf("Try programiz.pro\n");

    return 0;
}
