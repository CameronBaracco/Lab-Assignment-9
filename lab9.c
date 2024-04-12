#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
    int id;
    char name;
    int order;
};

// Node for chaining
struct Node
{
    struct RecordType data;
    struct Node* next;
};

// HashType
struct HashType
{
    struct Node* head;
    // You can add more members as needed for your implementation
};

// Hash table size
#define HASH_SIZE 10

// Hash function to determine the index for a given key
int hash(int x)
{
    return x % HASH_SIZE;
}

// Function to insert a record into the hash table
void insertRecord(struct HashType hashTable[], struct RecordType record)
{
    int index = hash(record.id);

    // Create a new node
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = record;
    newNode->next = NULL;

    // If the index is empty
    if (hashTable[index].head == NULL)
    {
        hashTable[index].head = newNode;
    }
    else
    {
        // Collision: Add to the beginning of the list
        newNode->next = hashTable[index].head;
        hashTable[index].head = newNode;
    }
}

// Function to display records in the hash structure
void displayRecordsInHash(struct HashType hashTable[], int hashSz)
{
    printf("\nHash Table:\n");
    for (int i = 0; i < hashSz; ++i)
    {
        printf("Index %d -> ", i);
        struct Node* current = hashTable[i].head;
        while (current != NULL)
        {
            printf("%d %c %d -> ", current->data.id, current->data.name, current->data.order);
            current = current->next;
        }
        printf("NULL\n");
    }
}

// Function to parse input file to an array of records
int parseData(char* inputFileName, struct RecordType** ppData)
{
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType* pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*)malloc(sizeof(struct RecordType) * dataSz);
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(EXIT_FAILURE);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
        }

        fclose(inFile);
    }

    return dataSz;
}

// Function to print records
void printRecords(struct RecordType pData[], int dataSz)
{
    printf("\nRecords:\n");
    for (int i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n");
}

int main(void)
{
    struct RecordType* pRecords;
    int recordSz = 0;

    // Parse data from file
    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    // Create hash table
    struct HashType hashTable[HASH_SIZE] = { 0 };

    // Insert records into the hash table
    for (int i = 0; i < recordSz; ++i)
    {
        insertRecord(hashTable, pRecords[i]);
    }

    // Display records in the hash table
    displayRecordsInHash(hashTable, HASH_SIZE);

    return 0;
}