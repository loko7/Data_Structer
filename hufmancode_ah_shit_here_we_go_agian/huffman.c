#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define size_c 256
char code_text[size_c][20];
char code_character[size_c];
int index_text = 0, index_front = 0;
typedef struct MinHeapNode
{
    char character;
    int frequency;
    struct MinHeapNode *left;
    struct MinHeapNode *right;
} MinHeapNode;

typedef struct
{
    MinHeapNode **array;
    int size;
    int capacity;
} MinHeap;

MinHeap *createMinHeap(int capacity)
{
    MinHeap *minHeap = (MinHeap *)malloc(sizeof(MinHeap));
    minHeap->capacity = capacity;
    minHeap->size = 0;
    minHeap->array = (MinHeapNode **)malloc(capacity * sizeof(MinHeapNode *));
    return minHeap;
}

MinHeapNode *createNode(char character, int frequency)
{
    MinHeapNode *node = (MinHeapNode *)malloc(sizeof(MinHeapNode));
    node->character = character;
    node->frequency = frequency;
    node->left = node->right = NULL;
    return node;
}

void swap(MinHeapNode **a, MinHeapNode **b)
{
    MinHeapNode *temp = *a;
    *a = *b;
    *b = temp;
}

void insertMinHeap(MinHeap *minHeap, MinHeapNode *node)
{

    minHeap->array[minHeap->size] = node;
    int i = minHeap->size;
    minHeap->size++;

    while (i && (minHeap->array[i]->frequency < minHeap->array[(i - 1) / 2]->frequency ||
                 (minHeap->array[i]->frequency == minHeap->array[(i - 1) / 2]->frequency &&
                  minHeap->array[i]->character < minHeap->array[(i - 1) / 2]->character)))
    {
        swap(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

MinHeapNode *extractMin(MinHeap *minHeap)
{
    MinHeapNode *temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->size--;

    int i = 0;
    while (i < minHeap->size / 2)
    {
        int smallest = i;
        if (2 * i + 1 < minHeap->size && minHeap->array[2 * i + 1]->frequency < minHeap->array[smallest]->frequency)
        {
            smallest = 2 * i + 1;
        }
        if (2 * i + 2 < minHeap->size && minHeap->array[2 * i + 2]->frequency < minHeap->array[smallest]->frequency)
        {
            smallest = 2 * i + 2;
        }
        if (smallest == i)
            break;
        swap(&minHeap->array[i], &minHeap->array[smallest]);
        i = smallest;
    }
    return temp;
}

MinHeapNode *buildHuffmanTree(MinHeap *minHeap)
{
    while (minHeap->size > 1)
    {
        MinHeapNode *left = extractMin(minHeap);
        MinHeapNode *right = extractMin(minHeap);

        MinHeapNode *newNode = createNode('$', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;

        insertMinHeap(minHeap, newNode);
    }
    return extractMin(minHeap);
}

void printCodes(MinHeapNode *root, int *arr, int top)
{
    if (root->left)
    {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
    if (root->right)
    {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
    if (!root->left && !root->right)
    {
        printf("'%c': ", root->character);
        code_character[index_front] = root->character;
        // index_text[top][index_text++] = root->character;
        for (int i = 0; i < top; i++)
        {
            //   index_text = 0;
            // code_text[index_front] = arr[i];
            char str[20];
            sprintf(str, "%d", arr[i]);
            strcat(code_text[index_front], str);
            printf("%d", arr[i]);
        }
        index_front++;
        printf("\n");
    }
}

void displayMinHeap(MinHeap *minHeap)
{
    if (minHeap->size == 0)
    {
        printf("MinHeap is empty.\n");
        return;
    }

    printf("MinHeap contents:\n");
    for (int i = 0; i < minHeap->size; i++)
    {
        printf("'%c': %d ", minHeap->array[i]->character, minHeap->array[i]->frequency);
    }
}

// Build min-heap
for (int i = n / 2 - 1; i >= 0; i--)
    heapify(arr, n, i);

// One by one extract elements from the heap
for (int i = n - 1; i > 0; i--)
{
    // Move the current smallest element (root) to the end
    swap(&arr[0], &arr[i]);

    // Call heapify on the reduced heap
    heapify(arr, i, 0);
}
}
int main()
{
    char text[1000];
    int frequency[size_c] = {0};
    int num_char = 0;

    // Read input from user
    printf("Enter sentence: ");
    scanf("%[^\n]", text);

    for (int i = 0; text[i] != '\0'; i++)
    {
        frequency[(unsigned char)text[i]]++;
        if (frequency[(unsigned char)text[i]] == 1)
            num_char++;
    }

    printf("Frequency table of %d characters:\n", num_char);
    MinHeap *minHeap = createMinHeap(size_c);
    for (int i = 0; i < size_c; i++)
    {
        if (frequency[i] > 0)
        {
            printf("'%c': %d ", i, frequency[i]);
            insertMinHeap(minHeap, createNode(i, frequency[i]));
        }
    }

    printf("\n2. A Min-Heap (the less frequency, the higher priority)\n");
    displayMinHeap(minHeap);

    MinHeapNode *root = buildHuffmanTree(minHeap);

    int arr[size_c], top = 0;
    printf("\n3. Huffman code for each character:\n");

    printCodes(root, arr, top);
    printf("4. Encoded sentence\n");

    for (int i = 0; i < strlen(text); i++)
    {
        for (int j = 0; j < size_c; j++)
        {
            if (text[i] == code_character[j])
                printf("%s ", code_text[j]);
        }
    }

    return 0;
}
