#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

typedef struct Symbol {
    char name[50];
    char type[20];
    char scope[20];
    int address;
    struct Symbol* next;
} Symbol;

Symbol* table[SIZE];
int count = 0;

int hash(char *key) {
    int sum = 0;
    for(int i=0; key[i]; i++)
        sum += key[i];
    return sum % SIZE;
}

void insertSymbol() {
    Symbol *newSym = (Symbol*)malloc(sizeof(Symbol));

    printf("Identifier Name: ");
    scanf("%s", newSym->name);

    printf("Data Type: ");
    scanf("%s", newSym->type);

    printf("Scope: ");
    scanf("%s", newSym->scope);

    printf("Memory Address: ");
    scanf("%d", &newSym->address);

    int index = hash(newSym->name);

    newSym->next = table[index];
    table[index] = newSym;

    count++;

    printf("Symbol inserted at index %d\n", index);
}

void searchSymbol() {
    char key[50];
    printf("Enter identifier to search: ");
    scanf("%s", key);

    int index = hash(key);
    Symbol *temp = table[index];

    while(temp) {
        if(strcmp(temp->name, key) == 0) {
            printf("Found\n");
            printf("%s\n", temp->type);
            printf("%s\n", temp->scope);
            printf("%d\n", temp->address);
            return;
        }
        temp = temp->next;
    }

    printf("Symbol not found\n");
}

void deleteSymbol() {
    char key[50];
    printf("Enter identifier to delete: ");
    scanf("%s", key);

    int index = hash(key);

    Symbol *temp = table[index];
    Symbol *prev = NULL;

    while(temp) {
        if(strcmp(temp->name, key) == 0) {
            if(prev == NULL)
                table[index] = temp->next;
            else
                prev->next = temp->next;

            free(temp);
            count--;
            printf("Symbol deleted\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    printf("Symbol not found\n");
}

void displayTable() {
    printf("\nSymbol Table:\n");

    for(int i=0;i<SIZE;i++) {
        printf("Bucket %d: ", i);
        Symbol *temp = table[i];

        while(temp) {
            printf("[%s, %s, %s, %d] -> ",
                temp->name,
                temp->type,
                temp->scope,
                temp->address);
            temp = temp->next;
        }

        printf("NULL\n");
    }
}

void loadFactor() {
    float lf = (float)count / SIZE;
    printf("Load Factor: %.2f\n", lf);

    if(lf > 0.75)
        printf("Rehash recommended (Load factor exceeded)\n");
}

int main() {

    int choice;

    for(int i=0;i<SIZE;i++)
        table[i] = NULL;

    while(1) {
        printf("\n1.Insert Symbol");
        printf("\n2.Search Symbol");
        printf("\n3.Delete Symbol");
        printf("\n4.Display Table");
        printf("\n5.Check Load Factor");
        printf("\n6.Exit");
        printf("\nEnter choice: ");

        scanf("%d",&choice);

        switch(choice) {

            case 1:
                insertSymbol();
                break;

            case 2:
                searchSymbol();
                break;

            case 3:
                deleteSymbol();
                break;

            case 4:
                displayTable();
                break;

            case 5:
                loadFactor();
                break;

            case 6:
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }
}
